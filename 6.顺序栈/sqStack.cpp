#include"sqStack.h"

//构造函数
sqStack::sqStack(int capacity)
{
	//开辟容量并且初始化为0
	pBottom = new int[capacity]();
	pTop = pBottom - 1;
	iCapacity = capacity;
	//-1代表栈中无元素 空栈
	iNum = -1;
}

//析构函数
sqStack::~sqStack()
{
	delete[] pBottom;
	pTop = nullptr;
	pBottom = nullptr;
	iCapacity = 0;
	iNum = 0;
}

//出栈
int sqStack::sqStackPop()
{
	if (IsEmpty())
	{
		std::cout << "栈已空，无法出栈" << std::endl;
		return -1;
	}
	else
	{
		int iTmp = 0;
		//获取出栈值
		iTmp = *pTop;
		//栈顶指针下移
		pTop--;
		//栈数量减少
		iNum--;
		
		return iTmp;
	}
}
//入栈
void sqStack::sqStackEnter(int num)
{
	if (IsFull())
	{
		std::cout << "栈已满，无法入栈" << std::endl;
	}
	else
	{
		//栈顶指针往上走，然后入栈
		++pTop;
		*pTop = num;
		iNum++;
	}

}

void sqStack::sqStackShow()
{
	if (IsEmpty())
	{
		std::cout << "栈已空，无法输出信息" << std::endl;
	}
	else
	{
		int iTmp = iNum;
		int* pTmp = pTop;

		std::cout << "栈数据:";
		while (iTmp != -1)
		{
			std::cout << *pTmp-- << " ";
			iTmp--;
		}
	}

}