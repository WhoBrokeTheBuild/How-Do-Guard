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

	double 
		fpsDelay = 1000.0 / _targetFPS,
		frameDelay = 0;

	Timer fpsTimer = Timer();
	fpsTimer.start();

	while (_running)
	{
		_pGameTime->update(frameDelay, _currentFPS, _targetFPS);

		_currentFPS = 1000.0 / frameDelay;

		update();
		draw();

		fpsTimer.sleepUntilElapsed(fpsDelay);
		frameDelay = fpsTimer.getElapsedMilli();
		fpsTimer.start();
	}
}

void Game::update( void )
{
	cout << "FPS: " << _currentFPS << endl;
}

void Game::draw( void )
{

}
