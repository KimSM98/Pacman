#pragma once
#include "AIState.h"
#include "PacmanMoveComponent.h"


class GhostAIState : public AIState
{
public:
	GhostAIState(class AIComponent* owner) : AIState(owner), _MoveComp(nullptr){}

	void SetPacmanMoveComponent(PacmanMoveComponent* p) { _MoveComp = p; }

protected:
	PacmanMoveComponent* _MoveComp;

	void SetDirection(Direction dir);
};

class GhostAIPatrol : public GhostAIState
{
public:
	GhostAIPatrol(class AIComponent* owner) : GhostAIState(owner) {}

	// 상태에 대한 행동 재정의
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Patrol";
	}

private:
	Direction GetRandomMovableDirection();
	/*void SetDirection(Direction dir);*/
};

class GhostAIDeath : public GhostAIState
{
public:
	GhostAIDeath(class AIComponent* owner) : GhostAIState(owner) {}

	// 상태에 대한 행동 재정의
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Death";
	}
};

class GhostAIChase : public GhostAIState
{
public:
	GhostAIChase(class AIComponent* owner, class Actor* target) : GhostAIState(owner), _Target(target){}

	// 상태에 대한 행동 재정의
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Chase";
	}

private:
	class Actor* _Target;

	Direction GetCloseNodeToTarget();
	float _MaxChasingTime = 2.f;
	float _TimeSinceCahsing = 0.f;
};