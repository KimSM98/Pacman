#include <SDL_image.h>
#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "TileMapComponent.h"
#include "AIComponent.h"
#include "AIState.h"
#include "Graph.h"
#include "SpriteSheetLibrary.h"
#include "Pacman.h"
#include "Ghost.h"
#include "CollisionComponent.h"

Game::Game()
	: _Window(nullptr)
	, _Renderer(nullptr)
	, _WindowWidth(1024)
	, _WindowHeight(1024)
	, _IsRunning(true)
	, _TickCount(0)
	, _IsUpdatingActors(false)
	, _Graph(nullptr)
	, _SpriteSheetLib(nullptr)
{
}

bool Game::Initialize()
{
	// SDL ���̺귯�� �ʱ�ȭ, �ʱ�ȭ ���� �� 0 ��ȯ
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	_Window = SDL_CreateWindow(
		"Pacman - Kim So-Min",
		100,
		50,
		_WindowWidth,
		_WindowHeight,
		0
	);

	if (!_Window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	_Renderer = SDL_CreateRenderer(
		_Window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!_Renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}
	// ���ӿ� ����� ��� ���� ����
	LoadData();

	_TickCount = SDL_GetTicks();

	return true;
}

void Game::Shutdown()
{
	SDL_DestroyWindow(_Window);
	SDL_DestroyRenderer(_Renderer);
	SDL_Quit();
}

void Game::RunLoop()
{
	while (_IsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::AddColliders(CollisionComponent* colComp)
{
	_Colliders.push_back(colComp);
}

void Game::RemoveCollider(CollisionComponent* colComp)
{
	auto iter = std::find(_Colliders.begin(),
		_Colliders.end(), colComp);
	if (iter != _Colliders.end())
	{
		_Colliders.erase(iter);
	}
}

void Game::AddGhosts(Ghost* ghost)
{
	_Ghosts.push_back(ghost);
}

void Game::RemoveGhost(Ghost* ghost)
{
	auto iter = std::find(_Ghosts.begin(),
		_Ghosts.end(), ghost);
	if (iter != _Ghosts.end())
	{
		_Ghosts.erase(iter);
	}
}

// private functions
void Game::ProcessInput()
{
	SDL_Event event;

	// queue�� �̺�Ʈ�� ���� ������
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_IsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		_IsRunning = false;
	}

	_IsUpdatingActors = true;
	for (auto actor : _Actors)
	{
		actor->ProcessInput(state);
	}
	_IsUpdatingActors = false;
}

void Game::UpdateGame()
{
	// ������ ������ ���ķ� 16ms�� ����� ������ ���
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), _TickCount + 16));

	float deltaTime = (SDL_GetTicks() - _TickCount) / 1000.f;
	// ���� �������� ���� Ticks Count ������Ʈ
	_TickCount = SDL_GetTicks();

	// �ִ� delta time�� ����
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// ��� ���͸� ������Ʈ
	_IsUpdatingActors = true;
	for (auto actor : _Actors)
	{
		actor->Update(deltaTime);
	}
	_IsUpdatingActors = false;

	// ������� ���͸� _Actor�� �̵�
	for (auto pendingActor : _PendingActors)
	{
		_Actors.emplace_back(pendingActor);
	}
	_PendingActors.clear();

	// ���� ���͸� �ӽ� ���Ϳ� �߰�
	std::vector<Actor*> deadActors;
	for (auto actor : _Actors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// ���� ���� ����
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(
		_Renderer,
		65, 65, 128, 255 // R, G, B, A
	);
	SDL_RenderClear(_Renderer);

	// Draw sprites
	for (auto sprites : _Sprites)
	{
		sprites->Draw(_Renderer);
	}

	// Draw Colliders
	for (auto col : _Colliders)
	{
		col->DrawCollider(_Renderer);
	}	

	SDL_RenderPresent(_Renderer);
}

void Game::LoadData()
{
	/*******************
	Sprite Sheet Library
	********************/
	// Initialize
	_SpriteSheetLib = new SpriteSheetLibrary(this);
	
	// BG�� ���� ��ġ�� ���� ���� ����
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(64.f, 0.f));

	/**************
	Tile Map, Graph
	***************/
	// * Tile Map
	// Load tile map sprite sheet
	_SpriteSheetLib->LoadSpriteSheet("Assets/TileMapSpriteSheet1.png", 32); 

	TileMapComponent* tileMap = new TileMapComponent(temp, 70);
	tileMap->SetClips(_SpriteSheetLib->GetSpriteSheetClips("Assets/TileMapSpriteSheet1.png", tileMap));
	tileMap->SetTileMapStateFromFile("Assets/Maps/Map_1.csv");

	// Graph
	_Graph = new Graph(temp, 69);
	// ��� ������
	_Graph->SetDistanceBetweenNodes(32);
	// ���Ͽ��� �׷��� �ޱ�
	_Graph->SetGraphStateFromFile("Assets/Maps/Map_1_Graph.csv");

	/**********************
	Player, Ghost Actor ����
	***********************/

	// Sprite Sheet Library
	_SpriteSheetLib->LoadSpriteSheet("Assets/PlayerSpriteSheet.png", 32);
	
	// * Player
	_Pacman = new Pacman(this);
	Node* node = _Graph->GetNode(1, 6);
	_Pacman->InitPositionByNode(node);

	// * Ghost 1 + chase
	Ghost* ghost = new Ghost(this);
	node = _Graph->GetNode(4, 6);
	ghost->InitByNode(node);
	// Chasing ��� �߰�
	ghost->ActiveChaseAI(_Pacman);

	// * Ghost 2
	ghost = new Ghost(this);
	node = _Graph->GetNode(14, 11);
	ghost->InitByNode(node);
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!_Actors.empty())
	{
		delete _Actors.back();
	}

	// Destroy textures
	for (auto tex : _Textures)
	{
		SDL_DestroyTexture(tex.second);
	}
	_Textures.clear();
}

// Actors
void Game::AddActor(Actor* actor)
{
	if (_IsUpdatingActors)
	{
		_PendingActors.emplace_back(actor);
	}
	else
	{
		_Actors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(_PendingActors.begin(), _PendingActors.end(), actor);
	if (iter != _PendingActors.end())
	{
		std::iter_swap(iter, _PendingActors.end() - 1);
		_PendingActors.pop_back();
	}

	iter = std::find(_Actors.begin(), _Actors.end(), actor);
	if (iter != _Actors.end())
	{
		std::iter_swap(iter, _Actors.end() - 1);
		_Actors.pop_back();
	}
}

// Sprites
void Game::AddSprite(SpriteComponent* sprite)
{
	int drawOrder = sprite->GetDrawOrder();

	auto iter = _Sprites.begin();
	for (; iter != _Sprites.end(); ++iter)
	{
		if (drawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	_Sprites.insert(iter, sprite);
}

void Game::RemoveSprite(class SpriteComponent* sprite)
{
	auto iter = std::find(_Sprites.begin(), _Sprites.end(), sprite);
	if (iter != _Sprites.end())
	{
		_Sprites.erase(iter);
	}
}

// Textures
SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* texture = nullptr;

	auto iter = _Textures.find(fileName);
	if (iter != _Textures.end())
	{
		texture = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		texture = SDL_CreateTextureFromSurface(_Renderer, surf);
		SDL_FreeSurface(surf);
		if (!texture)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		_Textures.emplace(fileName.c_str(), texture);
	}

	return texture;
}