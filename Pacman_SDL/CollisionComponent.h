#pragma once
#include "Component.h"
#include "Math.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(class Actor* owner);

	const Vector2& GetPosition() const;
};

bool Intersect(const class BoxComponent& a, const class BoxComponent& b);
bool Intersect(const class CircleComponent& a, const class CircleComponent& b);
bool Intersect(const class BoxComponent& a, const class CircleComponent& b);
