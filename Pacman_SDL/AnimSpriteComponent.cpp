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

	// AnimStatus���� isRecursive�� true�̸� ��� �ݺ�, false�� �ѹ��� �÷���
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
	if (_CurrentAnimation != animName) // ���� �ִϸ��̼��� ��� input�� �� �ִϸ��̼��� �ʱ�ȭ���� �ʵ��� �ϱ� ����.
	{
		_CurrentAnimation = animName;
		_AnimStatus = _Animations[_CurrentAnimation];
		_CurrentFrame = _AnimStatus.start;
	}
}