#pragma once

#ifndef __IMOUSE_LISTENER_H__
#define __IMOUSE_LISTENER_H__

#include "ArcCommon.h"
#include "MouseSource.h"

class IMouseListener
{
public:

    IMouseListener( void ) { }
    virtual ~IMouseListener( void ) { term(); };

    virtual void init( void )
    {
        gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_PRESSED,  this, &IMouseListener::mousePressed);
        gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_RELEASED, this, &IMouseListener::mouseReleased);
        gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_HELD,     this, &IMouseListener::mouseHeld);
        gpEventDispatcher->addEventListener(MouseSource::EVENT_MOUSE_MOVED,    this, &IMouseListener::mouseMoved);
    }

    virtual void term( void )
    {
        gpEventDispatcher->removeEventListener(MouseSource::EVENT_MOUSE_MOVED,    this, &IMouseListener::mouseMoved);
        gpEventDispatcher->removeEventListener(MouseSource::EVENT_MOUSE_HELD,     this, &IMouseListener::mouseHeld);
        gpEventDispatcher->removeEventListener(MouseSource::EVENT_MOUSE_RELEASED, this, &IMouseListener::mouseReleased);
        gpEventDispatcher->removeEventListener(MouseSource::EVENT_MOUSE_PRESSED,  this, &IMouseListener::mousePressed);
    }

    virtual void mousePressed ( const Event& event ) { };
    virtual void mouseReleased( const Event& event ) { };
    virtual void mouseHeld    ( const Event& event ) { };
    virtual void mouseMoved   ( const Event& event ) { };

};

#endif