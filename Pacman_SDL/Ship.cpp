#include "Ship.h"
#include "Game.h"
#include "AnimSpriteComponent.h"
#include "InputComponent.h"
#include "Laser.h"
#include "BoxComponent.h"
#include "Asteroid.h"

Ship::Ship(Game* game)
	: Actor(game)
	, _LaserCoolDown(0.0f)
{
	_SpriteComponent = new SpriteComponent(this, 150);
	_SpriteComponent->SetTexture(game->GetTexture("Assets/Ship.png"));

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

	_BoxComponent = new BoxComponent(this);
	_BoxComponent->SetSize(_SpriteComponent->GetTexWidth(), _SpriteComponent->GetTexHeight());
}

void Ship::UpdateActor(float deltaTime)
{
	_LaserCoolDown -= deltaTime;
}

void Ship::ActorInput(const uint8_t* keyState)
{
	_SpriteComponent->SetTexture(GetGame()->GetTexture("Assets/Ship.png"));

	if (keyState[SDL_SCANCODE_SPACE] && _LaserCoolDown <= 0.f)
	{
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());
		_LaserCoolDown = 0.5f;
	}
	if (keyState[SDL_SCANCODE_W])
	{
		_SpriteComponent->SetTexture(GetGame()->GetTexture("Assets/ShipWithThrust.png"));
	}

	// Collision
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*_BoxComponent, *(ast->GetCircle())))
		{
			SetState(EDead);
			ast->SetState(EDead);
			break;
		}
	}
}

//void Ship::ProcessKeyboard(const uint8_t* state)
//{
//	_RightSpeed = 0.f;
//	_DownSpeed = 0.f;
//
//	_SpriteComponent->SetTexture(GetGame()->GetTexture("Assets/Ship.png"));
//
//	if (state[SDL_SCANCODE_D])
//	{
//		_RightSpeed += 250.f;
//	}
//	if (state[SDL_SCANCODE_A])
//	{
//		_RightSpeed -= 250.f;
//	}
//	if (state[SDL_SCANCODE_S])
//	{
//		_DownSpeed += 300.f;
//	}
//	if (state[SDL_SCANCODE_W])
//	{
//		_DownSpeed -= 300.f;
//		_SpriteComponent->SetTexture(GetGame()->GetTexture("Assets/ShipWithThrust.png"));
//	}
//}