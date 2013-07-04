#pragma once

#ifndef __STRING_FUNC_H__
#define __STRING_FUNC_H__

#include <string>

using namespace std;

template <class T>
class ArrayList;

ArrayList<string> strSplit     ( string str, char sep, int limit = -1 );
string            strReplace   ( string str, const string& sub, const string& newStr );
string            strReplaceAll( string str, const string& sub, const string& newStr );
string            strSubstring ( string str, unsigned int begin, int maxLength = -1 );
bool              strContains  ( string str, string sub );

string basename( string fullPath );

template <class Number>
string numToString( const Number& value )
{
    stringstream ss;
    ss << value;
    return ss.str();
}

#endif