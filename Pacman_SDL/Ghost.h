#pragma once
#include "Actor.h"
#include "AnimSpriteSheetComponent.h"

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

protected:
	class AnimSpriteSheetComponent* _AnimSprSheetComp;
	std::map<std::string, AnimSpriteSheetComponent::AnimationStates> _AnimMap;

private:
	class AIComponent* _AIComp;
	class PacmanMoveComponent* _MoveComp;
	class CircleComponent* _CircleComp;

	//Vector2 _InitialPos;
	Actor* _Target;

	bool IsChasing = false;
};

class GhostRed : public Ghost
{
public:
	GhostRed(class Game* game);
};

class GhostBlue : public Ghost
{
public:
	GhostBlue(class Game* game);
};

class GhostPink : public Ghost
{
public:
	GhostPink(class Game* game);
};

class GhostOrange : public Ghost
{
public:
	GhostOrange(class Game* game);
};