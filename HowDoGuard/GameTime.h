#pragma once

#ifndef __GAME_TIME_H__
#define __GAME_TIME_H__

#include "GameObject.h"

class GameTime :
	public GameObject
{
private:

	double
		_totalMilliseconds,
		_elapsedMilliseconds,
		_deltaTime;

public:

	GameTime( void );
	virtual ~GameTime( void );

	virtual string toString( void ) const;

	void update(double elapsedMillis, double currFPS, double targetFPS);

	double totalSeconds  ( void );
	double elapsedSeconds( void );

	double totalMilliseconds  ( void );
	double elapsedMilliseconds( void );

	double deltaTime( void );

};

#endif

