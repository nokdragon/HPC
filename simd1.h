#pragma once 
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

//#include "mutil.h"

vuint8 if_else(vuint32 a, vuint32 b, vuint32 x, vuint32 y);

vuint8 abs_simd(vsint32 v);