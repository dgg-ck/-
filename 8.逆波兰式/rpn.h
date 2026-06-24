#pragma once
#include"sqStack.h"

void InfixToPostfix();   // 中缀转后缀并计算
double CalculatePostfix(const char* postfix);  // 计算后缀表达式