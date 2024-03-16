#pragma once

#ifdef RY_PLATFORM_WINDOWS
	#ifdef RY_BUILD_DLL
		#define RIYAL_API __declspec(dllexport)
	#else
		#define RIYAL_API __declspec(dllimport)
	#endif
#else
	#error Riyal only supports Windows!
#endif