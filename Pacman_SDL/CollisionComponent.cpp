#include "CollisionComponent.h"
#include "Actor.h"
#include "CircleComponent.h"
#include "BoxComponent.h"
#include "Actor.h"
#include "Game.h"

CollisionComponent::CollisionComponent(Actor* owner)
	: Component(owner)
{
	// 게임에 콜라이더 추가. 게임에서 콜라이더를 그리기 위한 작업. Game::GenerateOutput()에서 사용.
	owner->GetGame()->AddCollider(this);
}

CollisionComponent::~CollisionComponent()
{
	_Owner->GetGame()->RemoveCollider(this);
}

const Vector2& CollisionComponent::GetPosition() const
{
	return _Owner->GetPosition();
}

bool Intersect(const BoxComponent& a, const BoxComponent& b)
{
	Vector2 posA = a.GetPosition();
	Vector2 posB = b.GetPosition();

	if (posA.x < posB.x + b.GetWidth() &&
		posA.x + a.GetWidth() > posB.x &&
		posA.y < posB.y + b.GetHeight() &&
		posA.y + a.GetHeight() > posB.y
	)
	{
		return true;
	}

	return false;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	// 거리 제곱값을 계산
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	// 반지름 합의 제곱을 계산
	float radSq = a.GetRadius() + b.GetRadius();
	radSq *= radSq;

	return distSq <= radSq;
}

bool Intersect(const BoxComponent& a, const CircleComponent& c)
{
	Vector2 posA = a.GetPosition();
	Vector2 posC = c.GetCenter();
	posC.x -= c.GetRadius();
	posC.y -= c.GetRadius();
	float sizeC = c.GetRadius() * 2.f;

	if (posA.x < posC.x + sizeC &&
		posA.x + a.GetWidth() > posC.x &&
		posA.y < posC.y + sizeC &&
		posA.y + a.GetHeight() > posC.y
		)
	{
		return true;
	}

	return false;

}