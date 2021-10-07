#include "AnimSpriteSheetComponent.h"

AnimSpriteSheetComponent::AnimSpriteSheetComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, _CurrentFrame(0.f)
	, _AnimFPS(24.f)
	, _AnimStatus()
	, _Clips(nullptr)
{
}

void AnimSpriteSheetComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	// AnimStatus에서 isRecursive가 true이면 계속 반복, false면 한번만 플레이
	if (!_Clips->empty())
	{
		_CurrentFrame += _AnimFPS * deltaTime;
		SetClip((*_Clips)[static_cast<int>(_CurrentFrame)]);
		//SetTexture(_AnimTextures[static_cast<int>(_CurrentFrame)]);

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

void AnimSpriteSheetComponent::SetAnimClips(std::vector<SDL_Rect*>* clips)
{
	_Clips = clips;

	if (!_Clips->empty())
	{
		SetClip((*_Clips)[0]);
	}
}

void AnimSpriteSheetComponent::SetCurrentAnimation(const std::string animName)
{
	if (_CurrentAnimation != animName) // 같은 애니메이션이 계속 input될 때 애니메이션이 초기화되지 않도록 하기 위함.
	{
		_CurrentAnimation = animName;
		_AnimStatus = _Animations[_CurrentAnimation];
		_CurrentFrame = _AnimStatus.start;
	}
}