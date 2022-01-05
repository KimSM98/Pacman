#pragma once
#include "CollisionComponent.h"
#include "Math.h"

class CircleComponent : public CollisionComponent
{
public:
	CircleComponent(class Actor* owner);

	void SetRadius(float radius) { _Radius = radius; }
	float GetRadius() const;
	const Vector2& GetCenter() const;

	void DrawCollider(SDL_Renderer* renderer) override;

private:
	float _Radius;
};