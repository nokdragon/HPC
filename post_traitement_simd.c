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

	for(i=nrl+1; i<=nrh-1; i++) {
	    for(j=ncl+1; j<=nch-1; j++) {
			
	    }
  	}
}