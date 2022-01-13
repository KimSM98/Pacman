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
	// 현재 이동 방향이 None이거나 이동할 노드에 도착했으면 이동할 방향 찾기
	Direction currentDirection = _MoveComp->GetDirection();
	if (currentDirection == Direction::None || _MoveComp->GetHasReached())
	{
		Direction next = GetRandomMovableDirection();
		SetDirection(next);
	}
}

void GhostAIPatrol::OnEnter()
{
	// 현재 노드에서 이동 가능한 노드를 찾아서 이동한다.
	Direction next = GetRandomMovableDirection();
	SetDirection(next);
}

Direction GhostAIPatrol::GetRandomMovableDirection()
{
	// 현재 노드에서 이동 가능한 노드를 찾는다.
	Node* currentNode = _MoveComp->GetCurrentNode();
	std::unordered_map<Direction, Node*> adjNodes = currentNode->GetAdjNodes();

	Direction currentDir = _MoveComp->GetDirection();

	std::vector<Direction> movableDirection;
	for (auto n : adjNodes)
	{
		if (n.first == Direction::None) continue;
		
		// 현재 방향과 비교해서 반대 방향은 랜덤 방향에 포함하지 않는다.
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

	// 이동 가능한 방향이 없으면
	if (movableDirection.size() < 1)
	{
		return Direction::None;
	}

	// 랜덤으로 방향 정하기
	int randNum = rand() % movableDirection.size();

	return movableDirection[randNum];
}

void GhostAIPatrol::OnExit()
{

}

void GhostAIDeath::Update(float deltaTime)
{
	t += deltaTime;

	// 1이 넘으면 Patrol로 변경
	if (t > 1.f)
	{
		_Owner->ChangeState("Patrol");
		return;
	}

	// 초기 위치로 돌아간다.
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
	// Target의 위치와 몇 이상 멀어지면 Patrol로 바뀐다.
	Vector2 targetPos = _Target->GetPosition();
	Vector2 currentPos = _MoveComp->GetCurrentNode()->GetPos();

	float distance = (targetPos - currentPos).Length();

	if (distance > _ChaseDistance || _TimeSinceCahsing > _MaxChasingTime)
	{
		_Owner->ChangeState("Patrol");
		return;
	}

	_TimeSinceCahsing += deltaTime;

	// Target의 위치와 가까운 노드로 이동한다.
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
	// Target과 거리 비교
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
