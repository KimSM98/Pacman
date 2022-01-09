#include "PacmanInputComponent.h"
#include "Actor.h"
#include "AnimSpriteSheetComponent.h"

PacmanInputComponent::PacmanInputComponent(Actor* owner)
	: InputComponent(owner)
	, PacmanMoveComponent(owner)
	, _Owner(owner)
	, _OwnerAnimComp(nullptr)
{
}

void PacmanInputComponent::ProcessInput(const uint8_t* keyState)
{
	Direction moveToDirection = GetDirection();

	RotateCharacter(moveToDirection);
	
	if (_OwnerAnimComp != nullptr)
	{
		std::string animState;

		if (moveToDirection == Direction::None)
			animState = "Default";
		else
			animState = "Run";

		_OwnerAnimComp->SetCurrentAnimation(animState);
	}	

	if (keyState[GetRightKey()])
	{
		PacmanMoveComponent::SetNextNode(Direction::Right);
		if (moveToDirection == Direction::Left)
		{
			MoveToPrevious();
		}
	}
	else if (keyState[GetLeftKey()])
	{
		PacmanMoveComponent::SetNextNode(Direction::Left);
		if (moveToDirection == Direction::Right)
		{
			MoveToPrevious();
		}
	}
	else if (keyState[GetUpKey()])
	{
		PacmanMoveComponent::SetNextNode(Direction::Top);
		if (moveToDirection == Direction::Bottom)
		{
			MoveToPrevious();
		}
	}
	else if (keyState[GetDownKey()])
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

void PacmanInputComponent::RotateCharacter(Direction dir)
{
	switch (dir)
	{
	case Direction::Right:
		_Owner->SetRotation(0);
		break;
	case Direction::Left:
		_Owner->SetRotation(Math::Pi);
		break;
	case Direction::Top:
		_Owner->SetRotation(0.5f * Math::Pi);
		break;
	case Direction::Bottom:
		_Owner->SetRotation(1.5f * Math::Pi);
		break;
	default:
		break;
	}
}
