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
	Direction GetDirection() const { return _Direction; }

	void IncreaseT(float val);
	void DecreaseT(float val);

	void MoveToNext();
	void MoveToPrevious();

private:
	Node* FindNode(Direction d);

	Node* _CurrentNode;
	Node* _NextNode;
	Node* _ReservedNextNode;

	// Reboot
	void Move(float deltaTime);

	Vector2 lerp(Vector2 currecntPos, Vector2 destPos, float t);
	float t = 0.f;
	Direction _Direction = Direction::None;
	Direction _ReservedDirection = Direction::None;
	
	bool hasReachedEnd = false;

	float _DirVal = 0.f;
};
