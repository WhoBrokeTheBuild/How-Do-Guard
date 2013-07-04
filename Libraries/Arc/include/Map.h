#pragma once

#ifndef __MAP_H__
#define __MAP_H__

#include "ArcCommon.h"
#include "GameObject.h"

#include <map>

template <class T>
class LinkedList;

template <class T>
class ArrayList;

template <class K, class T, typename Sort = less<K>>
class Map :
    public GameObject
{
protected:

    map<K, T, Sort>
        _map;

public:

    typedef typename map<K, T, Sort>::iterator       Iterator;
    typedef typename map<K, T, Sort>::const_iterator ConstIterator;

    typedef pair<K, T> Pair;

    Map( void ) { }
    Map( const Map& rhs) : _map(rhs._map) { }
    virtual ~Map( void );

    Map& operator= ( const Map& rhs ) { _map = rhs._map; return *this; }
    T&   operator[]( const K& key )   { return at(key); } 

    virtual string toString( void ) const { return "Map"; }

    Iterator begin ( void ) { return _map.begin(); }
    Iterator end   ( void ) { return _map.end(); }
    Iterator rbegin( void ) { return _map.rbegin(); }
    Iterator rend  ( void ) { return _map.rend(); }

    ConstIterator cbegin ( void ) const { return _map.cbegin(); }
    ConstIterator cend   ( void ) const { return _map.cend(); }
    ConstIterator crbegin( void ) const { return _map.crbegin(); }
    ConstIterator crend  ( void ) const { return _map.crend(); }

    Iterator      find( K& key )       { return _map.find(key); }
    ConstIterator find (K& key ) const { return _map.find(key); }

    Map<K, T, Sort>* add            ( const K& key, const T& item );
    Map<K, T, Sort>* clear          ( void );
    bool             remove         ( const K& key );
    bool             removeKey      ( const K& key );
    bool             removeValue    ( const T& value );
    bool             removeAllValues( const T& value );

    T& at( const K& key ) { return _map[key]; }

    bool contains     ( const K& key );
    bool containsKey  ( const K& key );
    bool containsValue( const T& value );

    bool empty( void ) const { return _list.empty(); }

    K& indexOf( T& item );

    size_t size( void ) const { return _map.size(); }

    K*            keyArray     ( void ) { unsigned int i; return keyArray(i); }
    LinkedList<K> keyLinkedList( void ) { unsigned int i; return keyLinkedList(i); }
    ArrayList<K>  keyArrayList ( void ) { unsigned int i; return keyArrayList(i); }

    T*            valueArray     ( void ) { unsigned int i; return valueArray(i); }
    LinkedList<T> valueLinkedList( void ) { unsigned int i; return valueLinkedList(i); }
    ArrayList<T>  valueArrayList ( void ) { unsigned int i; return valueArrayList(i); }

    K*            keyArray     ( unsigned int& length );
    LinkedList<K> keyLinkedList( unsigned int& length );
    ArrayList<K>  keyArrayList ( unsigned int& length );

    T*            valueArray     ( unsigned int& length );
    LinkedList<T> valueLinkedList( unsigned int& length );
    ArrayList<T>  valueArrayList ( unsigned int& length );
};

#include "LinkedList.h"
#include "ArrayList.h"

template <class K, class T, typename Sort>
Map<K, T, Sort>::~Map( void )
{
    clear();
}

template <class K, class T, typename Sort>
Map<K, T, Sort>* Map<K, T, Sort>::add( const K& key, const T& item )
{
    _map.insert(Pair(key, item));
    return this;
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::remove( const K& key )
{
    return removeKey(key);
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::removeKey( const K& key )
{
    return (_map.erase(key) == 1);
}
template <class K, class T, typename Sort>
bool Map<K, T, Sort>::removeValue( const T& value )
{
    Iterator it;

    for (it = begin(); it != end(); ++it)
    {
        if (it->second == value)
        {
            _map.erase(it);
            return true;
        }
    }
    return false;
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::removeAllValues( const T& value )
{
    Iterator it;

    bool found = false;
    for (it = begin(); it != end(); ++it)
    {
        if (it->second == value)
        {
            _map.erase(it);
            found = true;
        }
    }
    return true;
}

template <class K, class T, typename Sort>
Map<K, T, Sort>* Map<K, T, Sort>::clear( void )
{
    _map.clear();
    return this;
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::contains( const K& key )
{
    return containsKey(key);
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::containsKey( const K& key )
{
    ConstIterator it = _map.find(key);

    return (it != cend());
}

template <class K, class T, typename Sort>
bool Map<K, T, Sort>::containsValue( const T& value )
{
    ConstIterator it;

    for (it = cbegin(); it != cend(); ++it)
    {
        if (it->second == value)
            return true;
    }

    return false;
}

template <class K, class T, typename Sort>
K& Map<K, T, Sort>::indexOf( T& item )
{
    ConstIterator it;

    for (it = cbegin(); it != cend(); ++it)
    {
        if (it->second == value)
            return it->first;
    }

    return K();
}
template <class K, class T, typename Sort>
K* Map<K, T, Sort>::keyArray( unsigned int& length )
{
    length = size();
    K* other = new T[length];

    int index = 0;
    for (Iterator it = begin(); it != end(); ++it, ++index)
        other[index] = it->first;

    return other;
}

template <class K, class T, typename Sort>
LinkedList<K> Map<K, T, Sort>::keyLinkedList( unsigned int& length )
{
    length = size();
    LinkedList<K> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(it->first);

    return other;
}

template <class K, class T, typename Sort>
ArrayList<K> Map<K, T, Sort>::keyArrayList( unsigned int& length )
{
    length = size();
    ArrayList<K> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(it->first);

    return other;
}

template <class K, class T, typename Sort>
T* Map<K, T, Sort>::valueArray( unsigned int& length )
{
    length = size();
    T* other = new T[length];

    int index = 0;
    for (Iterator it = begin(); it != end(); ++it, ++index)
        other[index] = it->second;

    return other;
}

template <class K, class T, typename Sort>
LinkedList<T> Map<K, T, Sort>::valueLinkedList( unsigned int& length )
{
    length = size();
    LinkedList<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(it->second);

    return other;
}

template <class K, class T, typename Sort>
ArrayList<T> Map<K, T, Sort>::valueArrayList( unsigned int& length )
{
    length = size();
    ArrayList<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(it->second);

    return other;
}

#endif