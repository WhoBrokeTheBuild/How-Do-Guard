#pragma once

#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <string>
#include <SDL.h>

using namespace std;

const int 
    MOUSE_WHEEL_DOWN = 4,
    MOUSE_WHEEL_UP   = 5;

enum MouseButton
{
    INVALID_MOUSE_BUTTON = -1,

    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_RIGHT,

    NUM_MOUSE_BUTTONS
};

const string MOUSE_BUTTON_NAMES[NUM_MOUSE_BUTTONS] = 
{
    "Left Button",
    "Middle Button",
    "Right Button"
};

#endif