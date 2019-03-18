#pragma once
#include "stdafx.h"
#include "BSP_Node.h"

const int BSP_Node::getWidth() {
	return m_width;
}
const int BSP_Node::getHeight() {
	return m_height;
}
void BSP_Node::setMIN_Node_Size(int size) {
	MIN_NODE_SIZE = size;
}

bool BSP_Node::split() {
	if (leftNode != nullptr || rightNode != nullptr)							//자식이 있는지 판정
		return false;

	bool splitH = (RandomRange<float>(0, 1) > 0.5f);              //수평으로 자를지 말지 판정

	if (m_width > m_height && m_width / m_height >= 1.25)                       //수평 조건 25%넘어갈경우
		splitH = false;

	else if (m_height > m_width && m_height / m_width >= 1.25)                  //수직 조건 25%넘어갈경우
		splitH = true;

	int max = (splitH ? m_height : m_width) - MIN_NODE_SIZE;					//방 하나 더 나올수 있는 공간이 있는지 판별

	if (max <= MIN_NODE_SIZE)													//없으면 리턴
		return false;

	int split = RandomRange<int>(MIN_NODE_SIZE, max);				//방을 자른다.

	if (splitH)
	{
		leftNode = new BSP_Node(m_x, m_y, m_width, split);                    // 수평이라면 이조건으로 자식 생성
		rightNode = new BSP_Node(m_x, m_y + split, m_width, m_height - split);
	}
	else
	{
		leftNode = new BSP_Node(m_x, m_y, split, m_height);                   //수직이라면 이조건으로 다시 자식생성
		rightNode = new BSP_Node(m_x + split, m_y, m_width - split, m_height);
	}
	return true;
}

void BSP_Node::createRooms()
{
	if (leftNode != nullptr || rightNode != nullptr)                           //자식이 없을때만  
	{
		if (leftNode != nullptr)
		{
			leftNode->createRooms();
		}
		if (rightNode != nullptr)
		{
			rightNode->createRooms();
		}

		if (leftNode != nullptr && rightNode != nullptr)
		{
			createHall(leftNode->getRoom(), rightNode->getRoom());
		}
	}
	else
	{
		data = new RoomData(
			RandomRange<float>(1, m_width - data->getRoomsize().m_x - 1),		//Pos
			RandomRange<float>(1, m_height - data->getRoomsize().m_y - 1),
			RandomRange<float>(3, m_width - 2),								//Size
			RandomRange<float>(3, m_height - 2)
		);

		BSP_Tree::Instance()->AddRoom(*data);
	}
}

RoomData* BSP_Node::getRoom()
{
	if (data != NULL)
		return data;
	else
	{
		RoomData* lRoom = new RoomData();
		RoomData* rRoom = new RoomData();

		if (leftNode != nullptr)
		{
			lRoom = leftNode->getRoom();
		}

		if (rightNode != nullptr)
		{
			rRoom = rightNode->getRoom();
		}

		if (lRoom == nullptr && rRoom == nullptr)
			return nullptr;
		else if (rRoom == nullptr)
			return lRoom;
		else if (lRoom == nullptr)
			return rRoom;
		else if (RandomRange<float>(0, 1) > 0.5f)
			return lRoom;
		else
			return rRoom;
	}
}

void BSP_Node::createHall(RoomData* l, RoomData* r)
{
	BSP_Tree* Tree;

	MyVector2* point1 =
		new MyVector2(
			RandomRange<float>(l->getRoomPos().m_x + 1, l->getRoomPos().m_y - 2),
			RandomRange<float>(l->getRoomPos().m_x + 1, l->getRoomPos().m_x - 2)
		);
	MyVector2* point2 =
		new MyVector2(
			RandomRange<float>(r->getRoomPos().m_x + 1, r->getRoomPos().m_y - 2),
			RandomRange<float>(r->getRoomPos().m_y + 1, r->getRoomPos().m_y - 2)
		);

	float w = point2->m_x - point1->m_x;
	float h = point2->m_y - point1->m_y;

	if (w < 0)
	{
		if (h < 0)
		{
			if (RandomRange<float>(0, 1) < 0.5f)
			{
				BSP_Tree::Instance()->AddHall(
					*new HallData(point2->m_x, point1->m_y, abs(w), 1)
				);
				BSP_Tree::Instance()->AddHall(
					*new HallData(point2->m_x, point2->m_y, 1, abs(h))
				);
			}
			else
			{
				BSP_Tree::Instance()->AddHall(
					*new HallData(point2->m_x, point2->m_y, abs(w), 1)
				);
				BSP_Tree::Instance()->AddHall(
					*new HallData(point1->m_x, point2->m_y, 1, abs(h))
				);
			}
		}
		else if (h > 0)
		{
			if (RandomRange<float>(0, 1) < 0.5)
			{
				BSP_Tree::Instance()->AddHall(
					*new HallData(point2->m_x, point1->m_y, abs(w), 1)
				);
				BSP_Tree::Instance()->AddHall(
					*new HallData(point2->m_x, point1->m_y, 1, abs(h))
				);
			}
			else
			{
				BSP_Tree::Instance()->AddHall(
					*new HallData(point2->m_x, point2->m_y, abs(w), 1)
				);
				BSP_Tree::Instance()->AddHall(
					*new HallData(point1->m_x, point1->m_y, 1, abs(h))
				);
			}
		}
		else // if (h == 0)
		{
			BSP_Tree::Instance()->AddHall(
				*new HallData(point2->m_x, point2->m_y, abs(w), 1)
			);
		}
	}
	else if (w > 0)
	{
		if (h < 0)
		{
			if (RandomRange<float>(0, 1) < 0.5)
			{
				BSP_Tree::Instance()->AddHall(
					*new HallData(point1->m_x, point2->m_y, abs(w), 1)
				);
				BSP_Tree::Instance()->AddHall(
					*new HallData(point1->m_x, point2->m_y, 1, abs(h))
				);
			}
			else
			{
				BSP_Tree::Instance()->AddHall(
					*new HallData(point1->m_x, point1->m_y, abs(w), 1)
				);
				BSP_Tree::Instance()->AddHall(
					*new HallData(point2->m_x, point2->m_y, 1, abs(h))
				);
			}
		}
		else if (h > 0)
		{
			if (RandomRange<float>(0, 1) < 0.5)
			{
				BSP_Tree::Instance()->AddHall(
					*new HallData(point1->m_x, point1->m_y, abs(w), 1)
				);
				BSP_Tree::Instance()->AddHall(
					*new HallData(point2->m_x, point1->m_y, 1, abs(h))
				);
			}
			else
			{
				BSP_Tree::Instance()->AddHall(
					*new HallData(point1->m_x, point2->m_y, abs(w), 1)
				);
				BSP_Tree::Instance()->AddHall(
					*new HallData(point1->m_x, point1->m_y, 1, abs(h))
				);
			}
		}
		else // if (h == 0)
		{
			BSP_Tree::Instance()->AddHall(
				*new HallData(point1->m_x, point1->m_y, abs(w), 1)
			);
		}
	}
	else // if (w == 0)
	{
		if (h < 0)
		{
			BSP_Tree::Instance()->AddHall(
				*new HallData(point2->m_x, point2->m_y, 1, abs(h))
			);
		}
		else if (h > 0)
		{
			BSP_Tree::Instance()->AddHall(
				*new HallData(point1->m_x, point1->m_y, 1, abs(h))
			);
		}
	}
}