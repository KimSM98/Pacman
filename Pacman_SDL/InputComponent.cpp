#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(Actor* owner)
	: MoveComponent(owner)
	, _ForwardKey(0)
	, _BackKey(0)
	, _ClockwiseKey(0)
	, _CounterClockwiseKey(0)
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// MoveComponent�� ���� ���� �ӵ� ���
	float forwardSpeed = 0.f;
	if (keyState[_ForwardKey])
	{
		forwardSpeed += _MaxForwardSpeed;
	}
	if (keyState[_BackKey])
	{
		forwardSpeed -= _MaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	// MoveComponent�� ���� �� �ӵ� ���
	float angularSpeed = 0.f;
	if (keyState[_ClockwiseKey])
	{
		angularSpeed += _MaxAngularSpeed;
	}
	if (keyState[_CounterClockwiseKey])
	{
		angularSpeed -= _MaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}