//================================//
//  This file contains the        //
//  declaration of the init       //
//  function, and is the file     //
//  that should be included when  //
//  using the library. It also    //
//  give access to the library's  //
//  static variables.             //
//================================//

#pragma once

#include "../window/window.h"
#include "../drawables/geometry.h"

	//===========//
	//  Statics  //
	//===========//

////////////////////////////////////
// These two aren't included here
// because they are needed by 
// window.c; See deps.h for 
// declaration
//
//extern uint32_t AXIA_VERSION_MAJOR;
//extern uint32_t AXIA_VERSION_MINOR;


	//========================//
	//  Functions and macros  //
	//========================//

AxiaError axiaInitializeFunction(uint32_t version_major, uint32_t version_minor);

#define axiaInit() axiaInitializeFunction(GL_VERSION_MAJOR, GL_VERSION_MINOR)

void axiaDeinit();
