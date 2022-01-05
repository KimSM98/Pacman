#pragma once
#include "Actor.h"

class Ghost : public Actor
{
public:
	Ghost(class Game* game);
	~Ghost();

	void UpdateActor(float deltaTime) override;

	void InitByNode(class Node* node);
	void SetTarget(Actor* target) { _Target = target; }
	void ActiveChaseAI(Actor* target);

	class CircleComponent* GetCircleComp() { return _CircleComp; }
private:
	class AnimSpriteSheetComponent* _AnimSprSheetComp;
	class AIComponent* _AIComp;
	class PacmanMoveComponent* _MoveComp;
	class CircleComponent* _CircleComp;

	Vector2 _InitialPos;
	Actor* _Target;
};