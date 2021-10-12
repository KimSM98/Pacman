#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;
	// Get Maxspeed
	float GetMaxForwardSpeed() const { return _MaxForwardSpeed; }
	float GetMaxAngularSpeed() const { return _MaxAngularSpeed; }
	float GetMaxRightSpeed() const { return _MaxRightSpeed; }
	float GetMaxDownSpeed() const { return _MaxDownSpeed; }
	// Get keys
	int GetForwardKey() const { return _ForwardKey; }
	int GetBackKey() const { return _BackKey; }
	int GetLeftKey() const { return _LeftKey; }
	int GetRightKey() const { return _RightKey; }
	int GetUpKey() const { return _UpKey; }
	int GetDownKey() const { return _DownKey; }
	int GetClockwiseKey() const { return _ClockwiseKey; }
	int GetCounterClockwiseKey() const { return _CounterClockwiseKey; }
	// Set max speed
	void SetMaxForwardSpeed(float speed) { _MaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { _MaxAngularSpeed = speed; }
	void SetMaxRightSpeed(float speed) { _MaxRightSpeed = speed; }
	void SetMaxDownSpeed(float speed) { _MaxDownSpeed = speed; }
	// Set keys
	void SetForwardKey(int key) { _ForwardKey = key; }
	void SetBackKey(int key) { _BackKey = key; }
	void SetLeftKey(int key) { _LeftKey = key; }
	void SetRightKey(int key) { _RightKey = key; }
	void SetUpKey(int key) { _UpKey = key; }
	void SetDownKey(int key) { _DownKey = key; }
	void SetClockwiseKey(int key) { _ClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { _CounterClockwiseKey = key; }
	
private:
	// �ִ� ���� �ӵ� / �ִ� �� �ӵ�
	float _MaxForwardSpeed;
	float _MaxAngularSpeed;
	// �¿� �ӵ� / ���� �ӵ�
	float _MaxRightSpeed;
	float _MaxDownSpeed;
	// ���� �� ������ ���� Ű
	int _ForwardKey;
	int _BackKey;
	// �¿� �̵��� ���� Ű
	int _LeftKey;
	int _RightKey;
	// ���� �̵��� ���� Ű
	int _UpKey;
	int _DownKey;
	// �� ��� ���� Ű
	int _ClockwiseKey;
	int _CounterClockwiseKey;
};
