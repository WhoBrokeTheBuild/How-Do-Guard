#pragma once

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Common.h"
#include <Unit.h>

class Button :
    public Unit
{
protected:

    CachedText
        *_pText;

    Font
        *_pFont;

    bool
        _hover,
        _held;

public:

    Vector2
        Padding;

    Color
        TextColor,
        BorderColor,
        BGColor,
        HoverTextColor,
        HoverBorderColor,
        HoverBGColor;

    static const EventType EVENT_BUTTON_PRESSED;
    static const EventType EVENT_BUTTON_RELEASED;
    static const EventType EVENT_BUTTON_CLICKED;
    static const EventType EVENT_BUTTON_HOVER_ENTER;
    static const EventType EVENT_BUTTON_HOVER_LEAVE;

    Button(void);
    virtual ~Button(void);

    virtual string toString( void ) const;

    virtual void init( Vector2 pos = Vector2::ZERO, string button = "", Vector2 origin = Vector2::ZERO, float rot = 0.0f, Color blendColor = Color::WHITE, float depth = 1.0f );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual void setText( string text );

    virtual void mouseMoved( const Event& event );
    virtual void mouseButtonPressed( const Event& event );
    virtual void mouseButtonReleased( const Event& event );

};

#endif