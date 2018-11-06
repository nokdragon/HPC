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

uint8 dilatation3(uint8 Et1, uint8 Et2, uint8 Et3, uint8 Et4, uint8 Et5, uint8 Et6, uint8 Et7, uint8 Et8, uint8 Et9) {
	int tmp;
	tmp = Et1;
	tmp += Et2;
	tmp += Et3;
	tmp += Et4;
	tmp += Et5;
	tmp += Et6;
	tmp += Et7;
	tmp += Et8;
	tmp += Et9;
	if (tmp == 0) {
		return 0;
	}
	else {
		return 255;
	}
}

//dilatation de carré de 3x3
void dilatation3_matrix(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch){
	int i, j;
	for(i=nrl+1; i<=nrh-1; i++) {
	    for(j=ncl+1; j<=nch-1; j++) {
			EtD[i][j] = dilatation3(Et[i - 1][j - 1], Et[i - 1][j], Et[i - 1][j + 1], Et[i][j - 1], Et[i][j], Et[i][j + 1], Et[i + 1][j - 1], Et[i + 1][j], Et[i + 1][j + 1]);
	    }
  	}
}


uint8 test_dilatation3() {

	int i, j, k, l, m, n, o, p, q;
	//9 boucle traitant tous les cas possible des entrée de la fonction dilatation3
	for (i = 0;i < 2;i++) {
		for (j = 0;j < 2;j++) {
			for (k = 0;k < 2;k++) {
				for (l = 0;l < 2;l++) {
					for (m = 0;m < 2;m++) {
						for (n = 0;n < 2;n++) {
							for (o = 0;o < 2;o++) {
								for (p = 0;p < 2;p++) {
									for (q = 0;q < 2;q++) {
										if (dilatation3(i * 255, j * 255, k * 255, l * 255, m * 255, n * 255, o * 255, p * 255, q * 255) == 255) {//si la sortie vaut 255(equivalent a 1)
											if (i == 0 || j == 0 || k == 0 || l == 0 || m == 0 || n == 0 || o == 0 || p == 0 || q == 0) {// et si on a au moins un paramètre qui vaut 0 alors on a une erreur
												printf("Erreur dilatation retourne 255 quand un point de la matice 3x3 vaut 0\n");
												return 0;
											}

										}
										else if (dilatation3(i * 255, j * 255, k * 255, l * 255, m * 255, n * 255, o * 255, p * 255, q * 255) == 0) {//si la sortie vaut 0
											if (i == 1 && j == 1 && k == 1 && l == 1 && m == 1 && n == 1 && o == 1 && p == 1 && q == 1) {//et si on a tous les paramètres qui valent 1 alors on a une erreur												printf("Erreur errosion3 retourne 0 quand tous les points de la matice 3x3 valent 1\n");
												return 0;
											}
										}
										else {//si la valeur de retour est ni 0 ni 255 alors on a une erreur
											printf("Erreur dilatation retourne autre chose que 0 ou 255\n");
												return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 1;
}



//dilatation de carré de 5x5
void dilatation5(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch){
	int i, j, k, l;
	for(i=nrl+2; i<=nrh-2; i++) {
	    for(j=ncl+2; j<=nch-2; j++) {
	    	if(Et[i][j]==255){
	    		for(k=-2;k<3;k++){
		    		for(l=-2;l<3;l++){
		    			EtD[i+k][j+l]=255;
		    		}
		    	}
	    	}
	    }
  	}
}


uint8 erosion3(uint8 Et1, uint8 Et2, uint8 Et3, uint8 Et4, uint8 Et5, uint8 Et6, uint8 Et7, uint8 Et8, uint8 Et9) {
	int tmp;
	tmp = Et1;
	tmp += Et2;
	tmp += Et3;
	tmp += Et4;
	tmp += Et5;
	tmp += Et6;
	tmp += Et7;
	tmp += Et8;
	tmp += Et9;
	if (tmp == 9*255) {
		return 255;
	}
	else {
		return 0;
	}
}

//erosion de carré de 3x3
void erosion3_matrix(uint8 **EtE, uint8 **Et, long nrl, long nrh, long ncl, long nch) {
	int i, j;
	for (i = nrl + 1; i <= nrh - 1; i++) {
		for (j = ncl + 1; j <= nch - 1; j++) {
			EtE[i][j] = erosion3(Et[i - 1][j - 1], Et[i - 1][j], Et[i - 1][j + 1], Et[i][j - 1], Et[i][j], Et[i][j + 1], Et[i + 1][j - 1], Et[i + 1][j], Et[i + 1][j + 1]);
		}
	}
}



uint8 test_erosion3() {

	int i, j, k, l, m, n, o, p, q;
	//9 boucle traitant tous les cas possible des entrée de la fonction erosion3
	for (i = 0;i < 2;i++) {
		for (j = 0;j < 2;j++) {
			for (k = 0;k < 2;k++) {
				for (l = 0;l < 2;l++) {
					for (m = 0;m < 2;m++) {
						for (n = 0;n < 2;n++) {
							for (o = 0;o < 2;o++) {
								for (p = 0;p < 2;p++) {
									for (q = 0;q < 2;q++) {
										if (erosion3(i * 255, j * 255, k * 255, l * 255, m * 255, n * 255, o * 255, p * 255, q * 255) == 255) {//si la sortie vaut 255(equivalent a 1)
											if (i == 0 || j == 0 || k == 0 || l == 0 || m == 0 || n == 0 || o == 0 || p == 0 || q == 0) {// et si on a au moins un paramètre qui vaut 0 alors on a une erreur
												printf("Erreur erosion3 retourne 255 quand un point de la matice 3x3 vaut 0\n");
												return 0;
											}
											
										}
										else if(erosion3(i * 255, j * 255, k * 255, l * 255, m * 255, n * 255, o * 255, p * 255, q * 255) == 0){//si la sortie vaut 0
											if (i == 1 && j == 1 && k == 1 && l == 1 && m == 1 && n == 1 && o == 1 && p == 1 && q == 1) {//et si on a tous les paramètres qui valent 1 alors on a une erreur												printf("Erreur errosion3 retourne 0 quand tous les points de la matice 3x3 valent 1\n");
												return 0;
											}
										}
										else {//si la valeur de retour est ni 0 ni 255 alors on a une erreur
											printf("Erreur erosion3 retourne autre chose que 0 ou 255\n");
											return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

//erosion de carré de 5x5
void erosion5(uint8 **EtE, uint8 **Et, long nrl, long nrh, long ncl, long nch){
	int i, j, k, l;
	for(i=nrl+2; i<=nrh-2; i++) {
	    for(j=ncl+2; j<=nch-2; j++) {
	    	if(Et[i][j]==0){
	    		for(k=-2;k<3;k++){
		    		for(l=-2;l<3;l++){
		    			EtE[i+k][j+l]=0;
		    		}
		    	}
	    	}
	    }
  	}
}


//ouverture de carré 3x3
void ouverture3(uint8 **Et, long nrl, long nrh, long ncl, long nch){


	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	Copy(tmp,Et, nrl, nrh, ncl, nch);
	erosion3_matrix(tmp, Et, nrl, nrh, ncl, nch);

	Copy(Et,tmp,nrl, nrh, ncl, nch);
	dilatation3_matrix(Et, tmp,nrl, nrh, ncl, nch);

	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}

//ouverture de carré 5x5
void ouverture5(uint8 **Et, long nrl, long nrh, long ncl, long nch){
	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	Copy(tmp,Et, nrl, nrh, ncl, nch);
	erosion5(tmp, Et, nrl, nrh, ncl, nch);

	Copy(Et,tmp,nrl, nrh, ncl, nch);
	dilatation5(Et, tmp,nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}

//fermeture de carré 3x3
void fermeture3(uint8 **Et, long nrl, long nrh, long ncl, long nch){
	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	Copy(tmp,Et, nrl, nrh, ncl, nch);
	dilatation3_matrix(tmp, Et,nrl, nrh, ncl, nch);

	Copy(Et,tmp,nrl, nrh, ncl, nch);
	erosion3_matrix(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}

//fermeture de carré 5x5
void fermeture5(uint8 **Et, long nrl, long nrh, long ncl, long nch){
	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	Copy(tmp,Et, nrl, nrh, ncl, nch);
	dilatation5(tmp, Et,nrl, nrh, ncl, nch);

	Copy(Et,tmp,nrl, nrh, ncl, nch);
	erosion5(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}


//post traitement ouverture puis fermeture
void posTraitementOF(uint8 **Et, long nrl, long nrh, long ncl, long nch){

	ouverture3(Et,nrl, nrh, ncl, nch);
	fermeture3(Et,nrl, nrh, ncl, nch);

	ouverture5(Et,nrl, nrh, ncl, nch);
	fermeture5(Et,nrl, nrh, ncl, nch);
}

//post traitement fermeture puis ouverture
void posTraitementFO(uint8 **Et, long nrl, long nrh, long ncl, long nch){

	fermeture3(Et,nrl, nrh, ncl, nch);
	ouverture3(Et,nrl, nrh, ncl, nch);

	fermeture5(Et,nrl, nrh, ncl, nch);
	ouverture5(Et,nrl, nrh, ncl, nch);
}