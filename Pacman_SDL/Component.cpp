#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
	:_Owner(owner), _UpdateOrder(updateOrder)
{
	_Owner->AddComponents(this);
}

Component::~Component()
{
	_Owner->RemoveComponents(this);
}

void Component::Update(float deltaTime)
{
}
