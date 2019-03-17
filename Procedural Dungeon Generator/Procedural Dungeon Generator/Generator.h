#pragma once
#include <iostream>
#include "BSP_Tree.h"
using namespace std;

class Generator
{
private:
	static bool isRestart;
	int m_MaxSize_x;
	int m_MaxSize_y;
private:
	void Initialize() {
		cout << "���� ���� �ʱ�ȭ ����" << endl;

		cout << "���� ���� ũ�� : ";
		cin >> m_MaxSize_x;

		cout << "���� ���� ũ�� : ";
		cin >> m_MaxSize_y;
	};

	void Run() {
		BSP_Tree::Instance()._Run(m_MaxSize_x, m_MaxSize_y);
	};

	bool ReStart()
	{
		static int input;
		cout << "���� : 0 , ����� : 1" << endl;
		cin >> input;

		return input == 0 ? false : true;
	};

public:
	Generator() {};
	~Generator() {};

	void Launcher() {
		do {
			this->Initialize();
			this->Run();
		} while (this->ReStart());
	}
};

