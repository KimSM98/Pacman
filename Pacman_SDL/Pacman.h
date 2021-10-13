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

	// 그래프에서 노드의 정보를 받아옴(이동범위)
	// 현재 노드 -> 다음 노드
	class Node* _CurrentNode;
	class Node* _NextNode;

	// 이동 범위
	std::pair<int, int> _MovingRangeX; // (min,max)
	std::pair<int, int> _MovingRangeY; // (min,max)	
};
