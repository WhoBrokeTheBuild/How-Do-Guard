#include "Game.h"

CachedText* Game::fpsText   = nullptr;
CachedText* Game::stateText = nullptr;

bool Game::DEBUG_SHOW_HITBOXES = false;

Game::Game(void)
{
}

Game::~Game(void)
{
    term();
}

std::string Game::toString( void ) const
{
    return "Fighting Game";
}

void Game::init( void )
{
    ArcApp::init(Size(1143, 480), "How Do Guard??");
    IKeyboardListener::init();

    _pGraphicsSystem->setWindowIcon("assets/icons/icon_32x32.png");

    gpDataManager = New DataManager();
    gpDataManager->init();

    bg = New AnimatedUnit();
    bg->init(gpDataManager->pAnimations->get("bg"));

    fpsFont = New Font("assets/fonts/ds-digital.ttf", 25);

    fpsText = New CachedText();
    fpsText->init("", fpsFont);

    stateText = New CachedText();
    stateText->init("", fpsFont);

    test = New Player();
    test->init(0, "wolf", Vector2(200));

    test2 = New Player();
    test2->init(1, "wolf", Vector2(500, 0));

    test->addEventListener(Player::EVENT_ENEMY_LOCATION, test2, &Player::updateEnemyLocation);
    test2->addEventListener(Player::EVENT_ENEMY_LOCATION, test, &Player::updateEnemyLocation);

    test->addEventListener(Player::EVENT_CHECK_COLLISION, test2, &Player::checkCollision);
    test2->addEventListener(Player::EVENT_CHECK_COLLISION, test, &Player::checkCollision);

    Game::DEBUG_SHOW_HITBOXES = true;
}

void Game::term( void )
{
    delete test2;
    delete test;

    delete stateText;
    delete fpsText;
    delete fpsFont;

    delete bg;

    delete gpDataManager;
}

void Game::update( const Event& event )
{
    ArcApp::update(event);

    stringstream ss;

    ss.str(string());
    ss << "FPS: " << ceil(_currentFPS, 1);
    fpsText->setText(ss.str());
}

void Game::render( const Event& event )
{
    ArcApp::render(event);

    const RenderData* data = event.dataAs<RenderData>();

    data->renderTarget()->drawText(Vector2(10), fpsText);
    data->renderTarget()->drawText(Vector2(10, 45), stateText);
}

void Game::initInput( void )
{
    _pInputSystem = New GameInputSystem();
    _pInputSystem->init();
}

void Game::keyPressed( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

    if (data->Key == KEY_ESCAPE)
    {
        gpEventDispatcher->dispatchEvent(Event(Game::EVENT_EXIT));
    }
    else if (data->Key == KEY_F1)
    {
        Game::DEBUG_SHOW_HITBOXES = !Game::DEBUG_SHOW_HITBOXES;
    }
}