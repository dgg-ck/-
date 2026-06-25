#include"CycleQueue.h"

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


//入队,环形队列直接覆盖掉旧数据
void sqQueue::EnQueue(int data)
{
	//队列已经满了
	if (iSize == BUFF_SIZE)
	{
		//判断pRear走到末尾没用
		//我的pRear永远走到存储数据的下一个位置
		//因此有下列公式成立
		if (pRear == pBase + BUFF_SIZE)
		{
			//进来就是满了，并且要进行数据覆盖了
			//先指向最开始的地方
			pRear = pBase;
			//数据覆盖
			*pRear = data;
		}
		else
		{
			//数据覆盖
			*pRear = data;
			//pRear往前走
			pRear++;
		}
		if (pFront == pBase + BUFF_SIZE)
		{
			//往前走
			pFront = pBase;
		}
		else
		{
			//往前走
			pFront++;
		}
	}
	else
	{
		//队列未满
		*pRear = data;
		pRear++;
		iSize++;
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
		if (pFront == pBase + BUFF_SIZE)
		{
			pFront = pBase;
		}

		//保存出队的数据
		int iTmp = *pFront;
		//清空出队位置的数据
		*pFront = 0;
		//pFront指向后一个需要出队的数据
		pFront++;
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
			
			if (pTmp == pBase + BUFF_SIZE)
			{
				pTmp = pBase;

			}
			std::cout << *pTmp++ << " ";

		}
		return ;
	}


}