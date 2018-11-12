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

//dilatation de carré de 3x3
uint8 dilatation3(uint8 Et1, uint8 Et2, uint8 Et3, uint8 Et4, uint8 Et5, uint8 Et6, uint8 Et7, uint8 Et8, uint8 Et9);

//dilatation de carré de 3x3 appliqué à une matrice
void dilatation3_matrix(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch);


//dilatation de carré de 5x5
void dilatation5(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch);

//erosion de carré de 3x3
uint8 erosion3(uint8 Et1, uint8 Et2, uint8 Et3, uint8 Et4, uint8 Et5, uint8 Et6, uint8 Et7, uint8 Et8, uint8 Et9);

//erosion de carré de 3x3 appliqué à une matrice
void erosion3_matrix(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch);

//erosion de carré de 5x5
void erosion5(uint8 **EtE, uint8 **Et, long nrl, long nrh, long ncl, long nch);

//ouverture de carré 3x3
void ouverture3(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//ouverture de carré 5x5
void ouverture5(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//fermeture de carré 3x3
void fermeture3(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//fermeture de carré 5x5
void fermeture5(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//post traitement ouverture puis fermeture
void posTraitementOF(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//post traitement fermeture puis ouverture
void posTraitementFO(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//post traitement custom
void posTraitementC(uint8 **Et, long nrl, long nrh, long ncl, long nch);
