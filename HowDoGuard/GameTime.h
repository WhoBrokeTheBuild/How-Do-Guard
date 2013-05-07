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
		_elapsedMilliseconds;

public:

	GameTime(void);
	virtual ~GameTime(void);

	virtual string toString( void ) const;

	void update(double elapsedMilliseconds);

	double getTotalSeconds(void);
	double getElapsedSeconds(void);

	double getTotalMilliseconds(void);
	double getElapsedMilliseconds(void);

};

#endif

