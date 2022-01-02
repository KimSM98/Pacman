#pragma once
#include "Actor.h"

class Ghost : public Actor
{
public:
	Ghost(class Game* game);

	void SetPositionByNode(class Node* node);

private:
	class AnimSpriteSheetComponent* _AnimSprSheetComp;
	class AIComponent* _AIComp;
	class PacmanMoveComponent* _MoveComp;

	Vector2 _InitialPos;
};