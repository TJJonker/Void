#pragma once

#ifdef VOID_PLATFORM_WINDOWS
	#ifdef VOID_BUILD_DLL
		#define VOID_API __declspec(dllexport)
	#else
		#define VOID_API __declspec(dllimport)
	#endif
#else
	#error Void only supports windows!
#endif

#define BIT(x) (1 << x)