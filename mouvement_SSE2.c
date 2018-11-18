#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mouvement.h"
#include "main.h"

#include "vnrdef.h"
#include "vnrutil.h"
#include "SSE2util.h"
#include "main.h"
#include "test_mouvement_SSE2.h"
#include "mouvement_SSE2.h"


vuint8 vuint8_fd_SSE2(vuint8 It, vuint8 It_1)
{	

	vuint8 Ot = vuint8_sub_abs(It, It_1);
	return vuint8_if_else(Ot, init_vuint8(THETA), init_vuint8(MAX_PIXEL_VALUE), _mm_setzero_si128());
}

void vuint8_fd_SSE2_matrixv2(uint8 **It, uint8 **It_1, uint8 **Et, long nrl, long nrh, long ncl, long nch)
{	

	long i;
	for(i=nrl; i<=nrh; i++) {
	    	
	    	vuint8_fd_SSE2_row(It[i], It_1[i], Et[i],  ncl,  nch);	    	
	}	
}

void vuint8_fd_SSE2_matrix(uint8 **It, uint8 **It_1, uint8 **Et, long nrl, long nrh, long ncl, long nch)
{	

	vuint8 vIt, vIt_1;
	long i,j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j+=16) {  	
	    	
			vIt = _mm_loadu_si128((__m128i *)&It[i][j]);
			vIt_1 = _mm_loadu_si128((__m128i *)&It_1[i][j]);
			_mm_storeu_si128((__m128i *)&Et[i][j], vuint8_fd_SSE2(vIt, vIt_1));
	    	
	    }
	}	

}


void vuint8_fd_SSE2_row(uint8 *It, uint8 *It_1, uint8 *Et, long ncl, long nch)
{	

	vuint8 vIt, vIt_1;
	long j;
	for(j=ncl; j<=nch; j+=16) {  	
	    	
			vIt = _mm_loadu_si128((__m128i *)&It[j]);
			vIt_1 = _mm_loadu_si128((__m128i *)&It_1[j]);
			_mm_storeu_si128((__m128i *)&Et[j], vuint8_fd_SSE2(vIt, vIt_1));
	    	
	}		

}


void vuint8_fd_SSE2_iteration(vuint8 vIt, vuint8 vIt_1, vuint8 Et)
{	
	_mm_storeu_si128( &Et, vuint8_fd_SSE2(vIt, vIt_1)); 	
}		


void vuint8_sd_SSE2(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch)
{
	vuint8 a,b,x,y, one;
	long i,j,k;
	one = init_vuint8(1);

	vuint8 vMt;
	vuint8 vIt;
	vuint8 vOt;
	vuint8 vVt_1;
	vuint8 vVt;

	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j+= NB_OCTET_M128) {

	    	a = _mm_loadu_si128((__m128i *) &Mt_1[i][j]);
	    	b = _mm_loadu_si128((__m128i *) &It[i][j]);
			x = _mm_sub_epi8(a, one);//Mt plus grand
			y = _mm_add_epi8(a, one);	
			_mm_storeu_si128( (__m128i *) &Mt[i][j], vuint8_if_elif_else(a, b, x, y ,a) );

			vMt = _mm_loadu_si128((__m128i *) &Mt[i][j]);
			vIt = _mm_loadu_si128((__m128i *) &It[i][j]);			
			vOt = vuint8_sub_abs( vMt, vIt);

	    	b = vOt;
	    	for (k = 0; k < N - 1; k++)
				b = _mm_adds_epu8(b, vOt);
			vVt_1 = _mm_loadu_si128((__m128i *) &Vt_1[i][j]);	
			x = _mm_sub_epi8(vVt_1, one);//Mt plus grand
			y = _mm_add_epi8(vVt_1, one);//Mt plus petit
			vVt= vuint8_if_elif_else(vVt_1, b, x, y ,vVt_1);
			
			b = init_vuint8(VMIN);
			vVt=_mm_max_epu8(vVt, b);

			b = init_vuint8(VMAX); 
			vVt=_mm_min_epu8(vVt, b);

			_mm_storeu_si128( (__m128i *) &Vt[i][j],vVt);
				
			x = init_vuint8(MAX_UINT8);
			y = _mm_setzero_si128();
			_mm_storeu_si128( (__m128i *) &Et[i][j], vuint8_if_else(vOt,vVt,x,y));
			
	    }
	}	

}
