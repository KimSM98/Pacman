#pragma once
#include <vector>
#include "SpriteComponent.h"
#include "Math.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	// 배경이기 때문에 그리기 순서 값은 낮게 설정
	BGSpriteComponent(Actor* owner, int drawOrder = 10);

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;

	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	void SetScreenSize(const Vector2& size) { _ScreenSize = size; }
	void SetScrollSpeed(float speed) { _ScrollSpeed = speed; }

	float GetScrollSpeed() const { return _ScrollSpeed; }

private:
	struct BGTexture
	{
		SDL_Texture* _Texture;
		Vector2 _Offset;
	};

	std::vector<BGTexture> _BGTextures;
	Vector2 _ScreenSize;
	float _ScrollSpeed;
};