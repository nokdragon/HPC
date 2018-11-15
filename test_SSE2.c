#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "SSE2util.h"
#include "mouvement_SSE2.h"
#include "mouvement.h"
#include "main.h"
#include "test_SSE2.h"

//focntion de test unitaire exhaustif de vuint8_if_else
int test_vuint8_if_else()
{	

	PRINT_BEGIN();

	//uint8 * tmp;
	vuint8 a, b, x, y, res;//,cmp;
	x = init_vuint8(7);
	y = init_vuint8(8);


	int i,j;

	for(i=MIN_UINT8;i<MAX_UINT8+1;i++){//parcours toutes les entrées possible de a
		for(j=MIN_UINT8;j<MAX_UINT8+1;j++){//et de b
			a=init_vuint8(i);
			b=init_vuint8(j);
			res = vuint8_if_else(a,b,x,y);
			if(i>=j){//si a est supérieur ou égale à b
				/*
				for(k=0;k<16;k++){//pour tous les uint8 du vuint8 on vérifie que le résultat est bon (res est bien égale a x)
					
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
				}*/
				if (comp_vuint8(x, res)){
					printf("Erreur de if_else simd i=%d j=%d\n",i,j);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(x, "%4.0x", "x "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
				}
			}
			else{//si a n'est pas supérieur ou égale à b
				/*
				for(k=0;k<16;k++){//pour tous les uint8 du vuint8 on vérifie que le résultat est bon (res est bien égale a y)
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
				}*/
					if (comp_vuint8(y, res)){
					printf("Erreur de if_else simd i=%d j=%d\n",i,j);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(y, "%4.0x", "y "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
				}
			}

		}
	}

	PRINT_OK();
	PRINT_END();
	return 0;	

}


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
	display_vsint16(abs_a, " %d\t", "abs_a\t"); puts("\n");

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



int  test_vuint8_if_elif_else()
{
	/*
	PRINT_BEGIN();
	vuint8 a,b,x,y,z;
	a = init_vuint8(4);
	b = init_vuint8(5);
	x = init_vuint8(6);
	y = init_vuint8(7);
	z = init_vuint8(8);
	vuint8_if_elif_else( a,  b,  x,  y,  z);
	PRINT_END();
	*/



	PRINT_BEGIN();

	//uint8 * tmp;
	vuint8 a, b, x, y, z, res;//,cmp;
	x = init_vuint8(7);
	y = init_vuint8(8);
	z = init_vuint8(9);


	int i,j;

	for(i=MIN_UINT8;i<MAX_UINT8+1;i++){//parcours toutes les entrées possible de a
		for(j=MIN_UINT8;j<MAX_UINT8+1;j++){//et de b
			a=init_vuint8(i);
			b=init_vuint8(j);
			res = vuint8_if_elif_else(a,b,x,y,z);
			if(i>j){//si a est supérieur ou égale à b
				/*
				for(k=0;k<16;k++){//pour tous les uint8 du vuint8 on vérifie que le résultat est bon (res est bien égale a x)
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
				}*/
				if (comp_vuint8(x, res)){
					printf("Erreur de if_else simd i=%d j=%d\n",i,j);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(x, "%4.0x", "x "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
				}
			}
			else if(i == j){
				/*
				for(k=0;k<16;k++){//pour tous les uint8 du vuint8 on vérifie que le résultat est bon (res est bien égale a x)
					cmp=_mm_cmpeq_epi8 (z,res);
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
				}*/
				if (comp_vuint8(z, res)){
					printf("Erreur de if_else simd i=%d j=%d\n",i,j);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(z, "%4.0x", "z "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
				}
			}
			else{//si a n'est pas supérieur ou égale à b
				/*
				for(k=0;k<16;k++){//pour tous les uint8 du vuint8 on vérifie que le résultat est bon (res est bien égale a y)
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
				*/
				if (comp_vuint8(y, res)){
					printf("Erreur de if_else simd i=%d j=%d\n",i,j);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(y, "%4.0x", "y "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
				}
			}

		}
	}

	PRINT_OK();
	PRINT_END();
	return 0;	
}

void test_ext_8_16()
{
	vuint8 v = init_vuint8(5);
	vuint16 v16 = ext_8_16(v);
	display_vuint8(v, "%4.0x", " v"); puts("\n");
	display_vuint16(v16, "%4.0x", " v16 "); puts("\n");
}
