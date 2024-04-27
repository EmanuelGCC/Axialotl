//=========================================//
//  This file includes the various         //
//  .h files that the rest of              //
//  Axialotl needs, and is therefore       //
//  included in quite a few files.         //
//  The reason this is not done            //
//  directly in each file is to            //
//  avoid possibly including the           //
//  same library twice or more             //
//  (and also is less includes per file)   //
//=========================================//

#pragma once

#ifndef GL_VERSION_MAJOR
#define GL_VERSION_MAJOR 3
#endif
#ifndef GL_VERSION_MINOR
#define GL_VERSION_MINOR 3
#endif

//===================================//
//  The include path may be changed  //
//  with the corresponding macro     //
//===================================//

#ifndef GLEW_PATH
#define GLEW_PATH <GL/glew.h>
#endif

#ifndef GLFW_PATH
#define GLFW_PATH <GLFW/glfw3.h>
#endif

#ifndef GL_PATH
#define GL_PATH <GL/gl.h>
#endif

#include GLEW_PATH
#include GLFW_PATH
#include GL_PATH

#ifndef STB_IMAGE_PATH
#define STB_IMAGE_PATH "stb_image.h"
#endif

#ifndef FT_BUILD_PATH
#define FT_BUILD_PATH <ft2build.h>
#endif

#include FT_BUILD_PATH
#include <freetype/freetype.h>
#include FT_FREETYPE_H  

// This is included only in
// drawables.c:
//
// #include STB_IMAGE_PATH

#include <stdbool.h>
#include <malloc.h>
#include "../error.h"
#include "../math/matrix.h"

//=============================//
//  The constants that are     //
//  used throught the library  //
//=============================//

typedef struct { int32_t width, height; } AxiaSize;
typedef struct { int32_t x, y; } AxiaScreenPos;
typedef struct { double  x, y; } AxiaMousePos;
