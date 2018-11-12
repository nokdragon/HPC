#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "simd1.h"
#include "traitement_simd.h"
#include "traitement.h"

//#define PRINT_BEGIN(msg) printf("\n\n==============================================BEGIN %s==============================================\n", msg);
//#define PRINT_END(msg) printf("==============================================END %s==============================================\n\n\n\n", msg);
#define PRINT_BEGIN() printf("\n\n==============================================BEGIN %s==============================================\n", __func__);
#define PRINT_END() printf("==============================================END %s==============================================\n\n\n\n", __func__);

#define MAX_UINT8 128

int test_vuint8_if_else()
{	

	//PRINT_BEGIN("test_if_else");
	PRINT_BEGIN();

	uint8 * tmp;
	vuint8 a, b, x, y, res,cmp;
	x = init_vuint8(7);
	y = init_vuint8(8);


	int i,j,k;

	for(i=-MAX_UINT8;i<MAX_UINT8;i++){
		for(j=-MAX_UINT8;j<MAX_UINT8;j++){
			a=init_vuint8(i);
			b=init_vuint8(j);
			res = vuint8_if_else(a,b,x,y);
			if(i>=j){
				for(k=0;k<16;k++){
					cmp=_mm_cmpeq_epi8 (x,res);
					tmp=(uint8 *)&cmp;
					if(tmp[k]){
					}
					else{
						printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
					}
				}
			}
			else{
				for(k=0;k<16;k++){
					cmp=_mm_cmpeq_epi8 (y,res);
					tmp=(uint8 *)&cmp;
					if(tmp[k]){
					}
					else{
						printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						return 1;
					}
				}
			}

		}
	}

	PRINT_END();
	return 0;

	

}
/*
void test_vuint8_if_else()
{	

	//PRINT_BEGIN("test_if_else");
	PRINT_BEGIN();

	vuint8 a, b, x, y, res;
	b = init_vuint8(5);
	x = init_vuint8(7);
	y = init_vuint8(8);

	printf("On fixe :\n");
	display_vuint8(b, "%4.0x", "b"); puts("");
	display_vuint8(x, "%4.0x", "x"); puts("");
	display_vuint8(y, "%4.0x", "y"); puts("");

	printf("\nOn teste pour differentes valeurs de a, la fonction if_else : \"if a >= b return x, else return y\" :\n\n");

	printf("Si a < b, on retourne bien y :\n");
	a = init_vuint8(4);
	display_vuint8(a, "%4.0x", "a\t"); puts("");
	res = vuint8_if_else(a,b,x,y);
	display_vuint8(res, "%4.0x", "res\t"); puts("\n");

	printf("Si a = b, on retourne bien x : \n");
	a = init_vuint8(5);
	display_vuint8(a, "%4.0x", "a\t"); puts("");
	res = vuint8_if_else(a,b,x,y);
	display_vuint8(res, "%4.0x", "res\t"); puts("\n");

	printf("Si a > b, on retourne bien x : \n");
	a = init_vuint8(6);
	display_vuint8(a, "%4.0x", "a\t"); puts("");
	res = vuint8_if_else(a,b,x,y);
	display_vuint8(res, "%4.0x", "res\t"); puts("\n");

	PRINT_END();

}*/

void test_vuint8_abs_simd()
{	
	PRINT_BEGIN();

	vuint8 a, abs_a;
	a = init_vuint8(-5);
	abs_a = vuint8_abs_simd(a);
	display_vsint8(a, " %d\t", "a\t"); puts("");
	display_vuint8(abs_a, " %d\t", "abs_a\t"); puts("\n");

	vuint8 b, abs_b;
	b = init_vuint8(8);
	abs_b = vuint8_abs_simd(b);
	display_vuint8(b, " %d\t", "b\t"); puts("");
	display_vuint8(abs_b, " %d\t", "abs_b\t"); puts("\n");

	vuint8 c, abs_c;
	c = init_vuint8(0);
	abs_c = vuint8_abs_simd(c);
	display_vuint8(c, " %d\t", "c\t"); puts("");
	display_vuint8(abs_c, " %d\t", "abs_c\t"); puts("\n");

	PRINT_END();

}

void test_vuint16_abs_simd()
{	
	PRINT_BEGIN();

	vuint16 a, abs_a;
	a = init_vuint16(-5);
	abs_a = vuint16_abs_simd(a);
	display_vsint16(a, " %d\t", "a\t"); puts("");
	display_vuint16(abs_a, " %d\t", "abs_a\t"); puts("\n");

	vuint16 b, abs_b;
	b = init_vuint16(16);
	abs_b = vuint16_abs_simd(b);
	display_vuint16(b, " %d\t", "b\t"); puts("");
	display_vuint16(abs_b, " %d\t", "abs_b\t"); puts("\n");

	vuint16 c, abs_c;
	c = init_vuint16(0);
	abs_c = vuint16_abs_simd(c);
	display_vuint16(c, " %d\t", "c\t"); puts("");
	display_vuint16(abs_c, " %d\t", "abs_c\t"); puts("\n");

	PRINT_END();

}

void test_fd_simd()
{
	PRINT_BEGIN();

	vuint16 It, It_1, res;

	It =  init_vuint16(40);
	It_1 =  init_vuint16(41);
	res = fd_simd(It, It_1);
	display_vuint16(It, " \t%d\t", "It\t"); puts("");
	display_vuint16(It_1, " \t%d\t", "It_1\t"); puts("");
	display_vsint16(_mm_sub_epi16(It , It_1), " \t%d\t", "It - It_1"); puts("");
	display_vsint16(vuint16_abs_simd(_mm_sub_epi16(It , It_1)), " \t%d\t", "|It - It_1|"); puts("\n");
	printf("La soustraction absolue des deux vecteurs est bien inférieur à theta =  %d, donc on retourne :\n",  THETA);
	display_vuint16(res, " \t%d\t", "res\t"); puts("\n");
	puts("\n\n");

	It =  init_vuint16(40);
	It_1 =  init_vuint16(240);
	res = fd_simd(It, It_1);
	display_vuint16(It, " \t%d\t", "It\t"); puts("");
	display_vuint16(It_1, " \t%d\t", "It_1\t"); puts("");
	display_vsint16(_mm_sub_epi16(It , It_1), " \t%d\t", "It - It_1"); puts("");
	display_vsint16(vuint16_abs_simd(_mm_sub_epi16(It , It_1)), " \t%d\t", "|It - It_1|"); puts("\n");
	printf("La soustraction absolue des deux vecteurs est bien supérieur à theta =  %d, donc on retourne :\n",  THETA);
	display_vuint16(res, " \t%d\t", "res\t"); puts("\n");
	puts("\n\n");

	It =  init_vuint16(40);
	It_1 =  init_vuint16(40);
	res = fd_simd(It, It_1);
	display_vuint16(It, " \t%d\t", "It\t"); puts("");
	display_vuint16(It_1, " \t%d\t", "It_1\t"); puts("");
	display_vsint16(_mm_sub_epi16(It , It_1), " \t%d\t", "It - It_1"); puts("");
	display_vsint16(vuint16_abs_simd(_mm_sub_epi16(It , It_1)), " \t%d\t", "|It - It_1|"); puts("\n");
	printf("La soustraction absolue des deux vecteurs est bien inférieur à theta = %d, donc on retourne :\n",  THETA);
	display_vuint16(res, " \t%d\t", "res\t"); puts("\n");

	PRINT_END();
}