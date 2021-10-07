#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>
#include <unordered_map>
 
class Graph : public SpriteComponent
{
public:
	Graph(class Actor* owner, int drawOrder = 100);
	~Graph();
 
	void Draw(SDL_Renderer* renderer) override;
 
	int SetGraphStateFromFile(std::string fileName);
	void SetDistanceBetweenNodes(int dist) { _DistanceBetweenNodes = dist; }
 
	void PrintNodes();
private:
	void ArrangeAdjNodes();
 
	int _DistanceBetweenNodes;
	bool _AllowsDrawing;
 
	std::vector<std::vector<class Node*>> _Nodes;
};
 
enum Direction{Top, Bottom, Left, Right};
 
class Node
{
public:
	Node() : _Pos(Vector2(0, 0)), _PixelSize(0) {};
	Node(Vector2 pos, int pixelSize);
 
	void Draw(SDL_Renderer* renderer);
 
	void AddAdjNode(int dir, Node* node);
 
	void SetPixelSize(int size) { _PixelSize = size; }
	SDL_Rect& GetRect() { return rect; }
	Vector2 GetPos() { return _Pos; }
 
private:
	Vector2 _Pos;
	SDL_Rect rect;
	int _PixelSize;
 
	std::unordered_map<int, Node*> _AdjNodes;
};