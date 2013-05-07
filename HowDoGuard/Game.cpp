#include "Game.h"

Game::Game(void)
{
}

Game::~Game(void)
{
	term();
}

std::string Game::toString( void ) const
{
	return "Game";
}

void Game::init( void )
{
	INF(toString(), "Starting Init");

	_targetFPS = 60.0;
	_currentFPS = 0;

	_pGameTime = New GameTime();

	INF(toString(), "Finished Init");
}

void Game::term( void )
{
	delete _pGameTime;
}

void Game::start( void )
{
	_running = true;

	double fpsDelay = 1000.0 / _targetFPS;

	while (_running)
	{
		_pGameTime->update(fpsDelay);

		update();
		draw();
	}
}

void Game::update( void )
{
	INF(toString(), "Shutting Down on first Game Update");
	_running = false;
}

void Game::draw( void )
{

}
