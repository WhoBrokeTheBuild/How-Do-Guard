#pragma once

#ifndef __CONFIG_ITEM_H__
#define __CONFIG_ITEM_H__

#include "Common.h"
#include <GameObject.h>

#include "ConfigType.h"

class ConfigObject;

struct ConfigItem : 
    GameObject
{
public:

    ConfigType
        Type;

    ConfigObject*
        ObjectData;

    int
        IntData;

    float
        FloatData;

    bool
        BoolData;

    string
        StringData;

    Vector2
        Vector2Data;

    Rect
        RectData;

    Circle
        CircleData;

    Color
        ColorData;

    ConfigItem( void );
    ConfigItem( ConfigObject* object );
    ConfigItem( int data );
    ConfigItem( float data );
    ConfigItem( bool data );
    ConfigItem( string data );
    ConfigItem( Vector2 data );
    ConfigItem( Rect data );
    ConfigItem( Circle data );
    ConfigItem( Color data );

    virtual string toString( void ) const { return "Config Item"; }

};

#endif