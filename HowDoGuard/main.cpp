
#include "Common.h"
#include "MemoryTracker.h"
#include "Game.h"

void main( void )
{
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
		system("PAUSE");
	}

#endif //DEBUG

}