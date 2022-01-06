#include "Pacman.h"
#include "Game.h"
#include "AnimSpriteSheetComponent.h"
#include "PacmanInputComponent.h"
#include "Node.h"
#include "CircleComponent.h"
#include "Ghost.h"

Pacman::Pacman(Game* game)
	: Actor(game)
{
	/***********
	* Animation
	************/
	// 애니메이션 컴포넌트 초기화
	AnimSpriteSheetComponent* animSprSheetComp = new AnimSpriteSheetComponent(this);
	animSprSheetComp->SetClip(game->GetSpriteSheetLib()->GetClip("Assets/PlayerSpriteSheet.png", 0, animSprSheetComp));
	animSprSheetComp->SetAnimClips(game->GetSpriteSheetLib()->GetSpriteSheetClips("Assets/PlayerSpriteSheet.png"));
	
	// 애니메이션 모음
	std::map<std::string, AnimSpriteSheetComponent::AnimationStates> animMap;
	// Default 애니메이션
	AnimSpriteSheetComponent::AnimationStates anim = { 0, 0, true };
	animMap["Default"] = anim;
	// Run 애니메이션
	anim = { 0, 2, true };
	animMap["Run"] = anim;

	// 애니메이션 컴포넌트에 애니메이션 모음 추가
	animSprSheetComp->SetAnimations(animMap);
	animSprSheetComp->SetCurrentAnimation("Default");
	animSprSheetComp->SetAnimFPS(12.f);
	
	/*********************
	InputComponent Setting
	**********************/
	_InputComp = new PacmanInputComponent(this);
	_InputComp->SetUpKey(SDL_SCANCODE_W);
	_InputComp->SetDownKey(SDL_SCANCODE_S);
	_InputComp->SetLeftKey(SDL_SCANCODE_A);
	_InputComp->SetRightKey(SDL_SCANCODE_D);
	_InputComp->SetMoveSpeed(6.f);
	// 입력에 따라 출력할 애니메이션 컴포넌트 설정
	_InputComp->SetAnimComp(animSprSheetComp);
		
	/*********
	* Collider
	**********/
	_CircleComp = new CircleComponent(this);
	// 게임에 콜라이더 추가. 게임에서 콜라이더를 그리기 위한 작업. Game::GenerateOutput()에서 사용.
	game->AddColliders(_CircleComp);
	// 설정
	_CircleComp->SetRadius(20.f);
	_CircleComp->SetActiveDrawing(true);
}

void Pacman::UpdateActor(float deltaTime)
{
	// Ghost와의 충돌 판정
	for (auto ghost : GetGame()->GetGhosts())
	{
		if (Intersect(*_CircleComp, *(ghost->GetCircleComp())))
		{
			// 충돌 했을 때 실행할 내용
		}
	}
}

void Pacman::InitPositionByNode(Node* node)
{
	if (node == nullptr) return;
	
	Vector2 nodePos = node->GetPos();
	SetPosition(nodePos);

	_InputComp->SetCurrentNode(node);
}
