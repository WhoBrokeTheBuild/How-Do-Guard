
#include "Common.h"
#include "MemoryTracker.h"
#include "Game.h"
#include "Console.h"

#include <SDL.h>
#include <SDL_opengl.h>

int main(int argc, char *argv[])
{

#ifdef DEBUG

	init_console();

	pause();

#endif

	INF("Main", "Starting Up");

	Game *game = New Game();
	game->init();

	INF("Main", "Starting Game Loop");

	game->start();

	INF("Main", "Shutting Down");

	delete game;

#ifdef DEBUG

	if (gMemoryTracker.numAllocations() > 0)
	{
		gMemoryTracker.printAllocations();
		pause();
	}

#endif //DEBUG

	return 0;

}