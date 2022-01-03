#include "GhostAI.h"
#include "AIComponent.h"
#include <time.h>

void GhostAIPatrol::Update(float deltaTime)
{
	// 현재 이동 방향이 None이면 이동할 방향 찾기
	Direction currentDirection = _MoveComp->GetDirection();
	if (currentDirection == Direction::None || _MoveComp->GetHasReached())
	{
		Direction next = GetRandomMovableDirection();
		SetDirection(next);
	}

	//bool dead = true; // 죽었는지 판단
	//if (dead)
	//{
	//	// AI 컴포넌트에 상태를 변경하라고 알림
	//	_Owner->ChangeState("Death");
	//}
}

void GhostAIPatrol::OnEnter()
{
	// 현재 노드에서 이동 가능한 노드를 찾아서 이동한다.
	Direction next = GetRandomMovableDirection();
	SetDirection(next);

}

void GhostAIPatrol::SetDirection(Direction dir)
{
	_MoveComp->SetNextNode(dir);
}

Direction GhostAIPatrol::GetRandomMovableDirection()
{
	// 현재 노드에서 이동 가능한 노드를 찾는다.
	Node* currentNode = _MoveComp->GetCurrentNode();
	std::unordered_map<Direction, Node*> adjNodes = currentNode->GetAdjNodes();

	// 현재 방향과 비교해서 반대 방향은 랜덤 방향에 포함하지 않는다.
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

	// 이동 가능한 방향이 없으면
	if (movableDirection.size() < 1)
	{
		return Direction::None;
	}

	// 랜덤으로 방향 정하기
	srand(time(NULL));
	int randNum = rand() % movableDirection.size();

	return movableDirection[randNum];
}

void GhostAIPatrol::OnExit()
{

}

void GhostAIDeath::Update(float deltaTime)
{
	// Update 작업

	// 죽으면 초기 위치로 돌아간다.
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