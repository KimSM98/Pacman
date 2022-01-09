#pragma once
#include "Component.h"
#include <unordered_map>

class AIComponent : public Component
{
public:
	AIComponent(class Actor* owner);

	void Update(float deltaTime) override;
	void ChangeState(const std::string& name);
	// AIState를 맵에 추가한다.
	void RegisterState(class AIState* state);
	
	std::string GetCurrecntState();
private:
	// 상태의 이름, AIState 객체를 매핑
	std::unordered_map<std::string, class AIState*> _StateMap;
	// AI의 현재 상태
	class AIState* _CurrentState;
};