#include "SpriteSheetLibrary.h"
#include <iostream>
#include "Game.h"
#include "SpriteComponent.h"
#include "TileMapComponent.h"
#include "AnimSpriteSheetComponent.h"

void SpriteSheetLibrary::LoadSpriteSheet(const std::string& fileName, int pixelSize)
{
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

//std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName, AnimSpriteSheetComponent* animSprSheetComp)
//{
//	if (!_SpriteSheets[fileName]) return nullptr;
//
//	animSprSheetComp->SetTexture(_Game->GetTexture(fileName));
//	int pixelSize = _SpriteSheetPixelSize[fileName];
//
//	return _SpriteSheets[fileName];
//}


SDL_Rect* SpriteSheetLibrary::GetClip(const std::string& fileName, int sprNum)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	return _SpriteSheets[fileName]->at(sprNum);
}

SDL_Rect* SpriteSheetLibrary::GetClip(const std::string& fileName, int sprNum, class SpriteComponent* sprComp)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	sprComp->SetTexture(_Game->GetTexture(fileName));
	int pixelSize = _SpriteSheetPixelSize[fileName];
	sprComp->SetHeight(pixelSize);
	sprComp->SetWidth(pixelSize);
	return _SpriteSheets[fileName]->at(sprNum);
}

//std::vector<SDL_Rect*>* SpriteSheetLibrary::SliceSpriteSheet(const std::string& fileName, int pixelSize)
//{
//	// Get Texture
//	SDL_Surface* surf = IMG_Load(fileName.c_str());
//	if (!surf)
//	{
//		SDL_Log("Failed to load texture file %s", fileName.c_str());
//
//	}
//
//	std::vector<SDL_Rect*>* clips = new std::vector<SDL_Rect*>();
//
//	// Slice surfaces
//	int Coloumn = surf->w / pixelSize;
//	int row = surf->h / pixelSize;
//	//std::cout << "Suface width : " << Coloumn << " height : " << row << '\n';
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < Coloumn; j++)
//		{
//			SDL_Rect dst;
//			dst.x = j * pixelSize;
//			dst.y = i * pixelSize;
//			dst.w = pixelSize;
//			dst.h = pixelSize;
//
//			clips->push_back(&dst);
//			//std::cout << "ddclip x : " << (*clips).back() << '\n';
//		}
//	}
//	std::cout << "Sliced!" << '\n';
//
//	return clips;
//}