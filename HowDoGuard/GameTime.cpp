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

void GameTime::update( double elapsedMilliseconds )
{
	_elapsedMilliseconds = elapsedMilliseconds;
	_totalMilliseconds += elapsedMilliseconds;
}

double GameTime::getTotalSeconds( void )
{
	return _totalMilliseconds / 1000.0;
}

double GameTime::getElapsedSeconds( void )
{
	return _elapsedMilliseconds / 1000.0;
}

double GameTime::getTotalMilliseconds( void )
{
	return _totalMilliseconds;
}

double GameTime::getElapsedMilliseconds( void )
{
	return _elapsedMilliseconds;
}
