#pragma once
#include "Actor.h"
#include <iostream>
class Pacman : public Actor
{
public:
	//Pacman(class Game* game);
	Pacman(class Game* game, class Node* node);

	class CircleComponent* GetCollider() { return _CircleComp; }

private:
	void InitAnimComp();
	void InitInputComp();
	void InitCollider();

	void SetPositionByNode(class Node* node);

	class AnimSpriteSheetComponent* _animSprSheetComp;
	class PacmanInputComponent* _InputComp;
	class CircleComponent* _CircleComp;
};
