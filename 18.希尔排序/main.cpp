#include<iostream>


void Swap(int* a, int* b)
{
	int iTmp = *a;
	*a = *b;
	*b = iTmp;
}

//希尔排序(插入排序的改良)
// 每次 gap = n / 2
//从小到大排序
void ShellSort(int* arr, int n)
{
	//算gap
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		//两个数直接的插入排序
		for (int i = gap; i < n; i++)
		{
			//记录当前分组的选中数值下标
			int iIndex = i;
			
			//插入排序比较
			while (iIndex >= gap)
			{
				//两个数相比，小数往前走
				if (arr[iIndex] < arr[iIndex - gap])
				{
					Swap(&arr[iIndex], &arr[iIndex - gap]);
				}
				else
				{
					break;
				}
				//插入排序往 当前组的数据 的前一个进行比较
				iIndex -= gap;
			}

		}

	}

}

int main()
{
	int arr[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	ShellSort(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;


	return 0;
}