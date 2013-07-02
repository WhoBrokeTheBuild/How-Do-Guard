#pragma once

#ifndef __DROPDOWN_H__
#define __DROPDOWN_H__

#include "Common.h"
#include "Component.h"

class DropdownChangedData
    : public EventData
{
public:

    int 
        Index;

    string
        Item;

    DropdownChangedData( int index, string item ) { Index = index; Item = item;}

    virtual string toString( void ) const { return "Dropdown Changed Data"; }

    virtual EventData* clone( void ) const { return New DropdownChangedData(Index, Item); }

};

class Dropdown :
    public Component
{
protected:

    bool
        _listShown;

    CachedText
        *_pText;

    Font
        *_pFont;

    float
        _leftTrianglePadding;

public:

    vector<string>
        Items;

    int
        Index,
        MaxRows;

    Color
        TextColor,
        BorderColor,
        BGColor,
        FocusTextColor,
        FocusBorderColor,
        FocusBGColor;

    static const EventType EVENT_SELECTED_INDEX_CHANGED;

    Dropdown( void ) { };
    virtual ~Dropdown( void );

    virtual string toString( void ) const;

    virtual void init( Vector2 pos = Vector2::ZERO, vector<string> items = vector<string>(),Vector2 padding = Vector2(5.0f) );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    virtual Size largestItem( void );
    virtual Size size( void );

    virtual void clickedOn ( Vector2 mousePos );
    virtual void clickedOff( Vector2 mousePos );

    virtual string selected( void );

};

#endif