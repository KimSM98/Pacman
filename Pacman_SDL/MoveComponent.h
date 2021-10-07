#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	// ���� ������Ʈ�ǵ��� ���� �������� ����
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return _AngularSpeed; }
	float GetForwardSpeed() const { return _ForwardSpeed; }
	void SetAngularSpeed(float speed) { _AngularSpeed = speed; }
	void SetForwardSpeed(float speed) { _ForwardSpeed = speed; }

private:
	// ȸ���� ����(�ʴ� ����)
	float _AngularSpeed;
	// ���� �̵��� ����(�ʴ� ����)
	float _ForwardSpeed;
};
