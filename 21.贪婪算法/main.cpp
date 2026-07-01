#include<iostream>

//贪心无套路
//总是选最近最划算的

//取钱问题


int main()
{
	int iMoney = 0;
	//零钱种类
	int change[] = { 100, 50, 10, 1 };
	int iChangeNum[4] = { 0 };

	std::cout << "请输入找钱总额:" << " ";
	std::cin >> iMoney;

	//100的个数
	iChangeNum[0] = iMoney / 100;
	iMoney = iMoney - 100 * iChangeNum[0];

	//50的个数
	iChangeNum[1] = iMoney / 50;
	iMoney = iMoney - 50 * iChangeNum[1];

	//10的个数
	iChangeNum[2] = iMoney / 10;
	iMoney = iMoney - 10 * iChangeNum[2];

	//10的个数
	iChangeNum[3] = iMoney / 1;
	iMoney = iMoney - 1 * iChangeNum[3];

	std::cout << std::endl;
	std::cout << "100:" << iChangeNum[0] << std::endl;
	std::cout << "50:" << iChangeNum[1] << std::endl;
	std::cout << "10:" << iChangeNum[2] << std::endl;
	std::cout << "1:" << iChangeNum[3] << std::endl;



	return 0;
}