#pragma once

#ifndef _SHAREDLIB_H
#define _SHAREDLIB_H

#if defined(_CMAKE_)
	#include <config.h>
#endif
#include <iostream>

#if (defined(WIN32) || defined(_WIN32)) &&  defined(LIB_BUILD_DLL)
#define LIBAPI __declspec(dllexport)
#elif defined(__GNUC__) && defined(LIB_BUILD_DLL) && defined(LIB_DLL)
#define LIBAPI __attribute__((visibility("default")))
#elif (defined(WIN32) || defined(_WIN32)) && defined(LIB_DLL) && !defined(LIB_BUILD_DLL)
#define LIBAPI __declspec(dllimport)
#else
#define LIBAPI //Static library
#endif // 

LIBAPI void hello();

#endif // !_SHAREDLIB_H
