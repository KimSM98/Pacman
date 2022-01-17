#include "Pacman.h"
#include "Game.h"
#include "AnimSpriteSheetComponent.h"
#include "PacmanInputComponent.h"
#include "Node.h"
#include "CircleComponent.h"
#include "Ghost.h"

Pacman::Pacman(Game* game, Node* node)
	: Actor(game)
{
	InitAnimComp();
	InitInputComp();
	InitCollider();

	SetPositionByNode(node);
}

void Pacman::InitAnimComp()
{
	_animSprSheetComp = new AnimSpriteSheetComponent(this);
	_animSprSheetComp->SetClip(GetGame()->GetSpriteSheetLib()->GetClip("Assets/PlayerSpriteSheet.png", 0, _animSprSheetComp));
	_animSprSheetComp->SetAnimClips(GetGame()->GetSpriteSheetLib()->GetSpriteSheetClips("Assets/PlayerSpriteSheet.png"));

	// �ִϸ��̼� ����
	std::map<std::string, AnimSpriteSheetComponent::AnimationStates> animMap;
	// �ִϸ��̼� ������ ����
	AnimSpriteSheetComponent::AnimationStates anim = { 0, 0, true };
	animMap["Default"] = anim;

	anim = { 0, 2, true };
	animMap["Run"] = anim;

	// �ִϸ��̼� ������Ʈ�� �ִϸ��̼� ���� �߰�
	_animSprSheetComp->SetAnimations(animMap);
	_animSprSheetComp->SetCurrentAnimation("Default");
	_animSprSheetComp->SetAnimFPS(12.f);
}

void Pacman::InitInputComp()
{
	_InputComp = new PacmanInputComponent(this);
	_InputComp->SetUpKey(SDL_SCANCODE_W);
	_InputComp->SetDownKey(SDL_SCANCODE_S);
	_InputComp->SetLeftKey(SDL_SCANCODE_A);
	_InputComp->SetRightKey(SDL_SCANCODE_D);
	_InputComp->SetMoveSpeed(6.f);
	// �Է¿� ���� ����� �ִϸ��̼� ������Ʈ ����
	_InputComp->SetAnimComp(_animSprSheetComp);
}

void Pacman::InitCollider()
{
	_CircleComp = new CircleComponent(this);
	// ����
	_CircleComp->SetRadius(20.f);
	_CircleComp->SetActiveDrawing(true);
}

void Pacman::SetPositionByNode(Node* node)
{
	if (node == nullptr) return;

	Vector2 nodePos = node->GetPos();
	SetPosition(nodePos);

	_InputComp->SetCurrentNode(node);
}