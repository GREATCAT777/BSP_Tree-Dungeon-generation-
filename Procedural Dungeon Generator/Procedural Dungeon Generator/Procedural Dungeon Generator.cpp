// Procedural Dungeon Generator.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include "stdafx.h"

using namespace std;

int main()
{
	_wsetlocale(LC_ALL, L"Korean"); //	한글 설정

	Generator* generator = new Generator();

	generator->Launcher();

    return 0;
}

