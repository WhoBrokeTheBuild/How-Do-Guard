
#include "Color.h"

Color Color::BLACK = Color(0, 0, 0);
Color Color::WHITE = Color(255, 255, 255);
Color Color::RED   = Color(255, 0, 0);
Color Color::GREEN = Color(0, 255, 0);
Color Color::BLUE  = Color(0, 0, 255);
Color Color::CORNFLOWER_BLUE = Color(100, 149, 237);
Color Color::STORM = Color(0, 170, 170);

Color::Color( void )
{
	init(0, 0, 0, 255);
}

Color::Color( float pR, float pG, float pB )
{
	init((int)(pR * 255), (int)(pG * 255),(int)(pB * 255), 255);
}

Color::Color( float pR, float pG, float pB, float pA )
{
	init((int)(pR * 255), (int)(pG * 255),(int)(pB * 255), (int)(pA * 255));
}

Color::Color( int pR, int pG, int pB )
{
	init(pR, pG, pB, 255);
}

Color::Color( int pR, int pG, int pB, int pA )
{
	init(pR, pG, pB, pA);
}

Color::~Color( void )
{
	term();
}

void Color::init( void )
{
}

void Color::init( int pR, int pG, int pB, int pA )
{
	mRed = clamp(pR, 0, 255);
	mGreen = clamp(pG, 0, 255);
	mBlue = clamp(pB, 0, 255);
	mAlpha = clamp(pA, 0, 255);
}

void Color::term( void )
{
}

string Color::toString( void ) const
{
	stringstream ss;
	ss << "Color [" << getR() << ", " << getG() << ", " << getB() << ", " << getA() << "]" << endl;
	return ss.str();
}

void Color::setRGB( float pR, float pG, float pB )
{
	mRed = clamp((int)(pR * 255), 0, 255);
	mGreen = clamp((int)(pG * 255), 0, 255);
	mBlue = clamp((int)(pB * 255), 0, 255);
}

void Color::setRGBA( float pR, float pG, float pB, float pA )
{
	mRed = clamp((int)(pA * 255), 0, 255);
	mGreen = clamp((int)(pG * 255), 0, 255);
	mBlue = clamp((int)(pB * 255), 0, 255);
	mAlpha = clamp((int)(pA * 255), 0, 255);
}

void Color::setRGB( int pR, int pG, int pB )
{
	mRed = clamp(pR, 0, 255);
	mGreen = clamp(pG, 0, 255);
	mBlue = clamp(pB, 0, 255);
}

void Color::setRGBA( int pR, int pG, int pB, int pA )
{
	mRed = clamp(pR, 0, 255);
	mGreen = clamp(pG, 0, 255);
	mBlue = clamp(pB, 0, 255);
	mAlpha = clamp(pA, 0, 255);
}

float Color::getR( void ) const
{
	return (float)(mRed / 255.0f);
}

float Color::getG( void ) const
{
	return (float)(mGreen / 255.0f);
}

float Color::getB( void ) const
{
	return (float)(mBlue / 255.0f);
}

float Color::getA( void ) const
{
	return (float)(mAlpha / 255.0f);
}

void Color::getRGB( int &pR, int &pG, int &pB )
{
	pR = mRed;
	pG = mGreen;
	pB = mBlue;
}

void Color::getRGBA( int &pR, int &pG, int &pB, int &pA )
{
	pR = mRed;
	pG = mGreen;
	pB = mBlue;
	pA = mAlpha;
}

void Color::getRGB( float &pR, float &pG, float &pB )
{
	pR = (float)(mRed / 255.0f);
	pG = (float)(mGreen / 255.0f);
	pB = (float)(mBlue / 255.0f);
}

void Color::getRGBA( float &pR, float &pG, float &pB, float &pA )
{
	pR = (float)(mRed / 255.0f);
	pG = (float)(mGreen / 255.0f);
	pB = (float)(mBlue / 255.0f);
	pA = (float)(mAlpha / 255.0f);
}