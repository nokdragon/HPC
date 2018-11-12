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

#include "simd1.h"

#define MAX_32B 0xffffffff //2 pow 32 - 1
#define MAX_8B 0xff //2 pow 8 -1
#define MAX_16B 0xffff //2 pow 16 -1

//if a >= b return x, else return y
vuint8 vuint8_if_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y)
{
    vuint8 c, z;
    c = _mm_cmplt_epi8(a ,b);//compare a and b
    z = _mm_or_si128(_mm_and_si128(c, y), _mm_andnot_si128(c,x));//select value
    return z;    
}

vuint16 vuint16_if_else(vuint16 a, vuint16 b, vsint16 x, vsint16 y)
{
    vuint16 c, z;
    c = _mm_cmplt_epi16(a ,b);//compare a and b
    z = _mm_or_si128(_mm_and_si128(c, y), _mm_andnot_si128(c,x));//select value
    return z;    
}

//complement à deux
vuint8 vuint8_ca2(vuint8 a)
{
     vuint8 _a;
     _a = _mm_xor_si128(a, init_vuint8(MAX_8B)); //_a = NOT a
     _a = _mm_add_epi8 (_a, _mm_set_epi8(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)); // on ajoute 1
     //a = _mm_add_epi8 (_a, init_vuint8(1));
     return _a;
}

//aide possible at : https://stackoverflow.com/questions/32408665/fastest-way-to-compute-absolute-value-using-sse
vuint8 vuint8_abs_simd(vuint8 a)
{   
    //si a > 0, return a, else return son complément à deux
    return vuint8_if_else(a, _mm_setzero_si128(), a, vuint8_ca2(a));
}

//complement à deux
vsint16 vuint16_ca2(vuint16 a)
{
     vuint16 _a;
     _a = _mm_xor_si128(a, init_vuint16(MAX_16B)); //_a = NOT a
     _a = _mm_add_epi16 (_a, init_vuint16(1));

     return _a;
}

//aide possible at : https://stackoverflow.com/questions/32408665/fastest-way-to-compute-absolute-value-using-sse
vuint16 vuint16_abs_simd(vuint16 a)
{   
    //si a > 0, return a, else return son complément à deux
    return vuint16_if_else(a, _mm_setzero_si128(), a, vuint16_ca2(a));
}