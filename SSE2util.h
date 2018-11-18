#pragma once 
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

vuint8 vuint8_if_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y);
vuint8 vuint8_if_elif_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y, vuint8 z);
vuint8 vuint8_sub_abs(vuint8 a, vuint b);
void Copy_SSE2(uint8 **Mt, uint8 **It, long nrl, long nrh, long ncl, long nch);

int comp_vuint8(vuint8 v1, vuint8 v2);
int compare_matrix(uint8 ** m1, uint8 ** m2, long nrl, long nrh, long ncl, long nch);