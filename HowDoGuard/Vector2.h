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
	virtual ~Vector2(void);

	float distanceTo(Vector2 v2);

	float directionToDeg(Vector2 v2);
	float directionToRad(Vector2 v2);

	const Vector2 operator+(const Vector2 &rhs) const;
	const Vector2 operator-(const Vector2 &rhs) const;
	const Vector2 operator*(float value) const;
	const Vector2 operator/(float value) const;

	Vector2 &operator+=(const Vector2 &rhs);
	Vector2 &operator-=(const Vector2 &rhs);
	Vector2 &operator*=(float value);
	Vector2 &operator/=(float value);
	Vector2 &operator=(const Vector2 &rhs);

	bool operator==(const Vector2 &rhs) const;
	bool operator!=(const Vector2 &rhs) const;

};

#endif