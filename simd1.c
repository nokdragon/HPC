/* --------------- */
/* --- simd1.c --- */
/* --------------- */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

void if_lt(vfloat32 a, vfloat32 b, vfloat32 k1, vfloat32 k2){

    vfloat32  k, c, d;

    //vuint8 p = _mm_set_ps(3);

    d = _mm_set_ps(4,4,4,4);

    k1 = _mm_set_ps(2,2,2,2);
    k2 = _mm_set_ps(-2,-2,-2,-2);
    c = _mm_cmplt_ps(a ,b);
    k = _mm_or_ps(_mm_and_ps(c,k2), _mm_andnot_ps(c,k1));
    d = _mm_add_ps(d,k);

    display_vfloat32(a, "%4.0f", "a"); puts("\n");
    display_vfloat32(b, "%4.0f", "b"); puts("\n");
    display_vfloat32(k1, "%4.0f", "k1"); puts("\n");
    display_vfloat32(k2, "%4.0f", "k2"); puts("\n");
    display_vfloat32(c, "%4.0f", "c"); puts("\n");
    display_vfloat32(k, "%4.0f", "k"); puts("\n");
    display_vfloat32(d, "%4.0f", "d"); puts("\n");
}

