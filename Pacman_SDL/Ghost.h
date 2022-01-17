#pragma once
#include "Actor.h"
#include "AnimSpriteSheetComponent.h"

class Ghost : public Actor
{
public:
	Ghost(class Game* game, class Node* node);
	~Ghost();

	void UpdateActor(float deltaTime) override;

	class CircleComponent* GetCircleComp() { return _CircleComp; }

	// Chase ����� �߰��ϱ� ���� �Լ�
	void ActiveChaseAI(Actor* target, float distance, float chaseTime);

protected:
	class AnimSpriteSheetComponent* _AnimSprSheetComp;
	std::map<std::string, AnimSpriteSheetComponent::AnimationStates> _AnimMap;

private:
	void InitPosition(class Node* node);
	void InitMoveComp(class Node* node);
	void InitAIComp(class Node* node);
	void InitCollider();
	void InitAnimationComp();

	class AIComponent* _AIComp;
	class PacmanMoveComponent* _MoveComp;
	class CircleComponent* _CircleComp;
	// Chase�� Ÿ��
	Actor* _Target;
	// Chase ����� ����ϴ� ��
	bool IsChasing = false;
	float _ChaseDistance;
};

class GhostRed : public Ghost
{
public:
	GhostRed(class Game* game, class Node* node);
};

class GhostBlue : public Ghost
{
public:
	GhostBlue(class Game* game, class Node* node);
};

class GhostPink : public Ghost
{
public:
	GhostPink(class Game* game, class Node* node);
};

class GhostOrange : public Ghost
{
public:
	GhostOrange(class Game* game, class Node* node);
};