#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "main.h"



void Frame_Difference_Matrix(uint8 **It, uint8 **It_1, uint8 **Et, long nrl, long nrh, long ncl, long nch);
uint8 Frame_Difference(uint8 It, uint8 It_1);
void SD(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, long nrl, long nrh, long ncl, long nch);
void Init_M(uint8 **Mt, uint8 **It, long nrl, long nrh, long ncl, long nch);
void Init_V(uint8 **Vt, long nrl, long nrh, long ncl, long nch);
void Copy(uint8 **Mt, uint8 **It, long nrl, long nrh, long ncl, long nch);
