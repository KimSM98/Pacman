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

	// SpriteSheet의 모든 Clip들을 반환한다.
	std::vector<SDL_Rect*>* GetSpriteSheetClips(const std::string& fileName);
	std::vector<SDL_Rect*>* GetSpriteSheetClips(const std::string& fileName, class SpriteComponent* sprComp);
	std::vector<SDL_Rect*>* GetSpriteSheetClips(const std::string& fileName, class TileMapComponent* sprComp);

	// SpriteSheet의 특정 Clip을 반환한다.
	SDL_Rect* GetClip(const std::string& fileName, int sprNum);
	SDL_Rect* GetClip(const std::string& fileName, int sprNum, class SpriteComponent* sprComp);

private:
	class Game* _Game;

	std::unordered_map <std::string, std::vector<SDL_Rect*>*> _SpriteSheets;
	std::unordered_map <std::string, int> _SpriteSheetPixelSize;
};