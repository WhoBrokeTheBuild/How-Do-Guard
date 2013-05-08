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
	gpEventDispatcher->addEventListener(Event::EVENT_ENTER_FRAME, this, &InputSystem::update);
}

void InputSystem::term( void )
{
	gpEventDispatcher->removeEventListener(Event::EVENT_ENTER_FRAME, this, &InputSystem::update);
}

std::string InputSystem::toString( void ) const
{
	return "Input System";
}

void InputSystem::update( const Event& event )
{
	SDL_Event inputEvent;
	SDLKey key;
	InputChange change;

	while (SDL_PollEvent(&inputEvent))
	{
		switch (inputEvent.type)
		{
		case SDL_KEYDOWN:
		case SDL_KEYUP:

			key = inputEvent.key.keysym.sym;

			change = InputChange(key);

			if (SDL_KEYDOWN)
				change.Pressed = true;
			else
				change.Released = true;

			_inputChanges.push(change);

			break;
		case SDL_QUIT:

			gpEventDispatcher->dispatchEvent(Event(Event::EVENT_GAME_END));

			break;
		}
	}
}

void InputSystem::process( const FrameData& frameData )
{
	InputChange change;
	GameInput gameInput;
	map<SDLKey, GameInput>::iterator aliasIter;
	map<GameInput, InputState>::iterator statesIter;

	if(_inputChanges.size > 0)
	{
		change = _inputChanges.back();

		aliasIter = _alias.find(change.Key);

		if(aliasIter != _alias.end())
			gameInput = aliasIter->second;

		statesIter = _inputStates.find(gameInput);

		if(statesIter != _inputStates.end())
		{
			statesIter->second.Pressed = change.Pressed;
			statesIter->second.Released = change.Released;
			statesIter->second.PressedTimeout -= frameData.elapsedMilliseconds;
		}

		_inputChanges.pop();
	}
}
