#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "morpho.h"
#include "morpho_SSE2.h"
#include "main.h"

#include "vnrdef.h"
#include "vnrutil.h"
#include "SSE2util.h"


void dilatation3_matrix_SSE2(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	int i, j;

	vuint8 ligne1;
	vuint8 ligne2;
	vuint8 ligne3;

	ligne1= init_vsint8(0);
	ligne2= init_vsint8(0);
	ligne3= init_vsint8(0);
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch-1; j+=14) {
	    	
			ligne1 =_mm_loadu_si128((__m128i *)(&Et[i-1][j-1]));
			ligne2 =_mm_loadu_si128((__m128i *)(&Et[i][j-1]));
			ligne3 =_mm_loadu_si128((__m128i *)(&Et[i+1][j-1]));


			ligne1=_mm_or_si128 (ligne1, ligne2);
			ligne1=_mm_or_si128 (ligne1, ligne3);


			ligne2=_mm_srli_si128 (ligne1, 1);
			ligne3=_mm_slli_si128 (ligne1, 1);

			ligne1=_mm_or_si128 (ligne1, ligne2);
			ligne1=_mm_or_si128 (ligne1, ligne3);

			ligne1=_mm_srli_si128 (ligne1, 1);
			_mm_storeu_si128 ((__m128i *)(&EtD[i][j]), ligne1);
	    }
	    j=nch;
	    EtD[i][j] = dilatation3(Et[i - 1][j - 1], Et[i - 1][j], Et[i - 1][j + 1], Et[i][j - 1], Et[i][j], Et[i][j + 1], Et[i + 1][j - 1], Et[i + 1][j], Et[i + 1][j + 1]);
  	}
}

void dilatation5_matrix_SSE2(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch) 
{
	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	dilatation3_matrix_SSE2(tmp, Et, nrl, nrh, ncl, nch);

	dilatation3_matrix_SSE2(EtD, tmp, nrl, nrh, ncl, nch);

	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);

	
}


void erosion3_matrix_SSE2(uint8 **EtE, uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	int i, j;

	vuint8 ligne1;
	vuint8 ligne2;
	vuint8 ligne3;

	ligne1 = init_vsint8(0);
	ligne2 = init_vsint8(0);
	ligne3 = init_vsint8(0);

	for (i = nrl; i <= nrh; i++) {
		for (j = ncl; j <= nch - 1; j += 14) {

			ligne1 = _mm_loadu_si128((__m128i *)(&Et[i - 1][j - 1]));
			ligne2 = _mm_loadu_si128((__m128i *)(&Et[i][j - 1]));
			ligne3 = _mm_loadu_si128((__m128i *)(&Et[i + 1][j - 1]));


			ligne1 = _mm_and_si128(ligne1, ligne2);
			ligne1 = _mm_and_si128(ligne1, ligne3);


			ligne2 = _mm_srli_si128(ligne1, 1);
			ligne3 = _mm_slli_si128(ligne1, 1);

			ligne1 = _mm_and_si128(ligne1, ligne2);
			ligne1 = _mm_and_si128(ligne1, ligne3);

			ligne1 = _mm_srli_si128(ligne1, 1);
			_mm_storeu_si128((__m128i *)(&EtE[i][j]), ligne1);
		}
		j = nch;
		EtE[i][j] = erosion3(Et[i - 1][j - 1], Et[i - 1][j], Et[i - 1][j + 1], Et[i][j - 1], Et[i][j], Et[i][j + 1], Et[i + 1][j - 1], Et[i + 1][j], Et[i + 1][j + 1]);
	}
}

void erosion5_matrix_SSE2(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch) 
{
	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Copy_SSE2(tmp, Et, nrl, nrh, ncl, nch);
	erosion3_matrix_SSE2(tmp, Et, nrl, nrh, ncl, nch);

	Copy_SSE2(Et, tmp, nrl, nrh, ncl, nch);
	erosion3_matrix_SSE2(EtD, tmp, nrl, nrh, ncl, nch);

	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);
}

//ouverture de carré 3x3
void ouverture3_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch) {


	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Init_mat(tmp, nrl-2, nrh+2, ncl-2, nch+2);
	erosion3_matrix_SSE2(tmp, Et, nrl, nrh, ncl, nch);

	dilatation3_matrix_SSE2(Et, tmp, nrl, nrh, ncl, nch);

	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);
}

//ouverture de carré 5x5
void ouverture5_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Copy_SSE2(tmp, Et, nrl, nrh, ncl, nch);
	erosion5_matrix_SSE2(tmp, Et, nrl, nrh, ncl, nch);

	Copy_SSE2(Et, tmp, nrl, nrh, ncl, nch);
	dilatation5_matrix_SSE2(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);
}

//fermeture de carré 3x3
void fermeture3_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Init_mat(tmp, nrl-2, nrh+2, ncl-2, nch+2);
	dilatation3_matrix_SSE2(tmp, Et, nrl, nrh, ncl, nch);


	erosion3_matrix_SSE2(Et, tmp, nrl, nrh, ncl, nch);

	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);
}

//fermeture de carré 5x5
void fermeture5_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Copy_SSE2(tmp, Et, nrl, nrh, ncl, nch);
	dilatation5_matrix_SSE2(tmp, Et, nrl, nrh, ncl, nch);

	Copy_SSE2(Et, tmp, nrl, nrh, ncl, nch);
	erosion5_matrix_SSE2(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);
}


//post traitement ouverture puis fermeture
void posTraitementOF_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch) {

	ouverture3_SSE2(Et, nrl, nrh, ncl, nch);
	fermeture3_SSE2(Et, nrl, nrh, ncl, nch);

	ouverture5_SSE2(Et, nrl, nrh, ncl, nch);
	fermeture5_SSE2(Et, nrl, nrh, ncl, nch);
}

//post traitement fermeture puis ouverture
void posTraitementFO_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch) {

	fermeture3_SSE2(Et, nrl, nrh, ncl, nch);
	ouverture3_SSE2(Et, nrl, nrh, ncl, nch);

	fermeture5_SSE2(Et, nrl, nrh, ncl, nch);
	ouverture5_SSE2(Et, nrl, nrh, ncl, nch);
}
