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
	void SetAnimComp(class AnimSpriteSheetComponent* animComp) { _OwnerAnimComp = animComp; }
private:
	Actor* _Owner;
	class AnimSpriteSheetComponent* _OwnerAnimComp;

	void RotateCharacter(Direction dir);
};