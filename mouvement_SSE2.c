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



vuint8 vuint8_fd_simd(vuint8 It, vuint8 It_1)
{	
	/*
	Description du problème : on veut stocker dans Ot la valeur absolue de It - It_1
	It et It_1 = {0,255}, donc leur soustraction = {-255,255}, non castable dans un uint 8 !
	la solution est donc de calculer : 
	max(It, It_1) - min(It, It_1) = {0,255}, castable dans un uint 8 cette fois !
	*/
	vuint8 Ot, max, min;
	max = _mm_max_epu8(It, It_1);
	min = _mm_min_epu8(It, It_1); //Solution alternative, utiliser un if_else
	Ot = _mm_sub_epi8(max , min);
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

void vuint8_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Et)
{	
	/*
	Description du problème : une image est composé de 83889 octets
	Soit 5243 paquets de 128 bits + 1 octets
	On traite d'abord un octet, puis les 5243paquet de 128 bits en simd
	*/

	vuint8 *pIt = (vuint8*) It[0];
	vuint8 *pIt_1 = (vuint8*) It_1[0];
	vuint8 *pEt = (vuint8 *) Et[0];

	for (int i = 0; i < NBE_VUINT8_IMAGE; i++)
	{
		pEt[i] = vuint8_fd_simd(pIt[i], pIt_1[i]);
		//display_vuint8(res[i], "%4.0d", "res= "); puts("\n");
	}

	//l'octet 
	/*
	uint8 *oIt = (uint8*) It[0];
	uint8 *oIt_1 = (uint8*) It_1[0];
	uint8 *oEt = (uint8 *) Et[0];
	int last_indice = NB_UINT8_IMAGE - 1; 
	oEt[last_indice] = Frame_Difference(oIt[last_indice], oIt_1[last_indice]);
	*/

}

void vuint8_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch)
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

	for (int i = 0; i < len; i++)
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
	
		for (int i = 0; i < NBE_VUINT8_IMAGE; ++i)
	{
		a = pOt[i];
		b = pVt[i];
		x = init_vuint8(MAX_UINT8);
		y = _mm_setzero_si128();
		pEt[i] = vuint8_if_else(a,b,x,y); 
	}

}


