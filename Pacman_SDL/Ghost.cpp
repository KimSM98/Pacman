#include "Ghost.h"
#include "Game.h"
#include "PacmanInputComponent.h"
#include "GhostAI.h"
#include "AIComponent.h"

Ghost::Ghost(Game* game)
	: Actor(game)
	, _AnimSprSheetComp(nullptr)
	, _AIComp(nullptr)
	, _MoveComp(nullptr)
	, _Target(nullptr)
{
	game->GetSpriteSheetLib()->LoadSpriteSheet("Assets/Ghost_Red.png", 32);

	SpriteComponent* sprComp = new SpriteComponent(this, 99);
	sprComp->SetClip(game->GetSpriteSheetLib()->GetClip("Assets/Ghost_Red.png", 7, sprComp));
}

void Ghost::UpdateActor(float deltaTime)
{
	// Target이 nullptr이 아니면 Chase 상태를 위해 체크한다.
	if (_Target != nullptr)
	{
		Vector2 targetPos = _Target->GetPosition();
		Vector2 currentPos = _MoveComp->GetCurrentNode()->GetPos();

		float distance = (targetPos - currentPos).Length();
		//SDL_Log("d: %f", distance);

		if (distance < 64.f)
		{
			//SDL_Log("FOLLOW PLAYER");
			_AIComp->ChangeState("Chase");
		}
	}
}

void Ghost::SetPositionByNode(Node* node)
{
	Vector2 nodePos = node->GetPos();
	_InitialPos = nodePos;
	SetPosition(nodePos);
	
	_MoveComp = new PacmanMoveComponent(this);
	_MoveComp->SetCurrentNode(node);
	_MoveComp->SetMoveSpeed(5.5f);

	// AI Component
	_AIComp = new AIComponent(this);
	// Patrol AI
	GhostAIPatrol* patrolAI = new GhostAIPatrol(_AIComp);
	patrolAI->SetPacmanMoveComponent(_MoveComp);
	// AI 등록
	_AIComp->RegisterState(patrolAI);
	_AIComp->ChangeState("Patrol");
}

void Ghost::ActiveChaseAI(Actor* target)
{
	_Target = target;

	GhostAIChase* chaseAI = new GhostAIChase(_AIComp, _Target);
	chaseAI->SetPacmanMoveComponent(_MoveComp);

	_AIComp->RegisterState(chaseAI);
}
