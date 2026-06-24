#include"rpn.h"
#include<cstring>
#include<iostream>
#include<stack>   // 用于计算后缀表达式的操作数栈

// 计算后缀表达式
double CalculatePostfix(const char* postfix)
{
    std::stack<double> numStack;  // 操作数栈

    int iLen = strlen(postfix);
    for (int i = 0; i < iLen; i++)
    {
        char ch = postfix[i];

        // 如果是数字（只支持个位数，如 3、4、5）
        if (ch >= '0' && ch <= '9')
        {
            numStack.push(ch - '0');  // 字符转数字
        }
        // 如果是操作符
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            // 弹出右操作数（先弹出的是右操作数）
            double right = numStack.top(); numStack.pop();
            double left = numStack.top();  numStack.pop();

            double result = 0;
            switch (ch)
            {
            case '+': result = left + right; break;
            case '-': result = left - right; break;
            case '*': result = left * right; break;
            case '/':
                if (right == 0)
                {
                    std::cout << "错误：除零！" << std::endl;
                    return 0;
                }
                result = left / right;
                break;
            }
            numStack.push(result);
        }
        // 忽略其他字符（如空格，但后缀表达式里没有空格）
    }

    return numStack.top();  // 栈顶就是最终结果
}

// 中缀转后缀（你的原函数，我加了调用计算）
void InfixToPostfix()
{
    // 表达式存储
    char* cExpres = new char[BUFF_SIZE];
    char* cPolishExpress = new char[BUFF_SIZE];  // 存储后缀表达式
    sqStack* pOperStack = new sqStack(BUFF_SIZE);

    std::cout << "请输入表达式:";
    std::cin.getline(cExpres, BUFF_SIZE - 1);

    int iIndex = 0;          // 后缀表达式索引
    int iStrLen = strlen(cExpres);

    for (int i = 0; i < iStrLen; i++)
    {
        char ch = cExpres[i];

        // 跳过空格（允许输入带空格的表达式）
        if (ch == ' ') continue;

        // 数字直接输出
        if (ch >= '0' && ch <= '9')
        {
            cPolishExpress[iIndex++] = ch;
        }
        // 左括号直接入栈
        else if (ch == '(')
        {
            pOperStack->sqStackEnter(ch);
        }
        // 右括号：弹出直到遇到左括号
        else if (ch == ')')
        {
            while (!pOperStack->IsEmpty())
            {
                char top = pOperStack->sqStackGetTop();
                if (top == '(')
                {
                    pOperStack->sqStackPop();  // 弹出 '(' 丢弃
                    break;
                }
                cPolishExpress[iIndex++] = pOperStack->sqStackPop();
            }
        }
        // 操作符 + - * /
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            // 弹出栈中优先级 >= 当前操作符的栈顶元素
            while (!pOperStack->IsEmpty())
            {
                char top = pOperStack->sqStackGetTop();
                if (top == '(') break;  // 遇到 '(' 停止

                // 当前是 + 或 -，弹出所有栈顶（优先级 >=）
                if ((ch == '+' || ch == '-') &&
                    (top == '+' || top == '-' || top == '*' || top == '/'))
                {
                    cPolishExpress[iIndex++] = pOperStack->sqStackPop();
                }
                // 当前是 * 或 /，只弹出 * 或 /
                else if ((ch == '*' || ch == '/') && (top == '*' || top == '/'))
                {
                    cPolishExpress[iIndex++] = pOperStack->sqStackPop();
                }
                else
                {
                    break;  // 优先级更低，停止弹出
                }
            }
            pOperStack->sqStackEnter(ch);  // 当前操作符入栈
        }
        // 其他字符忽略（如非数字非操作符）
    }

    // 弹出栈中所有剩余操作符
    while (!pOperStack->IsEmpty())
    {
        cPolishExpress[iIndex++] = pOperStack->sqStackPop();
    }
    cPolishExpress[iIndex] = '\0';  // 字符串结束符

    // 输出后缀表达式
    std::cout << "中缀表达式: " << cExpres << std::endl;
    std::cout << "后缀表达式: " << cPolishExpress << std::endl;

    //计算后缀表达式并输出结果
    double result = CalculatePostfix(cPolishExpress);
    std::cout << "计算结果: " << result << std::endl;

    // 释放内存
    delete[] cExpres;
    delete[] cPolishExpress;
    delete pOperStack;
}