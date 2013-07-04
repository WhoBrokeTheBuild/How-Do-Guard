#pragma once

#ifndef __KEYBOARD_CONTROLLER_H__
#define __KEYBOARD_CONTROLLER_H__

#include "ArcCommon.h"
#include "EventDispatcher.h"

#include "Keyboard.h"
#include "InputState.h"

#include "Map.h"

typedef Map<KeyboardKey, InputState> KeyStateMap;

class KeyboardSource :
    public EventDispatcher
{
private:

    Uint8
        *_sdlKeys;

protected:

    KeyStateMap
        _keyStates;

public:

    static const EventType 
        EVENT_KEY_PRESSED,
        EVENT_KEY_RELEASED,
        EVENT_KEY_HELD;

    KeyboardSource( void );
    virtual ~KeyboardSource( void );

    virtual string toString( void ) const;

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
};

#endif