//==========================================//
//  This file contains the declaration      //
//  of the AxiaShape and AxiaIndexedShape,  //
//  which are used to represent any shape.  //
//                                          //
//  To allow the user to not have to        //
//  manually define each geometric shape,   //
//  axia includes a cuple of functions      //
//  for the creation of specific shapes     //
//  (like rectangles) , whilst still        //
//  allowing custom shapes                  //
//==========================================//

#pragma once

#include "texture.h"

//===================================//
//  See drawables.c for definitions  //
//===================================//

typedef struct AxiaShape_t AxiaShape_t;
typedef AxiaShape_t* AxiaShape;

typedef struct AxiaIndexedShape_t AxiaIndexedShape_t;
typedef AxiaIndexedShape_t* AxiaIndexedShape;

typedef enum {
	AXIA_DRAW_TRIANGLES      = GL_TRIANGLES,
	AXIA_DRAW_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	AXIA_DRAW_TRIANGLE_FAN   = GL_TRIANGLE_FAN,
	AXIA_DRAW_LINES          = GL_LINES,
	AXIA_DRAW_POINTS         = GL_POINTS,
} AxiaShapeDrawMode;

AxiaShape axiaCreateShape(AxiaShapeDrawMode draw_mode);

void axiaChangeShapeDrawmode(GLenum draw_mode);

void axiaDestroyShape(AxiaShape *shape);

void axiaPopulateShape(AxiaShape shape, const float *data, 
                       uint32_t float_count, 
                       uint32_t vertex_count, 
                       uint32_t texcoor_start, 
                       size_t   texture_stride);

typedef enum {
	AXIA_INDEX_BYTE  = GL_UNSIGNED_BYTE,
	AXIA_INDEX_SHORT = GL_UNSIGNED_SHORT,
	AXIA_INDEX_INT   = GL_UNSIGNED_INT,
} AxiaIndexType;

AxiaError axiaShapeIndices(AxiaShape shape, const void *indices,
                      uint32_t index_count,
                      AxiaIndexType index_type);

AxiaMatPtr axiaGetShapeMatrix(AxiaShape shape);

void axiaBindShapeTexture(AxiaShape, AxiaTexture);

	//=======================//
	//  Specific shape       //
	//  functions and enums  //
	//=======================//
	
		//=============//
		//  Rectangle  //
		//=============//
		
AxiaShape axiaCreateRectangle(AxiaVec2 size, AxiaVec3 pos);

typedef enum {
	AXIA_RECT_X      = 0xC,
	AXIA_RECT_Y      = 0xD,
	AXIA_RECT_Z      = 0xE,
	AXIA_RECT_WIDTH  = 0x0,
	AXIA_RECT_HEIGHT = 0x5,
} AxiaRectDataNames;

	//========//
	//  Cube  //
	//========//
	
AxiaShape axiaCreateCube(AxiaVec3 size, AxiaVec3 pos);

typedef enum {
	AXIA_CUBE_X      = 0xC,
	AXIA_CUBE_Y      = 0xD,
	AXIA_CUBE_Z      = 0xE,
	AXIA_CUBE_WIDTH  = 0x0,
	AXIA_CUBE_HEIGHT = 0x5,
	AXIA_CUBE_DEPTH  = 0xA,
} AxiaCubeDataNames;

	//============//
	//  Triangle  //
	//============//
	
AxiaShape axiaCreateTriangle(AxiaVec3 pos, AxiaVec3 vert1, AxiaVec3 vert2);

typedef enum {
	AXIA_TRIA_X = 0xC,
	AXIA_TRIA_Y = 0xD,
	AXIA_TRIA_Z = 0xE,

	AXIA_TRIA_VERT1_X = 0x0,
	AXIA_TRIA_VERT1_Y = 0x1,
	AXIA_TRIA_VERT1_Z = 0x2,

	AXIA_TRIA_VERT2_X = 0x4,
	AXIA_TRIA_VERT2_Y = 0x5,
	AXIA_TRIA_VERT2_Z = 0x6,
} AxiaTriangleDataNames;

	//===============//
	//  Tetrahedron  //
	//===============//
	
AxiaShape axiaCreateTetrahedron(AxiaVec3 pos, AxiaVec3 vert1, 
                                AxiaVec3 vert2, AxiaVec3 vert3);

typedef enum {
	AXIA_TETRA_X = 0xC,
	AXIA_TETRA_Y = 0xD,
	AXIA_TETRA_Z = 0xE,

	AXIA_TETRA_VERT1_X = 0x0,
	AXIA_TETRA_VERT1_Y = 0x1,
	AXIA_TETRA_VERT1_Z = 0x2,

	AXIA_TETRA_VERT2_X = 0x4,
	AXIA_TETRA_VERT2_Y = 0x5,
	AXIA_TETRA_VERT2_Z = 0x6,

	AXIA_TETRA_VERT3_X = 0x8,
	AXIA_TETRA_VERT3_Y = 0x9,
	AXIA_TETRA_VERT3_Z = 0xA,
} AxiaTetrahedronDataNames;

	//==========//
	//  Circle  //
	//==========//
	
AxiaShape axiaCreateCircle(AxiaVec3 pos, float radious, uint8_t complexity);

typedef enum {
	AXIA_CIRCLE_X       = 0xC,
	AXIA_CIRCLE_Y       = 0xD,
	AXIA_CIRCLE_Z       = 0xE,
	AXIA_CIRCLE_SCALE_X = 0x0,
	AXIA_CIRCLE_SCALE_Y = 0x5,
} AxiaCircleDataNames;

	//==========//
	//  Sphere  //
	//==========//

AxiaShape axiaCreateSphere(AxiaVec3 pos, float radious, 
                           uint8_t h_complexity, uint8_t v_complexity);

typedef enum {
	AXIA_SPHERE_X = 0xC,
	AXIA_SPHERE_Y = 0xD,
	AXIA_SPHERE_Z = 0xE,
	
	AXIA_SPHERE_SCALE_X = 0x0,
	AXIA_SPHERE_SCALE_Y = 0x5,
	AXIA_SPHERE_SCALE_Z = 0xA,
} AxiaSphereDataNames;
