#include "Character.h"
#include "Game.h"
#include "AnimSpriteComponent.h"
#include "InputComponent.h"
#include <map>

Character::Character(Game* game)
	: Actor(game)
	, _RightSpeed(0.f)
	, _DownSpeed(0.f)
{
	_AnimSprComp = new AnimSpriteComponent(this);

	/*************************
	Animation Textures Setting
	**************************/
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Character00.png"),
		game->GetTexture("Assets/Character01.png"),
		game->GetTexture("Assets/Character02.png"),
		game->GetTexture("Assets/Character03.png"),
		game->GetTexture("Assets/Character04.png"),
		game->GetTexture("Assets/Character05.png"),
		game->GetTexture("Assets/Character06.png"),
		game->GetTexture("Assets/Character07.png"),
		game->GetTexture("Assets/Character08.png"),
		game->GetTexture("Assets/Character09.png"),
		game->GetTexture("Assets/Character10.png"),
		game->GetTexture("Assets/Character11.png"),
		game->GetTexture("Assets/Character12.png"),
		game->GetTexture("Assets/Character13.png"),
		game->GetTexture("Assets/Character14.png"),
		game->GetTexture("Assets/Character15.png"),
		game->GetTexture("Assets/Character16.png"),
		game->GetTexture("Assets/Character17.png"),
		game->GetTexture("Assets/Character18.png"),
	};

	_AnimSprComp->SetAnimTextures(anims);

	/****************
	Animation Setting
	*****************/
	std::map<std::string, AnimSpriteComponent::AnimationStates> animMap;

	AnimSpriteComponent::AnimationStates anim = { 0, 0, true };
	// Default animation
	animMap["Default"] = anim;

	// Walking animation
	anim = { 1,6, false };
	animMap["Walking"] = anim;

	// Jumping animation
	anim = { 7, 15, false };
	animMap["Jumping"] = anim;

	// Punch animation
	anim = { 16, 18, false };
	animMap["Punch"] = anim;
	
	_AnimSprComp->SetAnimations(animMap);
	_AnimSprComp->SetCurrentAnimation("Default");

	/*********************
	InputComponent Setting
	**********************/
	InputComponent* inputComp = new InputComponent(this);
	inputComp->SetForwardKey(SDL_SCANCODE_W);
	inputComp->SetBackKey(SDL_SCANCODE_S);
	inputComp->SetClockwiseKey(SDL_SCANCODE_A);
	inputComp->SetCounterClockwiseKey(SDL_SCANCODE_D);
	inputComp->SetMaxForwardSpeed(300.0f);
	inputComp->SetMaxAngularSpeed(Math::TwoPi);
}

void Character::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 pos = GetPosition();
	pos.x += _RightSpeed * deltaTime;
	pos.y += _DownSpeed * deltaTime;

	SetPosition(pos);
}

void Character::ProcessKeyboard(const uint8_t* state)
{
	_RightSpeed = 0.f;
	_DownSpeed = 0.f;

	if (state[SDL_SCANCODE_D])
	{
		_AnimSprComp->SetCurrentAnimation("Walking");
		_AnimSprComp->SetFlip(SDL_FLIP_NONE);

		_RightSpeed += 250.f;
	}
	if (state[SDL_SCANCODE_A])
	{
		_AnimSprComp->SetCurrentAnimation("Walking");
		_AnimSprComp->SetFlip(SDL_FLIP_HORIZONTAL);

		_RightSpeed -= 250.f;
	}
	if (state[SDL_SCANCODE_S])
	{
		_DownSpeed += 300.f;
	}
	if (state[SDL_SCANCODE_W])
	{
		_DownSpeed -= 300.f;
	}

	// Jump
	if (state[SDL_SCANCODE_SPACE])
	{
		_AnimSprComp->SetCurrentAnimation("Jumping");
	}
	// Attack
	if (state[SDL_SCANCODE_K])
	{
		_AnimSprComp->SetCurrentAnimation("Punch");
	}
}
