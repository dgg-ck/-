#pragma once
#include<iostream>
#include<atomic>
#include<vector>


//多读多写的无锁队列
//队列
template<class T, size_t N = 1024 >
class LockFreeQueue
{
public:

	struct Element
	{
		std::atomic<bool> afull;
		T data;
	};

	//构造函数，有固定大小的队列
	LockFreeQueue() :vData(N)
	{
		aReadIndex = 0;
		aWriteIndex = 0;
	}


	bool Enqueue(T value)
	{

		//从内存里面读值
		size_t sWriteIndex = 0;
		size_t index = 0;
		Element* e = nullptr;

		do
		{
			sWriteIndex = aWriteIndex.load(std::memory_order_relaxed);
			if (aWriteIndex >= aReadIndex.load(std::memory_order_relaxed) + vData.size())
			{
				return false;
			}
			index = sWriteIndex % N;
			e = &vData[index];
			if (e->afull.load(std::memory_order_relaxed))
			{
				return false;
			}

		} while (!aWriteIndex.compare_exchange_weak(sWriteIndex, sWriteIndex + 1, std::memory_order_release, std::memory_order_relaxed));

		e->data = std::move(value);
		e->afull.store(true, std::memory_order_release);

		return true;
	}


	bool Dequeue(T& value)
	{
		size_t sReadIndex = 0;
		size_t index = 0;
		Element* e = nullptr;
		do 
		{
			sReadIndex = aReadIndex.load(std::memory_order_relaxed);

			if (aReadIndex >= aWriteIndex.load(std::memory_order_relaxed))
			{
				return false;
			}

			index = sReadIndex % N;
			e = &vData[index];

			if (!e->afull.load(std::memory_order_relaxed))
			{
				return false;
			}

		} while (!aReadIndex.compare_exchange_weak(sReadIndex, sReadIndex + 1, std::memory_order_release, std::memory_order_relaxed));

		value = std::move(e->data);
		e->afull.store(false, std::memory_order_release);

		return true;
	}


private:
	std::vector<Element> vData;
	std::atomic<size_t> aReadIndex;
	std::atomic<size_t> aWriteIndex;
};