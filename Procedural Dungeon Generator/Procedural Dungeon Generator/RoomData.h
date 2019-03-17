#pragma once
#include "MyVector2.h"

class RoomData
{
private:
	MyVector2* roomPos;
	MyVector2* roomsize;
public:
	RoomData() {};
	RoomData(float _x, float _y, float _width, float _height) //Pos,Size
	{
		roomPos = new MyVector2(_x, _y);
		roomsize = new MyVector2(_width, _height);
	}
	~RoomData() {};

	const MyVector2& getRoomPos() const {
		return *roomPos;
	}
	const MyVector2& getRoomsize() const {
		return *roomsize;
	}
};

