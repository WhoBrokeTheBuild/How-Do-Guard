#include "GameInputSource.h"
#include "Game.h"

const EventType GameInputSource::EVENT_GAME_INPUT_PRESSED  = "gameInputPressed";
const EventType GameInputSource::EVENT_GAME_INPUT_RELEASED = "gameInputReleased";
const EventType GameInputSource::EVENT_GAME_INPUT_HELD     = "gameInputHeld";

GameInputSource::GameInputSource( void )
{
}

GameInputSource::~GameInputSource( void )
{
    term();
}

std::string GameInputSource::toString( void ) const
{
    stringstream ss;

    ss << "Game Input Controller (Player #" << (int)_playerIndex << ")";

    return ss.str();
}

void GameInputSource::init( PlayerIndex index )
{
    _playerIndex = index;

    _alias        = AliasMap();
    _inputStates  = GameInputStateMap();
    _simInputs    = vector<GameInputSimultanious>();
    _consecInputs = vector<GameInputConsecutive>();
    _inputChanges = queue<GameInputChange>();
    _hiddenInputs = vector<GameInput>();

    _maxInputDeltaTime = 0.75f;

    _eightWayDir = makeVector(8, GAME_INPUT_NORTH, GAME_INPUT_NORTH_EAST, GAME_INPUT_EAST,
                                 GAME_INPUT_SOUTH_EAST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST,
                                 GAME_INPUT_WEST, GAME_INPUT_NORTH_WEST);

    for (int input = 0; input < NUM_GAME_INPUTS; ++input)
    {
        _inputStates.insert(GameInputStatePair((GameInput)input, InputState()));
    }

    addDefaults();
  
    IKeyboardListener::init();
    IMouseListener::init();

    gpEventDispatcher->addEventListener(Game::EVENT_FRAME, this, &GameInputSource::update);
}

void GameInputSource::term( void )
{
    gpEventDispatcher->removeEventListener(Game::EVENT_FRAME, this, &GameInputSource::update);
}

void GameInputSource::update( const Event& event )
{
    const FrameData* data = event.dataAs<FrameData>();

    processChanges();
    processEightWayDir();
    processSimuInput();
    processConsecInput(data);

    GameInputStateMap::iterator it;
    for (it = _inputStates.begin(); it != _inputStates.end(); ++it)
    {
        if (vectorContains(_hiddenInputs, it->first))
            continue;

        GameInput  input   = it->first;
        InputState *pState = &it->second;

        if (pState->Tapped)
        {
            gpEventDispatcher->dispatchEvent(Event(GameInputSource::EVENT_GAME_INPUT_PRESSED,  GameInputData(input, _playerIndex)));
            gpEventDispatcher->dispatchEvent(Event(GameInputSource::EVENT_GAME_INPUT_HELD,     GameInputData(input, _playerIndex)));
            gpEventDispatcher->dispatchEvent(Event(GameInputSource::EVENT_GAME_INPUT_RELEASED, GameInputData(input, _playerIndex)));

            addInputToBuffer(input, data->totalSeconds());
        }
        else
        {
            if (pState->Pressed)
            {
                gpEventDispatcher->dispatchEvent(Event(GameInputSource::EVENT_GAME_INPUT_PRESSED, GameInputData(input, _playerIndex)));

                addInputToBuffer(input, data->totalSeconds());
            }
            else if (pState->Released)
            {
                gpEventDispatcher->dispatchEvent(Event(GameInputSource::EVENT_GAME_INPUT_RELEASED, GameInputData(input, _playerIndex)));
            }

            if (pState->Down)
            {
                gpEventDispatcher->dispatchEvent(Event(GameInputSource::EVENT_GAME_INPUT_HELD, GameInputData(input, _playerIndex)));
            }
        }

        pState->Pressed  = false;
        pState->Released = false;
        pState->Tapped   = false;
    }
    _hiddenInputs.clear();
}

void GameInputSource::processChanges( void )
{
    while (_inputChanges.size() > 0)
    {
        GameInputChange   change = _inputChanges.back();
        GameCombinedInput input  = change.Input;
        InputType         type   = change.Type;

        _inputChanges.pop();

        if (!mapContainsKey(_alias, input))
            continue;

        GameInput gameInput = _alias[input];

        if (type == INPUT_TYPE_PRESSED)
        {
            press(gameInput);
        }
        else if (type == INPUT_TYPE_RELEASED)
        {
            release(gameInput);
        }
    }
}

void GameInputSource::processEightWayDir( void )
{
    GameInput direction = INVALID_GAME_INPUT;

    bool
        up    = _inputStates[GAME_INPUT_UP].Down,
        down  = _inputStates[GAME_INPUT_DOWN].Down,
        left  = _inputStates[GAME_INPUT_LEFT].Down,
        right = _inputStates[GAME_INPUT_RIGHT].Down;

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

    InputState* pState;
    for (unsigned int i = 0; i < _eightWayDir.size(); ++i)
    {
        GameInput currentDir = _eightWayDir[i];
        pState = getInputState(currentDir);

        if (pState == nullptr) 
            continue;

        if (direction == currentDir)
        {
            press(currentDir);
        }
        else
        {
            release(currentDir);
        }
    }
}

void GameInputSource::processSimuInput( void )
{
    for (unsigned int i = 0; i < _simInputs.size(); ++i)
    {
        GameInputSimultanious simInput      = _simInputs[i];
        GameInput             output        = simInput.Output;
        InputState            *pOutputState = getInputState(output);
        vector<GameInput>     inputs        = simInput.Inputs;

        if (inputs.size() == 0 || pOutputState == nullptr)
            continue;

        bool down = true;
        for (unsigned int inputInd = 0; inputInd < inputs.size(); ++inputInd)
        {
            InputState *pState = &_inputStates[inputs[inputInd]];

            if (!pState->Down)
            {
                down = false;
                break;
            }
        }

        if (down && !pOutputState->Down)
        {
            press(output);
        }
        else if (!down && pOutputState->Down)
        {
            release(output);
        }

        if (down && simInput.BlockInput)
        {
            for (unsigned int inputInd = 0; inputInd < inputs.size(); ++inputInd)
            {
                if (!vectorContains(_hiddenInputs, inputs[inputInd]))
                {
                    _hiddenInputs.push_back(inputs[inputInd]);
                }
            }
        }
    }
}

void GameInputSource::processConsecInput( const FrameData* data )
{
    for (unsigned int i = 0; i < _consecInputs.size(); ++i)
    {
        GameInputConsecutive simInput      = _consecInputs[i];
        GameInput            output        = simInput.Output;
        InputState           *pOutputState = getInputState(output);
        vector<GameInput>    inputs        = simInput.Inputs;

        if (pOutputState->Down)
            continue;

        if (_inputBuffer.size() < inputs.size())
            continue;

        int  bufferStartInd = 0;
        vector<GameInputPress> presses = vector<GameInputPress>();

        for (unsigned int inputInd = 0; inputInd < inputs.size(); ++inputInd)
        {
            for (unsigned int bufferInd = bufferStartInd; bufferInd < _inputBuffer.size(); ++bufferInd)
            {
                if (inputs[inputInd] == _inputBuffer[bufferInd].Input)
                {
                    bufferStartInd = bufferInd + 1;
                    presses.push_back(_inputBuffer[bufferInd]);
                    break;
                }
            }
        }

        if (presses.size() < inputs.size())
            continue;

        GameInputPress
            first = presses[0],
            last  = presses[inputs.size() - 1];

        if (last.Time - first.Time > _maxInputDeltaTime)
            continue;

        tap(output);

        for (unsigned int pressesInd = 0; pressesInd < presses.size(); ++pressesInd)
        {
            for (unsigned int bufferInd = 0; bufferInd < _inputBuffer.size(); ++bufferInd)
            {
                if (_inputBuffer[bufferInd].Input == presses[pressesInd].Input &&
                    _inputBuffer[bufferInd].Time  == presses[pressesInd].Time)
                {
                    vectorRemoveAt(_inputBuffer, bufferInd);
                    --bufferInd;
                }
            }
        }
    }
}

void GameInputSource::tap ( GameInput input )
{
    InputState* pState = getInputState(input);

    if (pState == nullptr || pState->Down)
        return;

    pState->Pressed  = false;
    pState->Released = false;
    pState->Down     = false;
    pState->Tapped   = true;
}

void GameInputSource::press( GameInput input )
{
    InputState* pState = getInputState(input);

    if (pState == nullptr || pState->Down)
        return;

    pState->Pressed  = true;
    pState->Released = false;
    pState->Down     = true;
    pState->Tapped   = false;
}

void GameInputSource::release( GameInput input )
{
    InputState* pState = getInputState(input);

    if (pState == nullptr || !pState->Down)
        return;

    pState->Pressed  = false;
    pState->Released = true;
    pState->Down     = false;
    pState->Tapped   = false;
}

InputState* GameInputSource::getInputState( GameInput input )
{
    if (mapContainsKey(_inputStates, input))
    {
        return &_inputStates[input];
    }
    return nullptr;
}

void GameInputSource::addDefaults( void )
{
    _simInputs.push_back(GameInputSimultanious(GAME_INPUT_QCF, makeVector<GameInput>(2, GAME_INPUT_LIGHT_PUNCH, GAME_INPUT_HEAVY_PUNCH), true));

    _consecInputs.push_back(GameInputConsecutive(GAME_INPUT_HCF, makeVector<GameInput>(5, GAME_INPUT_WEST,  GAME_INPUT_SOUTH_WEST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST, GAME_INPUT_EAST)));
    _consecInputs.push_back(GameInputConsecutive(GAME_INPUT_HCB, makeVector<GameInput>(5, GAME_INPUT_EAST,  GAME_INPUT_SOUTH_EAST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST, GAME_INPUT_WEST)));

    _consecInputs.push_back(GameInputConsecutive(GAME_INPUT_DRAGON_FIST_FORWARD,  makeVector<GameInput>(3, GAME_INPUT_EAST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST)));
    _consecInputs.push_back(GameInputConsecutive(GAME_INPUT_DRAGON_FIST_BACKWARD, makeVector<GameInput>(3, GAME_INPUT_WEST, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST)));

    _consecInputs.push_back(GameInputConsecutive(GAME_INPUT_QCF, makeVector<GameInput>(3, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_EAST, GAME_INPUT_EAST)));
    _consecInputs.push_back(GameInputConsecutive(GAME_INPUT_QCB, makeVector<GameInput>(3, GAME_INPUT_SOUTH, GAME_INPUT_SOUTH_WEST, GAME_INPUT_WEST)));
}

void GameInputSource::addAlias( GameCombinedInput alias, GameInput input )
{
    _alias.insert(AliasPair(alias, input));
}

void GameInputSource::addInputToBuffer( GameInput input, double time )
{
    _inputBuffer.push_back(GameInputPress(input, time));

    while (_inputBuffer.size() > INPUT_BUFFER_MAX)
        vectorRemoveAt(_inputBuffer, 0);
}

void GameInputSource::keyPressed( const Event& event )
{
    const KeyData *data = event.dataAs<KeyData>();
    
    _inputChanges.push(GameInputChange(GameCombinedInput(data->Key), INPUT_TYPE_PRESSED));
}

void GameInputSource::keyReleased( const Event& event )
{
    const KeyData *data = event.dataAs<KeyData>();

    _inputChanges.push(GameInputChange(GameCombinedInput(data->Key), INPUT_TYPE_RELEASED));
}

void GameInputSource::keyHeld( const Event& event )
{
    const KeyData *data = event.dataAs<KeyData>();
}

void GameInputSource::mousePressed( const Event& event )
{
    const MouseData *data = event.dataAs<MouseData>();

    _inputChanges.push(GameInputChange(GameCombinedInput(data->Button), INPUT_TYPE_PRESSED));
}

void GameInputSource::mouseReleased( const Event& event )
{
    const MouseData *data = event.dataAs<MouseData>();

    _inputChanges.push(GameInputChange(GameCombinedInput(data->Button), INPUT_TYPE_RELEASED));
}

void GameInputSource::mouseHeld( const Event& event )
{
    const MouseData *data = event.dataAs<MouseData>();
}

void GameInputSource::mouseMoved( const Event& event )
{
    //const MouseData *data = event.dataAs<MouseData>();
}