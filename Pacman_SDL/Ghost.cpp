#include "Ghost.h"
#include "Game.h"
#include "PacmanInputComponent.h"
#include "GhostAI.h"
#include "AIComponent.h"
#include "CircleComponent.h"
#include "AnimSpriteSheetComponent.h"

Ghost::Ghost(Game* game)
	: Actor(game)
	, _AnimSprSheetComp(nullptr)
	, _AIComp(nullptr)
	, _MoveComp(nullptr)
	, _Target(nullptr)
{
	// Add to game
	game->AddGhosts(this);

	//// Asset폴더에서 스프라이트 시트 불러오기
	//game->GetSpriteSheetLib()->LoadSpriteSheet("Assets/Ghost_Red.png", 32);

	//// 애니메이션 컴포넌트 초기화
	//AnimSpriteSheetComponent* animSprSheetComp = new AnimSpriteSheetComponent(this);
	//animSprSheetComp->SetClip(game->GetSpriteSheetLib()->GetClip("Assets/Ghost_Red.png", 0, animSprSheetComp));
	//animSprSheetComp->SetAnimClips(game->GetSpriteSheetLib()->GetSpriteSheetClips("Assets/Ghost_Red.png"));
	//
	//// 애니메이션 설정
	//std::map<std::string, AnimSpriteSheetComponent::AnimationStates> animMap;
	//AnimSpriteSheetComponent::AnimationStates anim = { 0, 7, true };
	//animMap["Default"] = anim;

	//// 애니메이션 컴포넌트에 애니메이션 추가
	//animSprSheetComp->SetAnimations(animMap);
	//animSprSheetComp->SetCurrentAnimation("Default");
	//animSprSheetComp->SetAnimFPS(8.f);

	// Collider
	_CircleComp = new CircleComponent(this);
	game->AddColliders(_CircleComp);
	_CircleComp->SetActiveDrawing(true);
	_CircleComp->SetRadius(15.f);
}

Ghost::~Ghost()
{
	GetGame()->RemoveGhost(this);
}

void Ghost::UpdateActor(float deltaTime)
{
	// Target이 nullptr이 아니면 Chase 상태를 위해 체크한다.
	if (_Target != nullptr)
	{
		// Compare distance with Target
		Vector2 targetPos = _Target->GetPosition();
		Vector2 currentPos = _MoveComp->GetCurrentNode()->GetPos();

		float distance = (targetPos - currentPos).Length();

		if (distance < 96.f)
		{
			_AIComp->ChangeState("Chase");
		}
	}
}

void Ghost::InitByNode(Node* node)
{
	if (node == nullptr) return;

	Vector2 nodePos = node->GetPos();
	_InitialPos = nodePos;
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
}

void Ghost::ActiveChaseAI(Actor* target)
{
	_Target = target;

	GhostAIChase* chaseAI = new GhostAIChase(_AIComp, _Target);
	chaseAI->SetPacmanMoveComponent(_MoveComp);

	_AIComp->RegisterState(chaseAI);
}
