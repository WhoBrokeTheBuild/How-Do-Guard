#pragma once

#ifndef __GAME_INPUT_CONTROLLER_H__
#define __GAME_INPUT_CONTROLLER_H__

#include "Common.h"
#include <EventDispatcher.h>

#include <InputState.h>
#include <InputType.h>
#include <IKeyboardListener.h>
#include <IMouseListener.h>

#include "GameInput.h"
#include "GameCombinedInput.h"
#include "GameInputChange.h"

#include <map>
#include <queue>

typedef map<GameCombinedInput,  GameInput, CompGameCombinedInput> AliasMap;
typedef pair<GameCombinedInput, GameInput>                        AliasPair;

typedef map<GameInput,  InputState> GameInputStateMap;
typedef pair<GameInput, InputState> GameInputStatePair;

struct GameInputSimultanious
{
    GameInput 
        Output;

    vector<GameInput>
        Inputs;

    bool 
        BlockInput;

    GameInputSimultanious( GameInput output, vector<GameInput> inputs, bool blockInput = true)
    {
        Output     = output;
        Inputs      = inputs;
        BlockInput = blockInput;
    }
};

struct GameInputConsecutive
{
    GameInput
        Output;

    vector<GameInput>
        Inputs;

    GameInputConsecutive( GameInput output, vector<GameInput> inputs)
    {
        Output = output;
        Inputs  = inputs;
    }
};

struct GameInputPress
{
    GameInput
        Input;

    double
        Time;

    GameInputPress( GameInput input = INVALID_GAME_INPUT, double time = 0.0 )
    {
        Input = input;
        Time = time;
    }
};

#define INPUT_BUFFER_MAX 20

class GameInputSource :
    public EventDispatcher,
    public IKeyboardListener,
    public IMouseListener
{
protected:

    AliasMap
        _alias;

    vector<GameInputSimultanious>
        _simInputs;

    vector<GameInputConsecutive>
        _consecInputs;

    queue<GameInputChange>
        _inputChanges;

    GameInputStateMap
        _inputStates;

    vector<GameInput>
        _eightWayDir,
        _hiddenInputs;

    vector<GameInputPress>
        _inputBuffer;

    PlayerIndex
        _playerIndex;

    double
        _maxInputDeltaTime;

public:

    static const EventType
        EVENT_GAME_INPUT_PRESSED,
        EVENT_GAME_INPUT_RELEASED,
        EVENT_GAME_INPUT_HELD;

    GameInputSource( void );
    virtual ~GameInputSource( void );

    virtual string toString( void ) const;

    virtual void init( PlayerIndex index );
    virtual void term( void );

    virtual void update( const Event& event );

    virtual void processChanges    ( void );
    virtual void processEightWayDir( void );
    virtual void processSimuInput  ( void );
    virtual void processConsecInput( const FrameData* data  );

    virtual void tap    ( GameInput input );
    virtual void press  ( GameInput input );
    virtual void release( GameInput input );

    virtual InputState* getInputState( GameInput input );

    virtual void addDefaults     ( void );
    virtual void addAlias        ( GameCombinedInput alias, GameInput input );
    virtual void addInputToBuffer( GameInput input, double time );

    virtual void keyPressed ( const Event& event );
    virtual void keyReleased( const Event& event );
    virtual void keyHeld    ( const Event& event );

    virtual void mousePressed ( const Event& event );
    virtual void mouseReleased( const Event& event );
    virtual void mouseHeld    ( const Event& event );
    virtual void mouseMoved   ( const Event& event );
};

#endif