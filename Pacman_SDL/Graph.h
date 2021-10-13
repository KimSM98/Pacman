#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>
#include <unordered_map>
#include "Node.h"
 
class Graph : public SpriteComponent
{
public:
	Graph(class Actor* owner, int drawOrder = 100);
	~Graph();
 
	void Draw(SDL_Renderer* renderer) override;

	class Node* GetNode(int row, int column);
 
	int SetGraphStateFromFile(std::string fileName);
	void SetDistanceBetweenNodes(int dist) { _DistanceBetweenNodes = dist; }
 
	void PrintNodes();
private:
	void ArrangeAdjNodes();
 
	int _DistanceBetweenNodes;
	bool _AllowsDrawing;
 
	std::vector<std::vector<class Node*>> _Nodes;
};