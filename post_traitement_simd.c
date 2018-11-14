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
			ligne1 =_mm_loadu_si128(&Et[i-1][j-1]);
			ligne2 =_mm_loadu_si128(&Et[i][j-1]);
			ligne3 =_mm_loadu_si128(&Et[i+1][j-1]);			

			ligne1=_mm_and_si128 (ligne1, ligne2);
			ligne1=_mm_and_si128 (ligne1, ligne3);

			ligne2=_mm_srli_si128 (ligne1, 1);
			ligne3=_mm_slli_si128 (ligne1, 1);

			ligne1=_mm_and_si128 (ligne1, ligne2);
			ligne1=_mm_and_si128 (ligne1, ligne3);

			ligne1=_mm_slli_si128 (ligne1, 1);
			_mm_storeu_si128 (&EtD[i][j], ligne1);
	    }
	    j=nch;
	    EtD[i][j] = dilatation3(Et[i - 1][j - 1], Et[i - 1][j], Et[i - 1][j + 1], Et[i][j - 1], Et[i][j], Et[i][j + 1], Et[i + 1][j - 1], Et[i + 1][j], Et[i + 1][j + 1]);
  	}
}