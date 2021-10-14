#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	: Component(owner, updateOrder)
	, _AngularSpeed(0.f)
	, _ForwardSpeed(0.f)
	, _RightSpeed(0.f)
	, _DownSpeed(0.f)
{
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(_AngularSpeed))
	{
		float rotation = _Owner->GetRotation();
		rotation += _AngularSpeed * deltaTime;
		_Owner->SetRotation(rotation);
	}

	if (!Math::NearZero(_ForwardSpeed))
	{
		Vector2 pos = _Owner->GetPosition();
		pos += _Owner->GetForward() * _ForwardSpeed * deltaTime;

		if (pos.x < 0.f) pos.x = 1023.f;
		else if (pos.x > 1024) pos.x = 0.f;
		if (pos.y < 0.f) pos.y = 1023.f;
		else if (pos.y > 1024) pos.y = 1.f;

		_Owner->SetPosition(pos);
	}	

	if (!Math::NearZero(_DownSpeed))
	{
		Vector2 pos = _Owner->GetPosition();
		pos.y += _DownSpeed * deltaTime;

		if (pos.y < 0.f) pos.y = 1023.f;
		else if (pos.y > 1024) pos.y = 1.f;

		_Owner->SetPosition(pos);
	}

	if (!Math::NearZero(_RightSpeed))
	{
		Vector2 pos = _Owner->GetPosition();
		pos += _Owner->GetForward() * _RightSpeed * deltaTime;

		if (pos.x < 0.f) pos.x = 1023.f;
		else if (pos.x > 1024) pos.x = 0.f;

		_Owner->SetPosition(pos);
	}
}