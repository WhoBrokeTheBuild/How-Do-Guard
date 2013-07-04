
#pragma once

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Defines.h"

#include <iostream>
#include <conio.h>

#include "TimeFunc.h"
#include "MathFunc.h"
#include "RandFunc.h"
#include "ParseFunc.h"
#include "StringFunc.h"
#include "InputFunc.h"

using namespace std;

#ifdef DEBUG

    #define ERR(SRC, MSG) \
        cerr << "[" << SRC << "] Error: " << MSG << " (In " << basename(__FILE__) << " on line " << __LINE__ << ")" << endl;

    #define INF(SRC, MSG) \
        cout << "[" << SRC << "] Info: " << MSG << " (In " << basename(__FILE__) << " on line " << __LINE__ << ")" << endl;

#else

    #define ERR(SRC, MSG)
    #define INF(SRC, MSG)

#endif

inline void noop ( void ) { }
void die  ( int errorLevel = 0 );
void pause( void );

template <typename T>
bool isType( const void* object ) { return ( const T* convert = dynamic_cast<const T*>(object) ); }

template <typename Value>
bool arrayContains(unsigned int size, const Value list[], const Value& element)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if (list[i] == element)
            return true;
    }

    return false;
}

template <typename Value>
int arrayIndexOf(unsigned int size, const Value list[], const Value& element)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if (list[i] == element)
            return i;
    }

    return -1;
}

#endif 