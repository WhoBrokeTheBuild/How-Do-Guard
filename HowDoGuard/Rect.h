#pragma once

#ifndef __RECT_H__
#define __RECT_H__

#include "Vector2.h"

class Rect
{
private:

public:

	Rect
		ZERO,
		ONE;

	float 
		X,
		Y,
		Width,
		Height;

	Rect( void );
	Rect(  );
	virtual ~Rect( void );

	float halfWidth( void ) { return Width / 2; }
	float halfHeight( void ) { return Height / 2; }

	float top( void ) { return Y; }
	float bottom( void ) { return Y + Height; }
	float left( void ) { return X; }
	float right( void ) { return X + Width; }

};

#endif 