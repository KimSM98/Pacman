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

	// AnimStatus���� isRecursive�� true�̸� ��� �ݺ�, false�� �ѹ��� �÷���
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
	if (_CurrentAnimation != animName) // ���� �ִϸ��̼��� ��� input�� �� �ִϸ��̼��� �ʱ�ȭ���� �ʵ��� �ϱ� ����.
	{
		_CurrentAnimation = animName;
		_AnimStatus = _Animations[_CurrentAnimation];
		_CurrentFrame = _AnimStatus.start;
	}
}