#pragma once 
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

//#include "mutil.h"

vuint8 vuint8_if_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y);
vuint8 vuint8_ca2(vuint8 a);

vsint16 vsint16_if_else(vsint16 a, vsint16 b, vsint16 x, vsint16 y);
vuint16 vuint16_ca2(vuint16 a);
vuint16 vuint16_abs_simd(vsint16 a);

vuint8 vuint8_if_elif_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y, vuint8 z);
vuint8 vuint8_sub_abs(vuint8 a, vuint b);
vuint16 vuint16_if_elif_else(vuint16 a, vuint16 b, vuint16 x, vuint16 y, vuint16 z);

vuint16 ext_8_16(vuint8 x);

void vector_to_scalar(vuint8 *v, uint8 ** res);
int comp_vuint8(vuint8 v1, vuint8 v2);

int compare_matrix(uint8 ** m1, uint8 ** m2, long nrl, long nrh, long ncl, long nch);
int compare_matrix2(uint8 ** m1, uint8 ** m2, long nrl, long nrh, long ncl, long nch);