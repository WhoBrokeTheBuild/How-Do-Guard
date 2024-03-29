#pragma once

#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "Common.h"
#include <GameObject.h>

#include <Manager.h>

#include <Animation.h>
#include <Sprite.h>
#include <Texture.h>

#include <InputType.h>

#include "ConfigLevel.h"

#include <fstream>
#include <map>
#include <stack>

class DataManager :
    public GameObject
{
private:

    static ConfigLevel
        _config;

    void loadConfig( string filename, vector<string> levels = vector<string>() );
    void loadAssets( string filename, vector<string> levels = vector<string>() );

    void parseConfigLine ( string line, vector<string> levels, string listName );

public:

    string 
        BaseDir;

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

    void reload( void );

    ConfigValue          getData ( vector<ConfigKey> name, ConfigKey dataName );
    vector<ConfigValue>* getList ( vector<ConfigKey> name, ConfigKey listName );
    ConfigLevel*         getLevel( vector<ConfigKey> name );

    string  getString ( vector<ConfigKey> name );
    int     getInt    ( vector<ConfigKey> name );
    float   getFloat  ( vector<ConfigKey> name );
    double  getDouble ( vector<ConfigKey> name );
    Vector2 getVector2( vector<ConfigKey> name );
    Rect    getRect   ( vector<ConfigKey> name );
    Circle  getCircle ( vector<ConfigKey> name );
    Color   getColor  ( vector<ConfigKey> name );

    vector<string>  getStringList ( vector<ConfigKey> name );
    vector<int>     getIntList    ( vector<ConfigKey> name );
    vector<float>   getFloatList  ( vector<ConfigKey> name );
    vector<double>  getDoubleList ( vector<ConfigKey> name );
    vector<Vector2> getVector2List( vector<ConfigKey> name );
    vector<Rect>    getRectList   ( vector<ConfigKey> name );
    vector<Circle>  getCircleList ( vector<ConfigKey> name );
    vector<Color>   getColorList  ( vector<ConfigKey> name );

};

extern DataManager* gpDataManager;

#endif