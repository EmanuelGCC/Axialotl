//=====================================//
//  This file contains the definition  //
//  of various math related functions  //
//  declared in other files in this    //
//  folder                             //
//=====================================//

#ifdef AXIA_DEBUG
  #include <stdio.h>
#endif
#include "matrix.h"
//       └─  vector.h

	//======================//
	//  vector.h functions  //
	//======================//

AxiaVec3 axiaCross(const AxiaVec3 left, const AxiaVec3 right)
{
	return (AxiaVec3){
		left.y*right.z - left.z*right.y,
		left.z*right.x - left.x*right.z,
		left.x*right.y - left.y*right.x
	};
}


float axiaDot2(const AxiaVec2 left, const AxiaVec2 right)
{
	return
		left.x * right.x +
		left.y * right.y;
}

float axiaDot3(const AxiaVec3 left, const AxiaVec3 right)
{
	return
		left.x * right.x +
		left.y * right.y +
		left.z * right.z;
}

float axiaDot4(const AxiaVec4 left, const AxiaVec4 right)
{
	return
		left.x * right.x +
		left.y * right.y +
		left.z * right.z +
		left.w * right.w;
}


#define square(x) (x * x)
AxiaVec2 axiaNormalize2(const AxiaVec2 v)
{
	float magnitude = 
		sqrtf(square(v.x) + square(v.y));

	return (AxiaVec2){
		v.x / magnitude,
		v.y / magnitude
	};
}

AxiaVec3 axiaNormalize3(const AxiaVec3 v)
{
	float magnitude = 
		sqrtf(square(v.x) + square(v.y) + square(v.z));

	return (AxiaVec3){
		v.x / magnitude,
		v.y / magnitude,
		v.z / magnitude
	};
}

AxiaVec4 axiaNormalize4(const AxiaVec4 v)
{
	float magnitude = 
		sqrtf(square(v.x) + square(v.y) + 
		      square(v.z) + square(v.w));

	return (AxiaVec4){
		v.x / magnitude,
		v.y / magnitude,
		v.z / magnitude,
		v.w / magnitude
	};
}
#undef square


	//======================//
	//  matrix.h functions  //
	//======================//

void axiaMakeMatDefault(AxiaMat mat)
{
	mat[0x0] = 1;
	mat[0x5] = 1;
	mat[0xA] = 1;
	mat[0xF] = 1;

	mat[0x1] = 0;
	mat[0x2] = 0;
	mat[0x3] = 0;
	mat[0x4] = 0;

	mat[0x6] = 0;
	mat[0x7] = 0;
	mat[0x8] = 0;
	mat[0x9] = 0;

	mat[0xB] = 0;
	mat[0xC] = 0;
	mat[0xD] = 0;
	mat[0xE] = 0;
}

void axiaMakeMatZero(AxiaMat mat) 
{
	mat[0x0] = 0;
	mat[0x5] = 0;
	mat[0xA] = 0;
	mat[0xF] = 0;

	mat[0x1] = 0;
	mat[0x2] = 0;
	mat[0x3] = 0;
	mat[0x4] = 0;

	mat[0x6] = 0;
	mat[0x7] = 0;
	mat[0x8] = 0;
	mat[0x9] = 0;

	mat[0xB] = 0;
	mat[0xC] = 0;
	mat[0xD] = 0;
	mat[0xE] = 0;
}

void axiaCopyMat(AxiaMat dest, const AxiaMat src)
{
	dest[0x0] = src[0x0];
	dest[0x1] = src[0x1];
	dest[0x2] = src[0x2];
	dest[0x3] = src[0x3];

	dest[0x4] = src[0x4];
	dest[0x5] = src[0x5];
	dest[0x6] = src[0x6];
	dest[0x7] = src[0x7];

	dest[0x8] = src[0x8];
	dest[0x9] = src[0x9];
	dest[0xA] = src[0xA];
	dest[0xB] = src[0xB];

	dest[0xC] = src[0xC];
	dest[0xD] = src[0xD];
	dest[0xE] = src[0xE];
	dest[0xF] = src[0xF];
}

void axiaRotationMatX(AxiaMat dest, float angle)
{
	const float cos_a = cosf(angle);
	const float sin_a = sinf(angle);

	dest[0x5] = cos_a;
	dest[0x9] =-sin_a;
	dest[0x6] = sin_a;
	dest[0xA] = cos_a;
}

void axiaRotationMatY(AxiaMat dest, float angle)
{
	const float cos_a = cosf(angle);
	const float sin_a = sinf(angle);

	dest[0x0] = cos_a;
	dest[0x2] = sin_a;
	dest[0x8] =-sin_a;
	dest[0xA] = cos_a;
}

void axiaRotationMatZ(AxiaMat dest, float angle)
{
	const float cos_a = cosf(angle);
	const float sin_a = sinf(angle);

	dest[0x0] = cos_a;
	dest[0x1] =-sin_a;
	dest[0x4] = sin_a;
	dest[0x5] = cos_a;
}

void axiaMatXMat(AxiaMat dest, const AxiaMat left, const AxiaMat right)
{
#define mult(i,o) \
	left[0+4*i]*right[o+0] + \
	left[1+4*i]*right[o+4] + \
	left[2+4*i]*right[o+8] + \
	left[3+4*i]*right[o+12]

	dest[0x0] = mult(0,0);
	dest[0x1] = mult(0,1);
	dest[0x2] = mult(0,2);
	dest[0x3] = mult(0,3);

	dest[0x4] = mult(1,0);
	dest[0x5] = mult(1,1);
	dest[0x6] = mult(1,2);
	dest[0x7] = mult(1,3);

	dest[0x8] = mult(2,0);
	dest[0x9] = mult(2,1);
	dest[0xA] = mult(2,2);
	dest[0xB] = mult(2,3);

	dest[0xC] = mult(3,0);
	dest[0xD] = mult(3,1);
	dest[0xE] = mult(3,2);
	dest[0xF] = mult(3,3);

#undef mult
}

void axiaProjectionMat(AxiaMat dest, const float aspect_ratio, 
                        const float fov, const float near, const float far)
{
#ifdef AXIA_DEBUG
	//  This function assumes a AxiaMat initialized with zero,
	//  and so, for the sake of debugging, this is inserted
	//  to alert when a call to this function is done and the
	//  AxiaMat was not zero-initialized.

	for(int i=0;i<16;++i) {
		if(dest[i] != 0) {
			printf("Perspective[%i] != 0 ; it's equal to: %f\n", i, dest[i]);
		}
	}
#endif
	float tan_half_fov = 1 / tanf(fov / 2);

	//  Asign all the non-zero
	dest[0x0] = tan_half_fov / aspect_ratio;
	dest[0x5] = tan_half_fov;
	dest[0xA] = (near + far) / (near - far);
	dest[0xB] = -1;
	dest[0xE] = 2*near*far / (near - far);
}

void axiaLookAt(AxiaMat dest, const AxiaVec3 cam, const AxiaVec3 tar, const AxiaVec3 up)
{
	AxiaVec3 forward = 
		axiaNormalize3((AxiaVec3){ cam.x-tar.x, cam.y-tar.y, cam.z-tar.z });

	AxiaVec3 left = axiaNormalize3(axiaCross(up, forward));
	AxiaVec3 up_vec = axiaCross(forward, left);

	dest[0x0] = left.x;
	dest[0x4] = left.y;
	dest[0x8] = left.z;
	dest[0xC] = -left.x*cam.x - left.y*cam.y - left.z*cam.z;
	
	dest[0x1] = up_vec.x;
	dest[0x5] = up_vec.y;
	dest[0x9] = up_vec.z;
	dest[0xD] = -up_vec.x*cam.x - up_vec.y*cam.y - up_vec.z*cam.z;

	dest[0x2] = forward.x;
	dest[0x6] = forward.y;
	dest[0xA] = forward.z;
	dest[0xE] = -forward.x*cam.x - forward.y*cam.y - forward.z*cam.z;

	dest[0x3] = 0;
	dest[0x7] = 0;
	dest[0xB] = 0;
	dest[0xF] = 1;
}

