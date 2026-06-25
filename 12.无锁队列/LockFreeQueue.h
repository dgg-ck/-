#pragma once
#include <iostream>
#include <atomic>
#include <vector>

// ================================================================
// 多生产者 / 多消费者（MPMC）无锁队列
// 基于环形数组（Ring Buffer）实现，使用 CAS 原子操作控制索引
// 模板参数：T 为元素类型，N 为队列容量（默认 1024）
// ================================================================
template<class T, size_t N = 1024>
class LockFreeQueue
{
public:
    // ------------------------------------------------------------
    // 槽位结构体：每个数组元素包含一个数据和一个“是否有效”标志
    // ------------------------------------------------------------
    struct Element
    {
        std::atomic<bool> afull;   // true 表示该槽位有有效数据，false 表示空闲
        T data;                    // 实际存储的数据（非原子，由 afull 的屏障保护）
    };

    // ------------------------------------------------------------
    // 构造函数：创建 N 个槽位的环形队列
    // 注意：vData(N) 会调用 Element 的默认构造函数，afull 默认初始化为 false
    // ------------------------------------------------------------
    LockFreeQueue() : vData(N)
    {
        aReadIndex = 0;   // 读索引初始为 0
        aWriteIndex = 0;   // 写索引初始为 0
    }

    // ------------------------------------------------------------
    // 入队（生产）
    // 尝试将一个元素放入队列尾部
    // 返回值：true 表示成功入队，false 表示队列已满（入队失败）
    // ------------------------------------------------------------
    bool Enqueue(T value)
    {
        // ---------- 局部变量（每个线程独立） ----------
        size_t sWriteIndex = 0;          // 写索引的“快照”（期望值）
        size_t index = 0;                // 计算出的数组下标
        Element* e = nullptr;            // 指向将要写入的槽位

        // ---------- CAS 自旋循环：尝试抢占一个槽位 ----------
        do
        {
            // ① 加载当前写索引（快照）
            // 使用 relaxed 是因为：这只是预读，即使读到旧值，CAS 失败后会重试
            sWriteIndex = aWriteIndex.load(std::memory_order_relaxed);

            // ② 判满：如果写索引已经领先读索引超过一个数组长度，说明队列已满
            // 注意：这里用 relaxed 读 aReadIndex，因为只是快速失败检查
            if (sWriteIndex >= aReadIndex.load(std::memory_order_relaxed) + vData.size())
            {
                return false;   // 队列已满，入队失败
            }

            // ③ 根据写索引计算在环形数组中的实际位置
            // 用 sWriteIndex（快照）而非 aWriteIndex，确保位置与 CAS 争抢的位置一致
            index = sWriteIndex % N;

            // ④ 获取该槽位的指针
            e = &vData[index];

            // ⑤ 检查该槽位是否已被占用
            // 如果 afull 已经是 true，说明该槽位已有有效数据（可能是判满失效的极端情况）
            // 这里用 relaxed，因为即使读到旧值，最终 CAS 会保证一致性
            if (e->afull.load(std::memory_order_relaxed))
            {
                return false;   // 槽位被占用，入队失败
            }

            // ⑥ 尝试原子性地将写索引从 sWriteIndex 推进到 sWriteIndex + 1
            // compare_exchange_weak 成功时：
            //   - 使用 memory_order_release：确保在此之前的所有写操作（data）不会被重排到此次写之后
            //   - 即：其他线程看到索引变化前，data 已经写入完毕
            // compare_exchange_weak 失败时：
            //   - 使用 memory_order_relaxed：因为会立即重试，不需要额外的同步开销
            //   - 失败后 sWriteIndex 会被更新为当前最新的 aWriteIndex 值
        } while (!aWriteIndex.compare_exchange_weak(sWriteIndex, sWriteIndex + 1,
            std::memory_order_release,
            std::memory_order_relaxed));

        // ---------- 抢占成功：当前线程独占该槽位 ----------

        // ⑦ 将数据移动到槽位中（移动语义，避免拷贝）
        // 注意：这是一个普通的非原子写入，不需要加锁，
        //      因为 CAS 保证只有当前线程拥有该槽位的独占权
        e->data = std::move(value);

        // ⑧ 释放标志：将 afull 置为 true，标记该槽位数据有效
        // 使用 memory_order_release：
        //   - 保证 ⑦（data 写入）一定在 ⑧（afull 置 true）之前完成
        //   - 也就是说：消费者看到 afull == true 时，data 一定已经完整可见
        e->afull.store(true, std::memory_order_release);

        return true;   // 入队成功
    }

    // ------------------------------------------------------------
    // 出队（消费）
    // 尝试从队列头部取出一个元素
    // 参数 value 为输出参数，用于返回取出的数据
    // 返回值：true 表示成功出队，false 表示队列为空（出队失败）
    // ------------------------------------------------------------
    bool Dequeue(T& value)
    {
        // ---------- 局部变量 ----------
        size_t sReadIndex = 0;           // 读索引的“快照”（期望值）
        size_t index = 0;                // 计算出的数组下标
        Element* e = nullptr;            // 指向将要读取的槽位

        // ---------- CAS 自旋循环：尝试抢占一个槽位 ----------
        do
        {
            // ① 加载当前读索引（快照）
            sReadIndex = aReadIndex.load(std::memory_order_relaxed);

            // ② 判空：如果读索引已经追上写索引，说明队列为空
            if (sReadIndex >= aWriteIndex.load(std::memory_order_relaxed))
            {
                return false;   // 队列为空，出队失败
            }

            // ③ 根据读索引计算在环形数组中的实际位置
            index = sReadIndex % N;

            // ④ 获取该槽位的指针
            e = &vData[index];

            // ⑤ 检查该槽位的数据是否有效
            // 使用 memory_order_acquire：
            //   - 确保在此之后的所有读操作（data 的读取）不会重排到此次读之前
            //   - 与生产者中的 release 配对，保证能看到完整的 data
            if (!e->afull.load(std::memory_order_acquire))
            {
                return false;   // 槽位无有效数据，出队失败
            }

            // ⑥ 尝试原子性地将读索引从 sReadIndex 推进到 sReadIndex + 1
            // compare_exchange_weak 成功时：
            //   - 使用 memory_order_release：确保索引更新完成后，后续操作可见
            // compare_exchange_weak 失败时：
            //   - 使用 memory_order_relaxed：重试即可
        } while (!aReadIndex.compare_exchange_weak(sReadIndex, sReadIndex + 1,
            std::memory_order_release,
            std::memory_order_relaxed));

        // ---------- 抢占成功：当前线程拥有该槽位的读取权 ----------

        // ⑦ 从槽位中取出数据（移动语义）
        // 此时可以安全读取，因为：
        //   - afull.load(acquire) 已经建立了与生产者的同步
        //   - CAS 保证只有当前线程抢到了该槽位的读取权
        value = std::move(e->data);

        // ⑧ 重置标志：将 afull 置为 false，标记该槽位已空闲
        // 使用 memory_order_release：
        //   - 保证槽位重置的可见性，让后续生产者能够复用该槽位
        e->afull.store(false, std::memory_order_release);

        return true;   // 出队成功
    }

private:
    // ------------------------------------------------------------
    // 成员变量
    // ------------------------------------------------------------

    std::vector<Element> vData;      // 环形队列的底层数组（容量固定为 N）

    std::atomic<size_t> aReadIndex;  // 读索引（原子变量）：
                                     //   - 单调递增，从不回绕
                                     //   - 指向下一个要读取的槽位
                                     //   - 多个消费者通过 CAS 竞争推进此索引

    std::atomic<size_t> aWriteIndex; // 写索引（原子变量）：
                                     //   - 单调递增，从不回绕
                                     //   - 指向下一个要写入的槽位
                                     //   - 多个生产者通过 CAS 竞争推进此索引
};

// ================================================================
// 内存序使用总结
// ================================================================
// | 操作                    | 内存序            | 作用                          |
// |-------------------------|-------------------|-------------------------------|
// | 读索引快照（load）      | relaxed           | 预读，CAS 失败会重试           |
// | 判满/判空（load）       | relaxed           | 快速失败检查，不要求强同步      |
// | 检查 afull（load）      | acquire           | 与 release 配对，同步数据      |
// | CAS 成功时（写索引推进） | release           | 发布新索引，使其他线程可见      |
// | CAS 失败时（重试）      | relaxed           | 无需同步，自旋重试即可          |
// | 写 data                 | 普通赋值（无屏障） | CAS 已保证独占性               |
// | 写 afull（store）       | release           | 发布数据有效信号               |
// | 读 data                 | 普通赋值（无屏障） | acquire 已建立同步             |
// | 重置 afull（store）     | release           | 释放槽位，让生产者可见          |
// ================================================================