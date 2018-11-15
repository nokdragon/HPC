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
#include "main.h"
#include "test_simd.h"



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

vuint16 vuint16_fd_simd(vuint16 It, vuint16 It_1)
{
	
	vuint16 Ot;
	Ot = vuint16_abs_simd(_mm_sub_epi16(It , It_1));
	return vsint16_if_else(Ot, init_vuint16(THETA), init_vuint16(MAX_PIXEL_VALUE), _mm_setzero_si128());
}

void to_matrix(vuint8 *v, uint8 ** res)
{
	//uint8 **res = ui8matrix(NRL, NRH, NCL, NCH);
	uint8 * p = (uint8 *) v;
	long i,j,k;
	k = 0;
	for(i=NRL; i<=NRH; i++) {
	    for(j=NCL; j<=NCH; j++) {
			res[i][j] = p[k];
			//printf("res[%ld][%ld] = p[%ld] = %d\n",i,j,k,p[k]); 
			k++;
	    }
  	}
  	//return res;
}


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

/*
void SD(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, long nrl, long nrh, long ncl, long nch)
{
	long i,j;
	uint8 Ot;

	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {

	    	if(Mt_1[i][j]<It[i][j]){
	    		Mt[i][j] = Mt_1[i][j] + 1;
	    	}
	    	else if(Mt_1[i][j]>It[i][j]){
	    		Mt[i][j] = Mt_1[i][j] - 1;
	    	}
	    	else{
	    		Mt[i][j] = Mt_1[i][j];
	    	}

	    	Ot=abs( Mt[i][j] - It[i][j] );

	    	if(Vt_1[i][j] < N * Ot){
	    		Vt[i][j] = Vt_1[i][j] + 1;
	    	}
	    	else if(Vt_1[i][j] > N * Ot){
	    		Vt[i][j] = Vt_1[i][j] - 1;
	    	}
	    	else{
	    		Vt[i][j] = Vt_1[i][j];
	    	}

	    	if(Vt[i][j]<VMIN){
	    		Vt[i][j]=VMIN;
	    	}
	    	else if(Vt[i][j]>VMAX){
	    		Vt[i][j]=VMAX;
	    	}

	    	if(Ot < Vt[i][j]){
	    		Et[i][j]=0;
	    	}
	    	else{
	    		Et[i][j]=255;
	    	}
	    }
  	}
}
*/

void part1_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch)
{
	//vuint8 *pOt = (vuint8*) Ot[0];
	vuint8 *pIt = (vuint8*) It[0];
	//vuint8 *pIt_1 = (vuint8*) It_1[0];
	//vuint8 *pEt = (vuint8 *) Et[0];
	//vuint8 *pVt = (vuint8*) Vt[0];
	//vuint8 *pVt_1 = (vuint8*) Vt_1[0];
	vuint8 *pMt = (vuint8*) Mt[0];
	vuint8 *pMt_1 = (vuint8*) Mt_1[0];

	vuint8 a,b,x,y,z, one;
	one = init_vuint8(1);

	long len = ((nrh - nrl + 1) * (nch - ncl + 1))/16;
	//float flen = (float) (((nrh - nrl) * (nch - ncl))/16);
	//printf("len = %ld, flen = %f \n", len, flen);

	for (int i = 0; i < len; i++)
	{
		/*probleme avec le -1
		a = pMt_1[i];
		b = pIt[i];
		x = init_vsint8(-1);//Mt plus grand
		y = init_vsint8(+1);//Mt plus petit
		z = _mm_setzero_si128(); //Mt ==		
		pMt[i] = _mm_add_epi8(pMt_1[i], vuint8_if_elif_else(a, b, x, y ,z));
		*/

		a = pMt_1[i];
		b = pIt[i];
		x = _mm_sub_epi8(pMt_1[i], one);//Mt plus grand
		y = _mm_add_epi8(pMt_1[i], one);
		z = a; //Mt ==		
		pMt[i] = vuint8_if_elif_else(a, b, x, y ,z);

		//display_vuint8(pMt[i], "%4.0d", "pMt= "); puts("\n");
		//Ot=abs( Mt[i][j] - It[i][j] );	

		/* CE QUI MARCHE

			a = pMt_1[k];
			b = pIt[k];
			x = _mm_sub_epi8(pMt_1[k], one);//Mt plus grand
			y = _mm_add_epi8(pMt_1[k], one);
			z = a; //Mt ==		

			//display_vuint8(pMt_1[k], " %d", "sMt_1 AVANT IF\t"); puts("");
			//pMt[k] = _mm_add_epi8(pMt_1[k], vuint8_if_elif_else(a, b, x, y ,z));
			pMt[k] = vuint8_if_elif_else(a, b, x, y ,z);
			*/
	}

	
	/*
	//on traite l'octet restant 
	uint8 *oMt = (uint8*) Mt[0];
	uint8 *oMt_1 = (uint8*) Mt_1[0];
	uint8 *oIt = (uint8*) It[0];
	//uint8 *oIt_1 = (uint8*) It_1[0];
	//uint8 * oOt = (uint8*) Ot[0];
	int last_indice = NB_UINT8_IMAGE - 1; 

	if(oMt_1[last_indice]<oIt[last_indice]){
	    oMt[last_indice] = oMt_1[last_indice] + 1;
	}
	else if(oMt_1[last_indice]>oIt[last_indice]){
		oMt[last_indice] = oMt_1[last_indice] - 1;
	}
	else{
		oMt[last_indice] = oMt_1[last_indice];
	}
	*/


	return ;
}

void part1_sd_scalar(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch)
{
	long i,j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {

	    	if(Mt_1[i][j]<It[i][j]){
	    		Mt[i][j] = Mt_1[i][j] + 1;
	    	}
	    	else if(Mt_1[i][j]>It[i][j]){
	    		Mt[i][j] = Mt_1[i][j] - 1;
	    	}
	    	else{
	    		Mt[i][j] = Mt_1[i][j];
	    	}
	    }
	}

	return;
}

void part1mix(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **sMt, uint8 **sMt_1,  uint8 **Ot,long nrl, long nrh, long ncl, long nch)
{
	vuint8 a,b,x,y,z, one;
	one = init_vuint8(1);
	/*
	vuint8 test = init_vuint8(253);
	a = init_vuint8(253);
	b = init_vuint8(252);
	x = init_vsint8(-1);//Mt plus grand
	y = init_vsint8(+1);//Mt plus petit
	z = _mm_setzero_si128(); //Mt ==
	vuint test1 = _mm_adds_epi8(test, vuint8_if_elif_else(a, b, x, y ,z));
	*/


	long i,j,k;
	k=0;
	int cpt = 0;

	if(compare_matrix(sMt_1, Mt_1, nrl,  nrh,  ncl,  nch)){
		printf("DEBUT PROB\n");
		return;
	}
	

	vuint8 *pIt = (vuint8*) It[0];
	vuint8 *pMt = (vuint8*) sMt[0];
	vuint8 *pMt_1 = (vuint8*) sMt_1[0];
	
	//long len = ((nrh - nrl) * (nch - ncl))/15;
	//float flen = (float) (((nrh - nrl +1) * (nch - ncl +1))/16);
	//printf("len = %ld, flen = %f , %d %d% d %d\n", len, flen, nrl, nrh, ncl, nch);
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {

	    	
	    	if(Mt_1[i][j]<It[i][j]){
	    		Mt[i][j] = Mt_1[i][j] + 1;
	    	}
	    	else if(Mt_1[i][j]>It[i][j]){
	    		Mt[i][j] = Mt_1[i][j] - 1;
	    	}
	    	else{
	    		Mt[i][j] = Mt_1[i][j];
	    	}
	    	//printf("Mt[%d][%d] = %d\t",i,j,Mt[i][j]);
	    	//printf("Mt_1[%d][%d] = %d\t",i,j,Mt_1[i][j]);
	    	//printf("It[%d][%d] = %d\n",i,j,It[i][j]);
	    	cpt++;
	    	 if(cpt == 16){
	    	cpt = 0;
	    	/*a = pMt_1[k];
			b = pIt[k];
			x = init_vsint8(-1);//Mt plus grand
			y = init_vsint8(+1);//Mt plus petit
			z = _mm_setzero_si128(); //Mt ==
			*/

			a = pMt_1[k];
			b = pIt[k];
			x = _mm_sub_epi8(pMt_1[k], one);//Mt plus grand
			y = _mm_add_epi8(pMt_1[k], one);
			z = a; //Mt ==		

			//display_vuint8(pMt_1[k], " %d", "sMt_1 AVANT IF\t"); puts("");
			//pMt[k] = _mm_add_epi8(pMt_1[k], vuint8_if_elif_else(a, b, x, y ,z));
			pMt[k] = vuint8_if_elif_else(a, b, x, y ,z);
			
			//display_vuint8(pMt[k], " %d", "sMt\t"); puts("");
			//display_vuint8(pMt_1[k], " %d", "sMt_1\t"); puts("");
			/*
			display_vuint8(pMt_1[k], " %d", "sMt_1\t"); puts("");
				display_vuint8(pIt[k], " %d", "It\t"); puts("");
				printf("<, > ou = ?. On fait l'opération : \n");
				display_vuint8(pMt_1[k], " %d", "sMt_1\t"); puts("");
				printf("+\n");
				display_vsint8(vuint8_if_elif_else(a, b, x, y ,z), " %d", "if\t"); puts("");
				printf("=\n");
				display_vuint8(pMt[k], " %d", "sMt\t"); puts("");
			*/
			k++;
			if(compare_matrix(Mt, sMt, nrl,  nrh,  ncl,  nch)){
				k--;
				printf("Erreur : \n");
				display_vuint8(pMt_1[k], " %d", "sMt_1\t"); puts("");
				display_vuint8(pIt[k], " %d", "It\t"); puts("");
				printf("<, > ou = ?. On fait l'opération : \n");
				display_vuint8(pMt_1[k], " %d", "sMt_1\t"); puts("");
				printf("+\n");
				display_vsint8(vuint8_if_elif_else(a, b, x, y ,z), " %d", "if\t"); puts("");
				printf("=\n");
				display_vuint8(pMt[k], " %d", "sMt\t"); puts("");


				//display_vuint8(test1, " %d", "test1\t"); puts("");
				return;
			}


	    }
	    }
	    
	   
	}
	//printf(" k = %ld\n", k);
	return;
}

void part2_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch)
{
	vuint8 * pOt = (vuint8 *) Ot[0];

	//vuint8 *pOt = (vuint8*) Ot[0];
	vuint8 *pIt = (vuint8*) It[0];
	//vuint8 *pIt_1 = (vuint8*) It_1[0];
	//vuint8 *pEt = (vuint8 *) Et[0];
	//vuint8 *pVt = (vuint8*) Vt[0];
	//vuint8 *pVt_1 = (vuint8*) Vt_1[0];
	vuint8 *pMt = (vuint8*) Mt[0];
	//vuint8 *pMt_1 = (vuint8*) Mt_1[0];


	for (int i = 0; i < NBE_VUINT8_IMAGE; i++){
		//printf("i = %d \n", i);
		pOt[i]= vuint8_sub_abs(pMt[i], pIt[i]);
	}
	
}

void part2_sd_scalar(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch)
{
	long i,j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
	    	Ot[i][j]=abs( Mt[i][j] - It[i][j] );
	    }
	}	
}

void part3_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch)
{
	vuint8 * pOt = (vuint8 *) Ot[0];

	//vuint8 *pOt = (vuint8*) Ot[0];
	//uint8 *pIt = (vuint8*) It[0];
	//vuint8 *pIt_1 = (vuint8*) It_1[0];
	vuint8 *pEt = (vuint8 *) Et[0];
	vuint8 *pVt = (vuint8*) Vt[0];
	vuint8 *pVt_1 = (vuint8*) Vt_1[0];
	//vuint8 *pMt = (vuint8*) Mt[0];
	//vuint8 *pMt_1 = (vuint8*) Mt_1[0];
	//uint8 ** mb = ui8matrix(nrl,nrh,ncl,nch);

	vuint8 a,b,x,y,z, one;
	int i,j;
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

		/*
		if(i==3){
			display_vuint8(b, "%d ", "b\t"); puts("\n");
			display_vuint8(pVt_1[i], "%d ", "pvt_1\t"); puts("\n");
			display_vuint8(pOt[i], "%d ", "Ot\t"); puts("\n");
			display_vuint8(pVt[i], "%d ", "pvt absv\t"); puts("\n");
		}*/
		
		
	}
	
	//to_matrix(mb,b);
	//printf("mb[0][52] = %d\n", mb[0][52]);

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

void part3_sd_scalar(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch)
{
	long i,j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {    
	
			if(Vt_1[i][j] < N * Ot[i][j] ){
			    Vt[i][j] = Vt_1[i][j] + 1;
			}
			else if(Vt_1[i][j] > N * Ot[i][j]){
			    Vt[i][j] = Vt_1[i][j] - 1;
			}
			else{
			    Vt[i][j] = Vt_1[i][j];
			}

			if(j==52 && i==0){

				//printf("Vt_1[i][j] = %d, Ot = %d; N * Ot[i][j] = %d, Vt[i][j] =%d \n",Vt_1[i][j],Ot[i][j], N * Ot[i][j], Vt[i][j]);
			}
			if(Vt[i][j]<VMIN){
	    		Vt[i][j]=VMIN;
	    	}
	    	else if(Vt[i][j]>VMAX){
	    		Vt[i][j]=VMAX;
	    	}
	    	if(Ot[i][j] < Vt[i][j]){
	    		Et[i][j]=0;
	    	}
	    	else{
	    		Et[i][j]=255;
	    	}
	    }
	}


}