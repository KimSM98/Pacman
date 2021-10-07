#pragma once
#include "Actor.h"
#include <stdint.h>

class Character : public Actor
{
public:
	Character(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);

	float GetRightSpeed() const { return _RightSpeed; }
	float GetLeftSpeed() const { return _DownSpeed; }

private:
	float _RightSpeed;
	float _DownSpeed;

	class AnimSpriteComponent* _AnimSprComp;
};
