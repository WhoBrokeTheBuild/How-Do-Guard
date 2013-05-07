#pragma once

#ifndef __GAME_H__
#define __GAME_H__

#include "Common.h"
#include "EventDispatcher.h"
#include "Event.h"

#include "DataManager.h"

#include "GraphicsSystem.h"
#include "RenderTarget.h"

#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"

#include "BasicUnit.h"

#include "InputSystem.h"

#include "Timer.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>

class Game :
	public EventDispatcher
{
private:

	DataManager
		*_pDataManager;

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

	//TODO: Remove
	static bool endNow;
	Animation *anim;
	Sprite *frame1, *frame2, *frame3, *frame4, *frame5;
	Texture *sheet;
	BasicUnit *unit;

	Game( void );
	virtual ~Game( void );

	virtual string toString( void ) const;

	void init( void );
	void term( void );

	void start( void );
	void stop ( const Event& event );

	void update( const FrameData& frameData );
	void draw  ( const RenderData& renderData );
};

#endif
