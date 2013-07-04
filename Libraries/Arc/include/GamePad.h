#pragma once

#ifndef __GAME_PAD_H__
#define __GAME_PAD_H__

#include <string>

using namespace std;

enum GamePadButton
{
    INVALID_GAME_PAD_BUTTON = -1,

    DPAD_UP,
    DPAD_UP_LEFT,
    DPAD_LEFT,
    DPAD_DOWN_LEFT,
    DPAD_DOWN,
    DPAD_DOWN_RIGHT,
    DPAD_RIGHT,
    DPAD_UP_RIGHT,

    BUMPER_LEFT,
    BUMPER_RIGHT,

    TRIGGER_LEFT,
    TRIGGER_RIGHT,

    FACE_NORTH,
    FACE_SOUTH,
    FACE_EAST,
    FACE_WEST,

    START,
    SELECT,

    STICK_LEFT_PRESS,
    STICK_RIGHT_PRESS,

    STICK_LEFT_UP,
    STICK_LEFT_DOWN,
    STICK_LEFT_RIGHT,
    STICK_LEFT_LEFT,

    STICK_RIGHT_UP,
    STICK_RIGHT_DOWN,
    STICK_RIGHT_RIGHT,
    STICK_RIGHT_LEFT,

    NUM_GAME_PAD_BUTTONS
};

const string GAME_PAD_BUTTON_NAMES[NUM_GAME_PAD_BUTTONS] =
{
    "D-Pad Up",
    "D-Pad Up-Left",
    "D-Pad Left",
    "D-Pad Down-Left",
    "D-Pad Down",
    "D-Pad Down-Right",
    "D-Pad Right",
    "D-Pad Up-Right",

    "Left Bumper",
    "Right Bumper",

    "Left Trigger",
    "Right Trigger",

    "Face Button North",
    "Face Button South",
    "Face Button East",
    "Face Button West",

    "Start Button",
    "Select Button",

    "Left Stick Press",
    "Right Stick Press",

    "Left Stick Up",
    "Left Stick Down",
    "Left Stick Right"
    "Left Stick Left",

    "Right Stick Up",
    "Right Stick Down",
    "Right Stick Right"
    "Right Stick Left"
};

#endif