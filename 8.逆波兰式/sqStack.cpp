#include"sqStack.h"

// 构造函数
sqStack::sqStack(int capacity)
{
    pBottom = new char[capacity]();
    pTop = pBottom;      // 初始指向栈底
    iCapacity = capacity;
    iNum = 0;            // 0 表示空栈
}

// 析构函数
sqStack::~sqStack()
{
    delete[] pBottom;
    pTop = nullptr;
    pBottom = nullptr;
    iCapacity = 0;
    iNum = 0;
}

// 入栈
void sqStack::sqStackEnter(char num)
{
    if (IsFull())
    {
        std::cout << "栈已满，无法入栈" << std::endl;
        return;
    }
    *pTop = num;    // 先赋值
    pTop++;         // 再移动
    iNum++;
}

// 出栈
int sqStack::sqStackPop()
{
    if (IsEmpty())
    {
        std::cout << "栈已空，无法出栈" << std::endl;
        return -1;
    }
    pTop--;          // 先下移
    char ch = *pTop; // 再取值
    iNum--;
    return ch;
}

// 获取栈顶元素（不出栈）
char sqStack::sqStackGetTop() const
{
    if (IsEmpty())
        return '\0';
    return *(pTop - 1);  // pTop 指向下一个可用位置，栈顶在 pTop-1
}

// 显示栈内容（从栈顶到栈底）
void sqStack::sqStackShow() const
{
    if (IsEmpty())
    {
        std::cout << "栈已空，无法输出信息" << std::endl;
        return;
    }
    char* pTmp = pTop - 1;
    std::cout << "栈数据:";
    while (pTmp >= pBottom)
    {
        std::cout << *pTmp << " ";
        pTmp--;
    }
    std::cout << std::endl;
}