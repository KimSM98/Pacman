#pragma once
#include "Actor.h"

class Ghost : public Actor
{
public:
	Ghost(class Game* game);

	void UpdateActor(float deltaTime) override;

	void SetPositionByNode(class Node* node);
	void SetTarget(Actor* target) { _Target = target; }
	void ActiveChaseAI(Actor* target);
private:
	class AnimSpriteSheetComponent* _AnimSprSheetComp;
	class AIComponent* _AIComp;
	class PacmanMoveComponent* _MoveComp;

	Vector2 _InitialPos;
	Actor* _Target;
};