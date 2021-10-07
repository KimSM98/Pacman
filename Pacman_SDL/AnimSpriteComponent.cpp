#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, _CurrentFrame(0.f)
	, _AnimFPS(24.f)
	, _AnimStatus()
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	// AnimStatus에서 isRecursive가 true이면 계속 반복, false면 한번만 플레이
	if (_AnimTextures.size() > 0)
	{
		_CurrentFrame += _AnimFPS * deltaTime;
		SetTexture(_AnimTextures[static_cast<int>(_CurrentFrame)]);

		if (_CurrentFrame > _AnimStatus.end)
		{
			if (_AnimStatus.isRecursive)
			{
				_CurrentFrame = _AnimStatus.start;
			}
			else
			{
				SetCurrentAnimation("Default");
			}
		}		
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	_AnimTextures = textures;

	if (_AnimTextures.size() > 0)
	{
		_CurrentFrame = 0.f;
		SetTexture(_AnimTextures[0]);
	}
}

void AnimSpriteComponent::SetCurrentAnimation(const std::string animName)
{ 
	if (_CurrentAnimation != animName) // 같은 애니메이션이 계속 input될 때 애니메이션이 초기화되지 않도록 하기 위함.
	{
		_CurrentAnimation = animName;
		_AnimStatus = _Animations[_CurrentAnimation];
		_CurrentFrame = _AnimStatus.start;
	}
}