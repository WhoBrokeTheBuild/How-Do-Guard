#pragma once

#ifndef __INPUT_STATE_H__
#define __INPUT_STATE_H__

#include "ArcCommon.h"
#include "GameObject.h"

struct InputState
    : public GameObject
{
    bool
        Pressed,
        Released,
        Down,
        Tapped;

    InputState( bool pressed = false, bool released = false, bool down = false, bool tapped = false )
    {
        Pressed  = pressed;
        Released = released;
        Down     = down;
        Tapped   = tapped;
    }

    virtual string toString( void ) const { return "Input State"; }
};

#endif