#pragma once

#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include "ArcCommon.h"
#include "EventDispatcher.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "GamePad.h"
#include "InputState.h"

#include "KeyboardSource.h"
#include "MouseSource.h"
#include "TextInputSource.h"

class InputSystem :
    public EventDispatcher
{
protected:

    KeyboardSource
        *_pKeyboardSource;

    MouseSource
        *_pMouseSource;

    TextInputSource
        *_pTextInputSource;

    virtual void handleSDLEvent( SDL_Event sdlEvent );

public:

    InputSystem( void );
    virtual ~InputSystem( void );

    virtual string toString( void ) const;

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
};

#endif