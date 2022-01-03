#pragma once
#include "MoveComponent.h"
#include <utility>
#include "Node.h"

class PacmanMoveComponent :public MoveComponent
{
public:
	PacmanMoveComponent(class Actor* owner, int updateOrder = 10);
	
	void Update(float deltaTime) override;

	void SetCurrentNode(Node* node) { _CurrentNode = node; }
	bool SetNextNode(Direction d);
	void SetMoveSpeed(float val) { _MoveSpeed = val; }
	Direction GetDirection() const { return _Direction; }
	Node* GetCurrentNode() const { return _CurrentNode; }
	bool GetHasReached() const { return hasReachedEnd;	}
	void MoveToNext();
	void MoveToPrevious();

private:
	Node* FindNode(Direction d);

	Node* _CurrentNode;
	Node* _NextNode;

	void Move(float deltaTime);
	Vector2 lerp(Vector2 currecntPos, Vector2 destPos, float t);
	
	float t = 0.f;
	// 현재 이동 방향
	Direction _Direction = Direction::None;
	Direction _ReservedDirection = Direction::None;
	// 노드에 도착 했는지
	bool hasReachedEnd = false;
	// 이동 방향. 0: 출발지로 돌아감, 2: 목적지로 감
	float _DirVal = 1.f;
	float _MoveSpeed = 1.f;

	Actor* _Owner;
};
