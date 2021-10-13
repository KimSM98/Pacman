#include "Node.h"

Node::Node(Vector2 pos, int pixelSize)
	: _Pos(pos), _PixelSize(pixelSize)
{
	rect.x = _Pos.x - pixelSize / 8;
	rect.y = _Pos.y - pixelSize / 8;
	rect.w = pixelSize / 4;
	rect.h = pixelSize / 4;
}

void Node::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 125, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);

	if (!_AdjNodes.empty())
	{
		Vector2 adjNodePos;

		for (auto n : _AdjNodes)
		{
			adjNodePos = n.second->GetPos();
			SDL_RenderDrawLine(renderer, _Pos.x, _Pos.y, adjNodePos.x, adjNodePos.y);
		}
	}
}

void Node::AddAdjNode(int dir, Node* node)
{
	_AdjNodes[dir] = node;
}