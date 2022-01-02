#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "SpriteSheetLibrary.h"
#include "Graph.h"
class Game
{
public:
	Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);
	SpriteSheetLibrary* GetSpriteSheetLib() { return _SpriteSheetLib; }

	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return _Asteroids; }

	Graph* GetGraph() { return _Graph; }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	SDL_Window* _Window;
	SDL_Renderer* _Renderer;
	int _WindowWidth;
	int _WindowHeight;

	bool _IsRunning;

	Uint32 _TickCount;

	// Actors
	std::vector<class Actor*> _Actors;
	std::vector<class Actor*> _PendingActors; // 대기 중인 액터
	bool _IsUpdatingActors;

	// Textures
	std::unordered_map<std::string, SDL_Texture*> _Textures;

	// Sprites
	std::vector<class SpriteComponent*> _Sprites;

	// Game specific
	class Character* _Character;
	class Ship* _Ship;
	std::vector<class Asteroid*> _Asteroids;

	class Pacman* _Pacman;

	// Map
	class Graph* _Graph;
	class SpriteSheetLibrary* _SpriteSheetLib;
};
