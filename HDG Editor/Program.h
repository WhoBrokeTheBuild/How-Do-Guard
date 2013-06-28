#pragma once

#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "Common.h"
#include <ArcApp.h>

#include "Button.h"
#include "TextButton.h"
#include "Textbox.h"

class Program :
    public ArcApp
{
public:

    TextButton 
        *btnClose;

    Textbox
        *txtTest;

    static Font
        *spDefaultFont;

    Program(void);
    virtual ~Program(void);

    virtual string toString( void ) const;

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    void btnCloseClicked( const Event& event );
};

#endif