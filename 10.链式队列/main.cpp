#include"LinkQueue.h"


int main()
{

	pLinkQueue pLQueue = new LinkQueue();

	for (int i = 0; i < 5; i++)
	{
		pLQueue->EnQueue(new Node(i));
	}

	//入队
	pLQueue->EnQueue(new Node(6));
	pLQueue->EnQueue(new Node(7));
	pLQueue->EnQueue(new Node(8));
	//出队
	pLQueue->DeQueue();
	pLQueue->DeQueue();
	pLQueue->DeQueue();
	pLQueue->DeQueue();
	pLQueue->DeQueue();

	//输出
	pLQueue->ShowQueue();

	return 0;
}