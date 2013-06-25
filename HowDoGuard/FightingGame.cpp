#include "FightingGame.h"

CachedText* FightingGame::fpsText = nullptr;
CachedText* FightingGame::stateText = nullptr;

FightingGame::FightingGame(void)
{
}

FightingGame::~FightingGame(void)
{
    term();
}

std::string FightingGame::toString( void ) const
{
    return "Fighting Game";
}

void FightingGame::init( void )
{
    Game::init();

    _pGraphicsSystem->setWindowSize(Size(1143, 480));

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
    test->init(PLAYER_INDEX_ONE, "wolf", Vector2(200));

    test2 = New Player();
    test2->init(PLAYER_INDEX_TWO, "curl", Vector2(500, 0));

    test->addEventListener(Player::EVENT_ENEMY_LOCATION, test2, &Player::updateEnemyLocation);
    test2->addEventListener(Player::EVENT_ENEMY_LOCATION, test, &Player::updateEnemyLocation);
}

void FightingGame::term( void )
{
    INF(toString(), "Terminating");

    delete test2;
    delete test;

    delete stateText;
    delete fpsText;
    delete fpsFont;

    delete bg;

    delete gpDataManager;
}

void FightingGame::update( const Event& event )
{
    Game::update(event);

    stringstream ss;

    ss.str(string());
    ss << "FPS: " << ceil(_currentFPS, 1);
    fpsText->setText(ss.str());
}

void FightingGame::render( const Event& event )
{
    Game::render(event);

    const RenderData* data = event.dataAs<RenderData>();

    data->renderTarget()->drawText(Vector2(10), fpsText);
    data->renderTarget()->drawText(Vector2(10, 45), stateText);
}
