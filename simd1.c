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
#define MAX_8B 0xff //2 pow 8 -1


/*
void if_lt(vuint8 a, vuint8 b, vuint8 k1, vuint8 k2){

    vuint8  k, c, d;

    d = _mm_set_epi32


    d = _mm_set_si128(4,4,4,4);

    
    k1 = _mm_set_si128(2,2,2,2);
    k2 = _mm_set_si128(-2,-2,-2,-2);
    c = _mm_cmplt_si128(a ,b);
    k = _mm_or_si128(_mm_and_si128(c,k2), _mm_andnot_si128(c,k1));
    d = _mm_add_si128(d,k);

    display_vuint8(a, "%4.0d", "a"); puts("\n");
    display_vuint8(b, "%4.0d", "b"); puts("\n");
    display_vuint8(k1, "%4.0d", "k1"); puts("\n");
    display_vuint8(k2, "%4.0d", "k2"); puts("\n");
    display_vuint8(c, "%4.0d", "c"); puts("\n");
    display_vuint8(k, "%4.0d", "k"); puts("\n");
    display_vuint8(d, "%4.0d", "d"); puts("\n");
    
}
*/

//if a >= b return x, else return y
vuint8 if_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y)
{

    vuint8 c, z;
    c = _mm_cmplt_epi32(a ,b);//compare a and b
    z = _mm_or_si128(_mm_and_si128(c, y), _mm_andnot_si128(c,x));//select value
    return z;    
}

//complement à deux
vuint8 ca2(vuint8 a)
{
     vuint8 _a;
     _a = _mm_xor_si128(a, init_vuint8(MAX_8B)); //_a = NOT a
     //_a = _mm_add_epi8 (_a, _mm_set_epi8(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)); // on ajoute 1
     a = _mm_add_epi8 (_a, init_vuint8(1));
     return _a;
}

//aide possible at : https://stackoverflow.com/questions/32408665/fastest-way-to-compute-absolute-value-using-sse
vuint8 abs_simd(vuint8 a)
{   
    //si a > 0, return a, else return son complément à deux
    return if_else(a, _mm_setzero_si128(), a, ca2(a));
}