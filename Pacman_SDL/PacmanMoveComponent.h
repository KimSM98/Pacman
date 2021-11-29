#pragma once
#include "MoveComponent.h"
#include <utility>
#include "Node.h"

class PacmanMoveComponent :public MoveComponent
{
public:
	PacmanMoveComponent(class Actor* owner, int updateOrder = 10);
	
	void Update(float deltaTime) override;

	void SetCurrentNode(class Node* node);
	// bool SetNextNode(Direction d);
	bool SetNextNode(Direction d);
	void SetMoveSpeed(float val) { _MoveSpeed = val; }
	Direction GetDirection() const { return _Direction; }

	void IncreaseT(float val);
	void DecreaseT(float val);

	void MoveToNext();
	void MoveToPrevious();

private:
	Node* FindNode(Direction d);

	Node* _CurrentNode;
	Node* _NextNode;

	// Reboot
	void Move(float deltaTime);

	Vector2 lerp(Vector2 currecntPos, Vector2 destPos, float t);
	float t = 0.f;
	// 현재 이동 방향
	Direction _Direction = Direction::None;
	Direction _ReservedDirection = Direction::None;
	
	bool hasReachedEnd = false;

	float _DirVal = 0.f;
	float _MoveSpeed = 1.f;
};
