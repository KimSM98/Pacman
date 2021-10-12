#pragma once
#include "Actor.h"

class Pacman : public Actor
{
public:
	Pacman(class Game* game);

	void ProcessKeyboard(const uint8_t* state);

private:
	class AnimSpriteSheetComponent* _AnimSprSheetComp;

	// �׷������� ����� ������ �޾ƿ�(�̵�����)

	// ���� ��� -> ���� ���
	class Node* _CurrentNode;
	class Node* _NextNode;

	// �̵� ����
	std::pair<int, int> _MovingRangeX; // (min,max)
	std::pair<int, int> _MovingRangeY; // (min,max)
	
};
