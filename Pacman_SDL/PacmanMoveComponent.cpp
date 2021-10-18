#include "PacmanMoveComponent.h"
#include <iostream>
#include <algorithm>
#include "Actor.h"

PacmanMoveComponent::PacmanMoveComponent(Actor* owner, int updateOrder)
	: MoveComponent(owner)
{
}

void PacmanMoveComponent::Update(float deltaTime)
{

	// Current Character position
	Vector2 pos = _Owner->GetPosition();

	float rightSpeed = GetRightSpeed();
	float downSpeed = GetDownSpeed();

	// Reached to any node
	if (pos.x < _MovableRangeX.first + bindary)
	{
		SetRightSpeed(0.f);
		_Owner->SetPosition(Vector2(_MovableRangeX.first, pos.y));

		isUpdateNextNode = true;
	}
	else if (pos.x > _MovableRangeX.second - bindary)
	{
		SetRightSpeed(0.f);
		
		_Owner->SetPosition(Vector2(_MovableRangeX.second, pos.y));
		isUpdateNextNode = true;
	}
	if (pos.y < _MovableRangeY.first + bindary)
	{
		SetDownSpeed(0.f);
		//downSpeed = 0.f;
		_Owner->SetPosition(Vector2(pos.x, _MovableRangeY.first));
		isUpdateNextNode = true;
	}
	else if (pos.y > _MovableRangeY.second - bindary)
	{
		SetDownSpeed(0.f);
		//downSpeed = 0.f;
		_Owner->SetPosition(Vector2(pos.x, _MovableRangeY.second));
		isUpdateNextNode = true;
	}

	MoveComponent::Update(deltaTime);

	// Move
	
	//pos.y += downSpeed * deltaTime;

	//if (pos.y < 0.f) pos.y = 1023.f;
	//else if (pos.y > 1024) pos.y = 1.f;

	////_Owner->SetPosition(pos);
	//

	//
	//pos.x += rightSpeed * deltaTime;

	//if (pos.x < 0.f) pos.x = 1023.f;
	//else if (pos.x > 1024) pos.x = 0.f;

	//_Owner->SetPosition(pos);
	

	if (_CurrentNode != nullptr && _NextNode != nullptr && isUpdateNextNode)
	{
		SetCurrentNode(_NextNode);
	}

}

bool PacmanMoveComponent::SetNextNode(Direction d) 
{
	// 다음 노드를 설정
	// 이동 범위 업데이트
	if (!isUpdateNextNode)
	{
		return false;
	}

	if (FindNode(d))
	{
		_NextNode = _CurrentNode->GetAdjNode(d);

		_MovableRangeX = std::make_pair(_CurrentNode->GetPos().x, _NextNode->GetPos().x);
		_MovableRangeY = std::make_pair(_CurrentNode->GetPos().y, _NextNode->GetPos().y);

		if (_MovableRangeX.first > _MovableRangeX.second)
		{
			float temp = _MovableRangeX.second;
			_MovableRangeX.second = _MovableRangeX.first;
			_MovableRangeX.first = temp;
		}
		if (_MovableRangeY.first > _MovableRangeY.second)
		{
			float temp = _MovableRangeY.second;
			_MovableRangeY.second = _MovableRangeY.first;
			_MovableRangeY.first = temp;
		}

		return true;
	}

	return false;
}

bool PacmanMoveComponent::FindNode(Direction d) // from PacmanInputComponent
{
	if (_CurrentNode->GetAdjNode(d) != nullptr)
	{
		return true;
	}

	return false;
}

void PacmanMoveComponent::SetCurrentNode(Node* node)
{
	_CurrentNode = node;
}