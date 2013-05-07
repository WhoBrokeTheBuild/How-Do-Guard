#pragma once

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define DEBUG

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#define WINDOWS

#else

#define LINUX

#endif

#endif