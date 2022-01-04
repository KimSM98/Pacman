#pragma once
#include "InputComponent.h"
#include "PacmanMoveComponent.h"

class PacmanInputComponent : public InputComponent, PacmanMoveComponent
{
public:
	PacmanInputComponent(Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	void SetCurrentNode(class Node* node);
	void SetMoveSpeed(float val) { PacmanMoveComponent::SetMoveSpeed(val); }
private:
	Actor* _Owner;

	void RotateCharacter(Direction dir);
};