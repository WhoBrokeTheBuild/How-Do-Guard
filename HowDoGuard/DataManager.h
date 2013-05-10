#pragma once

#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "Common.h"
#include "GameObject.h"

#include "Manager.h"

#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"

#include "VerticalState.h"
#include "PlayerState.h"
#include "PlayerStateChange.h"
#include "GameInputType.h"

#include <fstream>
#include <map>

typedef vector<PlayerStateChange>										PlayerStateChangeList;
typedef map<VerticalState, PlayerStateChangeList>						VerticalPlayerStateMap; //TODO: Fix Names
typedef map<pair<GameInput, GameInputType>, VerticalPlayerStateMap>		PlayerStateMap;

class DataManager :
	public GameObject
{
private:

	void loadAssets( string filename );
	void loadAssetFile( string filename );
	void loadPlayerStates( string filename );

	string getNextLine( ifstream& in );

public:

	Manager<Animation>
		*pAnimations;

	Manager<Sprite>
		*pSprites;

	Manager<Texture>
		*pTextures;

	map<ItemKey, PlayerStateMap>
		PlayerStateData;

	DataManager( void );
	virtual ~DataManager( void );

	virtual string toString( void ) const;

	virtual void init( void );
	virtual void term( void );

};

extern DataManager* gpDataManager;

#endif