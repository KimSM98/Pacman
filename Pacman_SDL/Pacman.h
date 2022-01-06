#pragma once
#include "Actor.h"
#include <iostream>
class Pacman : public Actor
{
public:
	Pacman(class Game* game);

	void UpdateActor(float deltaTime) override;

	class CircleComponent* GetCollider() { return _CircleComp; }

	void InitPositionByNode(class Node* node);
private:
	class PacmanInputComponent* _InputComp;
	class CircleComponent* _CircleComp;
};
