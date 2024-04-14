//=====================================//
//  This file contains the definition  //
//  of the 2, 3, and 4 dimensional     //
//  vectors, and various functions     //
//  used for them.                     //
//                                     //
//  These vectors are supposed         //
//  to be a representation of GLSL's   //
//  vec2, vec3, and vec4               //
//=====================================//

#pragma once
#include <math.h>

typedef struct {
	float x, y;
} AxiaVec2;

typedef struct {
	float x, y, z;
} AxiaVec3;

typedef struct {
	float x, y, z, w;
} AxiaVec4;

	//================================//
	//  Quick vector creation macros  //
	//================================//

#define axiaVec2(x, y)       (AxiaVec2){ x, y }
#define axiaVec3(x, y, z)    (AxiaVec3){ x, y, z }
#define axiaVec4(x, y, z, w) (AxiaVec4){ x, y, z, w }

	//==================================//
	//  Function for calculating the    //
	//  cross product between two Vec3  //
	//==================================//

AxiaVec3 axiaCross(const AxiaVec3 left, const AxiaVec3 right);

	//===================================//
	//  Functions for calculating the    //
	//  dot product between the vectors  //
	//===================================//

float axiaDot2(const AxiaVec2 left, const AxiaVec2 right);

float axiaDot3(const AxiaVec3 left, const AxiaVec3 right);

float axiaDot4(const AxiaVec4 left, const AxiaVec4 right);

	//======================================//
	//  Functions for normalizing a vector  //
	//======================================//

AxiaVec2 axiaNormalize2(const AxiaVec2);

AxiaVec3 axiaNormalize3(const AxiaVec3);

AxiaVec4 axiaNormalize4(const AxiaVec4);

