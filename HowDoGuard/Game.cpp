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

	gpEventDispatcher = New EventDispatcher();

	_pGraphicsSystem = New GraphicsSystem();
	_pGraphicsSystem->init();

	_pDataManager = New DataManager();
	_pDataManager->init();

	_pInputSystem = New InputSystem();
	_pInputSystem->init();

	unit = New BasicUnit();
	unit->init(_pDataManager->pAnimations->get("toast-ghp"), Vector2(100));

	gpEventDispatcher->addEventListener(Event::EVENT_GAME_END, this, &Game::stop);

	INF(toString(), "Finished Init");
}

void Game::term( void )
{
	delete unit;

	gpEventDispatcher->removeEventListener(Event::EVENT_GAME_END, this, &Game::stop);

	delete _pInputSystem;
	delete _pGraphicsSystem;

	delete _pDataManager;
}

void Game::start( void )
{
	_running = true;

	double 
		fpsDelay = 1000.0 / _targetFPS,
		frameDelay = 0;

	FrameData frameData = FrameData();
	RenderData renderData = RenderData(_pGraphicsSystem->renderTarget());

	Timer fpsTimer = Timer();
	fpsTimer.start();

	while (_running)
	{
		frameData.update(frameDelay, _currentFPS, _targetFPS);

		update(frameData);
		draw(renderData);

		_currentFPS = (float)(1000.0 / frameDelay);

		fpsTimer.sleepUntilElapsed(fpsDelay);
		frameDelay = fpsTimer.getElapsedMilli();
		fpsTimer.start();
	}
}

void Game::stop ( const Event& event )
{
	_running = false;
}

void Game::update( const FrameData& frameData )
{
	gpEventDispatcher->dispatchEvent(Event(Event::EVENT_ENTER_FRAME, frameData));
	gpEventDispatcher->dispatchEvent(Event(Event::EVENT_FRAME,		 frameData));
	gpEventDispatcher->dispatchEvent(Event(Event::EVENT_EXIT_FRAME,  frameData));
}

void Game::draw( const RenderData& renderData )
{
	renderData.renderTarget()->beginDraw();

	gpEventDispatcher->dispatchEvent(Event(Event::EVENT_RENDER, renderData));

	renderData.renderTarget()->endDraw();
}
