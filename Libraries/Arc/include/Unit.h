#pragma once

#ifndef __UNIT_H__
#define __UNIT_H__

#include "ArcCommon.h"
#include "EventDispatcher.h"

#include "ArcApp.h"

class Unit :
    public EventDispatcher
{
public:

    Vector2
        Pos,
        Origin;

    Size
        UnitSize;

    Color
        BlendColor;

    float
        Rot,
        Depth;

    Unit(void);
    virtual ~Unit(void);

    virtual string toString( void ) const;

    virtual void init( Vector2 pos = Vector2::ZERO, Vector2 origin = Vector2::ZERO, float rot = 0.0f, Color blendColor = Color::WHITE, float depth = 1.0f);
    virtual void term( void );

    virtual Rect bounds( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );
};

#endif