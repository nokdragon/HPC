#pragma once

void dilatation3_matrix_simd(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch);

void erosion3_matrix_simd(uint8 **EtE, uint8 **Et, long nrl, long nrh, long ncl, long nch);


//ouverture de carr� 3x3
void ouverture3_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//ouverture de carr� 5x5
void ouverture5_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//fermeture de carr� 3x3
void fermeture3_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//fermeture de carr� 5x5
void fermeture5_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch);


//post traitement ouverture puis fermeture
void posTraitementOF_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch);

//post traitement fermeture puis ouverture
void posTraitementFO_simd(uint8 **Et, long nrl, long nrh, long ncl, long nch);