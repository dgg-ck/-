#include<iostream>


//插入算法
//从小到大排序
void InsertSort(int* arr, int n)
{
	int iTmp = 0;
	for (int i = 1; i < n; i++)
	{
		for (int j = i; j >= 1; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				iTmp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = iTmp;
			}
		}
	}

}

int main()
{
	int arr[7] = { 23, 4, 67, 12, 89, 34, 55 };
	
	InsertSort(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;


	return 0;
}