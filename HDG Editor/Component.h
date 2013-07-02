#pragma once

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Common.h"
#include <EventDispatcher.h>
#include <IMouseListener.h>

class Component :
    public EventDispatcher,
    public IMouseListener
{
protected:

    bool
        _hover;

public:

    bool 
        Focus;

    Vector2
        Pos,
        Padding;

    Component(void);
    virtual ~Component(void);

    virtual string toString( void ) const;

    virtual void init( Vector2 pos = Vector2::ZERO, Vector2 padding = Vector2::ZERO );
    virtual void term( void );

    virtual void update( const Event& event ) { };
    virtual void render( const Event& event ) { };

    virtual Size size( void ) { return Size::ZERO; }
    virtual Rect bounds( void ) { return Rect(Pos, size()); }

    virtual void mousePressed ( const Event& event );
    virtual void mouseMoved   ( const Event& event );

    virtual void hoverEnter( void );
    virtual void hoverLeave( void );

    virtual void clickedOn ( Vector2 mousePos );
    virtual void clickedOff( Vector2 mousePos );
};

#endif