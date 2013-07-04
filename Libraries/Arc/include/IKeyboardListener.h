#pragma once

#ifndef __IKEYBOARD_LISTENER_H__
#define __IKEYBOARD_LISTENER_H__

#include "ArcCommon.h"
#include "KeyboardSource.h"

class IKeyboardListener
{
public:

    IKeyboardListener( void ) { }
    virtual ~IKeyboardListener( void ) { term(); };

    virtual void init( void )
    {
        gpEventDispatcher->addEventListener(KeyboardSource::EVENT_KEY_PRESSED,  this, &IKeyboardListener::keyPressed);
        gpEventDispatcher->addEventListener(KeyboardSource::EVENT_KEY_RELEASED, this, &IKeyboardListener::keyReleased);
        gpEventDispatcher->addEventListener(KeyboardSource::EVENT_KEY_HELD,     this, &IKeyboardListener::keyHeld);
    }

    virtual void term( void )
    {
        gpEventDispatcher->removeEventListener(KeyboardSource::EVENT_KEY_HELD,     this, &IKeyboardListener::keyHeld);
        gpEventDispatcher->removeEventListener(KeyboardSource::EVENT_KEY_RELEASED, this, &IKeyboardListener::keyReleased);
        gpEventDispatcher->removeEventListener(KeyboardSource::EVENT_KEY_PRESSED,  this, &IKeyboardListener::keyPressed);
    }

    virtual void keyPressed ( const Event& event ) { };
    virtual void keyReleased( const Event& event ) { };
    virtual void keyHeld    ( const Event& event ) { };

};

#endif