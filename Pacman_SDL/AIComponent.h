#pragma once
#include "Component.h"
#include <unordered_map>

class AIComponent : public Component
{
public:
	AIComponent(class Actor* owner);

	void Update(float deltaTime) override;
	void ChangeState(const std::string& name);
	// AIState�� �ʿ� �߰��Ѵ�.
	void RegisterState(class AIState* state);
	
	std::string GetCurrecntState();
private:
	// ������ �̸�, AIState ��ü�� ����
	std::unordered_map<std::string, class AIState*> _StateMap;
	// AI�� ���� ����
	class AIState* _CurrentState;
};