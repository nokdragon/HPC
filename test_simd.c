#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "simd1.h"

void test_if_else()
{	

	vuint32 a, b, x, y, res;
	b = init_vuint32(5);
	x = init_vuint32(7);
	y = init_vuint32(8);

	printf("====TEST a < b ====\n");
	a = init_vuint32(4);
	display_vuint32(a, "%4.0d", "a"); puts("\n");
	display_vuint32(b, "%4.0d", "b"); puts("\n");
	display_vuint32(x, "%4.0d", "x"); puts("\n");
	display_vuint32(y, "%4.0d", "y"); puts("\n");
	printf("if a >= b return x, else return y\n");
	res = if_else(a,b,x,y);
	display_vuint32(res, "%4.0d", "res"); puts("");
	printf("a < b donc on retourne y\n\n");

	printf("====TEST a == b ====\n");
	a = init_vuint32(5);
	display_vuint32(a, "%4.0d", "a"); puts("\n");
	display_vuint32(b, "%4.0d", "b"); puts("\n");
	display_vuint32(x, "%4.0d", "x"); puts("\n");
	display_vuint32(y, "%4.0d", "y"); puts("\n");
	printf("if a >= b return x, else return y\n");
	res = if_else(a,b,x,y);
	display_vuint32(res, "%4.0d", "res"); puts("");
	printf("a == b donc on retourne x\n\n");

	printf("====TEST a > b ====\n");
	a = init_vuint32(6);
	display_vuint32(a, "%4.0d", "a"); puts("\n");
	display_vuint32(b, "%4.0d", "b"); puts("\n");
	display_vuint32(x, "%4.0d", "x"); puts("\n");
	display_vuint32(y, "%4.0d", "y"); puts("\n");
	printf("if a >= b return x, else return y\n");
	res = if_else(a,b,x,y);
	display_vuint32(res, "%4.0d", "res"); puts("");
	printf("a > b donc on retourne x\n\n");
}

