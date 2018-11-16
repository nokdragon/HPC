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



vuint8 vuint8_fd_simd(vuint8 It, vuint8 It_1)
{	

	vuint8 Ot = vuint8_sub_abs(It, It_1);
	return vuint8_if_else(Ot, init_vuint8(THETA), init_vuint8(MAX_PIXEL_VALUE), _mm_setzero_si128());
}



/*TO DEL
vuint16 vuint16_fd_simd(vuint16 It, vuint16 It_1)
{
	
	vuint16 Ot;
	Ot = vuint16_abs_simd(_mm_sub_epi16(It , It_1));
	return vsint16_if_else(Ot, init_vuint16(THETA), init_vuint16(MAX_PIXEL_VALUE), _mm_setzero_si128());
}
*/


/*TO DEL
void vuint16_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Ot, uint16 **Et)
{	
	vuint16 *pIt = (vuint8*) It;
	vuint16 *pIt_1 = (vuint8*) It_1;
	vuint16 *pEt = (vuint16*) Et;

	for (int i = 0; i < NBE_UINT16_IMAGE; i++)
	{
		pEt[i] = vuint16_fd_simd(pIt[i], pIt_1[i]);
		//_mm_store_si128(res[i], fd_simd(pIt[i], pIt_1[i]));
	}	
	
}
*/

void vuint8_fd_simd_matrixv2(uint8 **It, uint8 **It_1, uint8 **Et, long nrl, long nrh, long ncl, long nch)
{	

	long i;
	for(i=nrl; i<=nrh; i++) {
	    	
	    	vuint8_fd_simd_row(It[i], It_1[i], Et[i],  ncl,  nch);
			//display_vuint8(pIt, "%d ", "pIt\t"); puts("\n");
	    	
	}	
}

void vuint8_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Et, long nrl, long nrh, long ncl, long nch)
{	

	vuint8 vIt, vIt_1;
	long i,j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j+=16) {  	
	    	
			vIt = _mm_loadu_si128((__m128i *)&It[i][j]);
			vIt_1 = _mm_loadu_si128((__m128i *)&It_1[i][j]);
			_mm_storeu_si128((__m128i *)&Et[i][j], vuint8_fd_simd(vIt, vIt_1));

			//display_vuint8(pIt, "%d ", "pIt\t"); puts("\n");
	    	
	    }
	}	

}

void vuint8_fd_simd_row(uint8 *It, uint8 *It_1, uint8 *Et, long ncl, long nch)
{	

	vuint8 vIt, vIt_1;
	long j;
	for(j=ncl; j<=nch; j+=16) {  	
	    	
			vIt = _mm_loadu_si128((__m128i *)&It[j]);
			vIt_1 = _mm_loadu_si128((__m128i *)&It_1[j]);
			_mm_storeu_si128((__m128i *)&Et[j], vuint8_fd_simd(vIt, vIt_1));

			//display_vuint8(pIt, "%d ", "pIt\t"); puts("\n");
	    	
	}		

}

void vuint8_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch)
{
	vuint8 a,b,x,y,one;
	vuint8 vMt , vIt , vOt, vVt_1, vVt;
	long i,j,k;


	one = init_vuint8(1);

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

void vuint8_sd_simd_vnul(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch)
{
	vuint8 *pOt = (vuint8*) Ot[0];
	vuint8 *pIt = (vuint8*) It[0];
	//vuint8 *pIt_1 = (vuint8*) It_1[0];
	vuint8 *pEt = (vuint8 *) Et[0];
	vuint8 *pVt = (vuint8*) Vt[0];
	vuint8 *pVt_1 = (vuint8*) Vt_1[0];
	vuint8 *pMt = (vuint8*) Mt[0];
	vuint8 *pMt_1 = (vuint8*) Mt_1[0];
	vuint8 a,b,x,y,z, one;
	int i,j;

	one = init_vuint8(1);
	long len = ((nrh - nrl + 1) * (nch - ncl + 1))/16;

	for (i = 0; i < len; i++)
	{
		a = pMt_1[i];
		b = pIt[i];
		x = _mm_sub_epi8(pMt_1[i], one);//Mt plus grand
		y = _mm_add_epi8(pMt_1[i], one);
		z = a; //Mt ==		
		pMt[i] = vuint8_if_elif_else(a, b, x, y ,z);

	}

//========================================================================

	for (i = 0; i < NBE_VUINT8_IMAGE; i++){
		//printf("i = %d \n", i);
		pOt[i]= vuint8_sub_abs(pMt[i], pIt[i]);
	}

//========================================================================

	one = init_vuint8(1);
	for (i = 0; i < NBE_VUINT8_IMAGE; i++)
	{
		a = pVt_1[i];
		b = pOt[i];
		for (j = 0; j < N-1; j++){
			b = _mm_adds_epu8(b, pOt[i]);
		}

		x = _mm_sub_epi8(pVt_1[i], one);//Mt plus grand
		y = _mm_add_epi8(pVt_1[i], one);//Mt plus petit
		z = pVt_1[i];
		pVt[i] = vuint8_if_elif_else(a, b, x, y ,z);	
		
	}

//========================================================================
		
	for ( i = 0; i < NBE_VUINT8_IMAGE; ++i)
	{	
		
		a = pVt[i];
		b = init_vuint8(VMIN);
		x = a;
		y = b;
		pVt[i] = vuint8_if_else(a,b,x,y); 
		//opti possible en evitant de faire un autre if_else si le premier a été fait
		b = init_vuint8(VMAX);
		x = b;
		y = pVt[i];
		pVt[i] = vuint8_if_else(a,b,x,y); 

		if(i==0){
			//display_vuint8(b, "%d ", "b\t"); puts("\n");
			//display_vuint8(pVt_1[i], "%d ", "pvt_1\t"); puts("\n");
			//display_vuint8(pOt[i], "%d ", "Ot\t"); puts("\n");
			//display_vuint8(pVt[i], "%d ", "pvt ap\t"); puts("\n");
			a = pVt[i];
		b = init_vuint8(VMIN);
		x = a;
		y = b;
			//display_vuint8(vuint8_if_else(a,b,x,y), "%d ", "if\t"); puts("\n");
		}
	}
	
		for (i = 0; i < NBE_VUINT8_IMAGE; ++i)
	{
		a = pOt[i];
		b = pVt[i];
		x = init_vuint8(MAX_UINT8);
		y = _mm_setzero_si128();
		pEt[i] = vuint8_if_else(a,b,x,y); 
	}
}