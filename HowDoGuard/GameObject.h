#pragma once

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class GameObject
{
private:

public:

	GameObject( void );
	virtual ~GameObject( void );

	virtual string toString( void ) const = 0;

	friend ostream& operator<<( ostream& os, const GameObject& go );

};

#endif