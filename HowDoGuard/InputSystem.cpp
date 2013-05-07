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

void InputSystem::update( GameTime *pGameTime )
{
	SDL_Event inputEvent;

	while (SDL_PollEvent(&inputEvent))
	{
		switch (inputEvent.type)
		{
		case SDL_QUIT:

			Game::endNow = true;

			break;
		}
	}
}
