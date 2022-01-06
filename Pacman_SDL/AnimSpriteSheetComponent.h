#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <map>
#include <string>

class AnimSpriteSheetComponent : public SpriteComponent
{
public:
	struct AnimationStates
	{
		int start;
		int end;
		bool isRecursive;
	};

	AnimSpriteSheetComponent(class Actor* owner, int drawOrder = 100);

	// �����Ӹ��� �ִϸ��̼� ������Ʈ
	void Update(float deltaTime) override;
	
	void SetTexture(SDL_Texture* tex) { SpriteComponent::SetTexture(tex); }
	void SetAnimClips(std::vector<SDL_Rect*>* clips);
	void SetAnimations(std::map<std::string, AnimationStates>& anims) { _Animations = anims; }

	void SetCurrentAnimation(const std::string animName);
	std::string GetCurrentAnimation() { return _CurrentAnimation; }

	void SetAnimFPS(float fps) { _AnimFPS = fps; }
	float GetAnimFPS() const { return _AnimFPS; }

private:
	std::map<std::string, AnimationStates> _Animations;
	std::vector<SDL_Rect*>* _Clips;

	AnimationStates _AnimStatus;
	std::string _CurrentAnimation;
	float _CurrentFrame;
	float _AnimFPS; // ���� ���� �ִϸ��̼� ��� �ӵ��� ��������.
};
