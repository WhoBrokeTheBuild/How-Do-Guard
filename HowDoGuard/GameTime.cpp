#include "GameTime.h"

GameTime::GameTime(void)
{
	_totalMilliseconds   = 0;
	_elapsedMilliseconds = 0;
}

GameTime::~GameTime(void)
{
}

std::string GameTime::toString( void ) const
{
	return "Game Time";
}

void GameTime::update( double elapsedMillis, double currFPS, double targetFPS )
{
	_elapsedMilliseconds = elapsedMillis;
	_totalMilliseconds += elapsedMillis;
	_deltaTime = targetFPS / currFPS;
}

double GameTime::totalSeconds( void )
{
	return _totalMilliseconds / 1000.0;
}

double GameTime::elapsedSeconds( void )
{
	return _elapsedMilliseconds / 1000.0;
}

double GameTime::totalMilliseconds( void )
{
	return _totalMilliseconds;
}

double GameTime::elapsedMilliseconds( void )
{
	return _elapsedMilliseconds;
}

double GameTime::deltaTime( void )
{
	return _deltaTime;
}
