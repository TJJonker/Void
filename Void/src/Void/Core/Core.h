#pragma once
#include "Void/Debug/Log.h"

/// DLL and Platform specific settings.
#ifdef VOID_PLATFORM_WINDOWS
	//#ifdef VOID_BUILD_DLL
	//	#define VOID_API __declspec(dllexport)
	//#else
	//	#define VOID_API __declspec(dllimport)
	//#endif
#define VOID_API
#else
	#error Void only supports windows!
#endif

/// Assertion defines.
#ifdef VOID_ASSERT_ENABLED
	#define VOID_CORE_ASSERT(x, ...) { if(!(x)) { VOID_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define VOID_ASSERT(x, ...) { if(!(x)) { VOID_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define VOID_CORE_ASSERT(x, ...) 
	#define VOID_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x)