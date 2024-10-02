#pragma once

#ifdef BK_PLATFORM_WINDOWS
	#ifdef BK_BUILD_DLL
		#define BK_API __declspec(dllexport)
	#else
		#define BK_API __declspec(dllimport)
	#endif
#else
	#error The BadKey engine only supports windows
#endif