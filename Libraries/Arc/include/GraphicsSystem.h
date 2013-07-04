#pragma once

#ifndef __GRAPHICS_SYSTEM_H__
#define __GRAPHICS_SYSTEM_H__

#include "ArcCommon.h"
#include "EventDispatcher.h"

#include "RenderTarget.h"
#include "Color.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

class GraphicsSystem :
    public EventDispatcher
{
private:

    Color
        _clearColor;

    RenderTarget
        *_pRenderTarget;

    int 
        _screenBPP;

    Size
        _windowSize;

    string 
        _windowTitle;

    bool
        _fullscreen;
    
    void resetGL( void );
    void resetVideoMode( void );

public:

    static const EventType EVENT_GRAPHICS_RESET;

    GraphicsSystem( void );
    virtual ~GraphicsSystem( void );

    virtual void init( Size windowSize, string windowTitle );
    virtual void term( void );

    virtual string toString( void ) const;

    virtual void setFullscreen ( bool fullscreen );
    virtual void setWindowSize ( Size size );
    virtual void setWindowTitle( string title );
    virtual void setClearColor ( Color clearColor );
    virtual void setWindowIcon ( string filename );

    virtual bool   fullscreen ( void ) { return _fullscreen;  }
    virtual Size   windowSize ( void ) { return _windowSize;  }
    virtual string windowTitle( void ) { return _windowTitle; }
    virtual Color  clearColor ( void ) { return _clearColor;  }

    virtual RenderTarget *renderTarget( void ) { return _pRenderTarget; };
};

#endif