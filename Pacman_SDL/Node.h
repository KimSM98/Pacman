#pragma once
#include <SDL.h>
#include "Math.h"
#include <unordered_map>

enum Direction { Top, Bottom, Left, Right };

class Node
{
public:
	Node() : _Pos(Vector2(0, 0)), _PixelSize(0) {};
	Node(Vector2 pos, int pixelSize);

	void Draw(class SDL_Renderer* renderer);

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