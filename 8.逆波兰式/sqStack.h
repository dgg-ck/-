#pragma once
#include<iostream>

const int BUFF_SIZE = 256;

class sqStack
{
private:
    char* pBottom;   // 栈底指针
    char* pTop;      // 栈顶指针（指向下一个可用位置）
    int iCapacity;   // 栈容量
    int iNum;        // 栈中元素个数

public:
    sqStack(int capacity);
    ~sqStack();

    bool IsEmpty() const { return iNum == 0; }
    bool IsFull() const { return iNum == iCapacity; }

    void sqStackEnter(char num);   // 入栈
    int sqStackPop();              // 出栈（返回 -1 表示空栈）
    char sqStackGetTop() const;    // 获取栈顶元素（不出栈）
    void sqStackShow() const;      // 显示栈内容
};