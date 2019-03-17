#pragma once

#include <vector>
#include "RoomData.h"
#include "HallData.h"
#include "BSP_Node.h"

using namespace std;



class BSP_Tree {
private:
	static BSP_Tree* _instance;

	static const int MIN_NODE_SIZE;
	static const int MAX_NODE_SIZE;

	static vector<BSP_Node> Nodes; // -> 잘린조각들
	static vector<RoomData> Rooms; // -> 생성된 방들
	static vector<HallData> Halls; // -> 통로
public:
	BSP_Tree() {
	}

	static BSP_Tree& Instance() {					//싱글톤
		if (_instance == nullptr)
			_instance = new BSP_Tree();

		return *_instance;
	}
	void AddRoom(const RoomData* rhs) const {
		Rooms.push_back(*rhs);
	}
	void AddHall(const HallData* rhs) const {
		Halls.push_back(*rhs);
	}

	void _Run(int width,int hegith) {
		Nodes.clear();
		BSP_Node* root = new BSP_Node(0, 0, width, hegith);

		Nodes.push_back(*root);

		bool did_split = true;

		while (did_split)
		{
			did_split = false;

			for (int i = 0; i < Nodes.size(); i++)
			{
				if (Nodes[i].leftNode == nullptr && Nodes[i].rightNode == nullptr)
				{
					if (Nodes[i].width > BSP_Node::MAX_NODE_SIZE || Nodes[i].height > Utilclass.MAX_NODE_SIZE || Util::Instance().RandomRange<float>(0, 1) > 0.25f)
					{
						if (Nodes[i].split())
						{
							Nodes.push_back(*Nodes[i].leftNode);
							Nodes.push_back(*Nodes[i].rightNode);
							did_split = true;
						}
					}
				}
			}
		}

		root->createRooms();

		Render();
	}

	void Render() {

		for (int i = 0; i < Rooms.size(); i++)
		{

		}
	}
};