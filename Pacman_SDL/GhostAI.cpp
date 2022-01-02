#include "GhostAI.h"
#include "AIComponent.h"
#include <time.h>

void GhostAIPatrol::Update(float deltaTime)
{
	// ���� �̵� ������ None�̸� �̵��� ���� ã��
	Direction currentDirection = _MoveComp->GetDirection();
	if (currentDirection == Direction::None)
	{
		Direction next = GetRandomMovableDirection();
		SetDirection(next);
	}

	//bool dead = true; // �׾����� �Ǵ�
	//if (dead)
	//{
	//	// AI ������Ʈ�� ���¸� �����϶�� �˸�
	//	_Owner->ChangeState("Death");
	//}
}

void GhostAIPatrol::OnEnter()
{
	// ���� ��忡�� �̵� ������ ��带 ã�Ƽ� �̵��Ѵ�.
	Direction next = GetRandomMovableDirection();
	SetDirection(next);

}

void GhostAIPatrol::SetDirection(Direction dir)
{
	_MoveComp->SetNextNode(dir);
}

Direction GhostAIPatrol::GetRandomMovableDirection()
{
	// ���� ��忡�� �̵� ������ ��带 ã�´�.
	Node* currentNode = _MoveComp->GetCurrentNode();
	std::unordered_map<Direction, Node*> adjNodes = currentNode->GetAdjNodes();

	std::vector<Direction> movableDirection;
	for (auto n : adjNodes)
	{
		if (n.first == Direction::None) continue;
		movableDirection.push_back(n.first);
	}
	// �������� ���� ���ϱ�
	srand(time(NULL));
	int randNum = rand() % movableDirection.size();

	return movableDirection[randNum];
}

void GhostAIPatrol::OnExit()
{

}

void GhostAIDeath::Update(float deltaTime)
{
	// Update �۾�

	// ������ �ʱ� ��ġ�� ���ư���.
}

void GhostAIDeath::OnEnter()
{
	
}

void GhostAIDeath::OnExit()
{

}

void GhostAIChase::Update(float deltaTime)
{

}

void GhostAIChase::OnEnter()
{

}

void GhostAIChase::OnExit()
{

}