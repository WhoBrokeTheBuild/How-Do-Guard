
#include "common.h"

#include "Game.h"

void main( void )
{

	INF("Main", "Starting Up");

	Game game = Game();
	game.init();

	INF("Main", "Starting Game Loop");

	game.start();

	INF("Main", "Shutting Down");

	system("PAUSE");

}