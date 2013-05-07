
#pragma once

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Defines.h"

#include <iostream>
#include <string>
#include <cstdarg>
#include <ctime>

#define PI  3.14159
#define PI2 6.28318

using namespace std;

#ifdef DEBUG

#define ERR(SRC, MSG) \
	cerr << "[" << SRC << "] Error: " << MSG << " (In " << basename(__FILE__) << " on line " << __LINE__ << ")" << endl;

#define INF(SRC, MSG) \
	cout << "[" << SRC << "] Info: " << MSG << " (In " << basename(__FILE__) << " on line " << __LINE__ << ")" << endl;

#else

#define ERR(SRC, MSG)
#define INF(SRC, MSG)

#endif //DEBUG

template <class T>
T clamp(T n, T min, T max)
{
	if (n < min)
		n = min;
	else if (n > max)
		n = max;

	return n;
}

template <class T>
T lerp(T n, T start, T end)
{
	return start + (end - start) * n;
}

template <class T>
void copy_array(T from[], T to[], int count)
{
	for (int i = 0; i < count; ++i)
		to[i] = from[i];
}

void die( int errorLevel );

void init_utils( void );

int rand( int min, int max );

void delay( int millis );

string basename(string fullPath);

float deg_to_rad( float deg );
float rad_to_deg( float rad );

#endif 