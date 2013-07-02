#pragma once

#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__

#include "Common.h"
#include "Component.h"
#include <ITextInputListener.h>

#include <map>

class Textbox :
    public Component,
    public ITextInputListener
{
protected:

    Font
        *_pFont;

    map<char, CachedText*>
        _cachedChars;

    Size
        _maxCharSize;

    bool 
        _cursorShown;

    unsigned int
        _charWidth,
        _cursorPos,
        _textPos;

    float
        _width;

    double 
        _cursorTimeout,
        _cursorSpeed;

    virtual void insert( char ch );
    virtual void remove( bool before = true );

    virtual void checkTextPos( void );

public:

    string
        Text;

    Color
        TextColor,
        BorderColor,
        BGColor,
        FocusTextColor,
        FocusBorderColor,
        FocusBGColor;

	Textbox();
    virtual ~Textbox();

    virtual string toString( void ) const;

    virtual void init( Vector2 pos = Vector2::ZERO, float width = 100, Vector2 padding = Vector2(5.0f) );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual void textInputChar     ( const Event& event );
    virtual void textInputBackspace( const Event& event );
    virtual void textInputDelete   ( const Event& event );
    virtual void textInputArrows   ( const Event& event );
    virtual void textInputHomeEnd  ( const Event& event );

    virtual void clickedOn ( Vector2 mousePos );
    virtual void clickedOff( Vector2 mousePos );

    virtual Size size( void );

};

#endif