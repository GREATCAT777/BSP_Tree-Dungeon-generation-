#pragma once
#include "stdafx.h"
#include "BSP_Tree.h"

BSP_Tree* BSP_Tree::_instance = nullptr;

BSP_Tree::BSP_Tree() {
}

BSP_Tree::BSP_Tree(const BSP_Tree & other)
{
}

BSP_Tree* BSP_Tree::Instance() {					//싱글톤
	if (_instance == nullptr)
		_instance = new BSP_Tree();

	return _instance;
}
void BSP_Tree::AddRoom(const RoomData& rhs) {
	Rooms.push_back(rhs);
}
void BSP_Tree::AddHall(const HallData& rhs) {
	Halls.push_back(rhs);
}

void BSP_Tree::_Run(int width, int hegith, int MIN_NODE_SIZE, int MAX_NODE_SIZE) {

	Nodes.clear();

	BSP_Node* root = new BSP_Node(0, 0, width, hegith); //트리 시작점

	root->setMIN_Node_Size(MIN_NODE_SIZE);				//공간 최소 크기 설정

	Nodes.push_back(*root);								//등록

	bool did_split = true;

	while (did_split)
	{
		did_split = false;

		for (int i = 0; i < Nodes.size(); i++)
		{
			if (Nodes[i].leftNode == nullptr && Nodes[i].rightNode == nullptr)
			{
				if (
					Nodes[i].getWidth() > MAX_NODE_SIZE ||
					Nodes[i].getHeight() > MAX_NODE_SIZE ||
					RandomRange<float>(0, 1) > 0.25f
					)
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

void BSP_Tree::Render() { //화면에 그리기

	for (int i = 0; i < Rooms.size(); i++)
	{

	}

	cout << "Done!" << endl;
}