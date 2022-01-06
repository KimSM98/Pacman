#pragma once
#include "Component.h"
#include "Math.h"
#include "SDL.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(class Actor* owner);
	~CollisionComponent();

	const Vector2& GetPosition() const;
	
	void SetActiveDrawing(bool val) { _IsDrawing = val; }
	virtual void DrawCollider(SDL_Renderer* renderer) {};

protected:
	bool _IsDrawing = false;
};

bool Intersect(const class BoxComponent& a, const class BoxComponent& b);
bool Intersect(const class CircleComponent& a, const class CircleComponent& b);
bool Intersect(const class BoxComponent& a, const class CircleComponent& b);
