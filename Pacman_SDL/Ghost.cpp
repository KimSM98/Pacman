#include "Ghost.h"
#include "Game.h"
#include "PacmanInputComponent.h"
#include "GhostAI.h"
#include "AIComponent.h"
#include "CircleComponent.h"
#include "AnimSpriteSheetComponent.h"
#include "Pacman.h"

Ghost::Ghost(Game* game)
	: Actor(game)
	, _AnimSprSheetComp(nullptr)
	, _AIComp(nullptr)
	, _MoveComp(nullptr)
	, _Target(nullptr)
{
	// Add to game
	game->AddGhosts(this);

	// Collider
	_CircleComp = new CircleComponent(this);
	game->AddColliders(_CircleComp);
	_CircleComp->SetActiveDrawing(true);
	_CircleComp->SetRadius(15.f);

	// Animation
	_AnimSprSheetComp = new AnimSpriteSheetComponent(this);
	_AnimSprSheetComp->SetClip(game->GetSpriteSheetLib()->GetClip("Assets/Ghosts.png", 0, _AnimSprSheetComp));
	_AnimSprSheetComp->SetAnimClips(game->GetSpriteSheetLib()->GetSpriteSheetClips("Assets/Ghosts.png"));
	_AnimSprSheetComp->SetAnimFPS(8.f);

	AnimSpriteSheetComponent::AnimationStates anim = { 32, 39, true };
	_AnimMap["Death"] = anim;
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

		if (distance < 96.f)
		{
			_AIComp->ChangeState("Chase");
		}
	}

	if (Intersect(*_CircleComp, *pacman->GetCollider()))
	{
		_AIComp->ChangeState("Death");
	}

	// Target이 nullptr이 아니면 Chase 상태를 위해 체크한다.
	//if (_Target != nullptr)
	//{
	//	// Compare distance with Target
	//	Vector2 targetPos = _Target->GetPosition();
	//	Vector2 currentPos = _MoveComp->GetCurrentNode()->GetPos();

	//	float distance = (targetPos - currentPos).Length();

	//	if (distance < 96.f)
	//	{
	//		_AIComp->ChangeState("Chase");
	//	}
	//}
}

void Ghost::InitByNode(Node* node)
{
	if (node == nullptr) return;

	Vector2 nodePos = node->GetPos();
	SetPosition(nodePos);
	
	// MoveComponent
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

	// Death AI
	GhostAIDeath* DeathAI = new GhostAIDeath(_AIComp);
	DeathAI->SetPacmanMoveComponent(_MoveComp);
	DeathAI->SetInitNode(node);
	DeathAI->SetAnimComp(_AnimSprSheetComp);

	_AIComp->RegisterState(DeathAI);
}

void Ghost::ActiveChaseAI(Actor* target)
{
	IsChasing = true;

	_Target = target;

	GhostAIChase* chaseAI = new GhostAIChase(_AIComp, _Target);
	chaseAI->SetPacmanMoveComponent(_MoveComp);

	_AIComp->RegisterState(chaseAI);
}

GhostRed::GhostRed(Game* game)
	: Ghost(game)
{
	//// 애니메이션 설정
	AnimSpriteSheetComponent::AnimationStates anim = { 0, 7, true };
	_AnimMap["Default"] = anim;
	// 애니메이션 컴포넌트에 애니메이션 추가
	_AnimSprSheetComp->SetAnimations(_AnimMap);
	_AnimSprSheetComp->SetCurrentAnimation("Default");
}

GhostBlue::GhostBlue(Game* game)
	: Ghost(game)
{
	//// 애니메이션 설정
	AnimSpriteSheetComponent::AnimationStates anim = { 8, 15, true };
	_AnimMap["Default"] = anim;
	// 애니메이션 컴포넌트에 애니메이션 추가
	_AnimSprSheetComp->SetAnimations(_AnimMap);
	_AnimSprSheetComp->SetCurrentAnimation("Default");
}

GhostPink::GhostPink(Game* game)
	: Ghost(game)
{
	// 애니메이션 설정
	AnimSpriteSheetComponent::AnimationStates anim = { 16, 23, true };
	_AnimMap["Default"] = anim;
	// 애니메이션 컴포넌트에 애니메이션 추가
	_AnimSprSheetComp->SetAnimations(_AnimMap);
	_AnimSprSheetComp->SetCurrentAnimation("Default");
}

GhostOrange::GhostOrange(Game* game)
	: Ghost(game)
{
	// 애니메이션 설정
	AnimSpriteSheetComponent::AnimationStates anim = { 24, 31, true };
	_AnimMap["Default"] = anim;
	// 애니메이션 컴포넌트에 애니메이션 추가
	_AnimSprSheetComp->SetAnimations(_AnimMap);
	_AnimSprSheetComp->SetCurrentAnimation("Default");
}
