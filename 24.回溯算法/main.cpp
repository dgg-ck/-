#include<iostream>

//走n*n的迷宫
#define N 3

//不走0行/0列
bool Mark[N + 1][N + 1];
//记录路径
int Path[N * N + 1][3];

//方向判断 dx为行， dy为列
//原地，向右，向下，向左，向上
int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = { 0, 1, 0, -1, 0};

void PrintPath(int k)
{
	for (int i = 1; i < k; i++)
	{
		std::cout << Path[i][1] << "," << Path[i][2] << std::endl;
	}
	std::cout << Path[k][1] << "," << Path[k][2] << std::endl;
}


//Mark的行， Mark的列， Path的行
void DFS(int x, int y, int k)
{
	Path[k][1] = x;
	Path[k][2] = y;

	//是否到终点
	if(x == N && y == N)
	{
		//输出路径
		PrintPath(k);
		return;
	}

	//四个方向寻找
	for (int i = 1; i <= 4; i++)
	{
		int iTmpx = x + dx[i];
		int iTmpy = y + dy[i];

		//判断方向
		if (iTmpx >= 1 && iTmpx <= N && iTmpy >= 1 && iTmpy <= N && Mark[iTmpx][iTmpy] == false)
		{
			//标记已走过
			Mark[iTmpx][iTmpy] = true;
			DFS(iTmpx, iTmpy, k + 1);
			Mark[iTmpx][iTmpy] = false;
			Path[k + 1][1] = 0;
			Path[k + 1][2] = 0;
		}

	}


}


int main()
{

	//起始位置
	Mark[1][1] = true;
	//Mark的行， Mark的列， Path的行
	DFS(1, 1, 1);

	return 0;
}