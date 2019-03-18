#pragma once
#include "stdafx.h"
#include "Generator.h"

using namespace std;

Generator::Generator() {};
Generator::~Generator() {};

void Generator::Initialize() {
	cout << "던전 생성 초기화 진행" << endl;

	cout << "맵의 가로 크기 : ";
	cin >> m_MaxSize_x;

	cout << "맵의 세로 크기 : ";
	cin >> m_MaxSize_y;

	cout << "구역 분할을 제한하는 최소 크기 : ";
	cin >> MIN_NODE_SIZE;

	cout << "구역 분할을 제한하는 최대 크기 : ";
	cin >> MAX_NODE_SIZE;
};

void Generator::Run() {
	BSP_Tree::Instance()->_Run(m_MaxSize_x, m_MaxSize_y, MIN_NODE_SIZE, MAX_NODE_SIZE);
};

bool Generator::ReStart()
{
	static int input;
	cout << "종료 : 0 , 재시작 : 1" << endl;
	cin >> input;

	return input == 0 ? false : true;
};

void Generator::Launcher() {
	do {
		this->Initialize();
		this->Run();
	} while (this->ReStart());
}