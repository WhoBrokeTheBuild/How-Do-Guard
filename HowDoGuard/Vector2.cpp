#include "Vector2.h"

Vector2::Vector2(void)
{
}

Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Vector2::~Vector2(void)
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

}

const Vector2 Vector2::operator*( float value ) const
{

}

const Vector2 Vector2::operator/( float value ) const
{

}

Vector2 & Vector2::operator+=( const Vector2 &rhs )
{

}

Vector2 & Vector2::operator-=( const Vector2 &rhs )
{

}

Vector2 & Vector2::operator*=( float value )
{

}

Vector2 & Vector2::operator/=( float value )
{

}

Vector2 & Vector2::operator=( const Vector2 &rhs )
{

}

bool Vector2::operator==( const Vector2 &rhs ) const
{

}

bool Vector2::operator!=( const Vector2 &rhs ) const
{

}
