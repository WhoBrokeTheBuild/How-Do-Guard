#pragma once

#ifndef __CONFIG_OBJECT_H__
#define __CONFIG_OBJECT_H__

#include "Common.h"
#include <GameObject.h>

#include <Map.h>
#include <ArrayList.h>

#include "ConfigItem.h"

class DataManager;

typedef string ConfigKey;

class ConfigObject :
    public GameObject
{

    friend class DataManager;

private:

    Map<ConfigKey, ConfigItem>
        _items;

    Map<ConfigKey, ArrayList<ConfigItem>>
        _itemLists;

    virtual bool hasItem    ( ConfigKey key, ConfigType type );
    virtual bool hasItemList( ConfigKey key, ConfigType type );

    virtual ConfigItem            getItem( ConfigKey key, ConfigType type );
    virtual ArrayList<ConfigItem> getList( ConfigKey key, ConfigType type );

public:

    ConfigObject( void ) { }
    virtual ~ConfigObject( void );

    virtual string toString( void ) const { return "Config Object"; }

    virtual void init( void );
    virtual void term( void );

    virtual ArrayList<ConfigKey> getItemKeys( void );
    virtual ArrayList<ConfigKey> getListKeys( void );

    virtual bool hasObject ( ConfigKey key ) { return hasItem(key, CONFIG_TYPE_OBJECT); }
    virtual bool hasInt    ( ConfigKey key ) { return hasItem(key, CONFIG_TYPE_INT); }
    virtual bool hasFloat  ( ConfigKey key ) { return hasItem(key, CONFIG_TYPE_FLOAT); }
    virtual bool hasBool   ( ConfigKey key ) { return hasItem(key, CONFIG_TYPE_BOOL); }
    virtual bool hasString ( ConfigKey key ) { return hasItem(key, CONFIG_TYPE_STRING); }
    virtual bool hasVector2( ConfigKey key ) { return hasItem(key, CONFIG_TYPE_VECTOR2); }
    virtual bool hasRect   ( ConfigKey key ) { return hasItem(key, CONFIG_TYPE_RECT); }
    virtual bool hasCircle ( ConfigKey key ) { return hasItem(key, CONFIG_TYPE_CIRCLE); }
    virtual bool hasColor  ( ConfigKey key ) { return hasItem(key, CONFIG_TYPE_COLOR); }

    virtual ConfigObject* getObject ( ConfigKey key, ConfigObject* default = nullptr );
    virtual int           getInt    ( ConfigKey key, int           default = -1 );            
    virtual float         getFloat  ( ConfigKey key, float         default = -1.0f );       
    virtual bool          getBool   ( ConfigKey key, bool          default = false );       
    virtual string        getString ( ConfigKey key, string        default = "" );
    virtual Vector2       getVector2( ConfigKey key, Vector2       default = Vector2::ZERO );
    virtual Rect          getRect   ( ConfigKey key, Rect          default = Rect::ZERO ); 
    virtual Circle        getCircle ( ConfigKey key, Circle        default = Circle::ZERO );
    virtual Color         getColor  ( ConfigKey key, Color         default = Color::WHITE );

    virtual bool                     hasObjectList( ConfigKey key ) { return hasItemList(key, CONFIG_TYPE_OBJECT); }
    virtual ArrayList<ConfigObject*> getObjectList( ConfigKey key );

    virtual bool               hasIntList    ( ConfigKey key ) { return hasItemList(key, CONFIG_TYPE_INT); }
    virtual ArrayList<int>     getIntList    ( ConfigKey key );    
                                                                 
    virtual bool               hasFloatList  ( ConfigKey key ) { return hasItemList(key, CONFIG_TYPE_FLOAT); }
    virtual ArrayList<float>   getFloatList  ( ConfigKey key );  
                                                              
    virtual bool               hasBoolList   ( ConfigKey key ) { return hasItemList(key, CONFIG_TYPE_BOOL); }
    virtual ArrayList<bool>    getBoolList   ( ConfigKey key );
                               
    virtual bool               hasStringList ( ConfigKey key ) { return hasItemList(key, CONFIG_TYPE_STRING); }
    virtual ArrayList<string>  getStringList ( ConfigKey key );
                               
    virtual bool               hasVector2List( ConfigKey key ) { return hasItemList(key, CONFIG_TYPE_VECTOR2); }
    virtual ArrayList<Vector2> getVector2List( ConfigKey key );
                               
    virtual bool               hasRectList   ( ConfigKey key ) { return hasItemList(key, CONFIG_TYPE_RECT); }
    virtual ArrayList<Rect>    getRectList   ( ConfigKey key );
                               
    virtual bool               hasCircleList ( ConfigKey key ) { return hasItemList(key, CONFIG_TYPE_CIRCLE); }
    virtual ArrayList<Circle>  getCircleList ( ConfigKey key );
                               
    virtual bool               hasColorList  ( ConfigKey key ) { return hasItemList(key, CONFIG_TYPE_COLOR); }
    virtual ArrayList<Color>   getColorList  ( ConfigKey key );

};

#endif