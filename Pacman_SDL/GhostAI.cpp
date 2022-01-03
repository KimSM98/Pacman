#include "GhostAI.h"
#include "AIComponent.h"
#include <time.h>
#include "Actor.h"

void GhostAIState::SetDirection(Direction dir)
{
	_MoveComp->SetNextNode(dir);
}

void GhostAIPatrol::Update(float deltaTime)
{
	// ���� �̵� ������ None�̰ų� �̵��� ��忡 ���������� �̵��� ���� ã��
	Direction currentDirection = _MoveComp->GetDirection();
	if (currentDirection == Direction::None || _MoveComp->GetHasReached())
	{
		Direction next = GetRandomMovableDirection();
		SetDirection(next);
	}

	//// Target�� nullptr�� �ƴϸ� Chase ���¸� ���� üũ�Ѵ�.
	//if (_Target != nullptr)
	//{
	//	Vector2 targetPos = _Target->GetPosition();		
	//	Vector2 currentPos = _MoveComp->GetCurrentNode()->GetPos();
	//	
	//	float distance = (targetPos - currentPos).Length();
	//	SDL_Log("d: %f", distance);

	//	if (distance < 64.f)
	//	{
	//		SDL_Log("FOLLOW PLAYER");
	//	}
	//}
	// 
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


Direction GhostAIPatrol::GetRandomMovableDirection()
{
	// ���� ��忡�� �̵� ������ ��带 ã�´�.
	Node* currentNode = _MoveComp->GetCurrentNode();
	std::unordered_map<Direction, Node*> adjNodes = currentNode->GetAdjNodes();

	Direction currentDir = _MoveComp->GetDirection();

	std::vector<Direction> movableDirection;
	for (auto n : adjNodes)
	{
		if (n.first == Direction::None) continue;
		
		// ���� ����� ���ؼ� �ݴ� ������ ���� ���⿡ �������� �ʴ´�.
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
	// Target�� ��ġ�� �� �̻� �־����� Patrol�� �ٲ��.
	Vector2 targetPos = _Target->GetPosition();
	Vector2 currentPos = _MoveComp->GetCurrentNode()->GetPos();

	float distance = (targetPos - currentPos).Length();
	//SDL_Log("d: %f", distance);

	if (distance > 64.f || _TimeSinceCahsing > _MaxChasingTime)
	{
		//SDL_Log("DON'T FOLLOW PLAYER");
		_Owner->ChangeState("Patrol");
		return;
	}

	_TimeSinceCahsing += deltaTime;

	// Target�� ��ġ�� ����� ���� �̵��Ѵ�.
	Direction dir = GetCloseNodeToTarget();
	SetDirection(dir);
}

void GhostAIChase::OnEnter()
{
	_TimeSinceCahsing = 0.f;
}

void GhostAIChase::OnExit()
{

}

Direction GhostAIChase::GetCloseNodeToTarget()
{
	Vector2 targetPos = _Target->GetPosition();

	Node* currentNode = _MoveComp->GetCurrentNode();
	// Target�� �Ÿ� ��
	std::pair<Direction, Node*> closestNode;
	float shortestDistance = Math::Infinity;
	for (auto adj : currentNode->GetAdjNodes())
	{
		if (adj.first == Direction::None) continue;

		Vector2 adjToTarget = targetPos - adj.second->GetPos();
		float distance = adjToTarget.Length();
		if (distance < shortestDistance)
		{
			shortestDistance = distance;
			closestNode = adj;
		}
	}

	return closestNode.first;
}
