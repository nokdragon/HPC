#pragma once 
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

//#include "mutil.h"

vsint32 if_else(vsint32 a, vsint32 b, vsint32 x, vsint32 y);

__m128i abs_simd(__m128i v);