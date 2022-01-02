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

{
	game->GetSpriteSheetLib()->LoadSpriteSheet("Assets/Ghost_Red.png", 32);

	SpriteComponent* sprComp = new SpriteComponent(this, 99);
	sprComp->SetClip(game->GetSpriteSheetLib()->GetClip("Assets/Ghost_Red.png", 7, sprComp));
}

void Ghost::SetPositionByNode(Node* node)
{
	Vector2 nodePos = node->GetPos();
	_InitialPos = nodePos;
	SetPosition(nodePos);
	
	_MoveComp = new PacmanMoveComponent(this);
	_MoveComp->SetCurrentNode(node);
	_MoveComp->SetMoveSpeed(6.f);

	// AI Component
	AIComponent* AIComp = new AIComponent(this);
	// Patrol AI
	GhostAIPatrol* patrolAI = new GhostAIPatrol(AIComp);
	patrolAI->SetPacmanMoveComponent(_MoveComp);
	
	// AI µî·Ï
	AIComp->RegisterState(patrolAI);
	AIComp->ChangeState("Patrol");
}
