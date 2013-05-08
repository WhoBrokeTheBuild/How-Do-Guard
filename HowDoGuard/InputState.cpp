#include "InputState.h"

InputState::InputState( void )
{
	Pressed = false;
	Released = true;
	Down = false;

	PressedTimeout = -1;
}

InputState::InputState( bool pressed, bool released, bool down )
{
	Pressed = pressed;
	Released = released;
	Down = down;

	PressedTimeout = -1;
}

string InputState::toString( void ) const
{
	return "Input State";
}