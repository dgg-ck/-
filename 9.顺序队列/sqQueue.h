#pragma once
#include<iostream>

#define BUFF_SIZE 10

//顺序队列的类
class sqQueue
{
public:
	int* pBase;
	int* pFront;
	int* pRear;
	int iSize;

	sqQueue();
	~sqQueue();

	//入队
	void EnQueue(int data);
	
	//出队
	int DeQueue();

	//队列信息输出
	void ShowQueue();
};