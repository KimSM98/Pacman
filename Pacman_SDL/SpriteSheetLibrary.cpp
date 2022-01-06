#include "SpriteSheetLibrary.h"
#include <iostream>
#include "Game.h"
#include "SpriteComponent.h"
#include "TileMapComponent.h"
#include "AnimSpriteSheetComponent.h"

void SpriteSheetLibrary::LoadSpriteSheet(const std::string& fileName, int pixelSize)
{
	// _SpriteSheets에 이미 존재하면
	if (_SpriteSheets[fileName]) return;

	std::vector<SDL_Rect*>* clips = new std::vector<SDL_Rect*>();
	// Get pixel size
	_SpriteSheetPixelSize[fileName] = pixelSize;
	// Get Texture
	SDL_Texture* tex = _Game->GetTexture(fileName);
	
	// Slice Texture
	int coloumn;
	int row;

	SDL_QueryTexture(tex, nullptr, nullptr, &coloumn, &row);
	coloumn /= pixelSize;
	row /= pixelSize;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < coloumn; j++)
		{
			SDL_Rect* dst = new SDL_Rect();
			dst->x = j * pixelSize;
			dst->y = i * pixelSize;
			dst->w = pixelSize;
			dst->h = pixelSize;

			clips->push_back(dst);
		}
	}

	_SpriteSheets[fileName] = clips;
}

std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName)
{
	if (!_SpriteSheets[fileName])
	{
		std::cout << fileName << " clips does not exist!" << 'n';
		return nullptr;
	}

	return _SpriteSheets[fileName];
}

std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName, SpriteComponent* sprComp)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	sprComp->SetTexture(_Game->GetTexture(fileName));
	return _SpriteSheets[fileName];
}

std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName, TileMapComponent* sprComp)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	sprComp->SetTexture(_Game->GetTexture(fileName));
	sprComp->SetTileSetPixelSize(_SpriteSheetPixelSize[fileName]);
	return _SpriteSheets[fileName];
}

SDL_Rect* SpriteSheetLibrary::GetClip(const std::string& fileName, int sprNum)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	return _SpriteSheets[fileName]->at(sprNum);
}

SDL_Rect* SpriteSheetLibrary::GetClip(const std::string& fileName, int sprNum, class SpriteComponent* sprComp)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	// Sprite의 Texture 설정
	sprComp->SetTexture(_Game->GetTexture(fileName));
	
	// 해당 pixel size로 Sprite 사이즈 설정
	int pixelSize = _SpriteSheetPixelSize[fileName];
	sprComp->SetHeight(pixelSize);
	sprComp->SetWidth(pixelSize);

	return _SpriteSheets[fileName]->at(sprNum);
}