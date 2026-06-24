#include<iostream>
#include"sqStack.h"



//栈顶指针永远指向有效值的位置(除了空栈)

int main()
{
	sqStack* pstack = new sqStack(30);
	

	//删除栈
	delete pstack;
	pstack = nullptr;

	return 0;
}