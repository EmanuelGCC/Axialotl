//==================================//
//  This file contains the AxiaMat  //
//  type, and various functions     //
//  relating to it.                 //
//                                  //
//  AxiaMat is supposed to be a     //
//  representation of OpenGl's      //
//  4x4 matrices.                   //
//==================================//

#pragma once
#include "vector.h"

typedef float  AxiaMat[16];
typedef float* AxiaMatPtr;

#define axiaToRad(x)    ( x * M_PI / 180.f )
#define axiaToDegree(x) ( x * 180.f / M_PI )

	//=========================//
	//  Initialization macros  //
	//=========================//

#define axiaDefaultMat {\
	1,0,0,0,\
	0,1,0,0,\
	0,0,1,0,\
	0,0,0,1 \
}

#define axiaZeroMat {\
	0,0,0,0,\
	0,0,0,0,\
	0,0,0,0,\
	0,0,0,0 \
}

	//==============================//
	//  "Initialization" functions  //
	//==============================//

void axiaMakeMatDefault(AxiaMat);

void axiaMakeMatZero(AxiaMat);

void axiaCopyMat(AxiaMat dest, const AxiaMat src);

	//===============//
	//  Actual math  //
	//===============//

void axiaMatXMat(AxiaMat dest, const AxiaMat left, const AxiaMat right);

void axiaRotationMatX(AxiaMat dest, float angle_rad);

void axiaRotationMatY(AxiaMat dest, float angle_rad);

void axiaRotationMatZ(AxiaMat dest, float angle_rad);

/////////////////////////////////////////////////////////
///  This function creates a projection matrix.
///  It assumes that dest was initialized with zeros,
///  and only this function changed dest. The reason
///  for this assumption in to avoid zero-initializing
///  a bunch of addresses that are already zero whenever
///  the window is resized.
void axiaProjectionMat(AxiaMat dest, const float aspect_ratio, 
                        const float fov, const float near, const float far);

void axiaLookAt(AxiaMat dest, const AxiaVec3 cam_pos, 
                const AxiaVec3 target, const AxiaVec3 up);
