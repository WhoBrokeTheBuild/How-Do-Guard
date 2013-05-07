#pragma once

#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include "Common.h"
#include "GameObject.h"

#include "GameTime.h"

#include <SDL.h>

class InputSystem :
	public GameObject
{
private:

public:

	InputSystem( void );
	virtual ~InputSystem( void );

	virtual void init ( void );
	virtual void term ( void );

	virtual string toString( void ) const;

	virtual void update( GameTime *pGameTime );

};

#endif