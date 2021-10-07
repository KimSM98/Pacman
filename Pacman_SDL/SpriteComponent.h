#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Component.h"

class SpriteComponent : public Component
{
public:
	// drawOrder가 낮을 수록 더 뒤쪽에서 그린다.
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);

	virtual void SetTexture(SDL_Texture* texture);
	void SetFlip(SDL_RendererFlip flipStatus) { _RenderFlip = flipStatus; }
	void SetClip(SDL_Rect* rect);
	void SetWidth(int width) { _TexWidth = width; }
	void SetHeight(int height) { _TexHeight = height; }


	SDL_Texture* GetTexture() const { return _Texture; }
	int GetDrawOrder() const { return _DrawOrder; }
	int GetTexWidth() const { return _TexWidth; }
	int GetTexHeight() const { return _TexHeight; }

private:
	SDL_Texture* _Texture;
	SDL_RendererFlip _RenderFlip;
	SDL_Rect* _Clip;
	
	int _DrawOrder;
	int _TexWidth;
	int _TexHeight;
};