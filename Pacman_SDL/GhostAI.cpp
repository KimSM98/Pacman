#include "GhostAI.h"
#include "AIComponent.h"
#include <time.h>
#include "Actor.h"
#include "AnimSpriteSheetComponent.h"

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
	int randNum = rand() % movableDirection.size();

	return movableDirection[randNum];
}

void GhostAIPatrol::OnExit()
{

}

void GhostAIDeath::Update(float deltaTime)
{
	t += deltaTime;

	// 1�� ������ Patrol�� ����
	if (t > 1.f)
	{
		_Owner->ChangeState("Patrol");
		return;
	}

	// �ʱ� ��ġ�� ���ư���.
	Vector2 pos = _MoveComp->lerp(_DeadPos, _InitNode->GetPos(), t);
	_MoveComp->SetPosition(pos);
}

void GhostAIDeath::OnEnter()
{
	t = 0.f;
	_DeadPos = _MoveComp->GetCurrentPos(); 
	_MoveComp->InitializeDirection();
	_AnimComp->SetCurrentAnimation("Death");
}

void GhostAIDeath::OnExit()
{
	_MoveComp->SetCurrentNode(_InitNode);
	_AnimComp->SetCurrentAnimation("Default");
}

void GhostAIDeath::SetAnimComp(AnimSpriteSheetComponent* animComp)
{
	_AnimComp = animComp;
}

void GhostAIChase::Update(float deltaTime)
{
	// Target�� ��ġ�� �� �̻� �־����� Patrol�� �ٲ��.
	Vector2 targetPos = _Target->GetPosition();
	Vector2 currentPos = _MoveComp->GetCurrentNode()->GetPos();

	float distance = (targetPos - currentPos).Length();

	if (distance > _ChaseDistance || _TimeSinceCahsing > _MaxChasingTime)
	{
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
