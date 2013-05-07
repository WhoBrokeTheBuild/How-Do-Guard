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

	_targetFPS = 60.0f;
	_currentFPS = 0;

	_pGameTime = New GameTime();

	_pGraphicsSystem = New GraphicsSystem();
	_pGraphicsSystem->init();

	_pInputSystem = New InputSystem();
	_pInputSystem->init();

	font = New Font("ds-digital.ttf", 30);
	fpsText = New CachedText();
	fpsText->init("", font);

	INF(toString(), "Finished Init");
}

void Game::term( void )
{
	delete fpsText;
	delete font;

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

	stringstream ss;
	ss << "FPS: " << nearest(_currentFPS, 2);
	fpsText->setText(ss.str());

	if (endNow)
		_running = false;
}

void Game::draw( void )
{
	RenderTarget *pRenderTarget = _pGraphicsSystem->renderTarget();

	pRenderTarget->beginDraw();

	pRenderTarget->drawText(10, 10, fpsText, Color::BLACK);

	pRenderTarget->endDraw();
}
