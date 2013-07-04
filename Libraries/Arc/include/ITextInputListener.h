#pragma once

#ifndef __ITEXT_INPUT_LISTENER_H__
#define __ITEXT_INPUT_LISTENER_H__

#include "ArcCommon.h"
#include "TextInputSource.h"

class ITextInputListener
{
public:

    ITextInputListener( void ) { }
    virtual ~ITextInputListener( void ) { term(); };

    virtual void init( void )
    {
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_CHAR,      this, &ITextInputListener::textInputChar);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_NEWLINE,   this, &ITextInputListener::textInputNewline);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_BACKSPACE, this, &ITextInputListener::textInputBackspace);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_DELETE,    this, &ITextInputListener::textInputDelete);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_TAB,       this, &ITextInputListener::textInputTab);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_ARROWS,    this, &ITextInputListener::textInputArrows);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_HOME_END,  this, &ITextInputListener::textInputHomeEnd);
    }

    virtual void term( void )
    {
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_HOME_END,  this, &ITextInputListener::textInputHomeEnd);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_ARROWS,    this, &ITextInputListener::textInputArrows);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_TAB,       this, &ITextInputListener::textInputTab);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_DELETE,    this, &ITextInputListener::textInputDelete);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_BACKSPACE, this, &ITextInputListener::textInputBackspace);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_NEWLINE,   this, &ITextInputListener::textInputNewline);
        gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_CHAR,      this, &ITextInputListener::textInputChar);
    }

    virtual void textInputChar      ( const Event& event) { };
    virtual void textInputNewline   ( const Event& event) { };
    virtual void textInputBackspace ( const Event& event) { };
    virtual void textInputDelete    ( const Event& event) { };
    virtual void textInputTab       ( const Event& event) { };
    virtual void textInputArrows    ( const Event& event) { };
    virtual void textInputHomeEnd   ( const Event& event) { };

};

#endif