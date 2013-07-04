#include "GameInputSource.h"
#include "Game.h"

const EventType GameInputSource::EVENT_GAME_INPUT_PRESSED  = "gameInputPressed";
const EventType GameInputSource::EVENT_GAME_INPUT_RELEASED = "gameInputReleased";
const EventType GameInputSource::EVENT_GAME_INPUT_HELD     = "gameInputHeld";

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
    _simInputs    = ArrayList<GameInputSimultanious>();
    _consecInputs = ArrayList<GameInputConsecutive>();
    _hiddenInputs = ArrayList<GameInput>();
    _inputChanges = Queue<GameInputChange>();

    _maxInputDeltaTime = 0.75f;

    _eightWayDir.add(GAME_INPUT_NORTH)->add(GAME_INPUT_NORTH_EAST)
               ->add(GAME_INPUT_EAST)->add(GAME_INPUT_SOUTH_EAST)
               ->add(GAME_INPUT_SOUTH)->add(GAME_INPUT_SOUTH_WEST)
               ->add(GAME_INPUT_WEST)->add(GAME_INPUT_NORTH_WEST);

    for (int input = 0; input < NUM_GAME_INPUTS; ++input)
    {
        _inputStates.add((GameInput)input, InputState());
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

    GameInputStateMap::Iterator it;
    for (it = _inputStates.begin(); it != _inputStates.end(); ++it)
    {
        if (_hiddenInputs.contains(it->first))
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
    while (!_inputChanges.empty())
    {
        GameInputChange   change = _inputChanges.pop();
        GameCombinedInput input  = change.Input;
        InputType         type   = change.Type;

        if (!_alias.contains(input))
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
        ArrayList<GameInput>  inputs        = simInput.Inputs;

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
                if (!_hiddenInputs.contains(inputs[inputInd]))
                {
                    _hiddenInputs.add(inputs[inputInd]);
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
        ArrayList<GameInput> inputs        = simInput.Inputs;

        if (pOutputState->Down)
            continue;

        if (_inputBuffer.size() < inputs.size())
            continue;

        int  bufferStartInd = 0;
        ArrayList<GameInputPress> presses = ArrayList<GameInputPress>();

        for (unsigned int inputInd = 0; inputInd < inputs.size(); ++inputInd)
        {
            for (unsigned int bufferInd = bufferStartInd; bufferInd < _inputBuffer.size(); ++bufferInd)
            {
                if (inputs[inputInd] == _inputBuffer[bufferInd].Input)
                {
                    bufferStartInd = bufferInd + 1;
                    presses.add(_inputBuffer[bufferInd]);
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
                    _inputBuffer.removeAt(bufferInd);
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
    if (_inputStates.contains(input))
    {
        return &_inputStates[input];
    }
    return nullptr;
}

void GameInputSource::addDefaults( void )
{
    _simInputs.add(GameInputSimultanious(GAME_INPUT_QCF, *ArrayList<GameInput>().add(GAME_INPUT_LIGHT_PUNCH)->add(GAME_INPUT_HEAVY_PUNCH), true));

    _consecInputs.add(GameInputConsecutive(GAME_INPUT_HCF, *ArrayList<GameInput>().add(GAME_INPUT_WEST)->add(GAME_INPUT_SOUTH_WEST)->add(GAME_INPUT_SOUTH)->add(GAME_INPUT_SOUTH_EAST)->add(GAME_INPUT_EAST)));
    _consecInputs.add(GameInputConsecutive(GAME_INPUT_HCB, *ArrayList<GameInput>().add(GAME_INPUT_EAST)->add(GAME_INPUT_SOUTH_EAST)->add(GAME_INPUT_SOUTH)->add(GAME_INPUT_SOUTH_WEST)->add(GAME_INPUT_WEST)));

    _consecInputs.add(GameInputConsecutive(GAME_INPUT_DRAGON_FIST_FORWARD,  *ArrayList<GameInput>().add(GAME_INPUT_EAST)->add(GAME_INPUT_SOUTH)->add(GAME_INPUT_SOUTH_EAST)));
    _consecInputs.add(GameInputConsecutive(GAME_INPUT_DRAGON_FIST_BACKWARD, *ArrayList<GameInput>().add(GAME_INPUT_WEST)->add(GAME_INPUT_SOUTH)->add(GAME_INPUT_SOUTH_WEST)));

    _consecInputs.add(GameInputConsecutive(GAME_INPUT_QCF, *ArrayList<GameInput>().add(GAME_INPUT_SOUTH)->add(GAME_INPUT_SOUTH_EAST)->add(GAME_INPUT_EAST)));
    _consecInputs.add(GameInputConsecutive(GAME_INPUT_QCB, *ArrayList<GameInput>().add(GAME_INPUT_SOUTH)->add(GAME_INPUT_SOUTH_WEST)->add(GAME_INPUT_WEST)));
}

void GameInputSource::addAlias( GameCombinedInput alias, GameInput input )
{
    _alias.add(alias, input);
}

void GameInputSource::addInputToBuffer( GameInput input, double time )
{
    _inputBuffer.add(GameInputPress(input, time));

    while (_inputBuffer.size() > INPUT_BUFFER_MAX)
        _inputBuffer.removeFront();
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
