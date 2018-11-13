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



vuint16 vuint16_fd_simd(vuint16 It, vuint16 It_1)
{
	
	vuint16 Ot;
	Ot = vuint16_abs_simd(_mm_sub_epi16(It , It_1));
	return vsint16_if_else(Ot, init_vuint16(THETA), init_vuint16(MAX_PIXEL_VALUE), _mm_setzero_si128());
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


void vuint16_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Ot, uint16 **Et)
{	
	vuint8 *pIt = (vuint8*) It;
	vuint8 *pIt_1 = (vuint8*) It_1;
	vuint8 *pEt = (vuint8*) Et;

	for (int i = 0; i < NB_16o_IM - 1 ; i++)
	{
		pEt[i] = vuint16_fd_simd(pIt[i], pIt_1[i]);
		//_mm_store_si128(res[i], fd_simd(pIt[i], pIt_1[i]));
	}	
	
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

