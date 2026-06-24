#include"sqQueue.h"

//顺序队列的析构与构造
sqQueue::sqQueue()
{
	pBase = new int[BUFF_SIZE];
	pFront = pBase;
	pRear = pFront;
	iSize = 0;
}


sqQueue::~sqQueue()
{
	delete[] pBase;
	pFront = nullptr;
	pRear = nullptr;
	iSize = 0;
}


//入队
void sqQueue::EnQueue(int data)
{
	if(iSize == BUFF_SIZE)
	{ 
		std::cout << "队满,无法入队" << std::endl;
		return;
	}
	else 
	{
		//入队
		*pRear = data;
		//后指针往前走,指向下一个有效位置
		pRear++;
		iSize++;
		return;
	}

}

//出队
int sqQueue::DeQueue()
{
	if (iSize == 0)
	{
		std::cout << "队空，无法出栈" << std::endl;
		return -1;
	}
	else
	{
		//保存出队的数据
		int iTmp = *pFront;
		*pFront = 0;
		//pFront 往 pRear 靠
		pFront++;
		//数量减小
		iSize--;
		
		return iTmp;
	}

}

void sqQueue::ShowQueue()
{
	if (iSize == 0)
	{
		std::cout << "队列为空，无法输出" << std::endl;
		return;
	}
	else
	{
		int* pTmp = pFront;
		std::cout << "队列有:" << iSize << "个" << std::endl;
		std::cout << "数据有:";
		for (int i = 0; i < iSize; i++)
		{
			std::cout << *pTmp++ << " ";

		}
		return ;
	}


}