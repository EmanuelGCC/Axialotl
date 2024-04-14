//==========================================//
//  This file has declares various          //
//  functions to use with AxiaWindow,       //
//  which is a struct representing          //
//  an OS window, and is used a a possible  //
//  render target for AxiaRenderer          //
//==========================================//
// See src/render/render.h &     //
// see src/window/input/input.h  //
//===============================//

#pragma once

#include "input/input.h"
#include "../render/render.h"

//===================================//
//  See window.c for the definition  //
//===================================//
typedef struct AxiaWindow_t AxiaWindow_t;
typedef AxiaWindow_t* AxiaWindow;

//////////////////////////////////
//  This enum Holds the posssible
//  options that can be passed to
//  axiaCreateWindow
typedef enum {
	AXIA_WIN_RESIZEABLE = 0x1,
	AXIA_WIN_DECORATED  = 0x2,
	AXIA_WIN_VISIBLE    = 0x4,
	AXIA_WIN_NO_SHADER  = 0x80,

	AXIA_WIN_DEFAULT    = 0x7F,
} AxiaWinOps;

	//=========================//
	//  Functions that take a  //
	//  AxiaWindow pointer     //
	//=========================//

AxiaWindow axiaCreateWindow(
		int32_t width, int32_t height, 
		const char *title, AxiaShaderProgram *program, 
		AxiaWinOps options);

void axiaDestroyWindow(AxiaWindow *win);

void axiaMakeWinCurrent(AxiaWindow win);

bool axiaIsWinOpen(AxiaWindow win);

void axiaDisplay(AxiaWindow win);

void axiaUseWinFramebuffer(AxiaWindow win);

void axiaUseWinView(AxiaWindow win);

AxiaView axiaGetWinView(AxiaWindow win);

void axiaUseWinShaderProgram(AxiaWindow win);

		//=========================//
		//  Non-Crucial functions  //
		//=========================//

AxiaSize axiaGetWinSize(AxiaWindow win);

void axiaSetWinSize(AxiaWindow win, AxiaSize new_size);

void axiaMaximizeWin(AxiaWindow win);

void axiaMinimizeWin(AxiaWindow win);

void axiaRestoreWin(AxiaWindow win);

AxiaScreenPos axiaGetWinPos(AxiaWindow win);

void axiaSetWinPos(AxiaWindow win, AxiaScreenPos new_pos);

void axiaSetWinTitle(AxiaWindow win, const char *title);

const char *axiaGetWinTite(AxiaWindow win);

void axiaSetWinCursor(AxiaWindow win, bool created);

	//=====================================//
	//  See input.h for the definition of  //
	//  the various enums relating to      //
	//  input handling                     //
	//=====================================//

		//===========================//
		//  Input-related functions  //
		//===========================//

void axiaPollEvents(void);

	//====================================//
	//  See drawables.c for the           //
	//  definition of these functions.    //
	//                                    //
	//  The reason they are not defined   //
	//  in window.c is because the image  //
	//  processing is exclusive for       //
	//  drawables, and for the sake of    //
	//  not overly complicating things,   //
	//  they are defined there            //
	//====================================//

AxiaError axiaSetWinIcon(struct AxiaWindow_t *win, const char* img_path);

AxiaError axiaMakeWinCursor(struct AxiaWindow_t *win, const char* img_path, 
		                    int32_t xhot_spot, int32_t yhot_spot);

	//=============================//
	//  Functions that don't       //
	//  take a AxiaWindow pointer  //
	//=============================//

void axiaClear(void);

void axiaClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void axiaClearColorFloat(float r, float g, float b, float a);
