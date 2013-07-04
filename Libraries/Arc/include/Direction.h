#pragma once

#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <string>

using namespace std;

enum Direction
{
    INVALID_DIRECTION = -1,

    DIR_NORTH,
    DIR_NORTH_WEST,
    DIR_WEST,
    DIR_SOUTH_WEST,
    DIR_SOUTH,
    DIR_SOUTH_EAST,
    DIR_EAST,
    DIR_NORTH_EAST,

    NUM_DIRECTIONS
};

const string DIRECTION_NAMES[NUM_DIRECTIONS] = 
{
    "North",
    "North West",
    "West",
    "South West",
    "South",
    "South East",
    "East",
    "North East"
};

#endif