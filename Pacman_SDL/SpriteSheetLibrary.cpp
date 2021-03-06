#include "SpriteSheetLibrary.h"
#include <iostream>
#include "Game.h"
#include "SpriteComponent.h"
#include "TileMapComponent.h"
#include "AnimSpriteSheetComponent.h"

// SpriteSheet를 불러와서 pixelSize로 잘라서 Clip으로 만들어 저장한다.
void SpriteSheetLibrary::LoadSpriteSheet(const std::string& fileName, int pixelSize)
{
	if (_SpriteSheets[fileName]) return;

	// 해당 SpriteSheet의 픽셀 사이즈를 저장한다.
	_SpriteSheetPixelSize[fileName] = pixelSize;

	SDL_Texture* tex = _Game->GetTexture(fileName);	
	int coloumn;
	int row;
	// 텍스처의 width와 height를 coloumn과 row에 받아온다.
	SDL_QueryTexture(tex, nullptr, nullptr, &coloumn, &row);
	coloumn /= pixelSize;
	row /= pixelSize;

	// SpriteSheet를 자른다.
	// SpriteSheet를 자른 결과물을 Clip이라고 하고, clips에 저장한다.
	std::vector<SDL_Rect*>* clips = new std::vector<SDL_Rect*>();
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

void SpriteSheetLibrary::InitSpriteComp(const std::string& fileName, SpriteComponent* sprComp)
{
	// Sprite의 Texture 설정
	sprComp->SetTexture(_Game->GetTexture(fileName));

	// 해당 pixel size로 Sprite 사이즈 설정
	int pixelSize = _SpriteSheetPixelSize[fileName];
	sprComp->SetHeight(pixelSize);
	sprComp->SetWidth(pixelSize);
}

// 해당 SpriteSheet의 클립을 반환한다.
std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName)
{
	if (!_SpriteSheets[fileName])
	{
		std::cout << fileName << " clips does not exist!" << 'n';
		return nullptr;
	}
	SDL_Log("%s: %p", fileName.c_str(), _SpriteSheets[fileName]);
	return _SpriteSheets[fileName];
}

// 해당 SpriteSheet의 클립을 반환한다. SpriteComponent의 텍스처를 해당 SpriteSheet로 설정한다.
std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName, SpriteComponent* sprComp)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	sprComp->SetTexture(_Game->GetTexture(fileName));
	return _SpriteSheets[fileName];
}

// 해당 SpriteSheet의 클립을 반환한다. SpriteComponent의 텍스처를 해당 SpriteSheet로 설정한다.
// TileMap의 픽셀 사이즈를 설정한다.
std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName, TileMapComponent* tileMapComp)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	tileMapComp->SetTexture(_Game->GetTexture(fileName));
	tileMapComp->SetTileSetPixelSize(_SpriteSheetPixelSize[fileName]);
	return _SpriteSheets[fileName];
}

// 해당 SpriteSheet의 특정 번호의 클립을 반환한다.
SDL_Rect* SpriteSheetLibrary::GetClip(const std::string& fileName, int sprNum)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	return _SpriteSheets[fileName]->at(sprNum);
}
