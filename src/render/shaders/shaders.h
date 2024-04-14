//==========================================//
//  This file contains the declaration      //
//  of AxiaShader and AxiaShaderProgram,    //
//  as well as functions relating to them.  //
//                                          //
//  These structs are used as a             //
//  representation of GLSL shaders, and     //
//  GL's shader programs.                   //
//==========================================//

#pragma once

#include "../../dependencies/deps.h"

///////////////////////////////////
// These two are just 1 u32 each,
// so they are just const so that
// the user cannot modify them
// and shoot themselves in the foot
typedef const uint32_t AxiaShaderProgram;
typedef const uint32_t AxiaShader;

typedef enum {
	AXIA_VERTEX_SHADER   = GL_VERTEX_SHADER,
	AXIA_FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
	AXIA_GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
} AxiaShaderType;

#define AXIA_INVALID_SHADER 0xFFFFFFFF
#define AXIA_INVALID_SHADER_PROGRAM 0xFFFFFFFF

//=================================//
//  See shaders.c for definitions  //
//=================================//

AxiaShader axiaCreateShader(const char *code, GLenum shader_type);

void axiaDestroyShader(AxiaShader *shader);

AxiaShaderProgram axiaCreateShaderProgram();

void axiaDestroyShaderProgram(AxiaShaderProgram *program);

void axiaAttachShader(AxiaShaderProgram program, AxiaShader shader);

AxiaError axiaLinkProgram(AxiaShaderProgram program);

void axiaUseShaderProgram(AxiaShaderProgram program);
