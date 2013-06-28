#pragma once

#ifndef __GAME_COMBINED_INPUT_H__
#define __GAME_COMBINED_INPUT_H__

#include "Common.h"
#include <GameObject.h>

#include <InputSourceType.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <GamePad.h>

struct GameCombinedInput
    : public GameObject
{
private:

    virtual void defaults( void )
    {
        Type    = INVALID_INPUT_SOURCE_TYPE;
        Key     = INVALID_KEY;
        Mouse   = INVALID_MOUSE_BUTTON;
        GamePad = INVALID_GAME_PAD_BUTTON;
    }

public:

    InputSourceType
        Type;

    KeyboardKey
        Key;

    MouseButton
        Mouse;

    GamePadButton
        GamePad;

    GameCombinedInput( void ) 
    {
        defaults();
    };

    GameCombinedInput( KeyboardKey key ) 
    {
        defaults();
        Type = INPUT_SOURCE_TYPE_KEYBOARD;
        Key = key;
    };

    GameCombinedInput( MouseButton mouseButton ) 
    {
        defaults();
        Type = INPUT_SOURCE_TYPE_MOUSE;
        Mouse = mouseButton;
    };

    GameCombinedInput( GamePadButton gamePadButton ) 
    {
        defaults();
        Type = INPUT_SOURCE_TYPE_GAME_PAD;
        GamePad = gamePadButton;
    };

    virtual string toString( void ) const
    {
        return "Game Combined Input";
    };

    bool operator==( const GameCombinedInput &rhs ) const
    {
        if (Type != rhs.Type)
            return false;

        switch (Type)
        {
        case INPUT_SOURCE_TYPE_KEYBOARD:

            return (Key == rhs.Key);

            break;
        case INPUT_SOURCE_TYPE_MOUSE:

            return (Mouse == rhs.Mouse);

            break;
        case INPUT_SOURCE_TYPE_GAME_PAD:

            return (GamePad == rhs.GamePad);

            break;
        }

        return false;
    }

    bool operator!=( const GameCombinedInput &rhs ) const
    {
        return !(*this == rhs);
    }
};

struct CompGameCombinedInput
    : public binary_function<GameCombinedInput, GameCombinedInput, bool>
{
    bool operator()(const GameCombinedInput& lhs, const GameCombinedInput& rhs) const
    {
        if (lhs.Type == rhs.Type)
        {
            switch (lhs.Type)
            {
            case INPUT_SOURCE_TYPE_KEYBOARD:

                return (lhs.Key < rhs.Key);

                break;
            case INPUT_SOURCE_TYPE_MOUSE:

                return (lhs.Mouse < rhs.Mouse);

                break;
            case INPUT_SOURCE_TYPE_GAME_PAD:

                return (lhs.GamePad < rhs.GamePad);

                break;
            }
        }

        return (lhs.Type < rhs.Type);
    }
};

#endif