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
	if (_Direction != Direction::None) return false;
	if (!FindNode(d)) {
		_Direction = Direction::None;
		return false;
	}

	_NextNode = _CurrentNode->GetAdjNode(d);
	_Direction = d;

	return true;
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

void PacmanMoveComponent::Move(float deltaTime) 
{
	if (_Direction == Direction::None) return;
	Vector2 startPos = _CurrentNode->GetPos();
	Vector2 destPos = _NextNode->GetPos();

	// 2
	/*if (_Direction == Direction::Left){
		t -= GetRightSpeed() * deltaTime;
	}
	else if (_Direction == Direction::Right) {
		t += GetRightSpeed() * deltaTime;
	}
	else if (_Direction == Direction::Bottom){
		t += GetDownSpeed() * deltaTime;
	}
	else if (_Direction == Direction::Top) {
		t -= GetRightSpeed() * deltaTime;
	}*/


	//// Movement for AI
	//if (_Direction == Direction::Left || _Direction == Direction::Right) {
	//	t += deltaTime;
	//}
	//else if (_Direction == Direction::Bottom || _Direction == Direction::Top) {
	//	t += deltaTime;
	//}

	if (t < 0.f) { // return to current position
		t = 0.f;
		_Direction = Direction::None;
		_NextNode = nullptr;
	}
	else if (t > 1.f) { // Reached to destination
		t = 1.f;
		_Direction = Direction::None;
		_CurrentNode = _NextNode;
		_NextNode = nullptr;
	}

	Vector2 pos;
	pos = lerp(startPos, destPos, t);
	_Owner->SetPosition(pos);

	std::cout << "t: " << t << '\n';

	if (t >= 1.f) {
		t = 0.f;
	}
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
