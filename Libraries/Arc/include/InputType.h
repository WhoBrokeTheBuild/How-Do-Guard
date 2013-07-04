#pragma once

#ifndef __INPUT_TYPE_H__
#define __INPUT_TYPE_H__

#include <string>

using namespace std;

enum InputType
{
    INVALID_INPUT_TYPE = -1,

    INPUT_TYPE_PRESSED,
    INPUT_TYPE_RELEASED,
    INPUT_TYPE_HELD,
    INPUT_TYPE_OTHER,

    NUM_INPUT_TYPES
};

const string INPUT_TYPE_NAMES[NUM_INPUT_TYPES] = 
{
    "Pressed",
    "Released",
    "Held",
    "Other"
};

#endif