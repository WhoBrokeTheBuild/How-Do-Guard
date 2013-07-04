#pragma once

#ifndef __ARC_APP_H__
#define __ARC_APP_H__

#include "ArcCommon.h"
#include "EventDispatcher.h"
#include "Event.h"

#include "GraphicsSystem.h"
#include "RenderTarget.h"

#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"

#include "CachedText.h"

#include "InputSystem.h"

#include "Timer.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>

class ArcApp :
    public EventDispatcher
{
protected:

    GraphicsSystem
        *_pGraphicsSystem;

    InputSystem 
        *_pInputSystem;

    bool
        _running;

    float 
        _targetFPS,
        _currentFPS;

public:

    static const EventType 
        EVENT_ENTER_FRAME,
        EVENT_FRAME,
        EVENT_EXIT_FRAME,
        EVENT_RENDER_START,
        EVENT_RENDER,
        EVENT_RENDER_END,
        EVENT_EXIT;

    ArcApp( void );
    virtual ~ArcApp( void );

    virtual string toString( void ) const;

    virtual void init( Size windowSize = Size(640, 480), string windowTitle = "Arc" );
    virtual void term( void );

    virtual void start( void );
    virtual void stop ( const Event& event );

    virtual void updateFrame( const FrameData&  frameData );
    virtual void renderFrame( const RenderData& renderData );

    virtual void initGraphics( Size windowSize, string windowTitle );
    virtual void initInput   ( void );
    virtual void initAudio   ( void );

    virtual void update( const Event& event ) { };
    virtual void render( const Event& event ) { };
};

#endif
