#include "CircleComponent.h"
#include "Actor.h"

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