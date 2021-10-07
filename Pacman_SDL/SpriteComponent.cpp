#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, _DrawOrder(drawOrder)
	, _Texture(nullptr)
	, _Clip(nullptr)
	, _TexWidth(0)
	, _TexHeight(0)
	, _RenderFlip(SDL_RendererFlip::SDL_FLIP_NONE)
{
	_Owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	_Owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (_Texture)
	{
		// 그릴 위치에 따라 위치 조정(TOP-LEFT, MIDDLE 등)
		SDL_Rect rect;
		
		rect.w = static_cast<int>(_TexWidth * _Owner->GetScale());
		rect.h = static_cast<int>(_TexHeight * _Owner->GetScale());

		rect.x = static_cast<int>(_Owner->GetPosition().x - rect.w / 2);
		rect.y = static_cast<int>(_Owner->GetPosition().y - rect.h / 2);

		SDL_RenderCopyEx(
			renderer,
			_Texture,
			_Clip,
			&rect,
			-Math::ToDegrees(_Owner->GetRotation()),
			nullptr,
			_RenderFlip
		);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	_Texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &_TexWidth, &_TexHeight);
}

void SpriteComponent::SetClip(SDL_Rect* clip)
{
	_Clip = clip;
}