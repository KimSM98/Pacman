#include "PacmanMoveComponent.h"
#include "Node.h"
#include <iostream>
#include "Actor.h"

PacmanMoveComponent::PacmanMoveComponent(Actor* owner, int updateOrder)
	: MoveComponent(owner)
{
}

void PacmanMoveComponent::Update(float deltaTime) 
{
	if (_NextNode == nullptr) 
	{
		SetNextNode();
	}

	// Compare current position with next node's position,
	// then, if actor reached next node's postion, set the current node to next node.
	// and   if actor moved to current node's position again, set next node to null.

	// C.N과 N.N 사이에서만 이동 가능
	// 만약 C.N과 N.N사이가 아니라면 speed = 0;
	//Vector2 pos = _Owner->GetPosition();

	
	MoveComponent::Update(deltaTime);
}

void PacmanMoveComponent::SetNextNode() 
{
	Direction dir = Direction::None;

	float rightSpeed = GetRightSpeed();
	if (rightSpeed > 0.f)
	{
		dir = Direction::Right;
		/*if (_CurrentNode->GetAdjNode(Direction::Right) != nullptr)
			_NextNode = _CurrentNode->GetAdjNode(Direction::Right);
			*/
		std::cout << "Right!" << '\n';
	}
	else if (rightSpeed < 0.f)
	{
		dir = Direction::Left;
		std::cout << "Left!" << '\n';
	}

	float downSpeed = GetDownSpeed();
	if (downSpeed > 0.f)
	{
		dir = Direction::Bottom;
		std::cout << "down!" << '\n';
	}
	else if (downSpeed < 0.f)
	{
		dir = Direction::Top;
		std::cout << "Up!" << '\n';
	}

	if (_CurrentNode->GetAdjNode(dir) != nullptr)
	{
		_NextNode = _CurrentNode->GetAdjNode(dir);
	}
}