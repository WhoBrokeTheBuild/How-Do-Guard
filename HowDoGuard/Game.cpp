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

	sheet = New Texture();
	sheet->init("assets/sheets/sprsht_toast_ghp.png");

	frame1 = New Sprite();
	frame2 = New Sprite();
	frame3 = New Sprite();
	frame4 = New Sprite();
	frame5 = New Sprite();

	vector<Sprite*> frames;
	frames.push_back(frame1);
	frames.push_back(frame2);
	frames.push_back(frame3);
	frames.push_back(frame4);
	frames.push_back(frame5);

	Rect source = Rect(0, 0, 255, 255);

	for (int i = 0; i < 5; ++i)
	{
		frames[i]->init(sheet, source, 200);
		source.X += source.Width;
	}

	anim = New Animation();
	anim->init(frames, true, true);

	unit = New BasicUnit();
	unit->init(anim, Vector2(100));

	INF(toString(), "Finished Init");
}

void Game::term( void )
{
	delete unit;

	delete anim;
	
	delete frame1;
	delete frame2;
	delete frame3;
	delete frame4;
	delete frame5;

	delete sheet;

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

	unit->update(_pGameTime);

	if (endNow)
		_running = false;
}

void Game::draw( void )
{
	RenderTarget *pRenderTarget = _pGraphicsSystem->renderTarget();

	pRenderTarget->beginDraw();

	unit->draw(pRenderTarget);

	pRenderTarget->endDraw();
}
