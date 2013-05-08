#pragma once

#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Event.h"

#include "InputChange.h"
#include "InputState.h"
#include "GameInput.h"

#include <SDL.h>

#include <queue>

class InputSystem :
	public EventDispatcher
{
private:

	queue<InputChange>
		_inputChanges;

	map<GameInput, InputState> 
		_inputStates;

	map<SDLKey, GameInput> 
		_alias;

public:

	InputSystem( void );
	virtual ~InputSystem( void );

	virtual void init ( void );
	virtual void term ( void );

	virtual string toString( void ) const;

	virtual void update( const Event& event );

	virtual void process( const FrameData& frameData );

};

#endif