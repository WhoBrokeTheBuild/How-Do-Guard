#pragma once

#ifndef __BASIC_UNIT_H__
#define __BASIC_UNIT_H__

#include "Common.h"
#include "GameObject.h"

#include "Animation.h"
#include "Color.h"

#include "GameTime.h"
#include "RenderTarget.h"

class BasicUnit :
	public GameObject
{
protected:

	Animation
		*_pAnimation;

	double
		_animationTimeout;

	int
		_frame;

	bool
		_animationComplete;

	virtual void updateAnimation( GameTime *pGameTime );

public:

	Vector2
		Pos,
		Origin;

	Color
		BlendColor;

	float
		Rot,
		Depth;

	bool
		Animating,
		Looping;

	BasicUnit(void);
	virtual ~BasicUnit(void);

	virtual string toString( void ) const;

	virtual void init( Animation* pAnimation = nullptr, Vector2 pos = Vector2::ZERO, Vector2 origin = Vector2::ZERO, float rot = 0.0f, Color color = Color::WHITE, float depth = 1.0f);
	virtual void term( void );

	virtual void update( GameTime *pGameTime );
	virtual void draw  ( RenderTarget *pRenderTarget, Vector2 offset = Vector2::ZERO );

	virtual Animation* animation( void ) { return _pAnimation; }
	virtual void setAnimation( Animation *pAnimation, bool useDefaults = true);

};

#endif