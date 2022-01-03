#include "GhostAI.h"
#include "AIComponent.h"
#include <time.h>

void GhostAIPatrol::Update(float deltaTime)
{
	// ���� �̵� ������ None�̸� �̵��� ���� ã��
	Direction currentDirection = _MoveComp->GetDirection();
	if (currentDirection == Direction::None || _MoveComp->GetHasReached())
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

	// ���� ����� ���ؼ� �ݴ� ������ ���� ���⿡ �������� �ʴ´�.
	Direction currentDir = _MoveComp->GetDirection();

	std::vector<Direction> movableDirection;
	for (auto n : adjNodes)
	{
		if (n.first == Direction::None) continue;
		
		switch (currentDir)
		{
		case Direction::Top:
			if (n.first == Direction::Bottom) continue;
			break;
		case Direction::Bottom:
			if (n.first == Direction::Top) continue;
			break;
		case Direction::Left:
			if (n.first == Direction::Right) continue;
			break;
		case Direction::Right:
			if (n.first == Direction::Left) continue;
			break;
		}

		movableDirection.push_back(n.first);
	}

	// �̵� ������ ������ ������
	if (movableDirection.size() < 1)
	{
		return Direction::None;
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