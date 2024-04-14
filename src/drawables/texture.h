//========================================//
//  This file contains the declaration    //
//  of AxiaTexture and functions          //
//  relating to it. It is a               //
//  representation of OpenGL's Texture2D  //
//  and it is capable of loading image    //
//  files to create a valid texture.      //
//========================================//
//  The reading capabilities    //
//  of AxiaTexture is thanks    //
//  to The ImageMagick library  //
//==============================//

#pragma once

#include "../dependencies/deps.h"

//==================================//
//  See drawables.c for definition  //
//==================================//

typedef const uint32_t AxiaTexture;

//////////////////////////////////////
//  A change of name of some of
//  OpenGL's constants for the sake
//  of naming consistency
typedef enum {
	AXIA_RGBA = GL_RGBA,
	AXIA_RGB  = GL_RGB,
	AXIA_RG   = GL_RG,
	AXIA_GRAY = GL_RED,
} AxiaTextureFormat;

////////////////////////////////
//  Use this to unbind textures
#define AXIA_NO_TEXTURE 0

//=========================//
//  AxiaTexture functions  //
//=========================//

AxiaTexture axiaCreateTexture();

void axiaDestroyTexture(AxiaTexture *texture);

AxiaError axiaLoadTextureSource(AxiaTexture, AxiaTextureFormat,
		const AxiaSize size, const uint8_t *data, bool bitmapped);

AxiaError axiaLoadFromImage(AxiaTexture, const char *img_path);

void axiaTextureFromColor(AxiaTexture, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

