#pragma once

#ifndef __GAME_H__
#define __GAME_H__

#include "Common.h"
#include "GameObject.h"

#include "GraphicsSystem.h"
#include "RenderTarget.h"

#include "InputSystem.h"

#include "GameTime.h"
#include "Timer.h"

class Game :
	public GameObject
{
private:

	GraphicsSystem
		*_pGraphicsSystem;

	InputSystem 
		*_pInputSystem;

	GameTime
		*_pGameTime;

	bool
		_running;

	float 
		_targetFPS,
		_currentFPS;

public:

	//TODO: Remove
	static bool endNow;

	Game( void );
	virtual ~Game( void );

	virtual string toString( void ) const;

	void init( void );
	void term( void );

	void start( void );

	void update( void );
	void draw( void );

};

#endif
