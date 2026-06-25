#include "LockFreeQueue.h"   // 包含自定义的无锁队列头文件
#include <thread>            // C++11 多线程库
#include <iostream>          // 标准输入输出
#include <atomic>            // 原子操作库
#include <memory>            // std::unique_ptr

// ================================================================
// 测试目标：验证 LockFreeQueue 在多生产者、多消费者场景下，
//           是否存在数据竞争（Race Condition）。
// 测试方法：
//   1. 4 个生产者同时将 0~65535 的每个数字生产 MULTIPLIER 次（共4次）
//      即每个数字总共生产 4 * 4 = 16 次。
//   2. 4 个消费者同时从队列中取出数据，并统计每个数字出现的次数。
//   3. 最后验证每个数字的计数是否等于 16，若不是则说明有竞争或数据丢失。
// ================================================================

int main()
{
    // ---------- 1. 创建无锁队列（存储 uint16_t 类型，容量默认 1024） ----------
    LockFreeQueue<uint16_t> q;

    // ---------- 2. 全局序列号生成器（生产者共享） ----------
    // 用于生成 0~65535 的循环序号，原子变量保证多线程安全递增。
    std::atomic<uint16_t> seq;
    seq = 0;   // 初始化为 0

    // ---------- 3. 常量配置 ----------
    static const int PRODUCER_N = 4;      // 生产者线程数
    static const int CONSUMER_N = 4;      // 消费者线程数
    static const int MULTIPLIER = 4;      // 每个数字被生产的重复次数

    // ---------- 4. 生产者完成计数器 ----------
    // 用于通知消费者“所有生产者已结束”，原子变量保证多线程可见性。
    std::atomic<int> finished_producer;
    finished_producer.store(0);   // 初始为 0（尚未有生产者完成）

    // ---------- 5. 生产者线程函数（lambda 表达式） ----------
    // 每个生产者执行以下任务：
    //   - 循环 65536 * MULTIPLIER 次（即 262144 次）
    //   - 每次从 seq 中获取一个递增的序号（0~65535 循环）
    //   - 不断尝试将该序号入队，直到成功（while 循环自旋）
    //   - 循环结束后，将 finished_producer 加 1
    auto producer = [&q, &seq, &finished_producer]()
    {
        // 每个生产者需要生产的总次数：65536 * 4 = 262144
        for (int i = 0; i < 65536 * MULTIPLIER; i++)
        {
            // 原子地获取当前 seq 值，并将 seq 自增 1
            // 注意：uint16_t 溢出是明确定义的（从 65535 回绕到 0）
            uint16_t s = seq++;
            // 自旋等待，直到成功入队（无锁队列的 Enqueue 可能因队列满返回 false）
            // 这种忙等（Busy-Wait）在测试中是可以接受的，模拟高并发压力。
            while (!q.Enqueue(s));
        }
        // 该生产者已完成任务，原子地增加完成计数器
        finished_producer++;
    };

    // ---------- 6. 计数器数组（用于统计每个数字出现的次数） ----------
    // 数组大小为 65536，对应 uint16_t 的所有可能值。
    // 每个元素是 atomic<uint32_t>，因为多个消费者可能同时更新同一个数字的计数。
    std::atomic<uint32_t> counter[65536];
    // 初始化计数器全部为 0
    for (int i = 0; i < 65536; i++)
    {
        counter[i] = 0;
    }

    // ---------- 7. 消费者线程函数（lambda 表达式） ----------
    // 每个消费者执行以下任务：
    //   - 阶段1：当生产者尚未全部完成时，不断尝试出队。
    //           成功出队则增加相应数字的计数。
    //   - 阶段2：所有生产者完成后，继续尝试出队，直到队列为空。
    //   - 这样确保所有生产者生成的数据都被消费完。
    auto consumer = [&q, &counter, &finished_producer]()
    {
        uint16_t s = 0;   // 用于存储出队的数据

        // ---------- 阶段1：生产者还在运行时，不断尝试出队 ----------
        // 当 finished_producer < PRODUCER_N 时，说明还有生产者未完成
        while (finished_producer < PRODUCER_N)
        {
            // 尝试出队，如果成功则计数
            if (q.Dequeue(s))
            {
                counter[s]++;   // 原子地递增对应数字的计数
            }
            // 出队失败（队列为空）时，继续循环尝试，不阻塞
            // 这种忙等（Busy-Wait）测试高并发下的消费者吞吐量
        }

        // ---------- 阶段2：所有生产者已结束，消费队列剩余数据 ----------
        // 持续出队直到队列为空（Dequeue 返回 false）
        while (q.Dequeue(s))
        {
            counter[s]++;   // 原子地递增计数
        }
        // 此时，当前消费者已消费完所有数据，线程结束
    };

    // ---------- 8. 创建线程数组（使用 unique_ptr 管理） ----------
    std::unique_ptr<std::thread> produce_threads[PRODUCER_N];
    std::unique_ptr<std::thread> consumer_threads[CONSUMER_N];

    // ---------- 9. 先启动所有消费者线程 ----------
    // 这样做是为了让消费者先“等待”生产者生产数据，模拟真实场景
    for (int i = 0; i < CONSUMER_N; i++)
    {
        // 创建新线程并执行 consumer lambda
        consumer_threads[i].reset(new std::thread(consumer));
    }

    // ---------- 10. 再启动所有生产者线程 ----------
    for (int i = 0; i < PRODUCER_N; i++)
    {
        // 创建新线程并执行 producer lambda
        produce_threads[i].reset(new std::thread(producer));
    }

    // ---------- 11. 等待所有生产者完成 ----------
    // join() 阻塞直到对应线程结束
    for (int i = 0; i < PRODUCER_N; i++)
    {
        produce_threads[i]->join();
    }
    // 此时，所有生产者已完成，finished_producer 的值应该等于 PRODUCER_N

    // ---------- 12. 等待所有消费者完成 ----------
    // 消费者会在队列为空后自动退出
    for (int i = 0; i < CONSUMER_N; i++)
    {
        consumer_threads[i]->join();
    }
    // 此时，所有消费者已结束，队列中不应再有数据

    // ---------- 13. 验证计数结果 ----------
    bool has_race = false;   // 标记是否发现竞争条件

    // 遍历所有数字（0~65535）
    for (int i = 0; i < 65536; i++)
    {
        // 预期每个数字出现的次数 = MULTIPLIER * PRODUCER_N = 4 * 4 = 16
        // 因为每个生产者会生产 MULTIPLIER 次 0~65535 的完整序列
        if (counter[i] != MULTIPLIER * PRODUCER_N)
        {
            // 如果某个数字的计数不等于预期值，说明出现了数据竞争或丢失
            std::cout << "found race condition\t" << i << '\t' << counter[i] << std::endl;
            has_race = true;
            break;   // 发现一个错误即可退出循环
        }
    }

    // 输出最终测试结果
    if (has_race)
    {
        std::cout << "found race condition" << std::endl;
    }
    else
    {
        std::cout << "no race condition" << std::endl;
    }

    return 0;
}

// ================================================================
// 测试逻辑总结
// ================================================================
// 1. 4 个生产者总共生产 65536 * 4 * 4 = 1,048,576 个数据。
// 2. 4 个消费者并发消费这些数据，并统计每个数字的计数。
// 3. 如果无锁队列正确工作，每个数字的计数应恰好为 16。
// 4. 若有任何偏差，说明存在竞争条件（如数据覆盖、重复消费等）。
// 5. 该测试可充分验证无锁队列在多生产者多消费者下的正确性和健壮性。
// ================================================================