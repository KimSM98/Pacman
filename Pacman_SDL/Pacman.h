#pragma once
#include "Actor.h"
#include <iostream>
class Pacman : public Actor
{
public:
	Pacman(class Game* game);

	void UpdateActor(float deltaTime) override;

	class CircleComponent* GetCollider() { return _CircleComp; }
private:
	/*class AnimSpriteSheetComponent* _AnimSprSheetComp;*/
	class CircleComponent* _CircleComp;
};
