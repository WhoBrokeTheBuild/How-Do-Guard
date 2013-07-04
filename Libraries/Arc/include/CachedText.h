#pragma once

#ifndef __TEXT_H__
#define __TEXT_H__

#include "ArcCommon.h"
#include "GameObject.h"

#include "Texture.h"
#include "Font.h"
#include "Color.h"

class CachedText :
    public GameObject
{
private:

    Texture
        *_pTexture;

    string
        _text;

    Font
        *_pFont;

public:

    CachedText( void );
    virtual ~CachedText( void );

    virtual string toString( void ) const;

    virtual void init( string text, Font* pFont );
    virtual void term( void );

    virtual void graphicsReset( const Event& event );
    virtual void renderText( void );

    virtual string text( void ) const { return _text; }
    virtual void   setText( string text );

    virtual Size size( void );
    virtual Size measureString( string text );

    virtual Texture* texture( void ) { return _pTexture; }
};

#endif