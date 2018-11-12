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
#include "test.h"


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



//ROC est un tableau de 4 int VP FN FP VN
void calculate_ROC(uint8 ** EtRef, uint8 ** Et, long nrl, long nrh, long ncl, long nch, int *ROC) {
	int i, j;
	for (i = nrl; i <= nrh; i++) {
		for (j = ncl; j <= nch; j++) {
			if (Et[i][j] == 0) {
				if (EtRef[i][j] == 0) {
					ROC[3]++;
				}
				else {
					ROC[1]++;
				}
			}
			else {
				if(EtRef[i][j] == 0){
					ROC[2]++;
				}
				else {
					ROC[0]++;
				}
			}
		}
	}

}