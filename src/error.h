#pragma once

typedef enum {
	AXIA_OK                 = 0x0,
	AXIA_ALREADY_INIT       = 0x0,
	AXIA_FAILED_MALLOC      = 0x1,
	AXIA_GLFW_ERROR         = 0x2,
	AXIA_GL_ERROR           = 0x3,
	AXIA_INVALID_ARG        = 0x4,
	AXIA_FAILED_TO_INIT     = 0x5,
	AXIA_GLEW_ERROR         = 0x6,
	AXIA_LODING_FAILED      = 0x7,
	AXIA_INVALID_CONDITIONS = 0x8,
	AXIA_INVALID_ENUM       = 0x9,
	AXIA_OUT_OF_BOUNDS      = 0xA,
} AxiaError;

#ifdef AXIA_DEBUG
#define axiaprintdbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define axiaprintdbg(...) {}
#endif

/////////////////////////////////////////////////
// This macro is used specifically to check
// for errors in the arguments passed to a function
#ifndef AXIA_NO_ARG_CHECKING
#define axiacheckarg(condition, ret, ...) \
	if(condition) {\
		axiaprintdbg(__VA_ARGS__); \
		return ret;    \
	}
#else
#define axiacheckarg(...) {}
#endif
