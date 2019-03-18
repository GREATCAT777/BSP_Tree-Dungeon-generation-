#pragma once
#include "Util.h"
#include "BSP_Tree.h"
#include "RoomData.h"
#include <math.h>

class BSP_Node
{
private:
	int m_x, m_y;				//분할된 공간 좌표
	int m_width, m_height;		//분할된 공간 크기
	RoomData* data;				//방 데이터
	int MIN_NODE_SIZE;	//분할될 공간 최소크기
public:
	BSP_Node * leftNode;
	BSP_Node* rightNode;
private:

public:
	BSP_Node(int x, int y, int width, int height) :m_x(x), m_y(y), m_width(width), m_height(height) {};
	BSP_Node(const BSP_Node& rhs) :m_x(rhs.m_x), m_y(rhs.m_y), m_width(rhs.m_width), m_height(rhs.m_height) {};
	~BSP_Node() {};

	//const BSP_Node& operator=(const BSP_Node& rhs) {
	//	return *this;
	//}

	const int getWidth();
	const int getHeight();
	void setMIN_Node_Size(int size);

	bool split();

	void createRooms();
	RoomData* getRoom();
	void createHall(RoomData* l, RoomData* r);
};
