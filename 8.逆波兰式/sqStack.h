#pragma once
#include<iostream>

class sqStack
{
public:
	//Õ»¶¥Ö¸Õë
	int* pTop;
	//Õ»µ×Ö¸Õë
	int* pBottom;
	//ÈİÁ¿
	int iCapacity;
	//ÊıÁ¿
	int iNum;

	sqStack(int capacity);
	~sqStack();

	//³öÕ»
	int sqStackPop();
	//ÈëÕ»
	void sqStackEnter(int num);
	//Êä³öÕ»ÖĞÔªËØ
	void sqStackShow();

	//ÅĞ¶Ï¿ÕÕ»£¬ÂúÕ»
	//[this]()->bool {return iNum == (iCapacity - 1) ? true : false; };
	//[this]()->bool {return iNum == -1 ? true : false };
	//ÅĞ¶Ï¿ÕÕ»,ÂúÕ»,ÄÚÁª
	bool IsFull()
	{
		return iNum == (iCapacity - 1) ? true : false;
	}
	bool IsEmpty()
	{
		return iNum == -1 ? true : false;
	}

};