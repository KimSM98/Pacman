#pragma once
#include "InputComponent.h"

class PacmanInputComponent : public InputComponent
{
public:
	PacmanInputComponent(Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	void SetCurrentNode(class Node* node) { _CurrentNode = node; }

private:
	class Node* _CurrentNode;
	class Node* _NextNode;
};