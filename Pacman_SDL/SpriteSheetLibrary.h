#pragma once
#include <SDL_render.h>
#include <unordered_map>
#include <string>
#include <vector>

class SpriteSheetLibrary
{
public:
	SpriteSheetLibrary(class Game* game) : _Game(game) {}

	void LoadSpriteSheet(const std::string& fileName, int pixelSize);

	std::vector<SDL_Rect*>* GetSpriteSheetClips(const std::string& fileName);
	std::vector<SDL_Rect*>* GetSpriteSheetClips(const std::string& fileName, class SpriteComponent* sprComp);
	std::vector<SDL_Rect*>* GetSpriteSheetClips(const std::string& fileName, class TileMapComponent* sprComp);
	std::vector<SDL_Rect*>* GetSpriteSheetClips(const std::string& fileName, class AnimSpriteSheetComponent* sprComp);

	SDL_Rect* GetClip(const std::string& fileName, int sprNum);
	SDL_Rect* GetClip(const std::string& fileName, int sprNum, class SpriteComponent* sprComp);

private:
	//std::vector<SDL_Rect*>* SliceSpriteSheet(const std::string& fileName, int pixelSize);
	class Game* _Game;

	std::unordered_map <std::string, std::vector<SDL_Rect*>*> _SpriteSheets;
	std::unordered_map <std::string, int> _SpriteSheetPixelSize;
};

//class SpriteSheet
//{
//public:
//	void SetTexture(SDL_Texture* tex) { _Texture = tex; }
//	void SetPixelSize(int size) { _PixelSize = size; }
//
//private:
//	int _PixelSize;
//	SDL_Texture* _Texture;
//};