#include "PacmanMoveComponent.h"
#include <iostream>
#include <algorithm>
#include "Actor.h"
#include "Math.h"

PacmanMoveComponent::PacmanMoveComponent(Actor* owner, int updateOrder)
	: MoveComponent(owner)
	, _Owner(owner)
{
	//_Owner = owner;
}

void PacmanMoveComponent::Update(float deltaTime) 
{
	Move(deltaTime);
}

bool PacmanMoveComponent::SetNextNode(Direction d) 
{
	// 같은 방향을 Input한 경우
	if (_Direction == d) {
		_DirVal = 1.f;
		return false;
	}
	// _Direction이 있으면 다음 방향을 예약한다.
	if (_Direction != Direction::None)
	{
		_ReservedDirection = d;
		return false;
	}
		
	// Check current node has Direction d node in adj node.
	Node* node = FindNode(d);
	if (node == nullptr) {
		_Direction = Direction::None;
		return false;
	}

	// d 방향의 노드를 찾았을 때
	_Direction = d;
	_NextNode = node;

	return true;
}

void PacmanMoveComponent::SetPosition(Vector2 pos)
{
	_Owner->SetPosition(pos);
}

Node* PacmanMoveComponent::FindNode(Direction d) // from PacmanInputComponent
{
	return _CurrentNode->GetAdjNode(d);
}

void PacmanMoveComponent::Move(float deltaTime)
{
	if (_Direction == Direction::None) return;
	if (hasReachedEnd)
	{
		hasReachedEnd = false;
		
		// 움직임 멈춤
		Direction previousDirection = _Direction;
		_Direction = Direction::None;

		t = 0.f;
		_DirVal = 1.f;

		// 예약된 방향에 노드가 없으면
		if (!SetNextNode(_ReservedDirection))
		{
			SetNextNode(previousDirection);
		}

		_ReservedDirection = Direction::None;

		return;
	}

	Vector2 startPos = _CurrentNode->GetPos();
	Vector2 destPos = _NextNode->GetPos();

	t += deltaTime * _DirVal * _MoveSpeed;

	if (t < 0.f) { // return to current position
		t = 0.f;
		hasReachedEnd = true;
	}
	else if (t > 1.f) { // Reached to destination
		t = 1.f;
		hasReachedEnd = true;
		_CurrentNode = _NextNode;
	}

	Vector2 pos;
	pos = lerp(startPos, destPos, t);
	SetPosition(pos);
}

Vector2 PacmanMoveComponent::lerp(Vector2 currecntPos, Vector2 destPos, float t)
{
	// Get t value from Input component
	return (1.f - t) * currecntPos + t * destPos;
}

void PacmanMoveComponent::MoveToNext()
{
	_DirVal = 1.f;
}

void PacmanMoveComponent::MoveToPrevious()
{
	_DirVal = -1.f;
}
