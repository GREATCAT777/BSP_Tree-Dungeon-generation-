#pragma once
#include "Util.h"
#include "BSP_Tree.h"
#include "RoomData.h"
#include <math.h>

class BSP_Node
{
private:
	int m_x, m_y;			//����ǥ
	int m_width, m_height;	//��ũ��
	RoomData* data;
public:
	BSP_Node* leftNode;
	BSP_Node* rightNode;

private:

public:
	BSP_Node(int x, int y, int width, int height) :m_x(x), m_y(y), m_width(width), m_height(height) {};
	BSP_Node(const BSP_Node& rhs) :m_x(rhs.m_x), m_y(rhs.m_y), m_width(rhs.m_width), m_height(rhs.m_height) {};
	~BSP_Node() {};

	//const BSP_Node& operator=(const BSP_Node& rhs) {
	//	return *this;
	//}

	bool split() {
		if (leftNode != nullptr || rightNode != nullptr)							//�ڽ��� �ִ��� ����
			return false;

		bool splitH = (Util::Instance().RandomRange<float>(0, 1) > 0.5f);              //�������� �ڸ��� ���� ����

		if (m_width > m_height && m_width / m_height >= 1.25)                       //���� ���� 25%�Ѿ���
			splitH = false;

		else if (m_height > m_width && m_height / m_width >= 1.25)                  //���� ���� 25%�Ѿ���
			splitH = true;

		int max = (splitH ? m_height : m_width) - MIN_NODE_SIZE;					//�� �ϳ� �� ���ü� �ִ� ������ �ִ��� �Ǻ�

		if (max <= MIN_NODE_SIZE)													//������ ����
			return false;	

		int split = Util::Instance().RandomRange<int>(MIN_NODE_SIZE, max);				//���� �ڸ���.

		if (splitH)
		{
			leftNode = new BSP_Node(m_x, m_y, m_width, split);                    // �����̶�� ���������� �ڽ� ����
			rightNode = new BSP_Node(m_x, m_y + split, m_width, m_height - split);
		}
		else
		{
			leftNode = new BSP_Node(m_x, m_y, split, m_height);                   //�����̶�� ���������� �ٽ� �ڽĻ���
			rightNode = new BSP_Node(m_x + split, m_y, m_width - split, m_height);
		}
		return true;
	}

	void createRooms()
	{
		if (leftNode != nullptr || rightNode != nullptr)                           //�ڽ��� ��������  
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
				Util::Instance().RandomRange<float>(1, m_width - data->getRoomsize().m_x - 1),		//Pos
				Util::Instance().RandomRange<float>(1, m_height - data->getRoomsize().m_y - 1),
				Util::Instance().RandomRange<float>(3, m_width - 2),								//Size
				Util::Instance().RandomRange<float>(3, m_height - 2)
				);

			BSP_Tree::Instance().AddRoom(data);
		}
	}

	RoomData* getRoom()
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
			else if (Util::Instance().RandomRange<float>(0, 1) > 0.5f)
				return lRoom;
			else
				return rRoom;
		}
	}

	void createHall(RoomData* l, RoomData* r)
	{
		auto_ptr<MyVector2> point1 (
			new MyVector2(
				Util::Instance().RandomRange<float>(l->getRoomPos().m_x + 1, l->getRoomPos().m_y - 2),
				Util::Instance().RandomRange<float>(l->getRoomPos().m_x + 1, l->getRoomPos().m_x - 2)
			)
		);
		auto_ptr<MyVector2> point2 (
			new MyVector2(
				Util::Instance().RandomRange<float>(r->getRoomPos().m_x + 1, r->getRoomPos().m_y - 2),
				Util::Instance().RandomRange<float>(r->getRoomPos().m_y + 1, r->getRoomPos().m_y - 2)
			)
		);

		float w = point2->m_x - point1->m_x;
		float h = point2->m_y - point1->m_y;

		if (w < 0)
		{
			if (h < 0)
			{
				if (Util::Instance().RandomRange<float>(0, 1) < 0.5f)
				{
					BSP_Tree::Instance().AddHall(
						new HallData(	point2->m_x , point1->m_y,	abs(w) , 1	)
					);
					BSP_Tree::Instance().AddHall(
						new HallData(	point2->m_x , point2->m_y,	1 , abs(h)	)
					);
				}
				else
				{
					BSP_Tree::Instance().AddHall(
						new HallData(	point2->m_x, point2->m_y,	abs(w), 1	)
					);
					BSP_Tree::Instance().AddHall(
						new HallData(	point1->m_x, point2->m_y,	1, abs(h)	)
					);
				}
			}
			else if (h > 0)
			{
				if (Util::Instance().RandomRange<float>(0, 1) < 0.5)
				{
					BSP_Tree::Instance().AddHall(
						new HallData(point2->m_x, point1->m_y, abs(w), 1)
					);
					BSP_Tree::Instance().AddHall(
						new HallData(point2->m_x, point1->m_y, 1, abs(h))
					);
				}
				else
				{
					BSP_Tree::Instance().AddHall(
						new HallData(point2->m_x, point2->m_y, abs(w), 1)
					); 
					BSP_Tree::Instance().AddHall(
						new HallData(point1->m_x, point1->m_y, 1, abs(h))
					);
				}
			}
			else // if (h == 0)
			{
				BSP_Tree::Instance().AddHall(
					new HallData(point2->m_x, point2->m_y, abs(w), 1)
				);
			}
		}
		else if (w > 0)
		{
			if (h < 0)
			{
				if (Util::Instance().RandomRange<float>(0, 1) < 0.5)
				{
					BSP_Tree::Instance().AddHall(
						new HallData(point1->m_x, point2->m_y, abs(w), 1)
					); 
					BSP_Tree::Instance().AddHall(
						new HallData(point1->m_x, point2->m_y, 1, abs(h))
					);
				}
				else
				{
					BSP_Tree::Instance().AddHall(
						new HallData(point1->m_x, point1->m_y, abs(w), 1)
					);
					BSP_Tree::Instance().AddHall(
						new HallData(point2->m_x, point2->m_y, 1, abs(h))
					);
				}
			}
			else if (h > 0)
			{
				if (Util::Instance().RandomRange<float>(0, 1) < 0.5)
				{
					BSP_Tree::Instance().AddHall(
						new HallData(point1->m_x, point1->m_y, abs(w), 1)
					);
					BSP_Tree::Instance().AddHall(
						new HallData(point2->m_x, point1->m_y, 1, abs(h))
					);
				}
				else
				{
					BSP_Tree::Instance().AddHall(
						new HallData(point1->m_x, point2->m_y, abs(w), 1)
					);
					BSP_Tree::Instance().AddHall(
						new HallData(point1->m_x, point1->m_y, 1, abs(h))
					);
				}
			}
			else // if (h == 0)
			{
				BSP_Tree::Instance().AddHall(
					new HallData(point1->m_x, point1->m_y, abs(w), 1)
				);
			}
		}
		else // if (w == 0)
		{
			if (h < 0)
			{
				BSP_Tree::Instance().AddHall(
					new HallData(point2->m_x, point2->m_y, 1, abs(h))
				);
			}
			else if (h > 0)
			{
				BSP_Tree::Instance().AddHall(
					new HallData(point1->m_x, point1->m_y, 1, abs(h))
				);
			}
		}
	}
};
