#include "PacmanMap.h"
#include "Actor.h"
#include "Graph.h"

PacmanMap::PacmanMap(Actor* owner, int drawOrder)
	: TileMapComponent(owner, drawOrder)
	, _Graph(nullptr)
{
	_Graph = new Graph(owner);
}

void PacmanMap::CreateTiles()
{
	for (int i = 0; i < _TileMapState.size(); i++)
	{
		std::vector<Node*> nodeVec;
		
		for (int j = 0; j < _TileMapState.front().size(); j++)
		{
			Node* node;
			Vector2 vec =_Owner->GetPosition();

			// Wall �̿��� ���� �׷����� ��� �߰��ϱ�, Wall�̸� nullptr�߰�
			switch (_TileMapState[i][j])
			{				
			case -1: 
				node = nullptr;
				nodeVec.push_back(node);
				break;

			case GameObject::PacDot:
				node = new Node(vec, _TileSetPixelsize);
				// PacDot ����
				break;

			case GameObject::PowerPallet:
				// obj����
				break;
			case GameObject::Player:
				// obj����
				break;
			case GameObject::Ghost:
				// obj����
				break;

			default:
				SDL_Rect* r = nullptr;

				r->w = static_cast<int>(_TileSetPixelsize * _Owner->GetScale());
				r->h = static_cast<int>(_TileSetPixelsize * _Owner->GetScale());

				r->x = static_cast<int>(_Owner->GetPosition().x + _TileSetPixelsize * j);
				r->y = static_cast<int>(_Owner->GetPosition().y + _TileSetPixelsize * i);

				// Tile Set �κ� �簢�� // ��ȣ�� ��������?
				SDL_Rect src;
				src.w = _TileSetPixelsize;
				src.h = _TileSetPixelsize;
				src.x = _TileMapState[i][j] % (GetTexWidth() / _TileSetPixelsize)
					* _TileSetPixelsize;
				src.y = _TileMapState[i][j] / (GetTexWidth() / _TileSetPixelsize)
					* _TileSetPixelsize;

				// IF Map Tile�̸�
				/*Tile* tile = new Tile(&r, src);

				_Tiles.push_back(tile);*/
				node = nullptr;
				break;
		
			} // end of switch
			nodeVec.push_back(node);

		}
	}
}