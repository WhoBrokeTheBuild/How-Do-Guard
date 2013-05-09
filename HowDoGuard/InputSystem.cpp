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

/*

	// North <=> North-East, North <=> North-West

	addExclusive(GAME_INPUT_NORTH, GAME_INPUT_NORTH_EAST);
	addExclusive(GAME_INPUT_NORTH, GAME_INPUT_NORTH_WEST);

	// South <=> South-East, South <=> South-West

	addExclusive(GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST);
	addExclusive(GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST);

	// East <=> South-East, East <=> North-East

	addExclusive(GAME_INPUT_EAST, GAME_INPUT_NORTH_EAST);
	addExclusive(GAME_INPUT_EAST, GAME_INPUT_SOUTH_EAST);

	// West <=> South-West, West <=> North-West

	addExclusive(GAME_INPUT_WEST, GAME_INPUT_NORTH_WEST);
	addExclusive(GAME_INPUT_WEST, GAME_INPUT_SOUTH_WEST);

	// North <=> South, East <=> West


	// North-West <=> South-East, North-East <=> South-West

	addExclusive(GAME_INPUT_NORTH_EAST, GAME_INPUT_SOUTH_WEST);
	addExclusive(GAME_INPUT_SOUTH_WEST, GAME_INPUT_NORTH_EAST);
	*/

	addExclusive(GAME_INPUT_NORTH, GAME_INPUT_SOUTH);
	addExclusive(GAME_INPUT_EAST,  GAME_INPUT_WEST);

	_simultanious.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_NORTH_EAST, makeVector<GameInput>(2, GAME_INPUT_NORTH, GAME_INPUT_EAST)));
	_simultanious.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_NORTH_WEST, makeVector<GameInput>(2, GAME_INPUT_NORTH, GAME_INPUT_WEST)));
	_simultanious.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_SOUTH_EAST, makeVector<GameInput>(2, GAME_INPUT_SOUTH, GAME_INPUT_EAST)));
	_simultanious.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_SOUTH_WEST, makeVector<GameInput>(2, GAME_INPUT_SOUTH, GAME_INPUT_WEST)));

	_consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_QCF, makeVector<GameInput>(3, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST, GAME_INPUT_EAST)));
	_consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_QCB, makeVector<GameInput>(3, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST, GAME_INPUT_WEST)));
	_consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_HCF, makeVector<GameInput>(5, GAME_INPUT_WEST,  GAME_INPUT_SOUTH_WEST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST, GAME_INPUT_EAST)));
	_consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_HCB, makeVector<GameInput>(5, GAME_INPUT_EAST,  GAME_INPUT_SOUTH_EAST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST, GAME_INPUT_WEST)));
	
	_consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_DRAGON_FIST_FORWARD,  makeVector<GameInput>(3, GAME_INPUT_EAST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST)));
	_consecutive.insert(pair<GameInput, vector<GameInput>>(GAME_INPUT_DRAGON_FIST_BACKWARD, makeVector<GameInput>(3, GAME_INPUT_WEST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST)));

	_inputBufferIgnore = makeVector<GameInput>(10, GAME_INPUT_UP, GAME_INPUT_DOWN, GAME_INPUT_LEFT, GAME_INPUT_RIGHT, GAME_INPUT_QCF, GAME_INPUT_QCB, GAME_INPUT_HCF, GAME_INPUT_HCB, GAME_INPUT_DRAGON_FIST_FORWARD, GAME_INPUT_DRAGON_FIST_BACKWARD);
	_eightWayDir = makeVector<GameInput>(8, GAME_INPUT_NORTH, GAME_INPUT_NORTH_EAST, GAME_INPUT_EAST, GAME_INPUT_SOUTH_EAST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST, GAME_INPUT_WEST, GAME_INPUT_NORTH_WEST);

	for (int i = 0; i < NUM_GAME_INPUTS; ++i)
		_inputStates.insert(pair<GameInput, InputState>((GameInput)i, InputState()));
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
	InputChange
		change;

	GameInput
		input;

	InputState
		*pState;

	map<GameInput, InputState>::iterator		itStates;
	map<GameInput, vector<GameInput>>::iterator itMulti;
	
	while (_inputChanges.size() > 0)
	{
		change = _inputChanges.back();
		_inputChanges.pop();

		if (!mapContainsKey(_alias, change.Key))
			continue;

		input = _alias[change.Key];

		if (change.Pressed)
		{
			press(input);
		}
		else if (change.Released)
		{
			release(input);
		}
	}

	for (itStates = _inputStates.begin(); itStates != _inputStates.end(); ++itStates)
	{
		itStates->second.Hidden = false;
	}

	GameInput 
		direction = INVALID_GAME_INPUT;

	bool
		up    = getInputState(GAME_INPUT_UP)->Down,
		down  = getInputState(GAME_INPUT_DOWN)->Down,
		left  = getInputState(GAME_INPUT_LEFT)->Down,
		right = getInputState(GAME_INPUT_RIGHT)->Down;

	if (up)
	{
		if (left)
		{
			direction = GAME_INPUT_NORTH_WEST;
		}
		else if (right)
		{
			direction = GAME_INPUT_NORTH_EAST;
		}
		else
		{
			direction = GAME_INPUT_NORTH;
		}
	}
	else if (down)
	{
		if (left)
		{
			direction = GAME_INPUT_SOUTH_WEST;
		}
		else if (right)
		{
			direction = GAME_INPUT_SOUTH_EAST;
		}
		else
		{
			direction = GAME_INPUT_SOUTH;
		}
	}
	else if (left)
	{
		direction = GAME_INPUT_WEST;
	}
	else if (right)
	{
		direction = GAME_INPUT_EAST;
	}

	for (unsigned int i = 0; i < _eightWayDir.size(); ++i)
	{
		pState = getInputState(_eightWayDir[i]);

		if (direction == _eightWayDir[i])
		{
			press(_eightWayDir[i]);
		}
		else
		{
			release(_eightWayDir[i]);
		}
	}

	float maxDeltaTime = 0.5f;

	for (itMulti = _consecutive.begin(); itMulti != _consecutive.end(); ++itMulti)
	{
		input = itMulti->first;
		pState = getInputState(input);

		if (pState == nullptr)
			continue;

		release(input);

		if (_inputBuffer.size() < itMulti->second.size())
			continue;

		vector<GameInput> inputOrder = itMulti->second;
		bool combo = true;

		for (unsigned int i = 1; i < inputOrder.size(); ++i)
		{
			if (_inputBuffer[i].Time - _inputBuffer[i - 1].Time > maxDeltaTime)
			{
				combo = false;
				break;
			}
		}

		if (!combo)
			continue;

		for (unsigned int i = 0; i < inputOrder.size(); ++i)
		{
			if (_inputBuffer[i].Input != inputOrder[i])
			{
				combo = false;
				break;
			}
		}

		if (!combo)
			continue;

		for (unsigned int i = 0; i < inputOrder.size(); ++i)
			vectorRemoveAt(_inputBuffer, 0);

		press(input);
	}

	for (itStates = _inputStates.begin(); itStates!= _inputStates.end(); ++ itStates)
	{
		InputState state = itStates->second;
		input = itStates->first;

		if (state.Hidden)
			continue;

		if (state.Down)
		{
			gpEventDispatcher->dispatchEvent(Event(InputSystem::EVENT_INPUT_HELD, InputData(input)));
		}

		if (state.Pressed)
		{
			itStates->second.Pressed = false;
			gpEventDispatcher->dispatchEvent(Event(InputSystem::EVENT_INPUT_PRESSED, InputData(input)));
		}
		else if (state.Released)
		{
			itStates->second.Released = false;
			gpEventDispatcher->dispatchEvent(Event(InputSystem::EVENT_INPUT_RELEASED, InputData(input)));
		}
	}

}

void InputSystem::press( const GameInput input )
{
	InputState* pState = getInputState(input);

	if (pState == nullptr)
		return;

	if (pState->Down)
		return;

	addInputToBuffer(input);

	pState->Pressed = true;
	pState->Released = false;
	pState->Down = true;
}

void InputSystem::release( const GameInput input )
{
	InputState* pState = getInputState(input);

	if (pState == nullptr)
		return;

	if (!pState->Down)
		return;

	pState->Pressed = false;
	pState->Released = true;
	pState->Down = false;
}

void InputSystem::addExclusive( const GameInput first, const GameInput second )
{
	_exclusive.insert(pair<GameInput, GameInput>(first,  second));
	_exclusive.insert(pair<GameInput, GameInput>(second, first));
}

InputState * InputSystem::getInputState( GameInput input )
{
	if (!mapContainsKey(_inputStates, input))
		return nullptr;

	return &_inputStates[input];
}

void InputSystem::addInputToBuffer( GameInput input )
{
	if (!vectorContains(_inputBufferIgnore, input))
	{
		_inputBuffer.push_back(InputPress(input));
	}

	while (_inputBuffer.size() > INPUT_BUFFER_MAX)
		vectorRemoveAt(_inputBuffer, 0);
}
