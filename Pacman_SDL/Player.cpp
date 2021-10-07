#include "Player.h"
#include "Game.h"
#include "AnimSpriteSheetComponent.h"

Player::Player(Game* game)
	: Actor(game)
	, _RightSpeed(0.f)
	, _DownSpeed(0.f)
	, _AnimSprSheetComp(nullptr)
	, _CurrentNode(nullptr)
	, _NextNode(nullptr)
{
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
}

