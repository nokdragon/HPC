#pragma once 
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

//#include "mutil.h"

vuint8 vuint8_if_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y);
vuint8 vuint8_abs_simd(vsint8 v);
vuint8 vuint8_ca2(vuint8 a);

vsint16 vsint16_if_else(vsint16 a, vsint16 b, vsint16 x, vsint16 y);
vuint16 vuint16_ca2(vuint16 a);
vuint16 vuint16_abs_simd(vsint16 a);

vuint8 vuint8_if_elif_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y, vuint8 z);
vuint8 vuint8_sub_abs(vuint8 a, vuint b);