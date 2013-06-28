#pragma once

#ifndef __GAME_INPUT_CHANGE_H__
#define __GAME_INPUT_CHANGE_H__

#include "Common.h"
#include <GameObject.h>

#include "GameCombinedInput.h"
#include <InputType.h>

struct GameInputChange
    : public GameObject
{

    GameCombinedInput
        Input;

    InputType
        Type;

    GameInputChange( GameCombinedInput input = GameCombinedInput(), InputType type = INVALID_INPUT_TYPE)
    {
        Input = input;
        Type  = type;
    }

    virtual string toString( void ) const { return "Game Input Change"; }

};

#endif