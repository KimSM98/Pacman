#include "SpriteSheetLibrary.h"
#include <iostream>
#include "Game.h"
#include "SpriteComponent.h"
#include "TileMapComponent.h"
#include "AnimSpriteSheetComponent.h"

// SpriteSheet�� �ҷ��ͼ� pixelSize�� �߶� Clip���� ����� �����Ѵ�.
void SpriteSheetLibrary::LoadSpriteSheet(const std::string& fileName, int pixelSize)
{
	if (_SpriteSheets[fileName]) return;

	// �ش� SpriteSheet�� �ȼ� ����� �����Ѵ�.
	_SpriteSheetPixelSize[fileName] = pixelSize;

	SDL_Texture* tex = _Game->GetTexture(fileName);	
	int coloumn;
	int row;
	// �ؽ�ó�� width�� height�� coloumn�� row�� �޾ƿ´�.
	SDL_QueryTexture(tex, nullptr, nullptr, &coloumn, &row);
	coloumn /= pixelSize;
	row /= pixelSize;

	// SpriteSheet�� �ڸ���.
	// SpriteSheet�� �ڸ� ������� Clip�̶�� �ϰ�, clips�� �����Ѵ�.
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
	// Sprite�� Texture ����
	sprComp->SetTexture(_Game->GetTexture(fileName));

	// �ش� pixel size�� Sprite ������ ����
	int pixelSize = _SpriteSheetPixelSize[fileName];
	sprComp->SetHeight(pixelSize);
	sprComp->SetWidth(pixelSize);
}

// �ش� SpriteSheet�� Ŭ���� ��ȯ�Ѵ�.
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

// �ش� SpriteSheet�� Ŭ���� ��ȯ�Ѵ�. SpriteComponent�� �ؽ�ó�� �ش� SpriteSheet�� �����Ѵ�.
std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName, SpriteComponent* sprComp)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	sprComp->SetTexture(_Game->GetTexture(fileName));
	return _SpriteSheets[fileName];
}

// �ش� SpriteSheet�� Ŭ���� ��ȯ�Ѵ�. SpriteComponent�� �ؽ�ó�� �ش� SpriteSheet�� �����Ѵ�.
// TileMap�� �ȼ� ����� �����Ѵ�.
std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName, TileMapComponent* tileMapComp)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	tileMapComp->SetTexture(_Game->GetTexture(fileName));
	tileMapComp->SetTileSetPixelSize(_SpriteSheetPixelSize[fileName]);
	return _SpriteSheets[fileName];
}

// �ش� SpriteSheet�� Ư�� ��ȣ�� Ŭ���� ��ȯ�Ѵ�.
SDL_Rect* SpriteSheetLibrary::GetClip(const std::string& fileName, int sprNum)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	return _SpriteSheets[fileName]->at(sprNum);
}
