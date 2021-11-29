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
	Move(deltaTime);
}

bool PacmanMoveComponent::SetNextNode(Direction d) 
{
	// 같은 방향을 Input한 경우
	if (_Direction == d) {
		_DirVal = 1.f;
		return false;
	}
	// _Direction이 있으면
	if (_Direction != Direction::None)
	{
		_ReservedDirection = d;
		std::cout << "Reserved" << '\n';
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
	_DirVal = 1.f;

	return true;
}

Node* PacmanMoveComponent::FindNode(Direction d) // from PacmanInputComponent
{
	return _CurrentNode->GetAdjNode(d);
}

void PacmanMoveComponent::SetCurrentNode(Node* node)
{
	_CurrentNode = node;
}

void PacmanMoveComponent::Move(float deltaTime)
{
	if (_Direction == Direction::None) return;
	if (hasReachedEnd)
	{
		hasReachedEnd = false;
		t = 0.f;
		// Player want to keep move same direction
		if (_ReservedDirection == Direction::None) // 예약된 방향이 없으면
		{
			// 같은 방향으로 계속 이동 가능한지 확인
			Node* sameDirectionNode = FindNode(_Direction);
			// if cannot find direction node from adj node
			if (sameDirectionNode == nullptr) // 같은 방향의 노드가 없으면 초기화
			{
				_Direction = Direction::None;
				_NextNode = nullptr;
				_DirVal = 0.f;

				return;
			}
			else // 같은 방향으로 계속 이동
			{
				_NextNode = sameDirectionNode;
				t = 0.f;
			}			
		}
		else // 예약된 방향이 있으면
		{
			Direction temp = _Direction;
			_Direction = Direction::None;
			if (!SetNextNode(_ReservedDirection)) // 예약된 방향에 노드가 없으면
			{
				// 가던 방향으로 계속 이동 가능한지 확인
				SetNextNode(temp);
			}

			_ReservedDirection = Direction::None;
		}
		_DirVal = 1.f;

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
		_CurrentNode = _NextNode;
		hasReachedEnd = true;
	}

	Vector2 pos;
	pos = lerp(startPos, destPos, t);
	_Owner->SetPosition(pos);

	std::cout << "t: " << t << '\n';
}

Vector2 PacmanMoveComponent::lerp(Vector2 currecntPos, Vector2 destPos, float t)
{
	// Get t value from Input component
	return (1.f - t) * currecntPos + t * destPos;
}

void PacmanMoveComponent::IncreaseT(float val)
{
	t += val;
}

void PacmanMoveComponent::DecreaseT(float val)
{
	t -= val;
}

void PacmanMoveComponent::MoveToNext()
{
	_DirVal = 1.f;
}

void PacmanMoveComponent::MoveToPrevious()
{
	_DirVal = -1.f;
}
