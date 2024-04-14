//===================================//
//  This file has the definition     //
//  of the opaque structs, and       //
//  this file is only included       //
//  by the *.c files. The reason     //
//  for this file to exist is for    //
//  different *.c to be able to      //
//  access the same structs without  //
//  giving up the opaqueness for     //
//  the user                         //
//===================================//

#pragma once

#include "dependencies/deps.h"

//==========//
//  Render  //
//==========//

//////////////////////////////////
// Struct holding the uniforms
// passed to the default shaders.
// 
// combined is the result of 
//    perspective * view
// and is the one that is actually
// passed to the shaders
struct AxiaView_t
{
	AxiaMat combined;
	AxiaMat view;
	AxiaMat projection;
};

struct AxiaFramebuffer_t 
{
	uint32_t framebuffer;
	uint32_t renderbuffer;
	AxiaSize size;
};

//==========//
//  Window  //
//==========//

struct AxiaWindow_t {
	GLFWwindow *win;
	GLFWcursor *cursor;
	const char *title;
	AxiaSize    size;

	uint32_t    shader;
	struct AxiaView_t  view;

	//  Input related  //
	AxiaMousePos mouse;
	uint32_t     last_button;
	void        *utf_buffer;
	uint32_t     utf_size;
	uint32_t     utf_index;
};

//=============//
//  Drawables  //
//=============//

struct AxiaShape_t
{
	uint32_t vertex_buffer;
	uint32_t vertex_array;
	uint32_t element_buffer;
	uint32_t texture;
	AxiaMat  model;

	uint32_t vertex_count;
	uint32_t index_count;
	GLenum   draw_mode;
	GLenum   index_type;
};

