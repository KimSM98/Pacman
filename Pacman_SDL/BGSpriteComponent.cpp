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
		// x ������ �� ������Ʈ
		bg._Offset.x += _ScrollSpeed * deltaTime;
		//�� �ؽ�ó�� ȭ���� ������ ����� ������ ���� ������ ��� �ؽ�ó�� ������ ��ġ�� �ʱ�ȭ�Ѵ�.
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
		// �� �ؽ�ó�� �������� ȭ�� �ʺ� * count��.
		temp._Offset.x = count * _ScreenSize.x;
		temp._Offset.y = 0;

		_BGTextures.emplace_back(temp);
		count++;
	}
}