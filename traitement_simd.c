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

vuint8 fd_simd(vuint8 It, vuint8 It_1) {
	
	vuint8 Ot;
	//Ot = abs_simd(_mm_sub_epi8(It, It_1));
	Ot = abs_simd(_mm_sub_epi8(It , It_1));
	return if_else(Ot, init_vuint8(THETA), init_vuint8(1), _mm_setzero_si128());
}


void fd_simd_matrix(vuint8 **It, vuint8 **It_1, vuint8 **Ot, vuint8 **Et, long nrl, long nrh, long ncl, long nch) {
	
	long i,j;
}
