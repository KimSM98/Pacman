#pragma once
#include "MoveComponent.h"
#include <utility>
#include "Node.h"

class PacmanMoveComponent :public MoveComponent
{
public:
	PacmanMoveComponent(class Actor* owner, int updateOrder = 10);
	
	void Update(float deltaTime) override;

	void SetCurrentNode(class Node* node);
	bool SetNextNode(Direction d);

private:
	bool FindNode(Direction d);

	Node* _CurrentNode;
	Node* _NextNode;

	// Movable range
	std::pair<float, float> _MovableRangeX;
	std::pair<float, float> _MovableRangeY;

	// If actor reached to current node or next node, its true.
	bool isUpdateNextNode = true;

	float bindary = 0.f;
};
