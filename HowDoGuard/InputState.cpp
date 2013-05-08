#include "InputState.h"

InputState::InputState( void )
{
	_pressed = false;
	_released = true;
	_down = false;

	_time = -1;
}

string InputState::toString( void ) const
{
	return "Input State";
}