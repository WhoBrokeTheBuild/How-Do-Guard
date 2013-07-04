#pragma once

#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "Common.h"
#include <GameObject.h>

#include "ConfigObject.h"

#include <Texture.h>
#include <Animation.h>

#include <fstream>

class DataManager :
    public GameObject
{
private:

    ConfigObject
        *_pRoot;

    string
        _configDir,
        _sheetDir,
        _configExt;

    virtual void load( string filename );
    virtual void parseFile( string filename, ConfigObject* pObject );

    virtual void loadAssets( ArrayList<ConfigKey> path );

public:

    Map<ConfigKey, Texture*>
        Textures;

    ArrayList<Sprite*>
        Sprites;

    Map<ConfigKey, Animation*>
        Animations;

    DataManager( void ) { };
    virtual ~DataManager( void );

    virtual string toString( void ) const { return "Data Manager"; }

    virtual void init( void );
    virtual void term( void );

    ConfigObject*         getObject( ArrayList<ConfigKey> path );

};

extern DataManager* gpDataManager;

#endif