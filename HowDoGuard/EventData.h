#pragma once

#ifndef __EVENT_DATA_H__
#define __EVENT_DATA_H__

#include "Common.h"
#include "GameObject.h"

class EventData
	: public GameObject
{
public:

	virtual EventData *clone( void ) const { return New EventData(); };

	virtual string toString( void ) const { return "Event Data"; };

};

class PointData
	: public EventData
{
public:

	float 
		X,
		Y;

	PointData( float x, float y ) { X = x; Y = y; };
	PointData( Vector2 point ) { X = point.X; Y = point.Y; };

	Vector2 vector2( void ) { return Vector2(X, Y); };

	virtual EventData *clone( void ) const { return New PointData(X, Y); };

	virtual string toString( void ) const 
	{ 
		stringstream ss;
		ss << "Point Data [X: " << X << ", Y: " << Y << "]";
		return ss.str();
	};

};

class CountData
	: public EventData
{
public:

	int 
		Count;

	CountData( int count ) { Count = count; };

	virtual EventData *clone( void ) { return New CountData(Count); };

	virtual string toString( void ) const 
	{ 
		stringstream ss;
		ss << "Count Data [Count: " << Count << "]";
		return ss.str();
	};

};

#endif