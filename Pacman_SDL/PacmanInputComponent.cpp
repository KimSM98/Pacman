#include "PacmanInputComponent.h"
#include <iostream>

PacmanInputComponent::PacmanInputComponent(Actor* owner)
	: InputComponent(owner), PacmanMoveComponent(owner)
{
	SetMoveSpeed(3.f);
}
void PacmanInputComponent::ProcessInput(const uint8_t* keyState)
{
	Direction moveToDirection = GetDirection();
	
	if (keyState[GetRightKey()])
	{
		PacmanMoveComponent::SetNextNode(Direction::Right);
		if (moveToDirection == Direction::Left)
		{
			MoveToPrevious();
		}
	}
	if (keyState[GetLeftKey()])
	{
		PacmanMoveComponent::SetNextNode(Direction::Left);
		if (moveToDirection == Direction::Right)
		{
			MoveToPrevious();
		}
	}
	if (keyState[GetUpKey()])
	{
		PacmanMoveComponent::SetNextNode(Direction::Top);
		if (moveToDirection == Direction::Bottom)
		{
			MoveToPrevious();
		}
	}
	if (keyState[GetDownKey()])
	{
		PacmanMoveComponent::SetNextNode(Direction::Bottom);
		if (moveToDirection == Direction::Top)
		{
			MoveToPrevious();
		}
	}
}

void PacmanInputComponent::SetCurrentNode(class Node* node)
{
	PacmanMoveComponent::SetCurrentNode(node);
}