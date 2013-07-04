#pragma once

#ifndef __CONFIG_TYPE_H__
#define __CONFIG_TYPE_H__

#include <string>

using namespace std;

enum ConfigType
{
    INVALID_CONFIG_TYPE = -1,

    CONFIG_TYPE_OBJECT,
    CONFIG_TYPE_INT,
    CONFIG_TYPE_FLOAT,
    CONFIG_TYPE_BOOL,
    CONFIG_TYPE_STRING,
    CONFIG_TYPE_VECTOR2,
    CONFIG_TYPE_RECT,
    CONFIG_TYPE_CIRCLE,
    CONFIG_TYPE_COLOR,

    NUM_CONFIG_TYPES
};

const string CONFIG_TYPE_NAMES[NUM_CONFIG_TYPES] = 
{
    "Object",
    "Int",
    "Float",
    "Bool",
    "String",
    "Vector2",
    "Rect",
    "Circle",
    "Color"
};

#endif