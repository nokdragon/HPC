#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"
#include "post_traitement_simd.h"
#include "post_traitement.h"
#include "main.h"


int compare_matrix2(uint8 ** m1, uint8 ** m2, long nrl, long nrh, long ncl, long nch);

int test_dilatation_erosion_simd();

int test_morpho_simd();