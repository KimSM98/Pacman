#include "CircleComponent.h"
#include "Actor.h"
#include "Math.h"

CircleComponent::CircleComponent(Actor* owner)
	: CollisionComponent(owner)
	, _Radius(0.f)
{
}

float CircleComponent::GetRadius() const
{
	return _Owner->GetScale() * _Radius;
}

const Vector2& CircleComponent::GetCenter() const
{
	return _Owner->GetPosition();
}

void CircleComponent::DrawCollider(SDL_Renderer* renderer)
{
	if (!_IsDrawing) return;

	SDL_SetRenderDrawColor(renderer, 125, 255, 0, 255);

	float tick = 2 * Math::Pi / 36.f;

	float prevX = GetCenter().x + Math::Cos(0) * _Radius;
	float prevY = GetCenter().y + Math::Sin(0) * _Radius;	

	for (float theta = 0; theta < 2 * Math::Pi; theta += tick)
	{
		float nextX = GetCenter().x + Math::Cos(theta) * _Radius;
		float nextY = GetCenter().y + Math::Sin(theta) * _Radius;
		SDL_RenderDrawLine(
			renderer,
			prevX,
			prevY,
			nextX,
			nextY
		);

		prevX = nextX;
		prevY = nextY;
	}
}

//bool Intersect(const CircleComponent& a, const CircleComponent& b)
//{
//	// 거리 제곱값을 계산
//	Vector2 diff = a.GetCenter() - b.GetCenter();
//	float distSq = diff.LengthSq();
//
//	// 반지름 합의 제곱을 계산
//	float radSq = a.GetRadius() + b.GetRadius();
//	radSq *= radSq;
//
//	return distSq <= radSq;
//}