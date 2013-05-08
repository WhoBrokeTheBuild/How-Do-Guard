#include "InputSystem.h"
#include "Game.h"

const EventType InputSystem::EVENT_INPUT_PRESSED  = "inputPressed";
const EventType InputSystem::EVENT_INPUT_RELEASED = "inputReleased";
const EventType InputSystem::EVENT_INPUT_HELD     = "inputHeld";

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

	_alias.insert(pair<SDLKey, GameInput>(SDLK_w, GAME_INPUT_UP));
	_alias.insert(pair<SDLKey, GameInput>(SDLK_a, GAME_INPUT_LEFT));
	_alias.insert(pair<SDLKey, GameInput>(SDLK_s, GAME_INPUT_DOWN));
	_alias.insert(pair<SDLKey, GameInput>(SDLK_d, GAME_INPUT_RIGHT));

	_inputStates.insert(pair<GameInput, InputState>(GAME_INPUT_UP, InputState()));
	_inputStates.insert(pair<GameInput, InputState>(GAME_INPUT_LEFT, InputState()));
	_inputStates.insert(pair<GameInput, InputState>(GAME_INPUT_DOWN, InputState()));
	_inputStates.insert(pair<GameInput, InputState>(GAME_INPUT_RIGHT, InputState()));
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
	const FrameData* frameData = event.dataAs<FrameData>();

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

			if (inputEvent.type == SDL_KEYDOWN)
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

	process(frameData);
}

void InputSystem::process( const FrameData* frameData )
{
	InputChange change;
	GameInput gameInput = INVALID_GAME_INPUT;
	map<SDLKey, GameInput>::iterator aliasIter;
	map<GameInput, InputState>::iterator statesIter;

	while (_inputChanges.size() > 0)
	{
		change = _inputChanges.back();

		aliasIter = _alias.find(change.Key);

		if (aliasIter != _alias.end())
			gameInput = aliasIter->second;

		statesIter = _inputStates.find(gameInput);

		if (statesIter != _inputStates.end())
		{
			if (change.Pressed)
			{
				statesIter->second.Pressed = true;
				statesIter->second.Released = false;
				statesIter->second.Down = true;

				gpEventDispatcher->dispatchEvent(Event(InputSystem::EVENT_INPUT_PRESSED, InputData(gameInput)));

				//TODO: No magic numbers!
				statesIter->second.PressedTimeout = 48; // about 3 frames
			}
			else if (change.Released)
			{
				statesIter->second.Pressed = false;
				statesIter->second.Released = true;
				statesIter->second.Down = false;

				gpEventDispatcher->dispatchEvent(Event(InputSystem::EVENT_INPUT_RELEASED, InputData(gameInput)));

				statesIter->second.PressedTimeout = -1;
			}
		}

		_inputChanges.pop();
	}

	for (statesIter = _inputStates.begin(); statesIter!= _inputStates.end(); ++ statesIter)
	{
		if (statesIter->second.Pressed)
		{
			statesIter->second.PressedTimeout -= frameData->elapsedMilliseconds();
			if (statesIter->second.PressedTimeout < 0)
			{
				statesIter->second.Pressed = false;
			}
		}
		if (statesIter->second.Down)
		{
			gpEventDispatcher->dispatchEvent(Event(InputSystem::EVENT_INPUT_HELD, InputData(statesIter->first)));
		}
	}
}

