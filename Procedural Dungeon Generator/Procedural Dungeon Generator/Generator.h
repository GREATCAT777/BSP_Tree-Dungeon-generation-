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
		cout << "던전 생성 초기화 진행" << endl;

		cout << "맵의 가로 크기 : ";
		cin >> m_MaxSize_x;

		cout << "맵의 세로 크기 : ";
		cin >> m_MaxSize_y;
	};

	void Run() {
		BSP_Tree::Instance()._Run(m_MaxSize_x, m_MaxSize_y);
	};

	bool ReStart()
	{
		static int input;
		cout << "종료 : 0 , 재시작 : 1" << endl;
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

