#pragma once

#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Event.h"

#include <SDL.h>

class InputSystem :
	public EventDispatcher
{
private:

public:

	InputSystem( void );
	virtual ~InputSystem( void );

	virtual void init ( void );
	virtual void term ( void );

	virtual string toString( void ) const;

	virtual void update( const Event& event );

};

#endif