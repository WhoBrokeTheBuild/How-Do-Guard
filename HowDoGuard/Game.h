#pragma once

#ifndef __GAME_H__
#define __GAME_H__

#include "Common.h"
#include <ArcApp.h>

#include "GameInputSystem.h"

#include "DataManager.h"
#include "Player.h"

#include <IKeyboardListener.h>

class Game :
    public ArcApp, 
    public IKeyboardListener
{
public:

    //TODO: Remove
    Player *test, *test2;
    AnimatedUnit *bg;
    Font *fpsFont;
    static CachedText *fpsText, *stateText;

    static bool DEBUG_SHOW_HITBOXES;

    Game(void);
    virtual ~Game(void);

    virtual string toString( void ) const;

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual void initInput( void );

    virtual void keyPressed ( const Event& event );

};

#endif