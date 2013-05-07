#include "Circle.h"
#include "Rect.h"

Circle::Circle( void )
{
}

Circle::Circle( float x, float y, float radius )
{
	X = x;
	Y = y;
	Radius = radius;
}

Circle::Circle( Vector2 pos, float radius )
{
	X = pos.X;
	Y = pos.Y;
	Radius = radius;
}

Circle::~Circle( void )
{
}

std::string Circle::toString( void ) const
{
	stringstream ss;
	ss << "Circle [X: " << X << ", Y: " << Y << ", R:" << Radius << "]";
	return ss.str();
}

Vector2 Circle::pos( void )
{
	return Vector2( X, Y );
}

float Circle::diameter( void )
{
	return Radius * 2.0f;
}

float Circle::top( void )
{
	return Y - Radius;
}

float Circle::bottom( void )
{
	return Y + Radius;
}

float Circle::left( void )
{
	return X - Radius;
}

float Circle::right( void )
{
	return X + Radius;
}

bool Circle::collides( Circle other )
{
	float dist = pos().distanceTo(other.pos());

	return (dist < Radius + other.Radius);
}

bool Circle::collides( Rect rect ) //TODO: Test this later when primitives are implemented
{
	Rect bounds = Rect(left(), top(), diameter(), diameter());

	if (!rect.collides(bounds))
		return false;

	return true;
}

bool Circle::containsPoint( Vector2 point )
{
	return (pos().distanceTo(point) < Radius);
}
