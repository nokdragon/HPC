#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "main.h"
#include "mouvement.h"
#include "test_mouvement.h"
#include "morpho_SSE2.h"
#include "mouvement_SSE2.h"






//fonction de test unitaire de la fonction dilatation3. le test est exhaustif: il test toutes les entrées possible et vérifie que le résultat est bien celui escompté.
uint8 test_dilatation3() {
	PRINT_BEGIN();
	printf("test exhaustif\n");
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
											if (i == 0 && j == 0 && k == 0 && l == 0 && m == 0 && n == 0 && o == 0 && p == 0 && q == 0) {//et si on a tous les paramètres qui valent 0 alors on a une erreur
												printf("Erreur dilatation retourne 255 quand tous les points de la matice 3x3 valent 0\n");
												PRINT_END();
												return 1;
											}

										}
										else if (dilatation3(i * 255, j * 255, k * 255, l * 255, m * 255, n * 255, o * 255, p * 255, q * 255) == 0) {//si la sortie vaut 0
											if (i == 1 || j == 1 || k == 1 || l == 1 || m == 1 || n == 1 || o == 1 || p == 1 || q == 1) {// et si on a au moins un paramètre qui vaut 1 alors on a une erreur										printf("Erreur errosion3 retourne 0 quand tous les points de la matice 3x3 valent 1\n");
												printf("Erreur dilatation retourne 0 quand un point de la matice 3x3 vaut 1\n");
												PRINT_END();
												return 1;
											}
										}
										else {//si la valeur de retour est ni 0 ni 255 alors on a une erreur
											printf("Erreur dilatation retourne autre chose que 0 ou 255\n");
											PRINT_END();
											return 1;
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
	PRINT_OK();
	PRINT_END();
	return 0;
}



//fonction de test unitaire de la fonction erosion3. le test est exhaustif: il test toutes les entrées possible et vérifie que le résultat est bien celui escompté.
uint8 test_erosion3() {
	PRINT_BEGIN();
	printf("test exhaustif\n");
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
												PRINT_END();
												return 1;
											}
											
										}
										else if(erosion3(i * 255, j * 255, k * 255, l * 255, m * 255, n * 255, o * 255, p * 255, q * 255) == 0){//si la sortie vaut 0
											if (i == 1 && j == 1 && k == 1 && l == 1 && m == 1 && n == 1 && o == 1 && p == 1 && q == 1) {//et si on a tous les paramètres qui valent 1 alors on a une erreur												printf("Erreur errosion3 retourne 0 quand tous les points de la matice 3x3 valent 1\n");
												printf("Erreur dilatation retourne 255 quand tous les points de la matice 3x3 valent 1\n");
												PRINT_END();
												return 1;
											}
										}
										else {//si la valeur de retour est ni 0 ni 255 alors on a une erreur
											printf("Erreur erosion3 retourne autre chose que 0 ou 255\n");
											PRINT_END();
											return 1;
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
	PRINT_OK();
	PRINT_END();
	return 0;
}



//ROC est un tableau de 4 int VP FN FP VN
//cette focntion ajoute à la matrice ROC 1 dans la bonne case pour chaque pixel de la matrice Et. EtRef étant la référence
void calculate_ROC(uint8 ** EtRef, uint8 ** Et, long nrl, long nrh, long ncl, long nch, long * ROC) {
	int i, j;
	
	for (i = nrl; i <= nrh; i++) {
		for (j = ncl; j <= nch; j++) {
			if (Et[i][j] == 0) {
				if (EtRef[i][j] == 0) {//vrai négatif
					ROC[3]++;
				}
				else {//faux négatif
					ROC[1]++;
				}
			}
			else {
				if(EtRef[i][j] == 0){//faux positif
					ROC[2]++;
				}
				else {//vrai positif
					ROC[0]++;
				}
			}
		}
	}

}

//affichage de la matrice ROC
void print_ROC(long * ROC){
	printf("-----------------\n");
	printf("|%ld\t| %ld\t|\n",ROC[0],ROC[1]);
	printf("-----------------\n");
	printf("|%ld\t| %ld|\n",ROC[2],ROC[3]);
	printf("-----------------\n");
}

/*
Cette fonction execute le traitement et post traitement sur toutes les photos
 pour chaque photo appartenant à la liste des vérités terrain
 on calcule la matrice ROC de tout les cas possible (fd et sd avec et sans morpho)
 */
void validation(){


	//######################################### initialisation de tous les paramètres #########################################
	int i;

	long nrl, nrh, ncl, nch;
	uint8** It_1;
	It_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);

	uint8** It;
	It = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Et;
	Et = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);

	uint8 **Vt;
	Vt = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Vt_1;
	Vt_1 = ui8matrix(nrl, nrh, ncl, nch);

	Init_V(Vt_1, nrl, nrh, ncl, nch);

	uint8 **Mt;
	Mt = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Mt_1;
	Mt_1 = ui8matrix(nrl, nrh, ncl, nch);

	Init_M(Mt_1, It_1, nrl, nrh, ncl, nch);

	uint8** EtRef;
	EtRef = ui8matrix(nrl, nrh, ncl, nch);

	char file[255];

	//######################################### initialisation des matrices ROC #########################################

	long* ROC_FD;
	ROC_FD=(long *)malloc(4*sizeof(long));

	long* ROC_FD_P;
	ROC_FD_P=(long *)malloc(4*sizeof(long));

	long* ROC_SD;
	ROC_SD=(long *)malloc(4*sizeof(long));

	long* ROC_SD_P;
	ROC_SD_P=(long *)malloc(4*sizeof(long));

	long nbP=0;

	for(i=0;i<4;i++){
		ROC_FD[i]=0;
		ROC_SD[i]=0;
		ROC_FD_P[i]=0;
		ROC_SD_P[i]=0;
	}

	//######################################### parcours de toutes les photos #########################################

	for(i=1 ; i<300 ; i++){

		sprintf(file,"hall/hall%06d.pgm",i);

		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		//######################################### traitement fd #########################################
		

		Frame_Difference_Matrix(It, It_1, Et, nrl, nrh, ncl, nch);


		//######################################### test sur fd #########################################

		if((i % 20 == 4) && (i != 4) && (i<220)){//on teste uniquement quand la photo de vérité terrain existe
			nbP+=(nrh - nrl) * (nch - ncl);
			sprintf(file,"verite_terrain/hall%06d.pgm",i);//lecture de la vérité terrain

			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, EtRef);

			calculate_ROC(EtRef, Et, nrl, nrh, ncl, nch, ROC_FD);
		}

		//######################################### post traitement #########################################

		posTraitementFO(Et, nrl, nrh, ncl, nch);

		//######################################### test sur fd post traitement #########################################

		if(((i % 20 == 4) && (i != 4) && (i<220)) || ((i % 20 == 0) && (i > 200) && (i<300))){//on teste uniquement quand la photo de vérité terrain existe
			calculate_ROC(EtRef, Et, nrl, nrh, ncl, nch, ROC_FD_P);
		}

		//######################################### traitement sd #########################################
		
		SD(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);

		//######################################### test sur sd #########################################

		if(((i % 20 == 4) && (i != 4) && (i<220)) || ((i % 20 == 0) && (i > 200) && (i<300))){//on teste uniquement quand la photo de vérité terrain existe
			calculate_ROC(EtRef, Et, nrl, nrh, ncl, nch, ROC_SD);
		}

		//######################################### post traitement #########################################

		posTraitementOF(Et, nrl, nrh, ncl, nch);

		//######################################### test sur sd post traitement #########################################

		if(((i % 20 == 4) && (i != 4) && (i<220)) || ((i % 20 == 0) && (i > 200) && (i<300))){//on teste uniquement quand la photo de vérité terrain existe
			calculate_ROC(EtRef, Et, nrl, nrh, ncl, nch, ROC_SD_P);
		}

		//######################################### Itération #########################################

		Copy(It_1, It, nrl, nrh, ncl, nch);
		Copy(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy(Vt_1, Vt, nrl, nrh, ncl, nch);
	}

	//######################################### Affichage des résultats #########################################
	printf("-----------------\n");
	printf("|   VP  |   FN  |\n");
	printf("-----------------\n");
	printf("|   FP  |   VN  |\n");
	printf("-----------------\n");

	printf("Nb de pixel total: %ld\n", nbP);

	printf("ROC de fd\n");
	print_ROC(ROC_FD);

	printf("\nROC de fd avec post traitement\n");
	print_ROC(ROC_FD_P);

	printf("\n\nROC de sd\n");
	print_ROC(ROC_SD);

	printf("\nROC de sd avec post traitement\n");
	print_ROC(ROC_SD_P);

	free(ROC_FD);
	free(ROC_SD);
	free(ROC_FD_P);
	free(ROC_SD_P);
	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Vt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(EtRef, nrl, nrh, ncl, nch);
}

