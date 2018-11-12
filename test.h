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
#include "traitement.h"
#include "post_traitement.h"


//test unitaire de dilatation3
uint8 test_dilatation3();

//test unitaire de erosion3
uint8 test_erosion3();

//fonction qui calcule la matrice roc
void calculate_ROC(uint8 ** EtRef, uint8 ** Et, long nrl, long nrh, long ncl, long nch, int *ROC);