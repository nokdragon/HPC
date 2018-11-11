#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "simd1.h"

#define PRINT_BEGIN(msg) printf("\n\n==============================================BEGIN %s==============================================\n", msg);
#define PRINT_END(msg) printf("==============================================END %s==============================================\n\n\n\n", msg);


void test_if_else()
{	

	PRINT_BEGIN("test_if_else");

	vsint32 a, b, x, y, res;
	b = init_vsint32(5);
	x = init_vsint32(7);
	y = init_vsint32(8);

	printf("On fixe :\n");
	display_vsint32(b, "%4.0x", "b"); puts("");
	display_vsint32(x, "%4.0x", "x"); puts("");
	display_vsint32(y, "%4.0x", "y"); puts("");

	printf("\nOn teste pour differentes valeurs de a, la fonction if_else : \"if a >= b return x, else return y\" :\n\n");

	printf("Si a < b, on retourne bien y :\n");
	a = init_vsint32(4);
	display_vsint32(a, "%4.0x", "a\t"); puts("");
	res = if_else(a,b,x,y);
	display_vsint32(res, "%4.0x", "res\t"); puts("\n");

	printf("Si a = b, on retourne bien x : \n");
	a = init_vsint32(5);
	display_vsint32(a, "%4.0x", "a\t"); puts("");
	res = if_else(a,b,x,y);
	display_vsint32(res, "%4.0x", "res\t"); puts("\n");

	printf("Si a > b, on retourne bien x : \n");
	a = init_vsint32(6);
	display_vsint32(a, "%4.0x", "a\t"); puts("");
	res = if_else(a,b,x,y);
	display_vsint32(res, "%4.0x", "res\t"); puts("\n");

	PRINT_END("test_if_else");
}

void test_abs_simd()
{	
	PRINT_BEGIN("test_abs_simd");

	vsint32 a, abs_a;
	a = init_vsint32(-5);
	abs_a = abs_simd(a);
	display_vsint32(a, " %d\t", "a\t"); puts("");
	display_vsint32(abs_a, " %d\t", "abs_a\t"); puts("\n");

	vsint32 b, abs_b;
	b = init_vsint32(8);
	abs_b = abs_simd(b);
	display_vsint32(b, " %d\t", "b\t"); puts("");
	display_vsint32(abs_b, " %d\t", "abs_b\t"); puts("\n");

	vsint32 c, abs_c;
	c = init_vsint32(0);
	abs_c = abs_simd(c);
	display_vsint32(c, " %d\t", "c\t"); puts("");
	display_vsint32(abs_c, " %d\t", "abs_c\t"); puts("\n");

	PRINT_END("test_abs_simd");

}

