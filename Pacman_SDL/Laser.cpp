#include "Laser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Laser::Laser(Game* game)
	: Actor(game)
	, _DeathTimer(1.f)
{
	SpriteComponent* sprComp = new SpriteComponent(this);
	sprComp->SetTexture(game->GetTexture("Assets/Laser.png"));

	MoveComponent* moveComp = new MoveComponent(this);
	moveComp->SetForwardSpeed(800.f);

	_Circle = new CircleComponent(this);
	_Circle->SetRadius(14.f);
}

void Laser::UpdateActor(float deltaTime)
{
	_DeathTimer -= deltaTime;
	if (_DeathTimer <= 0.f)
	{
		SetState(EDead);
	}
	else
	{
		for (auto ast: GetGame()->GetAsteroids())
		{
			if (Intersect(*_Circle, *(ast->GetCircle())))
			{
				SetState(EDead);
				ast->SetState(EDead);
				break;
			}
		}
	}
}