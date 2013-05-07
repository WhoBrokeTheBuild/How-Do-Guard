#pragma once

#ifndef __RECT_H__
#define __RECT_H__

#include "GameObject.h"
#include "Vector2.h"

class Rect
	: public GameObject
{
private:

public:

	static Rect
		ZERO,
		ONE;

	float 
		X,
		Y,
		Width,
		Height;

	Rect( void );
	Rect( float x, float y, float width, float height );
	virtual ~Rect( void );

	virtual string toString( void ) const;

	void setPos( Vector2 pos );
	void setSize( Vector2 size );

	float halfWidth ( void ) { return Width / 2; }
	float halfHeight( void ) { return Height / 2; }

	Vector2 center( void ) { return Vector2( X + halfWidth(), Y + halfHeight() ); }

	Vector2 pos ( void ) { return Vector2( X, Y ); }
	Vector2 size( void ) { return Vector2( Width, Height ); }

	float top   ( void ) { return Y; }
	float bottom( void ) { return Y + Height; }
	float left  ( void ) { return X; }
	float right ( void ) { return X + Width; }

	bool collides(Rect other);
	bool containsPoint(Vector2 point);

};

#endif 