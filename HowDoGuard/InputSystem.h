#pragma once

#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include "Common.h"
#include "EventDispatcher.h"

#include "Event.h"

#include "InputChange.h"
#include "InputState.h"
#include "InputPress.h"
#include "GameInput.h"

#include <SDL.h>

#include <queue>

#define INPUT_BUFFER_MAX 15

class InputSystem :
	public EventDispatcher
{
private:

	map<GameInput, InputState> 
		_inputStates;

	queue<InputChange>
		_inputChanges;

	vector<GameInput>
		_inputBufferIgnore,
		_eightWayDir;

	vector<InputPress>
		_inputBuffer;

	map<SDLKey, GameInput> 
		_alias;

	map<GameInput, vector<GameInput>>
		_simultanious,
		_consecutive;

	map<GameInput, GameInput>
		_exclusive;

	virtual void process( const FrameData* frameData );

	virtual void addExclusive( const GameInput first, const GameInput second );

	void press  ( const GameInput input );
	void release( const GameInput input );

	InputState * getInputState( GameInput input );
	void addInputToBuffer( GameInput input );

public:

	static const EventType EVENT_INPUT_PRESSED;
	static const EventType EVENT_INPUT_RELEASED;
	static const EventType EVENT_INPUT_HELD;

	InputSystem( void );
	virtual ~InputSystem( void );

	virtual void init ( void );
	virtual void term ( void );

	virtual string toString( void ) const;

	virtual void update( const Event& event );
};

#endif