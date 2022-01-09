#pragma once
#include "MoveComponent.h"
#include <utility>
#include "Node.h"
#include "Actor.h"

class PacmanMoveComponent :public MoveComponent
{
public:
	PacmanMoveComponent(class Actor* owner, int updateOrder = 10);
	
	void Update(float deltaTime) override;

	void SetCurrentNode(Node* node) { _CurrentNode = node; }
	bool SetNextNode(Direction d);
	void SetMoveSpeed(float val) { _MoveSpeed = val; }
	void SetPosition(Vector2 pos);
	void InitializeDirection() { _Direction = Direction::None; }

	Direction GetDirection() const { return _Direction; }
	Node* GetCurrentNode() const { return _CurrentNode; }
	bool GetHasReached() const { return hasReachedEnd;	}
	Vector2 GetCurrentPos() const { return _Owner->GetPosition(); }

	void MoveToNext();
	void MoveToPrevious();
	Vector2 lerp(Vector2 currecntPos, Vector2 destPos, float t);

private:
	Node* FindNode(Direction d);

	Node* _CurrentNode;
	Node* _NextNode;

	void Move(float deltaTime);
	
	float t = 0.f;
	// ���� �̵� ����
	Direction _Direction = Direction::None;
	Direction _ReservedDirection = Direction::None;
	// ��忡 ���� �ߴ���
	bool hasReachedEnd = false;
	// �̵� ����. 0: ������� ���ư�, 2: �������� ��
	float _DirVal = 1.f;
	float _MoveSpeed = 1.f;

	Actor* _Owner;
};
