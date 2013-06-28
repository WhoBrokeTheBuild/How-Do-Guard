#pragma once

#ifndef __IMAGE_BUTTON_H__
#define __IMAGE_BUTTON_H__

#include "Common.h"
#include "Button.h"

#include <Sprite.h>

class ImageButton :
    public Button
{
protected:

    Sprite
        *_pImage,
        *_pHoverImage;

public:

    Color
        BlendColor,
        HoverBlendColor;

    ImageButton(void);
    virtual ~ImageButton(void);

    virtual string toString( void ) const;

    virtual void init( Vector2 pos = Vector2::ZERO, Sprite* image = nullptr, Sprite* hoverImage = nullptr, Vector2 padding = Vector2::ZERO );
    virtual void term( void );

    virtual Size size( void );

    virtual void render( const Event& event );

};

#endif