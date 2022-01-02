#include "Pacman.h"
#include "Game.h"
#include "AnimSpriteSheetComponent.h"
#include "PacmanInputComponent.h"
#include "Node.h"

Pacman::Pacman(Game* game)
	: Actor(game)
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

	// Add SpriteComponent to Pacman
	SpriteComponent* sprComp = new SpriteComponent(this);
	sprComp->SetClip(game->GetSpriteSheetLib()->GetClip("Assets/PlayerSpriteSheet.png", 0, sprComp));

	/*********************
	InputComponent Setting
	**********************/
	PacmanInputComponent* inputComp = new PacmanInputComponent(this);
	inputComp->SetUpKey(SDL_SCANCODE_W);
	inputComp->SetDownKey(SDL_SCANCODE_S);
	inputComp->SetLeftKey(SDL_SCANCODE_A);
	inputComp->SetRightKey(SDL_SCANCODE_D);
	inputComp->SetMoveSpeed(6.f);

	// Set Pacman position
	Node* node = game->GetGraph()->GetNode(1, 6);
	if (node != nullptr)
	{
		Vector2 nodePos = node->GetPos();
		SetPosition(nodePos);
		inputComp->SetCurrentNode(node);
	}
}
