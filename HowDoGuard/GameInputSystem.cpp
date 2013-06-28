#include "GameInputSystem.h"
#include "GameCombinedInput.h"

GameInputSystem::GameInputSystem(void)
{
}

GameInputSystem::~GameInputSystem(void)
{
    term();
}

std::string GameInputSystem::toString( void ) const
{
    return "Game Input System";
}

void GameInputSystem::init( void )
{
    InputSystem::init();

    _gameSources = PlayerGameInputSourceMap();

    for (PlayerIndex index = 0; index < PLAYER_INDEX_MAX; ++index)
    {
        _gameSources.insert(PlayerGameInputSourcePair(index, New GameInputSource()));
        _gameSources[index]->init(index);
    }

    _gameSources[0]->addAlias(GameCombinedInput(KEY_W),             GAME_INPUT_UP);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_A),             GAME_INPUT_LEFT);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_S),             GAME_INPUT_DOWN);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_D),             GAME_INPUT_RIGHT);
                                                 
    _gameSources[0]->addAlias(GameCombinedInput(KEY_O),             GAME_INPUT_LIGHT_PUNCH);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_P),             GAME_INPUT_LIGHT_KICK);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_K),             GAME_INPUT_HEAVY_PUNCH);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_L),             GAME_INPUT_HEAVY_KICK);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_LSHIFT),        GAME_INPUT_GUARD);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_LCONTROL),      GAME_INPUT_GRAB);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_Q),             GAME_INPUT_GUARD);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_E),             GAME_INPUT_GRAB);
                                                 
    _gameSources[1]->addAlias(GameCombinedInput(KEY_UP),            GAME_INPUT_UP);
    _gameSources[1]->addAlias(GameCombinedInput(KEY_LEFT),          GAME_INPUT_LEFT);
    _gameSources[1]->addAlias(GameCombinedInput(KEY_DOWN),          GAME_INPUT_DOWN);
    _gameSources[1]->addAlias(GameCombinedInput(KEY_RIGHT),         GAME_INPUT_RIGHT);
                                                 
    _gameSources[1]->addAlias(GameCombinedInput(KEY_PAD_8),         GAME_INPUT_LIGHT_PUNCH);
    _gameSources[1]->addAlias(GameCombinedInput(KEY_PAD_4),         GAME_INPUT_LIGHT_KICK);
    _gameSources[1]->addAlias(GameCombinedInput(KEY_PAD_9),         GAME_INPUT_HEAVY_KICK);
    _gameSources[1]->addAlias(GameCombinedInput(KEY_PAD_5),         GAME_INPUT_HEAVY_PUNCH);
    _gameSources[1]->addAlias(GameCombinedInput(KEY_RSHIFT),        GAME_INPUT_GUARD);
    _gameSources[1]->addAlias(GameCombinedInput(KEY_RCONTROL),      GAME_INPUT_GRAB);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_PAGE_UP),       GAME_INPUT_GUARD);
    _gameSources[0]->addAlias(GameCombinedInput(KEY_PAGE_DOWN),     GAME_INPUT_GRAB);

}

void GameInputSystem::term( void )
{
    PlayerGameInputSourceMap::iterator it;
    for (it = _gameSources.begin(); it != _gameSources.end(); ++it)
    {
        delete it->second;
    }
    _gameSources.clear();
}

void GameInputSystem::update( const Event& event )
{
    InputSystem::update(event);
}

void GameInputSystem::handleSDLEvent( SDL_Event sdlEvent )
{
    InputSystem::handleSDLEvent(sdlEvent);
}
