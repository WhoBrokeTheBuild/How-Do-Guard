#pragma once

#ifndef __IGAME_INPUT_LISTENER_H__
#define __IGAME_INPUT_LISTENER_H__

#include "Common.h"
#include <GameObject.h>

#include "GameInputSource.h"

class IGameInputListener
{
public:

    IGameInputListener( void ) { }
    virtual ~IGameInputListener( void ) { term(); }

    virtual void init( void )
    {
        gpEventDispatcher->addEventListener(GameInputSource::EVENT_GAME_INPUT_PRESSED,  this, &IGameInputListener::inputPressed);
        gpEventDispatcher->addEventListener(GameInputSource::EVENT_GAME_INPUT_RELEASED, this, &IGameInputListener::inputReleased);
        gpEventDispatcher->addEventListener(GameInputSource::EVENT_GAME_INPUT_HELD,     this, &IGameInputListener::inputHeld);
    }

    virtual void term( void )
    {
        gpEventDispatcher->removeEventListener(GameInputSource::EVENT_GAME_INPUT_HELD,     this, &IGameInputListener::inputHeld);
        gpEventDispatcher->removeEventListener(GameInputSource::EVENT_GAME_INPUT_RELEASED, this, &IGameInputListener::inputReleased);
        gpEventDispatcher->removeEventListener(GameInputSource::EVENT_GAME_INPUT_PRESSED,  this, &IGameInputListener::inputPressed);
    }

    virtual void inputPressed ( const Event& event ) { };
    virtual void inputReleased( const Event& event ) { };
    virtual void inputHeld    ( const Event& event ) { };

};

#endif