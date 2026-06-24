#include<iostream>
#include<time.h> //毫秒级
#include<chrono>//纳秒级
#include<Windows.h>
#include<thread>


long long Factorial(const int& iNum)
{
	if (iNum <= 0)
	{
		return -1;
	}
	else if (iNum == 1)
	{
		return 1;
	}
	else
	{
		return iNum * Factorial(iNum - 1);
	}

}


int main()
{
	volatile long long llResult = 0;

	//clock()函数，毫秒级,精度不高
	clock_t cStart;
	clock_t cEnd;
	cStart = clock(); //计算的是CPU的滴答数，需要通过计算才能得出时间
	// 多次执行阶乘，让CPU耗时超过1ms
	for (int i = 0; i < 100000; i++)
	{
		llResult = Factorial(20);
	}
	cEnd = clock();

	double dCostTime = 1000.0 * (static_cast<long long>(cEnd) - static_cast<long long>(cStart)) 
		/ CLOCKS_PER_SEC;
	std::cout << "阶乘结果：" <<llResult << "时间:" << dCostTime << "ms" << std::endl;

	//GetTickCount()现实墙上流逝总时间计算
	DWORD dStart;
	DWORD dEnd;
	dStart = GetTickCount();
	for (int i = 0; i < 100000; i++)
	{
		llResult = Factorial(20);
	}
	dEnd = GetTickCount();
	std::cout << "阶乘结果：" << llResult << "时间:" << dEnd - dStart << "ms" << std::endl;


	//高精度时控函数QueryPerformanceCounter()——微秒级
	//window下精度天花板,也是算真实时间
	LARGE_INTEGER ltHardwareCount;
	LARGE_INTEGER ltStart;
	LARGE_INTEGER ltEnd;
	//获取硬件计数器每秒跳动多少次（频率，开机固定，只需要调用 1 次）
	QueryPerformanceFrequency(&ltHardwareCount);
	//QueryPerformanceCounter(&cnt)：获取当前硬件计数器数值
	QueryPerformanceCounter(&ltStart);
	for (int i = 0; i < 100000; i++)
	{
		llResult = Factorial(20);
	}
	QueryPerformanceCounter(&ltEnd);
	std::cout << "阶乘结果：" << llResult << "时间:" 
		<< double(1000000.0*(ltEnd.QuadPart - ltStart.QuadPart)/ltHardwareCount.QuadPart) 
		<< "us" << std::endl;

	//C++专属 chrono时间库
	//有三个算运行时间的类
	//steady_clock ,单调递增，测速首选，跨平台统一
	//system_clock（墙上日历时钟，日志打时间戳用），不保证单调，精度不同平台不一致
	//high_resolution_clock（高精度别名，不推荐使用）是steady_clock的别名，跨平台不一致，兼容差

	//steady_clock
	auto scStart = std::chrono::steady_clock::now();
	for (int i = 0; i < 100000; i++)
	{
		llResult = Factorial(20);
	}
	auto scEnd = std::chrono::steady_clock::now();

	//转时间
	auto scUs = std::chrono::duration_cast<std::chrono::nanoseconds>(scEnd - scStart);
	std::cout << "阶乘结果：" << llResult << "时间:" << scUs << std::endl;



	return 0;
}