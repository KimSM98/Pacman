#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
	, _ScrollSpeed(0.f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	for (auto& bg : _BGTextures)
	{
		// x 오프셋 값 업데이트
		bg._Offset.x += _ScrollSpeed * deltaTime;
		//이 텍스처가 화면을 완전히 벗어나면 오프셋 값을 마지막 배경 텍스처의 오른쪽 위치로 초기화한다.
		if (bg._Offset.x <= -_ScreenSize.x)
		{
			bg._Offset.x = (_BGTextures.size() - 1) * _ScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& bg : _BGTextures)
	{
		SDL_Rect r;
		r.w = static_cast<int>(_ScreenSize.x);
		r.h = static_cast<int>(_ScreenSize.y);
		r.x = static_cast<int>(_Owner->GetPosition().x - r.w / 2 + bg._Offset.x);
		r.y = static_cast<int>(_Owner->GetPosition().y - r.h / 2 + bg._Offset.y);

		SDL_RenderCopy(renderer, bg._Texture, nullptr, &r);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;

	for (auto tex : textures)
	{
		BGTexture temp;
		temp._Texture = tex;
		// 각 텍스처의 오프셋은 화면 너비 * count다.
		temp._Offset.x = count * _ScreenSize.x;
		temp._Offset.y = 0;

		_BGTextures.emplace_back(temp);
		count++;
	}
}