#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <map>
#include <string>

class AnimSpriteComponent : public SpriteComponent
{
public:
	struct AnimationStates
	{
		int start;
		int end;
		bool isRecursive;
	};

	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

	// �����Ӹ��� �ִϸ��̼� ������Ʈ
	void Update(float deltaTime) override;

	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	void SetAnimations(std::map<std::string, AnimationStates>& anims) { _Animations = anims; }

	void SetCurrentAnimation(const std::string animName);
	std::string GetCurrentAnimation() { return _CurrentAnimation; }

	void SetAnimFPS(float fps) { _AnimFPS = fps; }
	float GetAnimFPS() const { return _AnimFPS; }


private:
	std::vector<SDL_Texture*> _AnimTextures;
	std::map<std::string, AnimationStates> _Animations;

	AnimationStates _AnimStatus;
	std::string _CurrentAnimation;

	float _CurrentFrame;
	float _AnimFPS; // ���� ���� �ִϸ��̼� ��� �ӵ��� ��������.
};
