#pragma once
#include "SpriteComponent.h"
#include <string>
#include <vector>
#include "Math.h"
#include <iostream>

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int drawOrder = 100);
	~TileMapComponent();

	void Draw(SDL_Renderer* renderer) override;

	void SetTileMapStateFromFile(std::string fileName);
	void SetTileSetPixelSize(const int size) { _TileSetPixelsize = size; }
	void SetClips(std::vector<SDL_Rect*>* vec) { _Clips = vec; }

	std::vector<std::vector<int>> GetTileMapState() { return _TileMapState; }

protected:
	virtual void CreateTiles();

	std::vector<std::vector<int>> _TileMapState;
	std::vector<class Tile*> _Tiles;
	std::vector<SDL_Rect*>* _Clips;

	int _TileSetPixelsize;
};

class Tile
{
public:
	Tile(SDL_Rect dst, int sprNum);
		
	SDL_Rect& GetDst() { return _Dst; }
	int GetSprNum() { return _SprNum; }

private:
	SDL_Rect _Dst;
	int _SprNum;
};