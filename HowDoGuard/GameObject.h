#pragma once

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "common.h"

class GameObject
{
private:

public:

	GameObject(void);
	virtual ~GameObject(void);

	virtual string toString( void ) const = 0;

	friend ostream& operator<<( ostream& os, const GameObject& go );

};

#endif