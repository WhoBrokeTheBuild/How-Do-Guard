#pragma once

#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "Common.h"
#include "GameObject.h"

#include "Manager.h"

#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"

#include <fstream>

class DataManager :
	public GameObject
{
private:

	virtual void loadAssets( string filename );
	virtual void loadAssetFile( string filename );

public:

	Manager<Animation>
		*pAnimations;

	Manager<Sprite>
		*pSprites;

	Manager<Texture>
		*pTextures;

	DataManager( void );
	virtual ~DataManager( void );

	virtual string toString( void ) const;

	virtual void init( void );
	virtual void term( void );

};

extern DataManager* gpDataManager;

#endif