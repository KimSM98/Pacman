#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxForwardSpeed() const { return _MaxForwardSpeed; }
	float Get_MaxAngularSpeed() const { return _MaxAngularSpeed; }
	int GetForwardKey() const { return _ForwardKey; }
	int GetBackKey() const { return _BackKey; }
	int GetClockwiseKey() const { return _ClockwiseKey; }
	int GetCounterClockwiseKey() const { return _CounterClockwiseKey; }

	void SetMaxForwardSpeed(float speed) { _MaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { _MaxAngularSpeed = speed; }
	void SetForwardKey(int key) { _ForwardKey = key; }
	void SetBackKey(int key) { _BackKey = key; }
	void SetClockwiseKey(int key) { _ClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { _CounterClockwiseKey = key; }
	
private:
	// �ִ� ���� �ӵ� / �ִ� �� �ӵ�
	float _MaxForwardSpeed;
	float _MaxAngularSpeed;
	// ���� �� ������ ���� Ű
	int _ForwardKey;
	int _BackKey;
	// �� ��� ���� Ű
	int _ClockwiseKey;
	int _CounterClockwiseKey;
};
