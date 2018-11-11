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

#define MAX_32B 0xffffffff //2 pow 32 - 1



/*
void if_lt(vsint32 a, vsint32 b, vsint32 k1, vsint32 k2){

    vsint32  k, c, d;

    d = _mm_set_epi32


    d = _mm_set_si128(4,4,4,4);

    
    k1 = _mm_set_si128(2,2,2,2);
    k2 = _mm_set_si128(-2,-2,-2,-2);
    c = _mm_cmplt_si128(a ,b);
    k = _mm_or_si128(_mm_and_si128(c,k2), _mm_andnot_si128(c,k1));
    d = _mm_add_si128(d,k);

    display_vsint32(a, "%4.0d", "a"); puts("\n");
    display_vsint32(b, "%4.0d", "b"); puts("\n");
    display_vsint32(k1, "%4.0d", "k1"); puts("\n");
    display_vsint32(k2, "%4.0d", "k2"); puts("\n");
    display_vsint32(c, "%4.0d", "c"); puts("\n");
    display_vsint32(k, "%4.0d", "k"); puts("\n");
    display_vsint32(d, "%4.0d", "d"); puts("\n");
    
}
*/

//if a >= b return x, else return y
vsint32 if_else(vsint32 a, vsint32 b, vsint32 x, vsint32 y)
{

    vsint32 c, z;
    c = _mm_cmplt_epi32(a ,b);//compare a and b
    z = _mm_or_si128(_mm_and_si128(c, y), _mm_andnot_si128(c,x));//select value
    return z;    
}

//complement à deux
vsint32 ca2(vsint32 a)
{
     vsint32 _a;
     _a = _mm_xor_si128(a, init_vuint32(MAX_32B)); //_a = NOT a
     _a = _mm_add_epi32 (_a, _mm_set_epi32(1, 1, 1, 1)); // on ajoute 1
     return _a;
}

//aide possible at : https://stackoverflow.com/questions/32408665/fastest-way-to-compute-absolute-value-using-sse
vsint32 abs_simd(vsint32 a)
{   
    //si a > 0, return a, else return son complément à deux
    return if_else(a, _mm_setzero_si128(), a, ca2(a));
}