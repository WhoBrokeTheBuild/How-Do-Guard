#pragma once

#ifndef __ANIMATED_UNIT_H__
#define __ANIMATED_UNIT_H__

#include "ArcCommon.h"
#include "Unit.h"

#include "ArcApp.h"

#include "Animation.h"
#include "Color.h"
#include "RenderTarget.h"

class AnimatedUnit :
    public Unit
{
protected:

    Animation
        *_pAnimation;

    double
        _animationTimeout;

    int
        _frame;

    bool
        _animationComplete;

    virtual void updateAnimation( const FrameData* pFrameData );

public:

    static const EventType
        EVENT_ANIMATION_COMPLETE;

    bool
        Animating,
        Looping;

    AnimatedUnit( void );
    virtual ~AnimatedUnit( void );

    virtual string toString( void ) const;

    virtual void init( Animation* pAnimation = nullptr, Vector2 pos = Vector2::ZERO, Vector2 origin = Vector2::ZERO, float rot = 0.0f, Color color = Color::WHITE, float depth = 1.0f);
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual Animation* animation( void ) { return _pAnimation; }

    virtual void setAnimation( Animation* pAnimation, bool useDefaults = true);

    virtual void animationComplete( const Event& event );

};

#endif