#include "TileMapComponent.h"
#include "Actor.h"
#include <fstream>

TileMapComponent::TileMapComponent(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
	, _TileSetPixelsize(0)
	, _Clips(nullptr)
{
}

TileMapComponent::~TileMapComponent()
{
	for (auto t : _Tiles)
	{
		delete t;
	}
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	for (auto t : _Tiles)
	{
		int sprNum = t->GetSprNum();
		
		SDL_RenderCopyEx(
			renderer,
			GetTexture(),
			_Clips->at(sprNum),
			&t->GetDst(),
			0,
			nullptr,
			SDL_FLIP_NONE
		);
	}	
}

void TileMapComponent::SetTileMapStateFromFile(std::string fileName)
{
	std::ifstream input((fileName));

	if (input.fail())
	{
		std::cout << "File Name : " << fileName << " does not exist." << '\n';
		return;
	}

	// 맵의 정보 받기
	std::string dataFromFile;
	std::string temp;
	int i(0), j(0);

	while (getline(input, dataFromFile)) // 엔터가 나오기 전까지를 string으로 받는다.
	{
		std::vector<int> tempVec;
		// ','를 기준으로 수를 자른다.
		for (int n = 0; n < dataFromFile.length(); n++)
		{
			if (dataFromFile[n] == ',')
			{
				tempVec.push_back(std::stoi(temp));
				temp.clear();
				j++;
			}
			else if (dataFromFile[n] != ',')
				temp += dataFromFile[n];
		}
		// ','가 없이 끝나기 때문에  
		tempVec.push_back(std::stoi(temp));
		temp.clear();
		i++;
		j = 0;

		_TileMapState.push_back(tempVec);
	}

	input.close();

	CreateTiles();
}

void TileMapComponent::CreateTiles()
{
	for (int i = 0; i < _TileMapState.size(); i++)
	{
		for (int j = 0; j < _TileMapState.front().size(); j++)
		{
			if (_TileMapState[i][j] != -1)
			{
				SDL_Rect r;

				r.w = static_cast<int>(_TileSetPixelsize * _Owner->GetScale());
				r.h = static_cast<int>(_TileSetPixelsize * _Owner->GetScale());

				r.x = static_cast<int>(_Owner->GetPosition().x + _TileSetPixelsize * j);
				r.y = static_cast<int>(_Owner->GetPosition().y + _TileSetPixelsize * i);

				// Tile Set 부분 사각형
				Tile* tile = new Tile(r, _TileMapState[i][j]);
				_Tiles.push_back(tile);
			}
		}
	}
}

Tile::Tile(SDL_Rect dst, int num)
{
	_Dst = dst;
	_SprNum = num;
}