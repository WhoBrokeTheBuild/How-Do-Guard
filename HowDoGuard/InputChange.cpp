#include "InputChange.h"

InputChange::InputChange( void )
{
	Key = SDLK_UNKNOWN;
	Pressed = false;
	Released = false;
}

InputChange::InputChange( SDLKey key )
{
	Key = key;
	Pressed = false;
	Released = false;
}

std::string InputChange::toString( void ) const
{
	return "Input Change";
}