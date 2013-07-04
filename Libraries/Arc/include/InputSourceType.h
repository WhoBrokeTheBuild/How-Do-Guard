#pragma once

#ifndef __INPUT_SOURCE_TYPE_H__
#define __INPUT_SOURCE_TYPE_H__

#include <string>

using namespace std;

enum InputSourceType
{
    INVALID_INPUT_SOURCE_TYPE = -1,

    INPUT_SOURCE_TYPE_KEYBOARD,
    INPUT_SOURCE_TYPE_MOUSE,
    INPUT_SOURCE_TYPE_GAME_PAD,

    NUM_INPUT_SOURCE_TYPES
};

const string INPUT_SOURCE_TYPE_NAMES[NUM_INPUT_SOURCE_TYPES] = 
{
    "Keyboard",
    "Mouse",
    "Game Pad"
};

#endif