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
	// �ִϸ��̼� ������Ʈ �ʱ�ȭ
	AnimSpriteSheetComponent* animSprSheetComp = new AnimSpriteSheetComponent(this);
	animSprSheetComp->SetClip(game->GetSpriteSheetLib()->GetClip("Assets/PlayerSpriteSheet.png", 0, animSprSheetComp));
	animSprSheetComp->SetAnimClips(game->GetSpriteSheetLib()->GetSpriteSheetClips("Assets/PlayerSpriteSheet.png"));
	
	// �ִϸ��̼� ����
	std::map<std::string, AnimSpriteSheetComponent::AnimationStates> animMap;
	// Default �ִϸ��̼�
	AnimSpriteSheetComponent::AnimationStates anim = { 0, 0, true };
	animMap["Default"] = anim;
	// Run �ִϸ��̼�
	anim = { 0, 2, true };
	animMap["Run"] = anim;

	// �ִϸ��̼� ������Ʈ�� �ִϸ��̼� ���� �߰�
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
	// �Է¿� ���� ����� �ִϸ��̼� ������Ʈ ����
	_InputComp->SetAnimComp(animSprSheetComp);
		
	/*********
	* Collider
	**********/
	_CircleComp = new CircleComponent(this);
	// ���ӿ� �ݶ��̴� �߰�. ���ӿ��� �ݶ��̴��� �׸��� ���� �۾�. Game::GenerateOutput()���� ���.
	game->AddColliders(_CircleComp);
	// ����
	_CircleComp->SetRadius(20.f);
	_CircleComp->SetActiveDrawing(true);
}

void Pacman::UpdateActor(float deltaTime)
{
	// Ghost���� �浹 ����
	for (auto ghost : GetGame()->GetGhosts())
	{
		if (Intersect(*_CircleComp, *(ghost->GetCircleComp())))
		{
			// �浹 ���� �� ������ ����
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
