#include "AIComponent.h"
#include "AIState.h"
#include <SDL_log.h>

AIComponent::AIComponent(Actor* owner)
	: Component(owner)
	, _CurrentState(nullptr)
{}

void AIComponent::RegisterState(AIState* state)
{
	_StateMap.emplace(state->GetName(), state);
}

std::string AIComponent::GetCurrecntState()
{
	return _CurrentState->GetName();
}

void AIComponent::Update(float deltaTime)
{
	if (_CurrentState)
	{
		_CurrentState->Update(deltaTime);
	}
}

void AIComponent::ChangeState(const std::string& name)
{
	// ���� ���¸� �������´�.
	if (_CurrentState)
	{
		_CurrentState->OnExit();
	}

	// �ʿ��� ���ο� ���¸� ã�´�.
	auto iter = _StateMap.find(name);
	if (iter != _StateMap.end())
	{
		_CurrentState = iter->second;
		// ���ο� ���·� ����
		_CurrentState->OnEnter();
	}
	else
	{
		SDL_Log("Could not find AIState %s in state map", name.c_str());
		_CurrentState = nullptr;
	}
}