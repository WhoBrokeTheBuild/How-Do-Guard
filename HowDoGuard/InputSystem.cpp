#include "InputSystem.h"
#include "Game.h"

InputSystem::InputSystem( void )
{
}

InputSystem::~InputSystem( void )
{
	term();
}

void InputSystem::init( void )
{

}

void InputSystem::term( void )
{

}

std::string InputSystem::toString( void ) const
{
	return "Input System";
}

void InputSystem::update( const Event& event )
{
	SDL_Event inputEvent;

	while (SDL_PollEvent(&inputEvent))
	{
		switch (inputEvent.type)
		{
		case SDL_QUIT:

			gpEventDispatcher->dispatchEvent(Event(Event::EVENT_GAME_END));

			break;
		}
	}
}
