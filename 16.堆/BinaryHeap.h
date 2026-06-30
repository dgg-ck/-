#pragma once
#include<iostream>

#define HEAPMAX 100


//堆结点
//开始索引为1
template<class T>
class BinaryHeap
{
public:
	//堆数量
	int m_iHeapSize;
	//堆指针
	T* m_pHeap;
	
	BinaryHeap() :m_iHeapSize(0)
	{
		m_pHeap = new T[HEAPMAX + 1];
	}

	~BinaryHeap()
	{
		delete[] m_pHeap;
		m_pHeap = nullptr;
	}


	//交换函数
	void Swap( T& e1,  T& e2)
	{
		//存子节点
		T mid = e2;
		//子节点和父节点交换
		e2 = e1;
		e1 = mid;
	}

	//大根堆插入
	void MaxHeapInsert(const T& e)
	{
		if (m_iHeapSize == HEAPMAX)
		{
			std::cout << "堆满了,无法插入" << std::endl;
			return;
		}

		//先存堆底
		m_pHeap[++m_iHeapSize] = e;
		//m_iHeapSize++;

		//向上调整，大就往上走
		int iTmp = m_iHeapSize;
		//找父结点进行对比
		while (iTmp / 2 >= 1 && m_pHeap[iTmp] >= m_pHeap[iTmp / 2])
		{
			Swap(m_pHeap[iTmp], m_pHeap[iTmp / 2]);
			iTmp = iTmp / 2;
		}

	}

	//小根堆插入
	void MinHeapInsert(const T& e)
	{
		if (m_iHeapSize == HEAPMAX)
		{
			std::cout << "堆满了,无法插入" << std::endl;
			return;
		}

		//先存堆底
		m_pHeap[++m_iHeapSize] = e;
		//m_iHeapSize++;

		//向上调整，小就往上走
		int iTmp = m_iHeapSize;
		//找父结点进行对比
		while (iTmp / 2 >= 1 && m_pHeap[iTmp] <= m_pHeap[iTmp / 2])
		{
			Swap(m_pHeap[iTmp], m_pHeap[iTmp / 2]);
			iTmp = iTmp / 2;
		}
	}

	
	//大根堆向下调整（将索引 i 处的元素下沉到合适位置）
	void MaxHeapDown(int i)
	{
		int iTmp = i;
		while (iTmp <= m_iHeapSize)
		{
			int MaxNumIndex = iTmp;

			// 左孩子比较
			if (2 * iTmp <= m_iHeapSize && m_pHeap[2 * iTmp] > m_pHeap[iTmp])
			{
				MaxNumIndex = 2 * iTmp;
			}
			// 右孩子比较
			if ((2 * iTmp + 1) <= m_iHeapSize && m_pHeap[2 * iTmp + 1] > m_pHeap[MaxNumIndex])
			{
				MaxNumIndex = 2 * iTmp + 1;
			}

			// 如果已经满足大根堆，退出
			if (iTmp == MaxNumIndex)
				break;

			Swap(m_pHeap[MaxNumIndex], m_pHeap[iTmp]);
			iTmp = MaxNumIndex;
		}
	}

	// 小根堆向下调整（将索引 i 处的元素下沉到合适位置）
	void MinHeapDown(int i)
	{
		int iTmp = i;
		while (iTmp <= m_iHeapSize)
		{
			int MinNumIndex = iTmp;

			// 左孩子比较
			if (2 * iTmp <= m_iHeapSize && m_pHeap[2 * iTmp] < m_pHeap[iTmp])
			{
				MinNumIndex = 2 * iTmp;
			}
			// 右孩子比较
			if ((2 * iTmp + 1) <= m_iHeapSize && m_pHeap[2 * iTmp + 1] < m_pHeap[MinNumIndex])
			{
				MinNumIndex = 2 * iTmp + 1;
			}

			if (iTmp == MinNumIndex)
				break;

			Swap(m_pHeap[MinNumIndex], m_pHeap[iTmp]);
			iTmp = MinNumIndex;
		}
	}

	//从当前数组构建大根堆
	void BuildMaxHeap()
	{
		//从最后一个非叶子节点开始，向前遍历，逐个向下调整
		for (int i = m_iHeapSize / 2; i >= 1; i--)
		{
			MaxHeapDown(i); 
		}
	}

	// 从当前数组构建小根堆
	void BuildMinHeap()
	{
		for (int i = m_iHeapSize / 2; i >= 1; i--)
		{
			MinHeapDown(i);
		}
	}

	//堆删除
	//将堆尾的值拿上去堆顶，然后向下调整
	void MaxHeapDelete()
	{
		if (m_iHeapSize == 0)
		{
			std::cout << "堆空，无法删除" << std::endl;
			return;
		}

		//直接拿堆尾的值放进堆头，相当于删除
		m_pHeap[1] = m_pHeap[m_iHeapSize--];

		//向下调整
		//根左右结点比较
		int iTmp = 1;
		while (iTmp <= m_iHeapSize)
		{
			//三者最大值的下标
			int MaxNumIndex = iTmp;

			//先根左边比较
			if (2 * iTmp <= m_iHeapSize && m_pHeap[2 * iTmp] > m_pHeap[iTmp])
			{
				MaxNumIndex = 2 * iTmp;
			}

			//再跟右边比较
			if ((2 * iTmp + 1) <= m_iHeapSize && m_pHeap[2 * iTmp + 1] > m_pHeap[MaxNumIndex])
			{
				MaxNumIndex = 2 * iTmp + 1;
			}

			//无处可走，已经是最佳位置了，终止循环
			if (iTmp == MaxNumIndex)
			{
				break;
			}

			Swap(m_pHeap[MaxNumIndex], m_pHeap[iTmp]);
			iTmp = MaxNumIndex;
		}


	}

	//堆删除
	//将堆尾的值拿上去堆顶，然后向下调整
	void MinHeapDelete()
	{
		if (m_iHeapSize == 0)
		{
			std::cout << "堆空，无法删除" << std::endl;
			return;
		}

		//直接拿堆尾的值放进堆头，相当于删除
		m_pHeap[1] = m_pHeap[m_iHeapSize--];

		//向下调整
		//根左右结点比较
		int iTmp = 1;
		while (iTmp <= m_iHeapSize)
		{
			//三者最小值的下标
			int MinNumIndex = iTmp;

			//先根左边比较
			if (2 * iTmp <= m_iHeapSize && m_pHeap[2 * iTmp] < m_pHeap[iTmp])
			{
				MinNumIndex = 2 * iTmp;
			}

			//再跟右边比较
			if ((2 * iTmp + 1) <= m_iHeapSize && m_pHeap[2 * iTmp + 1] < m_pHeap[MinNumIndex])
			{
				MinNumIndex = 2 * iTmp + 1;
			}

			//无处可走，已经是最佳位置了，终止循环
			if (iTmp == MinNumIndex)
			{
				break;
			}

			Swap(m_pHeap[MinNumIndex], m_pHeap[iTmp]);
			iTmp = MinNumIndex;
		}


	}

};