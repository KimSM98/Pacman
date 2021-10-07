#pragma once
#include "Actor.h"
#include <stdint.h>

class Ship : public Actor
{
public:
	Ship(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState);
	/*void ProcessKeyboard(const uint8_t* state);

	float GetRightSpeed() const { return _RightSpeed; }
	float GetLeftSpeed() const { return _DownSpeed; }*/
	class SpriteComponent* GetSpriteComponent() const { return _SpriteComponent; }

private:
	class SpriteComponent* _SpriteComponent;
	class BoxComponent* _BoxComponent;

	float _LaserCoolDown;
	//float _RightSpeed;
	//float _DownSpeed;
};
