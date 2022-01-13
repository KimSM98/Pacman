#include "Ghost.h"
#include "Game.h"
#include "PacmanInputComponent.h"
#include "GhostAI.h"
#include "AIComponent.h"
#include "CircleComponent.h"
#include "AnimSpriteSheetComponent.h"
#include "Pacman.h"

Ghost::Ghost(Game* game, Node* node)
	: Actor(game)
	, _AnimSprSheetComp(nullptr)
	, _AIComp(nullptr)
	, _MoveComp(nullptr)
	, _Target(nullptr)
	, _ChaseDistance(96.f)
{
	// Add to game
	game->AddGhosts(this);

	InitCollider();
	InitAnimationComp();
	InitPosition(node);
	InitMoveComp(node);
	InitAIComp(node);
}

Ghost::~Ghost()
{
	GetGame()->RemoveGhost(this);
}

void Ghost::UpdateActor(float deltaTime)
{
	Pacman* pacman = GetGame()->GetPacman();

	if (IsChasing && _AIComp->GetCurrecntState() == "Patrol")
	{
		Vector2 targetPos = pacman->GetPosition();
		Vector2 currentPos = _MoveComp->GetCurrentNode()->GetPos();
		float distance = (targetPos - currentPos).Length();
		if (distance < _ChaseDistance)
		{
			_AIComp->ChangeState("Chase");
		}
	}

	if (Intersect(*_CircleComp, *pacman->GetCollider()))
	{
		_AIComp->ChangeState("Death");
	}
}

void Ghost::InitPosition(Node* node)
{
	if (node == nullptr)
	{
		SDL_Log("Node is Nullptr. Ghost Init failed.");
		return;
	}

	// Initialize position
	Vector2 nodePos = node->GetPos();
	SetPosition(nodePos);
}

void Ghost::InitMoveComp(Node* node)
{
	_MoveComp = new PacmanMoveComponent(this);
	_MoveComp->SetCurrentNode(node);
	_MoveComp->SetMoveSpeed(5.5f);
}

void Ghost::InitAIComp(Node* node)
{
	// AI Component
	_AIComp = new AIComponent(this);

	// Patrol AI
	GhostAIPatrol* patrolAI = new GhostAIPatrol(_AIComp);
	patrolAI->SetPacmanMoveComponent(_MoveComp);

	// AI 등록
	_AIComp->RegisterState(patrolAI);
	_AIComp->ChangeState("Patrol");

	// Death AI
	GhostAIDeath* DeathAI = new GhostAIDeath(_AIComp);
	DeathAI->SetPacmanMoveComponent(_MoveComp);
	DeathAI->SetInitNode(node); // 초기 위치로 돌아가기 위한 설정
	DeathAI->SetAnimComp(_AnimSprSheetComp);

	_AIComp->RegisterState(DeathAI);
}

void Ghost::InitCollider()
{
	_CircleComp = new CircleComponent(this);
	_CircleComp->SetActiveDrawing(true);
	_CircleComp->SetRadius(15.f);
}

void Ghost::InitAnimationComp()
{
	_AnimSprSheetComp = new AnimSpriteSheetComponent(this);
	_AnimSprSheetComp->SetClip(GetGame()->GetSpriteSheetLib()->GetClip("Assets/Ghosts.png", 0, _AnimSprSheetComp));
	_AnimSprSheetComp->SetAnimClips(GetGame()->GetSpriteSheetLib()->GetSpriteSheetClips("Assets/Ghosts.png"));
	_AnimSprSheetComp->SetAnimFPS(8.f);

	AnimSpriteSheetComponent::AnimationStates anim = { 32, 39, true };
	_AnimMap["Death"] = anim;
}

void Ghost::ActiveChaseAI(Actor* target, float distance, float time)
{
	IsChasing = true;
	_Target = target;
	_ChaseDistance = distance;

	// Chase AI 생성
	GhostAIChase* chaseAI = new GhostAIChase(_AIComp, _Target);
	chaseAI->SetPacmanMoveComponent(_MoveComp);
	chaseAI->SetChaseDistance(distance); 
	chaseAI->SetMaxChasingTime(time);

	_AIComp->RegisterState(chaseAI);
}

GhostRed::GhostRed(Game* game, Node* node)
	: Ghost(game, node)
{
	// 애니메이션 설정
	AnimSpriteSheetComponent::AnimationStates anim = { 0, 7, true };
	_AnimMap["Default"] = anim;
	// 애니메이션 컴포넌트에 애니메이션 추가
	_AnimSprSheetComp->SetAnimations(_AnimMap);
	_AnimSprSheetComp->SetCurrentAnimation("Default");
}

GhostBlue::GhostBlue(Game* game, Node* node)
	: Ghost(game, node)
{
	AnimSpriteSheetComponent::AnimationStates anim = { 8, 15, true };
	_AnimMap["Default"] = anim;

	_AnimSprSheetComp->SetAnimations(_AnimMap);
	_AnimSprSheetComp->SetCurrentAnimation("Default");
}

GhostPink::GhostPink(Game* game, Node* node)
	: Ghost(game, node)
{
	AnimSpriteSheetComponent::AnimationStates anim = { 16, 23, true };
	_AnimMap["Default"] = anim;

	_AnimSprSheetComp->SetAnimations(_AnimMap);
	_AnimSprSheetComp->SetCurrentAnimation("Default");
}

GhostOrange::GhostOrange(Game* game, Node* node)
	: Ghost(game, node)
{
	AnimSpriteSheetComponent::AnimationStates anim = { 24, 31, true };
	_AnimMap["Default"] = anim;

	_AnimSprSheetComp->SetAnimations(_AnimMap);
	_AnimSprSheetComp->SetCurrentAnimation("Default");
}

