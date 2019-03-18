#pragma once
#include "Util.h"
#include "BSP_Tree.h"
#include "RoomData.h"
#include <math.h>

class BSP_Node
{
private:
	int m_x, m_y;				//���ҵ� ���� ��ǥ
	int m_width, m_height;		//���ҵ� ���� ũ��
	RoomData* data;				//�� ������
	int MIN_NODE_SIZE;	//���ҵ� ���� �ּ�ũ��
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
