#pragma once

#ifndef __FIGHTING_GAME_H__
#define __FIGHTING_GAME_H__

#include "Common.h"
#include <Game.h>

#include "DataManager.h"
#include "Player.h"

class FightingGame :
    public Game
{
public:

    //TODO: Remove
    Player *test, *test2;
    AnimatedUnit *bg;
    Font *fpsFont;
    static CachedText *fpsText, *stateText;

    FightingGame(void);
    virtual ~FightingGame(void);

    virtual string toString( void ) const;

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

};

#endif