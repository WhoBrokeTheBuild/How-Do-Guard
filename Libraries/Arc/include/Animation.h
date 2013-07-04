#pragma once

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "ArcCommon.h"
#include "EventDispatcher.h"

#include "ArrayList.h"

#include "Sprite.h"

class Animation :
    public EventDispatcher
{
private:

    ArrayList<Sprite*>
        _frames;

public:

    bool
        Looping;

    Animation( void );
    virtual ~Animation( void );

    virtual string toString( void ) const;

    virtual void init( ArrayList<Sprite*> frames = ArrayList<Sprite*>(), bool looping = false );
    virtual void term( void );

    virtual bool hasFrame   ( int frame );
    virtual void addFrame   ( Sprite* pFrame );
    virtual bool removeFrame( int pFrame );
    virtual bool removeFrame( Sprite* pFrame );

    virtual Size    frameSize( int frame );
    virtual Sprite* frameAt  ( int frame );

    virtual int length( void ) { return (int)_frames.size(); }

};

#endif