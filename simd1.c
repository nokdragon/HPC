/* --------------- */
/* --- simd1.c --- */
/* --------------- */
//https://software.intel.com/sites/landingpage/IntrinsicsGuide/

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"



/*
void if_lt(vuint32 a, vuint32 b, vuint32 k1, vuint32 k2){

    vuint32  k, c, d;

    d = _mm_set_epi32


    d = _mm_set_si128(4,4,4,4);

    
    k1 = _mm_set_si128(2,2,2,2);
    k2 = _mm_set_si128(-2,-2,-2,-2);
    c = _mm_cmplt_si128(a ,b);
    k = _mm_or_si128(_mm_and_si128(c,k2), _mm_andnot_si128(c,k1));
    d = _mm_add_si128(d,k);

    display_vuint32(a, "%4.0d", "a"); puts("\n");
    display_vuint32(b, "%4.0d", "b"); puts("\n");
    display_vuint32(k1, "%4.0d", "k1"); puts("\n");
    display_vuint32(k2, "%4.0d", "k2"); puts("\n");
    display_vuint32(c, "%4.0d", "c"); puts("\n");
    display_vuint32(k, "%4.0d", "k"); puts("\n");
    display_vuint32(d, "%4.0d", "d"); puts("\n");
    
}
*/

//if a >= b return x, else return y
vuint32 if_else(vuint32 a, vuint32 b, vuint32 x, vuint32 y){

    vuint32 c, z;
    c = _mm_cmplt_epi32(a ,b);
    z = _mm_or_si128(_mm_and_si128(c, y), _mm_andnot_si128(c,x));
    return z;    
}