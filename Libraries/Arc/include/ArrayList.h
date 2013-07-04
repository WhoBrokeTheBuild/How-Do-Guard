#pragma once

#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include "ArcCommon.h"
#include "GameObject.h"

#include <vector>

template <class T>
class LinkedList;

template <class T>
class Queue;

template <class T>
class ArrayList :
    public GameObject
{
protected:

    vector<T>
        _list;

public:

    typedef typename vector<T>::iterator       Iterator;
    typedef typename vector<T>::const_iterator ConstIterator;

    ArrayList ( void ) { } 
    ArrayList ( const ArrayList& rhs) : _list(rhs._list) { }
    virtual ~ArrayList( void );

    ArrayList& operator= ( const ArrayList& rhs ) { _list = rhs._list; return *this; }
    T&         operator[]( const int index)       { return at(index); }

    virtual string toString( void ) const { return "Array List"; }

    Iterator begin ( void ) { return _list.begin(); }
    Iterator end   ( void ) { return _list.end(); }
    Iterator rbegin( void ) { return _list.rbegin(); }
    Iterator rend  ( void ) { return _list.rend(); }

    ConstIterator cbegin ( void ) const { return _list.cbegin(); }
    ConstIterator cend   ( void ) const { return _list.cend(); }
    ConstIterator crbegin( void ) const { return _list.crbegin(); }
    ConstIterator crend  ( void ) const { return _list.crend(); }

    ArrayList<T>* add        ( const T& item );
    ArrayList<T>* insertAt   ( const T& item, const int& index );
    ArrayList<T>* clear      ( void );
    bool          remove     ( const T& item );
    bool          removeAll  ( const T& item );
    bool          removeAt   ( const unsigned int& index );
    bool          removeFront( void );
    bool          removeBack ( void );

    T& at( int index ) { return _list[index]; }

    T& front( void ) { return _list.front(); }
    T& back ( void ) { return _list.back(); }

    const T& front( void ) const { return _list.front(); }
    const T& back ( void ) const { return _list.back(); }

    bool contains( const T& item ) const;
    bool hasIndex( const int& index ) const;
    bool empty   ( void )    const { return _list.empty(); }

    int indexOf( T& item ) const;

    size_t size( void ) const { return _list.size(); }

    T*            toArray     ( void ) { unsigned int i; return toArray(i); }
    LinkedList<T> toLinkedList( void ) { unsigned int i; return toLinkedList(i); }
    Queue<T>      toQueue     ( void ) { unsigned int i; return toQueue(i); }

    T*            toArray     ( unsigned int& length );
    LinkedList<T> toLinkedList( unsigned int& length );
    Queue<T>      toQueue     ( unsigned int& length );

};

#include "LinkedList.h"
#include "Queue.h"

template <class T>
ArrayList<T>::~ArrayList( void )
{
    clear();
}

template <class T>
ArrayList<T>* ArrayList<T>::add( const T& item )
{
    _list.push_back(item);
    return this;
}

template <class T>
ArrayList<T>* ArrayList<T>::insertAt( const T& item, const int& index )
{
    _list.insert(_list.begin() + index, item);
    return this;
}

template <class T>
bool ArrayList<T>::remove( const T& item )
{
    Iterator it;

    for (it = begin(); it != end(); ++it)
    {
        if (*it == item)
        {
            _list.erase(it);
            return true;
        }
    }
    return false;
}

template <class T>
bool ArrayList<T>::removeAll( const T& item )
{
    Iterator it;

    bool found = false;
    for (it = begin(); it != end(); ++it)
    {
        if (it->second == value)
        {
            _list.erase(it);
            found = true;
        }
    }
    return found;
}

template <class T>
bool ArrayList<T>::removeAt( const unsigned int& index )
{
    if (!hasIndex(index))
        return false;

    _list.erase(begin() + index);
    return true;
}

template <class T>
bool ArrayList<T>::removeFront( void )
{
    if (empty())
        return false;

    removeAt(0);
    return true;
}

template <class T>
bool ArrayList<T>::removeBack( void )
{
    if (empty())
        return false;

    _list.pop_back();
    return true;
}

template <class T>
ArrayList<T>* ArrayList<T>::clear( void )
{
    _list.clear();
    return this;
}

template <class T>
bool ArrayList<T>::contains( const T& item ) const
{
    if (empty())
        return false;

    return (find(cbegin(), cend(), item) != cend());
}

template <class T>
bool ArrayList<T>::hasIndex( const int& index ) const
{
    return (between(index, 0, (const int)size()));
}

template <class T>
T* ArrayList<T>::toArray( unsigned int& length )
{
    length = size();
    T* other = new T[length];

    int index = 0;
    for (Iterator it = begin(); it != end(); ++it, ++index)
        other[index] = *it;

    return other;
}

template <class T>
LinkedList<T> ArrayList<T>::toLinkedList( unsigned int& length )
{
    length = size();
    LinkedList<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(*it);

    return other;
}

template <class T>
Queue<T> ArrayList<T>::toQueue( unsigned int& length )
{
    Queue<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.push(*it);

    return other;
}

#endif