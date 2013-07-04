#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "ArcCommon.h"
#include "GameObject.h"

#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL.h>

class RenderTarget;
class CachedText;
class Event;

class Texture :
    public GameObject
{

    friend class RenderTarget;
    friend class CachedText;

private:

    string
        _filename;

    GLuint
        _texture;

    Size
        _size;

    virtual void init( SDL_Surface* pSurface );

    virtual void load( string filename );
    virtual void load( SDL_Surface* pSurface );

    virtual void deleteTexture( void );

    virtual GLuint GLTexture( void ) { return _texture; }

public:

    Texture( void );
    virtual ~Texture( void );

    virtual string toString( void ) const;

    virtual void init( string filename );
    virtual void term( void );

    virtual void graphicsReset( const Event& event );

    virtual Size size( void ) { return _size; }

};

#endif