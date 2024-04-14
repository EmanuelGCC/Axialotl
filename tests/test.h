#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static char fail[]    = "\033[91m"; 
static char success[] = "\033[92m";
static char end[]     = "\033[0m";

#define printa(assertion) (\
		printf("\n\t%s "#assertion"%s\n",\
		   	(assertion)? success : fail, end))

#define printe2(v) (printf("{ %f, %f }\n", v.x, v.y))

#define printe3(v) (printf("{ %f, %f, %f }\n", v.x, v.y, v.z))

#define printe4(v) (printf("{ %f, %f, %f, %f }\n", v.x, v.y, v.z, v.w))


