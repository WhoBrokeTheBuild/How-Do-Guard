#pragma once

#ifndef __TEXT_BUTTON_H__
#define __TEXT_BUTTON_H__

#include "Common.h"
#include "Button.h"
#include <AnimatedUnit.h>

class TextButton :
    public Button
{
protected:

    CachedText
        *_pText;

    Font
        *_pFont;

public:

    Color
        TextColor,
        BorderColor,
        BGColor,
        HoverTextColor,
        HoverBorderColor,
        HoverBGColor;

    TextButton(void);
    virtual ~TextButton(void);

    virtual string toString( void ) const;

    virtual void init( Vector2 pos = Vector2::ZERO, string text = "Button", Vector2 padding = Vector2::ZERO );
    virtual void term( void );

    virtual void render( const Event& event );

    virtual Size   size( void );
    virtual string text ( void );

    virtual void setText( string text );

};

#endif