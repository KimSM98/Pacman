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
	if (_Direction == d) {
		_DirVal = 1.f;
		return false;
	}
	// Check current node has Direction d node in adj node.
	Node* node = FindNode(d);
	if (node == nullptr) {
		_Direction = Direction::None;
		return false;
	}

	if (_Direction == Direction::None) {
		_Direction = d;
		_NextNode = node;
		//_NextNode = _CurrentNode->GetAdjNode(d);
		_DirVal = 1.f;
	}
	else {
		_ReservedDirection = d;
		_ReservedNextNode = node;
	}

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

		// Player want to keep move same direction
		if (_ReservedDirection == Direction::None)
		{
			Node* sameDirectionNode = FindNode(_Direction);
			// if cannot find direction node from adj node
			if (sameDirectionNode == nullptr)
			{
				_Direction = Direction::None;
				_NextNode = nullptr;
				_DirVal = 0.f;

				return;
			}
			else // keep move to same direction
			{
				_NextNode = sameDirectionNode;
				t = 0.f;
			}			
		}
		else // move to reserved direction
		{
			_Direction = _ReservedDirection;
			_NextNode = _ReservedNextNode;

			_ReservedDirection = Direction::None;
			_ReservedNextNode = nullptr;
		}
		_DirVal = 1.f;
		t = 0.f;

		return;
	}

	Vector2 startPos = _CurrentNode->GetPos();
	Vector2 destPos = _NextNode->GetPos();

	t += deltaTime * _DirVal;

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
