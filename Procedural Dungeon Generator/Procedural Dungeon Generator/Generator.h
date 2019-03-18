#pragma once
#include <iostream>
#include "BSP_Tree.h"
using namespace std;

class Generator
{
private:
	static bool isRestart;
	int m_MaxSize_x;		//���� ũ��
	int m_MaxSize_y;

	int MIN_NODE_SIZE;		//�ڸ��� ���� ũ���� ����
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

