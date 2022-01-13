#include "SpriteSheetLibrary.h"
#include <iostream>
#include "Game.h"
#include "SpriteComponent.h"
#include "TileMapComponent.h"
#include "AnimSpriteSheetComponent.h"

// SpriteSheet�� �ҷ��ͼ� pixelSize�� �߶� Clip���� ����� �����Ѵ�.
void SpriteSheetLibrary::LoadSpriteSheet(const std::string& fileName, int pixelSize)
{
	// �̹� �ҷ��� ���� �ִ� ��������Ʈ ��Ʈ���
	if (_SpriteSheets[fileName]) return;

	std::vector<SDL_Rect*>* clips = new std::vector<SDL_Rect*>();
	// �ش� SpriteSheet�� �ȼ� ����� �����Ѵ�.
	_SpriteSheetPixelSize[fileName] = pixelSize;
	// Get Texture
	SDL_Texture* tex = _Game->GetTexture(fileName);
	
	int coloumn;
	int row;

	// �ؽ�ó�� width�� height�� coloumn�� row�� �޾ƿ´�.
	SDL_QueryTexture(tex, nullptr, nullptr, &coloumn, &row);
	coloumn /= pixelSize;
	row /= pixelSize;

	// SpriteSheet�� �ڸ���.
	// SpriteSheet�� �ڸ� ������� Clip�̶�� �ϰ�, clips�� �����Ѵ�.
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

// �ش� SpriteSheet�� Ŭ���� ��ȯ�Ѵ�.
std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName)
{
	if (!_SpriteSheets[fileName])
	{
		std::cout << fileName << " clips does not exist!" << 'n';
		return nullptr;
	}

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
std::vector<SDL_Rect*>* SpriteSheetLibrary::GetSpriteSheetClips(const std::string& fileName, TileMapComponent* sprComp)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	sprComp->SetTexture(_Game->GetTexture(fileName));
	sprComp->SetTileSetPixelSize(_SpriteSheetPixelSize[fileName]);
	return _SpriteSheets[fileName];
}

// �ش� SpriteSheet�� Ư�� ��ȣ�� Ŭ���� ��ȯ�Ѵ�.
SDL_Rect* SpriteSheetLibrary::GetClip(const std::string& fileName, int sprNum)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	return _SpriteSheets[fileName]->at(sprNum);
}

// �ش� SpriteSheet�� Ư�� ��ȣ�� Ŭ���� ��ȯ�ϰ�, SpriteComponent�� �ȼ� ����� �ش� SpriteSheet�� ������� �����Ѵ�.
SDL_Rect* SpriteSheetLibrary::GetClip(const std::string& fileName, int sprNum, class SpriteComponent* sprComp)
{
	if (!_SpriteSheets[fileName]) return nullptr;

	// Sprite�� Texture ����
	sprComp->SetTexture(_Game->GetTexture(fileName));
	
	// �ش� pixel size�� Sprite ������ ����
	int pixelSize = _SpriteSheetPixelSize[fileName];
	sprComp->SetHeight(pixelSize);
	sprComp->SetWidth(pixelSize);

	return _SpriteSheets[fileName]->at(sprNum);
}