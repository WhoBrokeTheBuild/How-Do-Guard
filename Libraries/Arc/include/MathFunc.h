#pragma once

#ifndef __MATH_FUNC_H__
#define __MATH_FUNC_H__

#include <cmath>

#define PI  3.14159
#define PI2 6.28318

#define TO_RAD (PI / 180.0)
#define TO_DEG (180.0 / PI)

inline float toRad( float deg ) { return (float)( deg * TO_RAD ); }
inline float toDeg( float rad ) { return (float)( rad * TO_DEG ); };

inline double toRad( double deg ) { return (double)( deg * TO_RAD ); }
inline double toDeg( double rad ) { return (double)( rad * TO_DEG ); };

float floor  (float value, int accuracy);
float nearest(float value, int accuracy);
float ceil   (float value, int accuracy);

double floor  (double value, int accuracy);
double nearest(double value, int accuracy);
double ceil   (double value, int accuracy);

template <class Number>
Number clamp(Number value, Number min, Number max) { return ( ( value > max ) ? max : ( ( value < min ) ? min : value ) ); }

template <class Number>
Number lerp( Number start, Number end, float fraction) { return ( start + (end - start) * fraction ); }

template <class Number>
int sign( Number value ) { return ( value > 0 ? 1 : ( value < 0 ? -1 : 0 ) ); }

template <class Number>
Number approach( Number value, Number target, Number speed ) { return ( ( value > target ) ? max( value - speed, target ) : min( value + speed, target ) ); }

template <class Number>
Number reduce( Number value, Number speed ) { return ( ( value > 0 ) ? max( value - speed, 0 ) : min( value + speed, 0 ) ); }

template <class Number>
bool between( Number value, Number min, Number max ) { return ( value >= min && value <= max); }

#endif