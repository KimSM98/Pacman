#include "PacmanInputComponent.h"
#include <iostream>

PacmanInputComponent::PacmanInputComponent(Actor* owner)
	: InputComponent(owner), PacmanMoveComponent(owner)
{

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


	if (moveToDirection == Direction::Right || moveToDirection == Direction::Left)
	{

	}
}
//void PacmanInputComponent::ProcessInput(const uint8_t* keyState) 
//{
//	// Up / Down Movement
//	float downSpeed = 0.f;
//	Direction moveToDirection = GetDirection();
//
//	float moveSpeed = 0.02f;
//	if (keyState[GetDownKey()])
//	{
//		//downSpeed += GetMaxDownSpeed();
//		if (moveToDirection == Direction::None)
//		{
//			PacmanMoveComponent::SetNextNode(Direction::Bottom);
//		}
//		if (moveToDirection == Direction::Bottom)
//			IncreaseT(moveSpeed);
//		else if (moveToDirection == Direction::Top)
//			DecreaseT(moveSpeed);
//	}
//	if (keyState[GetUpKey()])
//	{
//		//downSpeed -= GetMaxDownSpeed();
//		if (moveToDirection == Direction::None)
//		{
//			PacmanMoveComponent::SetNextNode(Direction::Top);
//		}
//		if (moveToDirection == Direction::Top)
//			IncreaseT(moveSpeed);
//		else if (moveToDirection == Direction::Bottom)
//			DecreaseT(moveSpeed);
//	}
//	PacmanMoveComponent::SetDownSpeed(downSpeed);
//
//
//	// Left / Right Movement
//	float rightSpeed = 0.f;
//	if (keyState[GetRightKey()])
//	{
//		//rightSpeed += GetMaxRightSpeed();
//		if (moveToDirection == Direction::None)
//		{
//			PacmanMoveComponent::SetNextNode(Direction::Right);
//		}
//		if (moveToDirection == Direction::Right)
//			IncreaseT(moveSpeed);
//		else if (moveToDirection == Direction::Left)
//			DecreaseT(moveSpeed);
//	}
//	if (keyState[GetLeftKey()])
//	{
//		/*rightSpeed -= GetMaxRightSpeed();*/
//		if (moveToDirection == Direction::None)
//		{
//			PacmanMoveComponent::SetNextNode(Direction::Left);
//		}
//		if (moveToDirection == Direction::Left)
//			IncreaseT(moveSpeed);
//		else if (moveToDirection == Direction::Right)
//			DecreaseT(moveSpeed);
//	}
//	PacmanMoveComponent::SetRightSpeed(rightSpeed);
//}

void PacmanInputComponent::SetCurrentNode(class Node* node)
{
	PacmanMoveComponent::SetCurrentNode(node);
}