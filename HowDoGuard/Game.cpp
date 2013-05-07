#include "Game.h"

bool Game::endNow = false;

Game::Game( void )
{
}

Game::~Game( void )
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

	_pGraphicsSystem = New GraphicsSystem();
	_pGraphicsSystem->init();

	_pInputSystem = New InputSystem();
	_pInputSystem->init();

	INF(toString(), "Finished Init");
}

void Game::term( void )
{
	delete _pInputSystem;
	delete _pGraphicsSystem;

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

		_currentFPS = (float)(1000.0 / frameDelay);

		update();
		draw();

		fpsTimer.sleepUntilElapsed(fpsDelay);
		frameDelay = fpsTimer.getElapsedMilli();
		fpsTimer.start();
	}
}

void Game::update( void )
{
	_pInputSystem->update(_pGameTime);

	if (endNow)
		_running = false;
}

void Game::draw( void )
{
	RenderTarget *pRenderTarget = _pGraphicsSystem->renderTarget();

	pRenderTarget->beginDraw();

	pRenderTarget->drawHexagon(320, 240, 240, Color::BLACK);
	pRenderTarget->drawHexagon(320, 240, 240, Color::BLACK, PI / 4);
	pRenderTarget->drawHexagon(320, 240, 240, Color::BLACK, -PI / 4);

	pRenderTarget->fillCircle(320, 240, 150, Color::BLUE);

	pRenderTarget->fillTriangle(320, 240, 100, Color::RED);
	pRenderTarget->fillTriangle(320, 240, 100, Color::RED, PI);

	pRenderTarget->endDraw();
}
