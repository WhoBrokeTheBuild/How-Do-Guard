#pragma once

#ifndef __INPUT_FUNC_H__
#define __INPUT_FUNC_H__

#include "Keyboard.h"
#include "Mouse.h"
#include <SDL.h>

KeyboardKey SDLKeyToKey( SDLKey sdlKey );

SDLKey KeyToSDLKey( KeyboardKey key );

char KeyToChar( KeyboardKey key, bool shift = false );

MouseButton SDLMouseToMouse( int sdlButton );

int MouseToSDLMouse( MouseButton button );

#endif