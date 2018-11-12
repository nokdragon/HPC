#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "traitement.h"
#include "main.h"

#include "vnrdef.h"
#include "vnrutil.h"
#include "simd1.h"

#define NB_8_I_128 16

#define NRL 0
#define NRH 239
#define NCL 0
#define NCH 351

#define NB_OCTET_IMAGE 83889 //351 * 239
#define NB_OCTET_M128 16 //128b = 16o
#define NB_16o_IM 5243 //(int) OCTET_IM / OCTET_M128
#define NBP_REST_128 49// NB_PIXEL - NBP_MUL_128 = 49

#define MAX_PIXEL_VALUE 255



vuint16 fd_simd(vsint16 It, vsint16 It_1) {
	
	vuint16 Ot;
	//Ot = abs_simd(_mm_sub_epi16(It, It_1));
	Ot = vuint16_abs_simd(_mm_sub_epi16(It , It_1));

	//Debug 
	/*
	sint16 *pIt = (sint16 *) &It;
	sint16 *pIt_1 = (sint16 *) &It_1;
	printf("pIt[0] - pIt_1[0] = %2.0d\n", pIt[0] - pIt_1[0]);
	printf("pIt_1[0] - pIt[0] = %2.0d\n", pIt_1[0] - pIt[0]);
	display_vsint16(_mm_sub_epi16(It , It_1), " %d ", "It - It_1"); puts("");
	display_vsint16(_mm_sub_epi16(It_1 , It), " %d ", "It_1 - It"); puts("");
	*/
	display_vsint16(Ot, " %d", "Ot"); puts("");

	return vuint16_if_else(Ot, init_vuint16(THETA), init_vuint16(MAX_PIXEL_VALUE), _mm_setzero_si128());
}

uint8 ** to_matrix(vuint8 *v)
{
	uint8 **res = ui8matrix(NRL, NRH, NCL, NCH);
	uint8 * p = (uint8 *) v;
	long i,j,k;
	k = 0;
	for(i=NRL; i<=NRH; i++) {
	    for(j=NCL; j<=NCH; j++) {
			res[i][j] = p[k];
			k++;
	    }
  	}
  	return res;
}


void fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Ot, uint8 **Et)
{	
	vuint8 *pIt = (vuint8*) It;
	vuint8 *pIt_1 = (vuint8*) It_1;
	//vuint8 *pEt = (vuint8*) Et;
	vuint8 res[NB_16o_IM];

	//vuint8 vIt, vIt_1;


	for (int i = 0; i < NB_16o_IM - 1 ; i++)
	{
		//vIt = _mm_set_epi8(pIt[i],pIt[i+1],pIt[i+2],pIt[i+3],pIt[i+4],pIt[i+5],pIt[i+6],pIt[i+7],pIt[i+8],pIt[i+9],pIt[i+10],pIt[i+11],pIt[i+12],pIt[i+13],pIt[i+14],pIt[i+15]);
		//vIt_1 = _mm_set_epi8(pIt_1[i],pIt_1[i+1],pIt_1[i+2],pIt_1[i+3],pIt_1[i+4],pIt_1[i+5],pIt_1[i+6],pIt_1[i+7],pIt_1[i+8],pIt_1[i+9],pIt_1[i+10],pIt_1[i+11],pIt_1[i+12],pIt_1[i+13],pIt_1[i+14],pIt_1[i+15]);
		printf("tour  : %d\n", i);
		res[i] = fd_simd(pIt[i], pIt_1[i]);
		//_mm_store_si128(res[i], fd_simd(pIt[i], pIt_1[i]));
	}	

	Et = to_matrix(res);
	
}

/*
void Frame_Difference_Matrix(uint8 **It, uint8 **It_1, uint8 **Ot, uint8 **Et, long nrl, long nrh, long ncl, long nch)
{
	long i,j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
			Et[i][j] = Frame_Difference(It[i][j], It_1[i][j]);
	    }
  	}
}
*/

