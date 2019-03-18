#pragma once
#include <iostream>
#include "BSP_Tree.h"
using namespace std;

class Generator
{
private:
	static bool isRestart;
	int m_MaxSize_x;		//맵의 크기
	int m_MaxSize_y;

	int MIN_NODE_SIZE;		//자르는 구역 크기의 제한
	int MAX_NODE_SIZE;
private:
	void Initialize();

	void Run() ;
	bool ReStart();

public:
	Generator();
	~Generator();

	void Launcher();
};

