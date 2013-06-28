#pragma once

#ifndef __GAME_INPUT_SYSTEM_H__
#define __GAME_INPUT_SYSTEM_H__

#include "Common.h"
#include <InputSystem.h>

#include "GameInputSource.h"

#include <map>

typedef map<PlayerIndex,  GameInputSource*> PlayerGameInputSourceMap;
typedef pair<PlayerIndex, GameInputSource*> PlayerGameInputSourcePair;

class GameInputSystem :
    public InputSystem 
{
protected:

    PlayerGameInputSourceMap
        _gameSources;

    virtual void handleSDLEvent( SDL_Event sdlEvent ); 

public:

    GameInputSystem( void );
    virtual ~GameInputSystem( void );

    virtual string toString( void ) const;

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );

};

#endif