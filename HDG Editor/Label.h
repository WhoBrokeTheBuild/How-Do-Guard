#pragma once

#ifndef __LABEL_H__
#define __LABEL_H__

#include "Common.h"
#include "Component.h"

#include <CachedText.h>

class Label :
    public Component
{
private:

    CachedText
        *_pText;

public:

    Color
        TextColor;

    Label( void ) { }
    virtual ~Label( void ) { term(); }

    virtual string toString( void ) const;

    virtual void init( Vector2 pos = Vector2::ZERO, string text = "Label", Vector2 padding = Vector2::ZERO );
    virtual void term( void );

    virtual void render( const Event& event );

    virtual Size size( void ) { return _pText->size() + (Padding * 2.0f); }

    virtual void setText( string text ) { _pText->setText(text); }
    virtual string text ( void )        { return _pText->text(); }

};

#endif