
#pragma once

#ifndef __COLOR_H__
#define __COLOR_H__

#include "Common.h"
#include "GameObject.h"

class Color
	: public GameObject
{

private:

	int 
		mRed,
		mGreen,
		mBlue,
		mAlpha;

public:

	static Color
		BLACK,
		WHITE,
		RED,
		GREEN,
		BLUE,
		CORNFLOWER_BLUE,
		STORM;

	Color( void );

	Color( float pR, float pG, float pB );
	Color( float pR, float pG, float pB, float pA );

	Color( int pR, int pG, int pB );
	Color( int pR, int pG, int pB, int pA );

	virtual ~Color( void );

	virtual void init( void );
	virtual void init( int pR, int pG, int pB, int pA );
	virtual void term( void );

	virtual string toString( void ) const;

	void setRGB ( float pR, float pG, float pB );
	void setRGBA( float pR, float pG, float pB, float pA );

	void setRGB ( int pR, int pG, int pB );
	void setRGBA( int pR, int pG, int pB, int pA );

	float getR( void ) const;
	float getG( void ) const;
	float getB( void ) const;
	float getA( void ) const;

	void getRGB ( int &pR, int &pG, int &pB );
	void getRGBA( int &pR, int &pG, int &pB, int &pA );
				  
	void getRGB ( float &pR, float &pG, float &pB );
	void getRGBA( float &pR, float &pG, float &pB, float &pA );

};

#endif  //__COLOR_H__