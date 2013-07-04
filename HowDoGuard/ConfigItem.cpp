#include "ConfigItem.h"
#include "ConfigObject.h"

ConfigItem::ConfigItem( void )
{
    Type = INVALID_CONFIG_TYPE;
}

ConfigItem::ConfigItem( ConfigObject* object )
{
    Type = CONFIG_TYPE_OBJECT;
    ObjectData = object;
}

ConfigItem::ConfigItem( int data )
{
    Type = CONFIG_TYPE_INT;
    IntData = data;
}

ConfigItem::ConfigItem( float data )
{
    Type = CONFIG_TYPE_FLOAT;
    FloatData = data;
}

ConfigItem::ConfigItem( bool data )
{
    Type = CONFIG_TYPE_BOOL;
    BoolData = data;
}

ConfigItem::ConfigItem( string data )
{
    Type = CONFIG_TYPE_STRING;
    StringData = data;
}

ConfigItem::ConfigItem( Vector2 data )
{
    Type = CONFIG_TYPE_VECTOR2;
    Vector2Data = data;
}

ConfigItem::ConfigItem( Rect data )
{
    Type = CONFIG_TYPE_RECT;
    RectData = data;
}

ConfigItem::ConfigItem( Circle data )
{
    Type = CONFIG_TYPE_CIRCLE;
    CircleData = data;
}

ConfigItem::ConfigItem( Color data )
{
    Type = CONFIG_TYPE_COLOR;
    ColorData = data;
}
