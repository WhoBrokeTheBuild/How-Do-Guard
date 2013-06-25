#pragma once

#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "Common.h"
#include <Game.h>

#include "Button.h"

class Program :
    public Game
{
public:

    Button *button;

    static Font
        *spDefaultFont;

    Program(void);
    virtual ~Program(void);

    virtual string toString( void ) const;

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    void testLeave( const Event& event );
    void testEnter( const Event& event );
    void testPress( const Event& event );
    void testRelease( const Event& event );
    void testClick( const Event& event );
};

#endif