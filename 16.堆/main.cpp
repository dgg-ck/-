#include"BinaryHeap.h"

int main()
{
	BinaryHeap<int>* pHeap = new BinaryHeap<int>();

	//pHeap->MaxHeapInsert(1);
	//pHeap->MaxHeapInsert(2);
	//pHeap->MaxHeapInsert(3);
	//pHeap->MaxHeapInsert(4);
	//pHeap->MaxHeapInsert(5);
	//pHeap->MaxHeapInsert(6);
	//pHeap->MaxHeapInsert(7);
	//pHeap->MaxHeapInsert(8);

	pHeap->MinHeapInsert(23);
	pHeap->MinHeapInsert(5);
	pHeap->MinHeapInsert(67);
	pHeap->MinHeapInsert(12);
	pHeap->MinHeapInsert(89);
	pHeap->MinHeapInsert(34);
	pHeap->MinHeapInsert(55);
	pHeap->MinHeapInsert(1);
	pHeap->MinHeapInsert(99);
	pHeap->MinHeapInsert(46);
	for (int i = 1; i <= pHeap->m_iHeapSize; i++)
	{
		std::cout << pHeap->m_pHeap[i] << " ";
	}
	std::cout<<std::endl;

	//输出大小
	std::cout << "大小:" << pHeap->m_iHeapSize << std::endl;
	
	//优先队列 小根堆先出
	pHeap->MinPriorityQueue();


	

	delete pHeap;

	return 0;
}