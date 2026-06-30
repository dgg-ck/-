#include<iostream>
//快速排序，有分治法
//第一次排序时，选一个数为基准
//经过第一次排序后，这个数会将整个数组分为比基准大的，和比基准小的。
//然后第二次排序，大的部分，和小的部分各自再选一个基准，然后进行排序
//如此类推，就会排序完成

void QuickSort(int* arr, int left, int right)
{
	//左右到头了返回
	if (left >= right)
	{
		return;
	}

	//基准值
	int pivot = arr[left];
	//临时遍历
	int iTmpLeft = left;
	int iTmpRight = right;

	//比较，比基准值大的放右边，小的放左边
	while (iTmpLeft < iTmpRight)
	{

		//因为存储了最左边的为基准值，因此先从右边开始比较
		while (iTmpLeft < iTmpRight && arr[iTmpRight] > pivot)
		{
			iTmpRight--;
		}
		//ok，如果来到了这步，可能已经找到了比基准值小的值了
		//也可能没找到，直接找完了
		if (iTmpLeft < iTmpRight && arr[iTmpRight] <= pivot)
		{
			arr[iTmpLeft] = arr[iTmpRight];
			iTmpLeft++;
		}

		//现在从左边开始比较，因为左边的坑已经被填了，现在右边有坑
		while (iTmpLeft < iTmpRight && arr[iTmpLeft] < pivot)
		{
			iTmpLeft++;
		}
		if (iTmpLeft < iTmpRight && arr[iTmpLeft] >= pivot)
		{
			arr[iTmpRight] = arr[iTmpLeft];
			iTmpRight--;
		}

	}
	//基准归位
	arr[iTmpLeft] = pivot;

	//左边排序
	QuickSort(arr, left, iTmpLeft - 1);
	//右边排序
	QuickSort(arr, iTmpLeft + 1, right);
}


int main()
{
	//乱序数组
	int arr[20] = { 5,-10,7,9,12,13,100,88,20,3,4,8,213,-2,-6,-7,2,66,11,22 };

	QuickSort(arr, 0, 19);

	for (int i = 0; i < 20; i++)
	{
		std::cout << arr[i] << " ";
	}

	return 0;
}