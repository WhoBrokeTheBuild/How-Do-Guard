#pragma once

#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

class Vector2
{
private:

public:

	float
		X,
		Y;

	Vector2(void);

	Vector2(float x, float y);

	float distanceTo(Vector2 v2);

	float directionToDeg(Vector2 v2);
	float directionToRad(Vector2 v2);

	virtual ~Vector2(void);

};

#endif