//=======================================//
//  This file contains the declaration   //
//  of the AxiaView structure, which is  //
//  used to represent the matrices       //
//  that are related to how an entire    //
//  view of a window looks like,         //
//  and AxiaFramebuffer, which is used   // 
//  to represent a framebuffer that      //
//  is a valid render target.            //
//                                       //
//  It also contains the declaration of  //
//  Axialotl's draw functions            //
//=======================================//

#pragma once

#include "shaders/shaders.h"
#include "../drawables/geometry.h"

//================================//
//  See render.c for definitions  //
//================================//

typedef struct AxiaView_t AxiaView_t;
typedef AxiaView_t* AxiaView;

typedef struct AxiaFramebuffer_t AxiaFramebuffer_t;
typedef AxiaFramebuffer_t* AxiaFramebuffer;

//=================================//
//  See objects/texture/texture.c  //
//  for definition of the type     //
//=================================//

	//======================//
	//  AxiaView functions  //
	//======================//

AxiaView axiaCreateView(
		const AxiaSize target_size, const AxiaVec3 cam_pos,
		const AxiaVec3 target,      const AxiaVec3 up);

void axiaDestroyView(AxiaView *view);

void axiaChangeViewTargetSize(AxiaView, const AxiaSize new_size);

void axiaChangeViewLookAt(AxiaView, const AxiaVec3 cam_pos, 
                          const AxiaVec3 target, const AxiaVec3 up);

void axiaUpdateView(AxiaView);

void axiaUseView(const AxiaView);

	//=============================//
	//  AxiaFramebuffer functions  //
	//=============================//

AxiaFramebuffer axiaCreateFramebuffer(const AxiaSize size);

void axiaDestroyFramebuffer(AxiaFramebuffer *framebuffer);

void axiaBindFramebufferTexture(AxiaFramebuffer, AxiaTexture);

void axiaUseFramebuffer(AxiaFramebuffer framebuffer);

	//==============================//
	//  Object rendering functions  //
	//==============================//

void axiaDrawShape(AxiaShape);

void axiaDrawIndexedShape(AxiaShape);
