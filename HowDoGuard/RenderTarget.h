#pragma once

#ifndef __RENDER_TARGET_H__
#define __RENDER_TARGET_H__

#include "GameObject.h"

class RenderTarget :
	public GameObject
{
private: 



public:

	RenderTarget( void );
	virtual ~RenderTarget( void );

	virtual string toString( void ) const;

};

#endif