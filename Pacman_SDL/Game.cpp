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
#include "AnimSpriteSheetComponent.h"

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
	// SDL 라이브러리 초기화, 초기화 성공 시 0 반환
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
	// 게임에 사용할 모든 액터 생성
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

void Game::AddCollider(CollisionComponent* colComp)
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

	// queue에 이벤트가 남아 있으면
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
	// 마지막 프레임 이후로 16ms가 경과할 때까지 대기
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), _TickCount + 16));

	float deltaTime = (SDL_GetTicks() - _TickCount) / 1000.f;
	// 다음 프레임을 위해 Ticks Count 업데이트
	_TickCount = SDL_GetTicks();

	// 최대 delta time값 고정
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// 모든 액터를 업데이트
	_IsUpdatingActors = true;
	for (auto actor : _Actors)
	{
		actor->Update(deltaTime);
	}
	_IsUpdatingActors = false;

	// 대기중인 액터를 _Actor로 이동
	for (auto pendingActor : _PendingActors)
	{
		_Actors.emplace_back(pendingActor);
	}
	_PendingActors.clear();

	// 죽은 액터를 임시 벡터에 추가
	std::vector<Actor*> deadActors;
	for (auto actor : _Actors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// 죽은 액터 제거
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

// 게임에 넣을 데이터. Unity의 Scnene과 같은 역할
void Game::LoadData()
{
	/*******************
	Sprite Sheet Library
	********************/
	// Initialize
	_SpriteSheetLib = new SpriteSheetLibrary(this);
	// Load Sprite sheet
	_SpriteSheetLib->LoadSpriteSheet("Assets/TileMapSpriteSheet1.png", 32); 
	_SpriteSheetLib->LoadSpriteSheet("Assets/PlayerSpriteSheet.png", 32);
	_SpriteSheetLib->LoadSpriteSheet("Assets/Ghosts.png", 32);

	/**************
	Tile Map, Graph
	***************/
	// Tile Map을 배치할 위치를 정하기 위한 액터
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(64.f, 0.f));
	
	// * Tile Map
	// Tile Map 생성
	TileMapComponent* tileMap = new TileMapComponent(temp, 70);
	// Tile Map에서 사용할 스프라이트 시트와 클립을 가져온다.
	tileMap->SetClips(_SpriteSheetLib->GetSpriteSheetClips("Assets/TileMapSpriteSheet1.png", tileMap));
	// csv파일로부터 타일 맵 정보를 가져오고, 타일을 생성한다.
	tileMap->SetTileMapStateFromFile("Assets/Maps/Map_1.csv");

	// * Graph
	// Graph 생성
	_Graph = new Graph(temp, 69);
	// 노드의 픽셀 사이즈(노드 간의 간격)
	_Graph->SetDistanceBetweenNodes(32);
	// csv 파일에서 그래프 정보 가져오기
	_Graph->SetGraphStateFromFile("Assets/Maps/Map_1_Graph.csv");

	/**********************
	Player, Ghost Actor 생성
	***********************/
	// * Player
	_Pacman = new Pacman(this);
	Node* node = _Graph->GetNode(1, 6);
	// 해당 노드의 위치로 위치 초기화
	_Pacman->InitPositionByNode(node);
	
	// * Ghost 1 + chase
	node = _Graph->GetNode(14, 13);
	Ghost* ghost = new GhostRed(this, node);
	// Chasing 기능 추가
	ghost->ActiveChaseAI(_Pacman, 128.f, 5.f);

	// * Ghost 2
	node = _Graph->GetNode(14, 11);
	ghost = new GhostBlue(this, node);
		
	// * Ghost 3
	node = _Graph->GetNode(14, 12);
	ghost = new GhostPink(this, node);
	
	// * Ghost 4
	node = _Graph->GetNode(14, 14);
	ghost = new GhostOrange(this, node);
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