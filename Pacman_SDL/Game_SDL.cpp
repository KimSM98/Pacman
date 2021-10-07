#pragma comment (lib, "SDL2")
#pragma comment (lib, "SDL2main")
#pragma comment (lib, "SDL2_image")
#include <SDL.h>
#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;

	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}

	game.Shutdown();

	return 0;
}