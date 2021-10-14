#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	// 먼저 업데이트되도록 갱신 순서값을 낮춤
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return _AngularSpeed; }
	float GetForwardSpeed() const { return _ForwardSpeed; }
	float GetRightSpeed() const { return _RightSpeed; }
	float GetDownSpeed() const { return _DownSpeed; }

	void SetAngularSpeed(float speed) { _AngularSpeed = speed; }
	void SetForwardSpeed(float speed) { _ForwardSpeed = speed; }
	void SetRightSpeed(float speed) { _RightSpeed = speed; }
	void SetDownSpeed(float speed) { _DownSpeed = speed; }

private:
	// 회전을 제어(초당 라디안)
	float _AngularSpeed;
	// 전방 이동을 제어(초당 단위)
	float _ForwardSpeed;

	float _RightSpeed;

	float _DownSpeed;
};
