#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "post_traitement.h"
#include "main.h"

#include "vnrdef.h"
#include "vnrutil.h"
#include "simd1.h"


//Copie It dans Mt
void Copy_simd(uint8 **Mt, uint8 **It, long nrl, long nrh, long ncl, long nch)
{
	int i, j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j+=16) {
	    	_mm_storeu_si128 ((__m128i *)(&Mt[i][j]), _mm_loadu_si128((__m128i *)(&It[i][j])));
	    }
  	}
}

void dilatation3_matrix_simd(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch) {
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

void dilatation5_matrix_simd(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Copy_simd(tmp, Et, nrl, nrh, ncl, nch);
	dilatation3_matrix_simd(tmp, Et, nrl, nrh, ncl, nch);

	Copy_simd(Et, tmp, nrl, nrh, ncl, nch);
	dilatation3_matrix_simd(EtD, tmp, nrl, nrh, ncl, nch);

	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);

	
}


void erosion3_matrix_simd(uint8 **EtE, uint8 **Et, long nrl, long nrh, long ncl, long nch) {
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

void erosion5_matrix_simd(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Copy_simd(tmp, Et, nrl, nrh, ncl, nch);
	erosion3_matrix_simd(tmp, Et, nrl, nrh, ncl, nch);

	Copy_simd(Et, tmp, nrl, nrh, ncl, nch);
	erosion3_matrix_simd(EtD, tmp, nrl, nrh, ncl, nch);

	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);
}

//ouverture de carr� 3x3
void ouverture3_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch) {


	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Copy_simd(tmp, Et, nrl, nrh, ncl, nch);
	erosion3_matrix_simd(tmp, Et, nrl, nrh, ncl, nch);

	Copy_simd(Et, tmp, nrl, nrh, ncl, nch);
	dilatation3_matrix_simd(Et, tmp, nrl, nrh, ncl, nch);

	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);
}

//ouverture de carr� 5x5
void ouverture5_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Copy_simd(tmp, Et, nrl, nrh, ncl, nch);
	erosion5_matrix_simd(tmp, Et, nrl, nrh, ncl, nch);

	Copy_simd(Et, tmp, nrl, nrh, ncl, nch);
	dilatation5_matrix_simd(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);
}

//fermeture de carr� 3x3
void fermeture3_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Copy_simd(tmp, Et, nrl, nrh, ncl, nch);
	dilatation3_matrix_simd(tmp, Et, nrl, nrh, ncl, nch);

	Copy_simd(Et, tmp, nrl, nrh, ncl, nch);
	erosion3_matrix_simd(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);
}

//fermeture de carr� 5x5
void fermeture5_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	uint8 **tmp;
	tmp = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);
	Copy_simd(tmp, Et, nrl, nrh, ncl, nch);
	dilatation5_matrix_simd(tmp, Et, nrl, nrh, ncl, nch);

	Copy_simd(Et, tmp, nrl, nrh, ncl, nch);
	erosion5_matrix_simd(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl - 2, nrh + 2, ncl - 2, nch + 2);
}


//post traitement ouverture puis fermeture
void posTraitementOF_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch) {

	ouverture3_simd(Et, nrl, nrh, ncl, nch);
	fermeture3_simd(Et, nrl, nrh, ncl, nch);

	ouverture5_simd(Et, nrl, nrh, ncl, nch);
	fermeture5_simd(Et, nrl, nrh, ncl, nch);
}

//post traitement fermeture puis ouverture
void posTraitementFO_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch) {

	fermeture3_simd(Et, nrl, nrh, ncl, nch);
	ouverture3_simd(Et, nrl, nrh, ncl, nch);

	fermeture5_simd(Et, nrl, nrh, ncl, nch);
	ouverture5_simd(Et, nrl, nrh, ncl, nch);
}
