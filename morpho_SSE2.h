#pragma once

//ouverture de carré 3x3
void ouverture3_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//ouverture de carré 5x5
void ouverture5_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//fermeture de carré 3x3
void fermeture3_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//fermeture de carré 5x5
void fermeture5_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch);



void dilatation3_matrix_SSE2(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch);

void dilatation5_matrix_SSE2(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch);

void erosion3_matrix_SSE2(uint8 **EtE, uint8 **Et, long nrl, long nrh, long ncl, long nch);

void erosion5_matrix_SSE2(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch);



//post traitement ouverture puis fermeture
void posTraitementOF_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//post traitement fermeture puis ouverture
void posTraitementFO_SSE2(uint8 **Et, long nrl, long nrh, long ncl, long nch);