#include "Vector2.h"

Vector2::Vector2( void )
{
}

Vector2::Vector2( float x, float y )
{
	X = x;
	Y = y;
}

Vector2::Vector2( float both )
{
	X = both;
	Y = both;
}

Vector2::~Vector2( void )
{
}

const Vector2 Vector2::operator+( const Vector2 &rhs ) const
{
	Vector2 result = *this;
	result += rhs;
	return result;
}

const Vector2 Vector2::operator-( const Vector2 &rhs ) const
{
	Vector2 result = *this;
	result -= rhs;
	return result;
}

const Vector2 Vector2::operator*( float value ) const
{
	Vector2 result = *this;
	result *= value;
	return result;
}

const Vector2 Vector2::operator/( float value ) const
{
	Vector2 result = *this;
	result /= value;
	return result;
}

Vector2 & Vector2::operator+=( const Vector2 &rhs )
{
	X += rhs.X;
	Y += rhs.Y;
	return *this;
}

Vector2 & Vector2::operator-=( const Vector2 &rhs )
{
	X -= rhs.X;
	Y -= rhs.Y;
	return *this;
}

Vector2 & Vector2::operator*=( float value )
{
	X *= value;
	Y *= value;
	return *this;
}

Vector2 & Vector2::operator/=( float value )
{
	X /= value;
	Y /= value;
	return *this;
}

Vector2 & Vector2::operator=( const Vector2 &rhs )
{
	X = rhs.X;
	Y = rhs.Y;
	return *this;
}

bool Vector2::operator==( const Vector2 &rhs ) const
{
	return (X == rhs.X && Y == rhs.Y);
}

bool Vector2::operator!=( const Vector2 &rhs ) const
{
	return !(*this == rhs);
}
