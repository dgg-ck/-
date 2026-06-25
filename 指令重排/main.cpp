#include<iostream>


int main()
{
	//未优化前
	int iX = 1;
	int iY = 1;
	int iA = iX * 1;
	int iB = iY * 1;
	int iC = iX * 2;
	int iD = iY * 2;

	//经过编译器优化后
	int iX = 1;
	int iY = 1;
	int iA = iX * 1;
	int iC = iX * 2;
	int iB = iY * 1;
	int iD = iY * 2;
//经过编译器优化，我CPU只需要读取一次寄存器就能够将iA与iC算出来


//CPU	
	int iX = 1;
	int iY = 1;
	//原本执行代码
	int iA = iX * 1;
	int iB = iY * 1;

	//CPU乱序执行
	int iB = iY * 1;
	int iA = iX * 1;



	return 0;
}