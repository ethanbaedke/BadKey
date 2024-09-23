#pragma once

#ifdef BK_BUILD_DLL
	#define BK_API __declspec(dllexport)
#else
	#define BK_API __declspec(dllimport)
#endif