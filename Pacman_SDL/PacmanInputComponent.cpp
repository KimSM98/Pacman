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
	}
	if (keyState[GetUpKey()])
	{
		downSpeed -= GetMaxDownSpeed();
	}
	PacmanMoveComponent::SetDownSpeed(downSpeed);
	//MoveComponent::SetDownSpeed(downSpeed);


	// Left / Right Movement
	float rightSpeed = 0.f;
	if (keyState[GetRightKey()])
	{
		rightSpeed += GetMaxRightSpeed();
	}
	if (keyState[GetLeftKey()])
	{
		rightSpeed -= GetMaxRightSpeed();
	}
	PacmanMoveComponent::SetRightSpeed(rightSpeed);
}