#pragma once

#ifndef __MORE_EVENT_DATA__
#define __MORE_EVENT_DATA__

#include <EventData.h>

#include "Common.h"
#include "GameInput.h"

class GameInputData
    : public EventData
{
private:

public:

    GameInput 
        Input;

    PlayerIndex
        Index;

    GameInputData( GameInput input, PlayerIndex index ) { Input = input; Index = index; }

    virtual string toString( void ) const { return "Input Data"; }

    virtual EventData* clone( void ) const { return New GameInputData(Input, Index); }

};

#endif