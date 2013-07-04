#pragma once

#ifndef __RECT_H__
#define __RECT_H__

#include "GameObject.h"
#include "Vector2.h"

class Circle;

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
    Rect( Vector2 pos, Size size );
    virtual ~Rect( void );

    virtual string toString( void ) const;

    void setPos( Vector2 pos );
    void setSize( Size size );

    float halfWidth ( void ) { return Width * 0.5f; }
    float halfHeight( void ) { return Height * 0.5f; }

    Vector2 center( void ) { return Vector2( X + halfWidth(), Y + halfHeight() ); }

    Vector2 pos ( void ) { return Vector2( X, Y ); }
    Size    size( void ) { return Vector2( Width, Height ); }

    float top   ( void ) { return Y; }
    float bottom( void ) { return Y + Height; }
    float left  ( void ) { return X; }
    float right ( void ) { return X + Width; }

    bool collides( Rect other );
    bool collides( Circle other );
    bool containsPoint( Vector2 point );

    const Rect operator+( const Rect &rhs ) const;
    const Rect operator-( const Rect &rhs ) const;

    Rect &operator+=( const Rect &rhs );
    Rect &operator-=( const Rect &rhs );

    bool operator==( const Rect &rhs ) const;
    bool operator!=( const Rect &rhs ) const;

};

struct CompRect 
    : public binary_function<Rect, Rect, bool>
{
    bool operator()(const Rect& lhs, const Rect& rhs) const
    {
        return lhs.X < rhs.X; // Simple Sorting
    }
};

#endif 