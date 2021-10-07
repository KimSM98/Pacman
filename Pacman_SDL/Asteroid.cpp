#include "Asteroid.h"
#include "Game.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game)
	: Actor(game)
	, _Circle(nullptr)
{
	game->AddAsteroid(this);

	// 랜덤하게 위치와 방향을 초기화한다.
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.f, 768.f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.f);

	_Circle = new CircleComponent(this);
	_Circle->SetRadius(40.f);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}