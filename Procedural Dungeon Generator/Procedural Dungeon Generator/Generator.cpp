#pragma once
#include "stdafx.h"
#include "Generator.h"

using namespace std;

Generator::Generator() {};
Generator::~Generator() {};

void Generator::Initialize() {
	cout << "���� ���� �ʱ�ȭ ����" << endl;

	cout << "���� ���� ũ�� : ";
	cin >> m_MaxSize_x;

	cout << "���� ���� ũ�� : ";
	cin >> m_MaxSize_y;

	cout << "���� ������ �����ϴ� �ּ� ũ�� : ";
	cin >> MIN_NODE_SIZE;

	cout << "���� ������ �����ϴ� �ִ� ũ�� : ";
	cin >> MAX_NODE_SIZE;
};

void Generator::Run() {
	BSP_Tree::Instance()->_Run(m_MaxSize_x, m_MaxSize_y, MIN_NODE_SIZE, MAX_NODE_SIZE);
};

bool Generator::ReStart()
{
	static int input;
	cout << "���� : 0 , ����� : 1" << endl;
	cin >> input;

	return input == 0 ? false : true;
};

void Generator::Launcher() {
	do {
		this->Initialize();
		this->Run();
	} while (this->ReStart());
}