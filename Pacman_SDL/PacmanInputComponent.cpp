#include "PacmanInputComponent.h"
#include <iostream>

PacmanInputComponent::PacmanInputComponent(Actor* owner)
	: InputComponent(owner), PacmanMoveComponent(owner)
{

}

void PacmanInputComponent::ProcessInput(const uint8_t* keyState) 
{
	// Up / Down Movement
	float downSpeed = 0.f;
	if (keyState[GetDownKey()])
	{
		downSpeed += GetMaxDownSpeed();
		PacmanMoveComponent::SetNextNode(Direction::Bottom);
	}
	if (keyState[GetUpKey()])
	{
		downSpeed -= GetMaxDownSpeed();
		PacmanMoveComponent::SetNextNode(Direction::Top);
	}
	PacmanMoveComponent::SetDownSpeed(downSpeed);


	// Left / Right Movement
	float rightSpeed = 0.f;
	if (keyState[GetRightKey()])
	{
		rightSpeed += GetMaxRightSpeed();
		PacmanMoveComponent::SetNextNode(Direction::Right);
	}
	if (keyState[GetLeftKey()])
	{
		rightSpeed -= GetMaxRightSpeed();
		PacmanMoveComponent::SetNextNode(Direction::Left);
	}
	PacmanMoveComponent::SetRightSpeed(rightSpeed);
}

void PacmanInputComponent::SetCurrentNode(class Node* node)
{
	PacmanMoveComponent::SetCurrentNode(node);
}