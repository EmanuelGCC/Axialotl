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

#define axiaCheckAlloc(ptr) if ((ptr) == NULL) { return AXIA_FAILED_MALLOC; }
