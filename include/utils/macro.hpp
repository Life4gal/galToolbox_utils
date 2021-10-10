#pragma once

#ifdef _WIN32
#ifdef GALTOOLBOX_NEED_EXPORT
	#define GAL_EXPORT __declspec(dllexport)
#else
	#define GAL_EXPORT __declspec(dllimport)
#endif
#else
	#define GAL_EXPORT
#endif
