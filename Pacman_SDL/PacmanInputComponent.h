#pragma once
#include "InputComponent.h"

class PacmanInputComponent : public InputComponent
{
public:
	PacmanInputComponent(Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

private:

};