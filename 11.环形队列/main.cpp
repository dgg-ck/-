#include"CycleQueue.h"


int main()
{
	sqQueue* pQueue = new sqQueue;

	for (int i = 0; i < 5; i++)
	{
		pQueue->EnQueue(i);
	}

	//出队
	pQueue->DeQueue();
	pQueue->DeQueue();
	pQueue->DeQueue();
	//pQueue->DeQueue();
	//pQueue->DeQueue();

	//输出队列信息
	pQueue->ShowQueue();

	return 0;
}