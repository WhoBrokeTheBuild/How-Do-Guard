#pragma once

#ifndef __RENDER_TARGET_H__
#define __RENDER_TARGET_H__

#include "Common.h"
#include "GameObject.h"

#include "Color.h"

#include <SDL.h>
#include <SDL_opengl.h>

class GraphicsSystem;

class RenderTarget :
	public GameObject
{
private: 

	GraphicsSystem
		*_pGraphicsSystem;

	virtual void drawShape( float x, float y, float radius, float shapeValue, Color color, float rotation = 0.0f );
	virtual void fillShape( float x, float y, float radius, float shapeValue, Color color, float rotation = 0.0f );

public:

	RenderTarget( void );
	virtual ~RenderTarget( void );

	virtual void init( GraphicsSystem *pGraphicsSystem );
	virtual void term( void );

	virtual string toString( void ) const;

	virtual void beginDraw( void );
	virtual void endDraw( void );

	virtual void drawRect( float x, float y, float width, float height, Color color, float rotation = 0.0f );
	virtual void drawRect( Rect rect, Color color, float rotation = 0.0f );

	virtual void fillRect( float x, float y, float width, float height, Color color, float rotation = 0.0f );
	virtual void fillRect( Rect rect, Color color, float rotation = 0.0f );

	virtual void drawCircle( float x, float y, float radius, Color color, float rotation = 0.0f );
	virtual void drawCircle( Circle circle, Color color, float rotation = 0.0f );

	virtual void fillCircle( float x, float y, float radius, Color color, float rotation = 0.0f );
	virtual void fillCircle( Circle circle, Color color, float rotation = 0.0f );

	virtual void drawTriangle( float x, float y, float radius, Color color, float rotation = 0.0f );
	virtual void fillTriangle( float x, float y, float radius, Color color, float rotation = 0.0f );

	virtual void drawPentagon( float x, float y, float radius, Color color, float rotation = 0.0f );
	virtual void fillPentagon( float x, float y, float radius, Color color, float rotation = 0.0f );

	virtual void drawHexagon ( float x, float y, float radius, Color color, float rotation = 0.0f );
	virtual void fillHexagon ( float x, float y, float radius, Color color, float rotation = 0.0f );

};

#endif