#pragma once

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "ArcCommon.h"
#include <list>
#include <algorithm>

template <class T>
class ArrayList;

template <class T>
class Queue;

template <class T>
class LinkedList :
    public GameObject
{
protected:

    list<T>
        _list;

public:

    typedef typename list<T>::iterator       Iterator;
    typedef typename list<T>::const_iterator ConstIterator;

    LinkedList ( void ) { }
    LinkedList ( const LinkedList& rhs) : _list(rhs._list) { }
    virtual ~LinkedList( void );

    LinkedList& operator=( const LinkedList& rhs ) { _list = rhs._list; return *this; }

    virtual string toString( void ) const { return "Linked List"; }

    Iterator begin ( void ) { return _list.begin(); }
    Iterator end   ( void ) { return _list.end(); }
    Iterator rbegin( void ) { return _list.rbegin(); }
    Iterator rend  ( void ) { return _list.rend(); }

    ConstIterator cbegin ( void ) const { return _list.cbegin(); }
    ConstIterator cend   ( void ) const { return _list.cend(); }
    ConstIterator crbegin( void ) const { return _list.crbegin(); }
    ConstIterator crend  ( void ) const { return _list.crend(); }

    LinkedList<T>* add        ( const T& item );
    LinkedList<T>* addFront   ( const T& item );
    LinkedList<T>* addBack    ( const T& item );
    LinkedList<T>* insertAt   ( const T& item, const int& index );
    LinkedList<T>* clear      ( void );
    bool           remove     ( const T& item );
    bool           removeAll  ( const T& item );
    bool           removeAt   ( const unsigned int& index );
    bool           removeFront( void );
    bool           removeBack ( void );

    T& front( void ) { return _list.front(); }
    T& back ( void ) { return _list.back(); }

    const T& front( void ) const { return _list.front(); }
    const T& back ( void ) const { return _list.back(); }

    bool contains( const T& item ) const;
    bool hasIndex( const int& index) const;
    bool empty   ( void )    const { return _list.empty(); }

    int indexOf( T& item ) const;

    size_t size( void ) const { return _list.size(); }

    T*           toArray    ( void ) { unsigned int i; return toArray(i); }
    ArrayList<T> toArrayList( void ) { unsigned int i; return toArrayList(i); }
    Queue<T>     toQueue    ( void ) { unsigned int i; return toQueue(i); }

    T*           toArray    ( unsigned int& length );
    ArrayList<T> toArrayList( unsigned int& length );
    Queue<T>     toQueue    ( unsigned int& length );

};

#include "ArrayList.h"
#include "Queue.h"

template <class T>
LinkedList<T>::~LinkedList( void )
{
    clear();
}

template <class T>
LinkedList<T>* LinkedList<T>::add( const T& item )
{
    addBack(item);
    return this;
}

template <class T>
LinkedList<T>* LinkedList<T>::addFront( const T& item )
{
    _list.push_front(item);
    return this;
}

template <class T>
LinkedList<T>* LinkedList<T>::addBack( const T& item )
{
    _list.push_back(item);
    return this;
}

template <class T>
LinkedList<T>* LinkedList<T>::insertAt( const T& item, const int& index )
{
    _list.insert(_list.begin() + index, item);
    return this;
}

template <class T>
bool LinkedList<T>::remove( const T& item )
{
    Iterator it;

    for (it = begin(); it != end(); ++it)
    {
        if (it == item)
        {
            _list.erase(it);
            return true;
        }
    }
    return false;
}

template <class T>
bool LinkedList<T>::removeAll( const T& item )
{
    return (_list.remove(item) > 0);
}

template <class T>
bool LinkedList<T>::removeAt( const unsigned int& index )
{
    if (!hasIndex(index))
        return false;

    _list.erase(begin() + index);
    return true;
}

template <class T>
bool LinkedList<T>::removeFront( void )
{
    if (empty())
        return false;

    _list.pop_front();
    return true;
}

template <class T>
bool LinkedList<T>::removeBack( void )
{
    if (empty())
        return false;

    _list.pop_back();
    return true;
}

template <class T>
LinkedList<T>* LinkedList<T>::clear( void )
{
    _list.clear();
    return this;
}

template <class T>
bool LinkedList<T>::contains( const T& item ) const
{
    if (empty()) 
        return false;

    return (find(cbegin(), cend(), item) != cend())
}

template <class T>
bool LinkedList<T>::hasIndex( const int& index ) const
{
    return (between(index, 0, (const int)size()));
}

template <class T>
T* LinkedList<T>::toArray( unsigned int& length )
{
    length = size();
    T* other = new T[length];

    int index = 0;
    for (Iterator it = begin(); it != end(); ++it, ++index)
        other[index] = *it;

    return other;
}

template <class T>
ArrayList<T> LinkedList<T>::toArrayList( unsigned int& length )
{
    ArrayList<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.add(*it);

    return other;
}

template <class T>
Queue<T> LinkedList<T>::toQueue( unsigned int& length )
{
    Queue<T> other;

    for (Iterator it = begin(); it != end(); ++it)
        other.push(*it);

    return other;
}

#endif