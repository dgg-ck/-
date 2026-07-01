#include<iostream>
#include<vector>


//背包总容量为8

//			重量   价值
//物品1		 2		3
//物品2		 3		4
//物品3		 4		5
//物品4		 5		6



//二维数组dp[i][j]
//[0, i]物品，任取放背包容量为j中的最大价值
//完成dp表
void Dp(std::vector<std::vector<int>>& vDp, std::vector<int>& vVal, std::vector<int>& vWeight, int iNum, int iCap)
{
	//先将第0行和第0列的Dp全部设为0

	//外层循环，物品个数
	for (int i = 1; i <= iNum; i++)
	{
		//内层循环，剩余容量遍历
		for (int j = 1; j <= iCap; j++)
		{
			//装不下
			if (j < vWeight[i])
			{
				vDp[i][j] = vDp[i - 1][j];
			}
			//装得下
			else
			{
				//如果放，剩余容量为多少
				int FreeSpace = j - vWeight[i];
				//如果放，计算放的最大价值
				int iTmpVal = vDp[i - 1][FreeSpace] + vVal[i];

				//不放的话，前一个的最大价值
				int iPreVal = vDp[i - 1][j];

				//权衡两者的最大价值放进Dp表
				vDp[i][j] = std::max(iTmpVal, iPreVal);
			}

		}

	}

}

void Show(std::vector<std::vector<int>>& vDp,  std::vector<int> vWeight, int iNum, int iCap)
{
	std::cout << "---------------------------------" << std::endl;
	//保存物品的索引
	int iTmpNum = iNum;
	int iTmpCap = iCap;

	//从最后一个开始找
	while (iTmpNum > 0)
	{
		//没放的情况
		if (vDp[iTmpNum][iTmpCap] == vDp[iTmpNum - 1][iTmpCap])
		{
			iTmpNum--;
		}
		else
		{
			std::cout << iTmpNum << " ";
			iTmpCap = iTmpCap - vWeight[iTmpNum];
			iTmpNum--;
		}
		
	}

}

// 0/1背包
int main()
{
	//物品数量
	int iNum = 4;
	//背包容量
	int iCap = 8;
	//定义dp
	std::vector<std::vector<int>> vDp(iNum + 1, std::vector<int>(iCap + 1, 0)) ;
	//物品价值(包含0号物品)
	std::vector<int> vVal = {0,2, 3, 4, 5};
	//物品重量（包含0号物品）
	std::vector<int> vWeight = {0,3, 4, 5, 6};
	

	Dp(vDp, vVal, vWeight, iNum, iCap);


	//输出DP表
	for (int i = 0; i < iNum + 1; i++)
	{
		for (int j = 0; j < iCap + 1; j++)
		{
			std::cout << vDp[i][j] << " ";
		}
		std::cout << std::endl;

	}

	Show(vDp, vWeight, iNum, iCap);

	return 0;
}