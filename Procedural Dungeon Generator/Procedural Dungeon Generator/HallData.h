#pragma once

#include "MyVector2.h"

//복도 자료형
class HallData {
private:
	MyVector2* hallPos;
	MyVector2* hallSize;
public:
	HallData(float _x, float _y, float _width, float _height)
	{
		hallPos = new MyVector2(_x, _y);
		hallSize = new MyVector2(_width, _height);
	}
	HallData(MyVector2* pos, MyVector2* size) {
		hallPos = pos;
		hallSize = size;
	}
};