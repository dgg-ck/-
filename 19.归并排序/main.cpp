#include<iostream>


void Merge(int* arr, int* iTmpArr, int left, int mid, int right)
{
	//左半区第一个元素下标
	int iLeftIndex = left;
	//右半区第一个元素下表
	int iRightIndex = mid + 1;

	//临时下标 用于暂存区的数组下标表示
	int iTmpIndex = left;

	//合并
	//左右半区都有元素存在
	while (iLeftIndex <= mid && iRightIndex <= right)
	{
		//左半区元素比右半区小，放进暂存区
		if (arr[iLeftIndex] < arr[iRightIndex])
		{
			//存进暂存区并且下标右移
			//左半区的索引也需要右移
			iTmpArr[iTmpIndex++] = arr[iLeftIndex++];
		}
		//右半区元素比左半区小，放进暂存区
		else
		{
			//存进暂存区并且下标右移
			//左半区的索引也需要右移
			iTmpArr[iTmpIndex++] = arr[iRightIndex++];
		}
	}

	//OK，经过上面算法处理，左半区或右半区已经有一遍是走到头了
	//有一遍半区还有数据留存再左右半区未经处理

	//右半区有残留数据
	while (iRightIndex <= right)
	{
		iTmpArr[iTmpIndex++] = arr[iRightIndex++];
	}

	//左半区有残留数据
	while (iLeftIndex <= left)
	{
		iTmpArr[iTmpIndex++] = arr[iLeftIndex++];
	}
	//处理完成

	//将暂存数组里面的数据放进去实际数组
	while (left <= right)
	{
		arr[left] = iTmpArr[left++];
	}
}

void MergeSort(int* arr, int* iTmpArr, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	//左边
	MergeSort(arr, iTmpArr, left, right / 2);
	//右边
	MergeSort(arr, iTmpArr, mid + 1, right);
	//合并
	Merge(arr, iTmpArr, left, mid, right);

}


int main()
{
	//乱序数组
	int arr[20] = { -10,5,7,9,12,13,100,88,20,3,4,8,213,-2,-6,-7,2,66,11,22 };
	//暂存空间
	int *iTmpArr = new int[20];

	MergeSort(arr, iTmpArr, 0, 19);

	for (int i = 0; i < 20; i++)
	{
		std::cout << arr[i] << " ";
	}

	delete iTmpArr;

	return 0;
}