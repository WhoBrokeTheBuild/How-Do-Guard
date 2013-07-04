#pragma once

#ifndef __RAND_FUNC_H__
#define __RAND_FUNC_H__

#include <cstdlib>
#include <ctime>

void initRandom( void );

int    randInt   ( int    min, int    max );
float  randFloat ( float  min, float  max );
double randDouble( double min, double max );

#endif