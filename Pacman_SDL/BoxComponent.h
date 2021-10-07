#pragma once
#include "CollisionComponent.h"

class BoxComponent : public CollisionComponent
{
public:
	BoxComponent(class Actor* owner);

	void SetSize(int w, int h) { _W = w, _H = h; }

	float GetWidth() const { return _W; }
	float GetHeight() const { return _H; }

private:
	float _W;
	float _H;
};
