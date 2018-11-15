#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"
#include "morpho_SSE2.h"
#include "morpho.h"
#include "main.h"


int test_dilatation_erosion_simd();

int test_morpho_simd();