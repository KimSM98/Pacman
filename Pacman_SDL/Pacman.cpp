#include "Pacman.h"
#include "Game.h"
#include "AnimSpriteSheetComponent.h"
#include "PacmanInputComponent.h"
#include "Node.h"

Pacman::Pacman(Game* game)
	: Actor(game)
	, _AnimSprSheetComp(nullptr)
	, _CurrentNode(nullptr)
	, _NextNode(nullptr)
{
	/*
	_AnimSprSheetComp = new AnimSpriteSheetComponent(this);
	_AnimSprSheetComp->SetTexture(game->GetTexture("Assets/PlayerSpriteSheet.png"));

	game->GetSpriteSheetLib()->LoadSpriteSheet("Assets/PlayerSpriteSheet.png", 32);
	//game->GetSpriteSheetLib()->GetSpriteSheetClips("Assets/PlayerSpriteSheet.png");
	_AnimSprSheetComp->SetAnimClips(game->GetSpriteSheetLib()->GetSpriteSheetClips("Assets/PlayerSpriteSheet.png"));
	
	std::map<std::string, AnimSpriteSheetComponent::AnimationStates> animMap;

	AnimSpriteSheetComponent::AnimationStates anim = { 0, 0, true };
	// Default animation
	animMap["Default"] = anim;

	// Walking animation
	anim = { 1,2, false };
	animMap["Walking"] = anim;

	_AnimSprSheetComp->SetAnimations(animMap);
	_AnimSprSheetComp->SetCurrentAnimation("Default");
	*/

	/*********************
	InputComponent Setting
	**********************/
	inputComp = new PacmanInputComponent(this);
	inputComp->SetUpKey(SDL_SCANCODE_W);
	inputComp->SetDownKey(SDL_SCANCODE_S);
	inputComp->SetLeftKey(SDL_SCANCODE_A);
	inputComp->SetRightKey(SDL_SCANCODE_D);

	inputComp->SetMaxDownSpeed(150.f);
	inputComp->SetMaxRightSpeed(150.f);

}

void Pacman::SetCurrentNode(Node* node)
{
	inputComp->SetCurrentNode(node);
	_CurrentNode = node; 
}
