#pragma once

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Common.h"
#include "Component.h"

class Button :
    public Component
{
protected:

    bool
        _held;

public:

    static const EventType EVENT_BUTTON_PRESSED;
    static const EventType EVENT_BUTTON_RELEASED;
    static const EventType EVENT_BUTTON_CLICKED;
    static const EventType EVENT_BUTTON_HOVER_ENTER;
    static const EventType EVENT_BUTTON_HOVER_LEAVE;

    Button(void);
    virtual ~Button(void);

    virtual string toString( void ) const;

    virtual void init( Vector2 pos = Vector2::ZERO, Vector2 padding = Vector2::ZERO );
    virtual void term( void );

    virtual void mouseMoved   ( const Event& event );
    virtual void mousePressed ( const Event& event );
    virtual void mouseReleased( const Event& event );

    virtual void hoverEnter( void );
    virtual void hoverLeave( void );

};

#endif