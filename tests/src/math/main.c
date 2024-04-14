#include "../../../src/math/matrix.h"
#include "../../test.h"

bool eq2(const AxiaVec2 a, const AxiaVec2 b) {
	return a.x == b.x && a.y == b.y;
}

bool eq3(const AxiaVec3 a, const AxiaVec3 b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool eq4(const AxiaVec4 a, const AxiaVec4 b) {
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

int main()
{
	AxiaVec2 v1 = { 1, 2 };
	AxiaVec3 v2 = { 0.3, 66, 83.45 };
	AxiaVec3 v2_5 = { 0.5, 30, 223 };
	AxiaVec4 v3 = { 20, 20, 20, 20 };

	printa(eq2(axiaNormalize2(v1), ((AxiaVec2){1.f/sqrtf(5), 2.f/sqrtf(5)})));

	printa(eq3(axiaNormalize3(v2), ((AxiaVec3){ 0.002820f, 0.620327f, 0.784338f })));

	printa(eq4(axiaNormalize4(v3), ((AxiaVec4){ 0.5f, 0.5f, 0.5f, 0.5f })));

	printf("\tDot product result : %f\n", axiaDot3(v2, v2_5));

	/////////////////
	
	printf("\n");
	printf("Expected:\n\t");
	printe3(((AxiaVec3){ 12214.5f, -25.175f, -24.f }));
	printf("Found:\n\t");
	printe3(axiaCross(v2, v2_5));
	printf("\n");

	/////////////////
	
	AxiaMat m1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	AxiaMat m2 = { 3, 4, 5, 1, 2, 6, 9, 10, 11, 16, 8, 7, 15, 14, 13, 12 };
	AxiaMat res;

	axiaMatXMat(res, m1, m2);
	for(int i=0;i<4;++i) {
		for(int o=0;o<4;++o)
			printf("%f ", res[i*4+o]);
		printf("\n");
	}

	////////////////
	
	AxiaMat viewMat;
	axiaLookAt(viewMat, (AxiaVec3){ -0.9, 0, 0.1 }, (AxiaVec3){ 0, 2, 0 }, (AxiaVec3){ 0, 1, 0 });

	printf("\n");

	for(int i=0;i<4;++i) {
		for(int o=0;o<4;++o)
			printf("%f ", viewMat[i*4+o]);
		printf("\n");
	}

	return 0;
}
