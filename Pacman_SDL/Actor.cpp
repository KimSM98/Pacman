#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor(Game* game)
	:_State(EActive)
	, _Position(Vector2())
	, _Scale(1.f)
	, _Rotation(0.f)
	, _Game(game)
{
	_Game->AddActor(this);
}

Actor::~Actor()
{
	_Game->RemoveActor(this);

	while (!_Components.empty())
	{
		delete _Components.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (_State == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : _Components)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (_State == EActive)
	{
		for (auto comp : _Components)
		{
			comp->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::AddComponents(Component* component)
{
	int myOrder = component->GetUpdateOrder();

	auto iter = _Components.begin();
	for (; iter != _Components.end(); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	_Components.insert(iter, component);
}

void Actor::RemoveComponents(Component* component)
{
	auto iter = std::find(_Components.begin(), _Components.end(), component);
	if (iter != _Components.end())
	{
		_Components.erase(iter);
	}
}