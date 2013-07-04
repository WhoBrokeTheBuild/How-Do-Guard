#pragma once

#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include "GameObject.h"
#include "Functions.h"

class Vector2;

typedef Vector2 Point;
typedef Vector2 Size;

class Vector2
    : public GameObject
{
private:

public:

    static Vector2
        ZERO,
        ONE,
        NEGATIVE_ONE;

    float
        X,
        Y;

    Vector2( void );
    Vector2( float x, float y );
    Vector2( float both );
    virtual ~Vector2( void );

    virtual string toString( void ) const;

    float distanceTo( Vector2 other );
    float directionToDeg( Vector2 other );
    float directionToRad( Vector2 other );

    float halfX( void ) { return (X * 0.5f); }
    float halfY( void ) { return (Y * 0.5f); }

    float width( void )  { return X; }
    float height( void ) { return Y; }
    float halfWidth( void )  { return halfX(); }
    float halfHeight( void ) { return halfY(); }

    const Vector2 operator+( const Vector2 &rhs ) const;
    const Vector2 operator-( const Vector2 &rhs ) const;
    const Vector2 operator*( float value ) const;
    const Vector2 operator/( float value ) const;

    Vector2 &operator+=( const Vector2 &rhs );
    Vector2 &operator-=( const Vector2 &rhs );
    Vector2 &operator*=( float value );
    Vector2 &operator/=( float value );
    Vector2 &operator= ( const Vector2 &rhs );

    bool operator==( const Vector2 &rhs ) const;
    bool operator!=( const Vector2 &rhs ) const;

};

struct CompVector2
    : public binary_function<Vector2, Vector2, bool>
{
    bool operator()(const Vector2& lhs, const Vector2& rhs) const
    {
        return lhs.X < rhs.X; // Simple Sorting
    }
};

#endif