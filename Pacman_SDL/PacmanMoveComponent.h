#pragma once
#include "MoveComponent.h"

class PacmanMoveComponent :public MoveComponent
{
public:
	PacmanMoveComponent(class Actor* owner, int updateOrder = 10);
	
	void Update(float deltaTime) override;

	void SetCurrentNode(class Node* node) { _CurrentNode = node; }

private:
	void SetNextNode();

	class Node* _CurrentNode;
	class Node* _NextNode;
};
