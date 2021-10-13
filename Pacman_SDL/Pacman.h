#pragma once
#include "Actor.h"
#include <iostream>
class Pacman : public Actor
{
public:
	Pacman(class Game* game);

	void SetCurrentNode(class Node* node);

private:
	class AnimSpriteSheetComponent* _AnimSprSheetComp;
	class PacmanInputComponent* inputComp;

	// �׷������� ����� ������ �޾ƿ�(�̵�����)
	// ���� ��� -> ���� ���
	class Node* _CurrentNode;
	class Node* _NextNode;

	// �̵� ����
	std::pair<int, int> _MovingRangeX; // (min,max)
	std::pair<int, int> _MovingRangeY; // (min,max)	
};
