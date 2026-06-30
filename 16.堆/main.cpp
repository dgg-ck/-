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

	pHeap->MinHeapInsert(8);
	pHeap->MinHeapInsert(7);
	pHeap->MinHeapInsert(6);
	pHeap->MinHeapInsert(5);
	pHeap->MinHeapInsert(4);
	pHeap->MinHeapInsert(3);
	pHeap->MinHeapInsert(2);
	pHeap->MinHeapInsert(1);
	for (int i = 1; i <= pHeap->m_iHeapSize; i++)
	{
		std::cout << pHeap->m_pHeap[i] << " ";
	}
	std::cout<<std::endl;

	pHeap->MinHeapDelete();
	pHeap->MinHeapDelete();
	pHeap->MinHeapDelete();
	pHeap->MinHeapDelete();
	pHeap->MinHeapDelete();
	pHeap->MinHeapDelete();
	pHeap->MinHeapDelete();
	pHeap->MinHeapDelete();
	//pHeap->MinHeapDelete();



	for (int i = 1; i <= pHeap->m_iHeapSize; i++)
	{
		std::cout << pHeap->m_pHeap[i] << " ";
	}

	delete pHeap;

	return 0;
}