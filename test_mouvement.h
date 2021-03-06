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
#include "mouvement.h"
#include "morpho.h"


//test unitaire de dilatation3
uint8 test_dilatation3();

//test unitaire de erosion3
uint8 test_erosion3();

//fonction qui calcule la matrice roc
void calculate_ROC(uint8 ** EtRef, uint8 ** Et, long nrl, long nrh, long ncl, long nch, long *ROC);


//fonction qui donne les performances de fd et sd avec ou sans post traitement
void validation();

//affiche la matrice ROC
void print_ROC(long * ROC);

