#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player(class Game* game);

private:
	float _RightSpeed;
	float _DownSpeed;

	class AnimSpriteSheetComponent* _AnimSprSheetComp;

	// �׷������� ����� ������ �޾ƿ�(�̵�����)

	// ���� ��� -> ���� ���
	class Node* _CurrentNode;
	class Node* _NextNode;

	// �̵� ����
	std::pair<int, int> _MovingRangeX; // (min,max)
	std::pair<int, int> _MovingRangeY; // (min,max)
	
};
