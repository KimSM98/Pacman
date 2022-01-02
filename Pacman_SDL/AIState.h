#pragma once

class AIState
{
public:
	AIState(class AIComponent* owner) : _Owner(owner) {}

	// 각 상태의 행동
	virtual void Update(float deltaTime) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	// 상태의 이름 얻기
	virtual const char* GetName() const = 0;

protected:
	class AIComponent* _Owner;
};

//
//class AIPatrol : public AIState
//{
//public:
//	AIPatrol(class AIComponent* owner) : AIState(owner) {}
//
//	// 상태에 대한 행동 재정의
//	void Update(float deltaTime) override;
//	void OnEnter() override;
//	void OnExit() override;
//
//	const char* GetName() const override
//	{
//		return "Patrol";
//	}
//};
//
//class AIDeath : public AIState
//{
//public:
//	AIDeath(class AIComponent* owner) : AIState(owner) {}
//
//	// 상태에 대한 행동 재정의
//	void Update(float deltaTime) override;
//	void OnEnter() override;
//	void OnExit() override;
//
//	const char* GetName() const override
//	{
//		return "Death";
//	}
//};
//
//class AIAttack : public AIState
//{
//public:
//	AIAttack(class AIComponent* owner) : AIState(owner) {}
//
//	// 상태에 대한 행동 재정의
//	void Update(float deltaTime) override;
//	void OnEnter() override;
//	void OnExit() override;
//
//	const char* GetName() const override
//	{
//		return "Death";
//	}
//};