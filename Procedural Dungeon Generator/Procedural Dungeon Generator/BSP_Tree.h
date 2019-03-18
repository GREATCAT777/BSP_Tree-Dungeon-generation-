#pragma once

#include <vector>
#include "RoomData.h"
#include "HallData.h"
#include "BSP_Node.h"

using namespace std;

class BSP_Tree {
private:
	static BSP_Tree* _instance;

	vector<BSP_Node> Nodes; // -> �߸�������
	vector<RoomData> Rooms; // -> ������ ���
	vector<HallData> Halls; // -> ���
public:
	BSP_Tree();
	BSP_Tree(const BSP_Tree& other);

	static BSP_Tree* Instance();
	void AddRoom(const RoomData& rhs);
	void AddHall(const HallData& rhs);

	void _Run(int width, int hegith, int MIN_NODE_SIZE, int MAX_NODE_SIZE);

	void Render();
};