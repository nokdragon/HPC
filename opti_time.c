#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include "mouvement.h"
#include "main.h"
#include "morpho.h"
#include "test_morpho_SSE2.h"
#include "SSE2util.h"
#include "test_mouvement_SSE2.h"
#include "mouvement_SSE2.h"
#include "test_mouvement.h"
#include "bench_mouvement.h"
#include "bench_mouvement_SSE2.h"
#include "bench_morpho.h"
#include "bench_morpho_SSE2.h"

void entrelacement_memoire (uint8 ** It, uint8 ** It_1)
{

}