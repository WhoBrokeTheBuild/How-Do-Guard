#pragma once

#ifndef __INPUT_STATE_H__
#define __INPUT_STATE_H__

#include "MemoryTracker.h"
#include "common.h"

struct InputState : public MemoryTracker
{
	bool 
		_pressed,
		_released,
		_down;

	double
		_time;

	InputState( void );

	virtual string toString( void ) const;
};

#endif