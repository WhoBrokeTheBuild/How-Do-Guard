#pragma once

#ifndef __TOAST_H__
#define __TOAST_H__

#include "Common.h"
#include "BasicUnit.h"

#include "DataManager.h"

class Toast :
	public BasicUnit
{
private:

	Vector2
		_vel;

public:

	Toast(void);
	virtual ~Toast(void);

	virtual string toString( void ) const;

	virtual void init( void );
	virtual void term( void );

	virtual void update( const Event& event );

	virtual void input( const Event& event );
};

#endif