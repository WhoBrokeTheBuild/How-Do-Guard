#include "ConfigObject.h"
#include "DataManager.h"

ConfigObject::~ConfigObject(void)
{
    term();
}

void ConfigObject::init( void )
{
}

void ConfigObject::term( void )
{
    Map<ConfigKey, ConfigItem>::Iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
    {
        if (it->second.Type == CONFIG_TYPE_OBJECT)
        {
            delete it->second.ObjectData;
        }
    }

    Map<ConfigKey, ArrayList<ConfigItem>>::Iterator listIt;
    for (listIt = _itemLists.begin(); listIt != _itemLists.end(); ++listIt)
    {
        ArrayList<ConfigItem>* pList = &listIt->second;

        for (unsigned int i = 0; i < pList->size(); ++i)
        {
            if (pList->at(i).Type == CONFIG_TYPE_OBJECT)
            {
                delete pList->at(i).ObjectData;
            }
        }

        pList->clear();
    }

    _items.clear();
    _itemLists.clear();
}

bool ConfigObject::hasItem( ConfigKey key, ConfigType type )
{
    return (_items.contains(key) && _items[key].Type == type);
}

bool ConfigObject::hasItemList( ConfigKey key, ConfigType type )
{
    if (!_itemLists.contains(key))
        return false;

    ArrayList<ConfigItem> list = _itemLists[key];

    bool hasType = false;
    ArrayList<ConfigItem>::Iterator it;
    for (it = list.begin(); it != list.end(); ++it)
    {
        if (it->Type == type)
        {
            hasType = true;
            break;
        }
    }

    return hasType;
}

ConfigItem ConfigObject::getItem( ConfigKey key, ConfigType type )
{
    if (hasItem(key, type))
    {
        return _items[key];
    }

    return ConfigItem();
}

ArrayList<ConfigItem> ConfigObject::getList( ConfigKey key, ConfigType type )
{
    if (hasItemList(key, type))
    {
        ArrayList<ConfigItem> 
            list = _itemLists[key],
            filtered;

        ArrayList<ConfigItem>::Iterator it;
        for (it = list.begin(); it != list.end(); ++it)
        {
            if (it->Type != type)
                continue;

            filtered.add(*it);
        }

        return filtered;
    }

    return ArrayList<ConfigItem>();
}

ConfigObject* ConfigObject::getObject( ConfigKey key, ConfigObject* default /*= nullptr */ )
{
    if (!hasObject(key))
        return default;
    
    return getItem(key, CONFIG_TYPE_OBJECT).ObjectData;
}

int ConfigObject::getInt( ConfigKey key, int default /*= -1 */ )
{
    if (!hasInt(key))
        return default;

    return getItem(key, CONFIG_TYPE_INT).IntData;
}

float ConfigObject::getFloat( ConfigKey key, float default /*= -1.0f */ )
{
    if (!hasFloat(key))
        return default;

    return getItem(key, CONFIG_TYPE_FLOAT).FloatData;
}

bool ConfigObject::getBool( ConfigKey key, bool default /*= false */ )
{
    if (!hasBool(key))
        return default;

    return getItem(key, CONFIG_TYPE_BOOL).BoolData;
}

std::string ConfigObject::getString( ConfigKey key, string default /*= "" */ )
{
    if (!hasString(key))
        return default;

    return getItem(key, CONFIG_TYPE_STRING).StringData;
}

Vector2 ConfigObject::getVector2( ConfigKey key, Vector2 default /*= Vector2::ZERO */ )
{
    if (!hasVector2(key))
        return default;

    return getItem(key, CONFIG_TYPE_VECTOR2).Vector2Data;
}

Rect ConfigObject::getRect( ConfigKey key, Rect default /*= Rect::ZERO*/ )
{
    if (!hasRect(key))
        return default;

    return getItem(key, CONFIG_TYPE_RECT).RectData;
}

Circle ConfigObject::getCircle( ConfigKey key, Circle default /*= Circle::ZERO*/ )
{
    if (!hasCircle(key))
        return default;

    return getItem(key, CONFIG_TYPE_CIRCLE).CircleData;
}

Color ConfigObject::getColor( ConfigKey key, Color default /*= Color::WHITE */ )
{
    if (!hasColor(key))
        return default;

    return getItem(key, CONFIG_TYPE_COLOR).ColorData;
}

ArrayList<ConfigObject*> ConfigObject::getObjectList( ConfigKey key )
{
    ArrayList<ConfigItem>    itemList = getList(key, CONFIG_TYPE_OBJECT);
    ArrayList<ConfigObject*> list;

    ArrayList<ConfigItem>::Iterator it;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        list.add(it->ObjectData);
    }

    return list;
}

ArrayList<int> ConfigObject::getIntList( ConfigKey key )
{
    ArrayList<ConfigItem> itemList = getList(key, CONFIG_TYPE_INT);
    ArrayList<int>        list;

    ArrayList<ConfigItem>::Iterator it;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        list.add(it->IntData);
    }

    return list;
}

ArrayList<float> ConfigObject::getFloatList( ConfigKey key )
{
    ArrayList<ConfigItem> itemList = getList(key, CONFIG_TYPE_FLOAT);
    ArrayList<float>        list;

    ArrayList<ConfigItem>::Iterator it;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        list.add(it->FloatData);
    }

    return list;
}

ArrayList<bool> ConfigObject::getBoolList( ConfigKey key )
{
    ArrayList<ConfigItem> itemList = getList(key, CONFIG_TYPE_BOOL);
    ArrayList<bool>        list;

    ArrayList<ConfigItem>::Iterator it;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        list.add(it->BoolData);
    }

    return list;
}

ArrayList<string> ConfigObject::getStringList( ConfigKey key )
{
    ArrayList<ConfigItem> itemList = getList(key, CONFIG_TYPE_STRING);
    ArrayList<string>        list;

    ArrayList<ConfigItem>::Iterator it;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        list.add(it->StringData);
    }

    return list;
}

ArrayList<Vector2> ConfigObject::getVector2List( ConfigKey key )
{
    ArrayList<ConfigItem> itemList = getList(key, CONFIG_TYPE_VECTOR2);
    ArrayList<Vector2>        list;

    ArrayList<ConfigItem>::Iterator it;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        list.add(it->Vector2Data);
    }

    return list;
}

ArrayList<Rect> ConfigObject::getRectList( ConfigKey key )
{
    ArrayList<ConfigItem> itemList = getList(key, CONFIG_TYPE_RECT);
    ArrayList<Rect>        list;

    ArrayList<ConfigItem>::Iterator it;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        list.add(it->RectData);
    }

    return list;
}

ArrayList<Circle> ConfigObject::getCircleList( ConfigKey key )
{
    ArrayList<ConfigItem> itemList = getList(key, CONFIG_TYPE_CIRCLE);
    ArrayList<Circle>        list;

    ArrayList<ConfigItem>::Iterator it;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        list.add(it->CircleData);
    }

    return list;
}

ArrayList<Color> ConfigObject::getColorList( ConfigKey key )
{
    ArrayList<ConfigItem> itemList = getList(key, CONFIG_TYPE_COLOR);
    ArrayList<Color>        list;

    ArrayList<ConfigItem>::Iterator it;
    for (it = itemList.begin(); it != itemList.end(); ++it)
    {
        list.add(it->ColorData);
    }

    return list;
}

ArrayList<ConfigKey> ConfigObject::getItemKeys( void )
{
    return _items.keyArrayList();
}

ArrayList<ConfigKey> ConfigObject::getListKeys( void )
{
    return _itemLists.keyArrayList();
}