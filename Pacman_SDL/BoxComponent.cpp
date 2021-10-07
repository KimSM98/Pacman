#include "BoxComponent.h"
#include "Actor.h"

BoxComponent::BoxComponent(Actor* owner)
	: CollisionComponent(owner)
	, _W(0.f)
	, _H(0.f)
{
}