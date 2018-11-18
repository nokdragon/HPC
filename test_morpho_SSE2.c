
#include "test_morpho_SSE2.h"
#include "SSE2util.h"
#include "mouvement.h"

#define B1 11 //bordure que l'on ne vérifie pas car le simd et le scalaire la traite différement : pas d'insidence sur les résultat car se que l'on détecte est relativement centré
#define B2 11 //bordure que l'on ne vérifie pas car le simd et le scalaire la traite différement : pas d'insidence sur les résultat car se que l'on détecte est relativement centré



int test_dilatation_erosion_SSE2() {
	PRINT_BEGIN();
	printf("Test comparant toutes les erosions faites en SSE2 de celle faite en scalaire sur 300 images\n");
	int i;
	long nrl, nrh, ncl, nch;
	int flag=0;
	uint8** It_1;
	char dir[255];
	sprintf(dir, image_directory, 0);
	It_1 = LoadPGM_ui8matrix(dir, &nrl, &nrh, &ncl, &nch);


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

	uint8 **Dref;
	Dref = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);

	uint8 **D;
	D = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);


	char file[255];



	for (i = 1; i<300; i++) {

		sprintf(file, image_directory, i);

		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		Frame_Difference_Matrix(It, It_1, Et, nrl, nrh, ncl, nch);

		dilatation3_matrix(D, Et, nrl, nrh, ncl, nch);
		dilatation3_matrix_SSE2(Dref, Et, nrl, nrh, ncl, nch);

		if(compare_matrix(Dref, D, nrl, nrh, ncl, nch)){
			printf("Erreur sur la dilatation3_matrix_SSE2 en testant avec FD\n");
			flag++;
		}


		erosion3_matrix(D, Et, nrl, nrh, ncl, nch);
		erosion3_matrix_SSE2(Dref, Et, nrl, nrh, ncl, nch);

		if(compare_matrix(Dref, D, nrl, nrh, ncl, nch)){
			printf("Erreur sur la erosion3_matrix_SSE2 en testant avec FD\n");
			flag++;
		}

		SD(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);

		dilatation3_matrix(D, Et, nrl, nrh, ncl, nch);
		dilatation3_matrix_SSE2(Dref, Et, nrl, nrh, ncl, nch);

		if(compare_matrix(Dref, D, nrl, nrh, ncl, nch)){
			printf("Erreur sur la dilatation3_matrix_SSE2 en testant avec SD\n");
			flag++;
		}

		erosion3_matrix(D, Et, nrl, nrh, ncl, nch);
		erosion3_matrix_SSE2(Dref, Et, nrl, nrh, ncl, nch);

		if(compare_matrix(Dref, D, nrl, nrh, ncl, nch)){
			printf("Erreur sur la erosion3_matrix_SSE2 en testant avec SD\n");
			flag++;
		}

		Copy(It_1, It, nrl, nrh, ncl, nch);
		Copy(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy(Vt_1, Vt, nrl, nrh, ncl, nch);

	}


	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Vt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(D, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Dref, nrl-2, nrh+2, ncl-2, nch+2);
	

	if(flag==0){
		PRINT_OK();
	}
	PRINT_END();

	return flag;

}

int test_morpho_SSE2() {

	PRINT_BEGIN();
	printf("Test comparant toutes les erosions faites en SSE2 de celle faite en scalaire sur 300 images\n");
	int i;
	long nrl, nrh, ncl, nch;
	int flag=0;
	uint8** It_1;
		char dir[255];
	sprintf(dir, image_directory, 0);
	It_1 = LoadPGM_ui8matrix(dir, &nrl, &nrh, &ncl, &nch);


	uint8** It;
	It = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Et;
	Et = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	Init_mat(Et, nrl-2, nrh+2, ncl-2, nch+2);

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

	uint8 **Dref;
	Dref = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	Init_mat(Dref, nrl-2, nrh+2, ncl-2, nch+2);

	uint8 **D;
	D = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	Init_mat(D, nrl-2, nrh+2, ncl-2, nch+2);


	char file[255];



	for (i = 1; i<300; i++) {

		sprintf(file, image_directory, i);

		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		Frame_Difference_Matrix(It, It_1, Et, nrl, nrh, ncl, nch);


		Copy_SSE2(D, Et, nrl, nrh, ncl, nch);

		Copy_SSE2(Dref, Et, nrl, nrh, ncl, nch);

		posTraitementOF(D, nrl, nrh, ncl, nch);


		posTraitementOF_SSE2(Dref, nrl, nrh, ncl, nch);

		if(compare_matrix(D, Dref, nrl+B1, nrh-B1, ncl+B1, nch-B1)){
			printf("Erreur sur la posTraitementOF_SSE2 en testant avec FD sur l'image %d\n",i);
			flag++;
		}


		Copy(D, Et, nrl-2, nrh+2, ncl-2, nch+2);

		Copy(Dref, Et, nrl-2, nrh+2, ncl-2, nch+2);

		posTraitementFO(D, nrl, nrh, ncl, nch);


		posTraitementFO_SSE2(Dref, nrl, nrh, ncl, nch);

		if(compare_matrix(D, Dref, nrl+B2, nrh-B2, ncl+B2, nch-B2)){
			printf("Erreur sur la posTraitementFO_SSE2 en testant avec FD sur l'image %d\n",i);
			flag++;
		}


		SD(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);

		

		Copy(D, Et, nrl-2, nrh+2, ncl-2, nch+2);

		Copy(Dref, Et, nrl-2, nrh+2, ncl-2, nch+2);

		posTraitementOF(D, nrl, nrh, ncl, nch);


		posTraitementOF_SSE2(Dref, nrl, nrh, ncl, nch);


		if(compare_matrix(D, Dref, nrl+B1, nrh-B1, ncl+B1, nch-B1)){
			printf("Erreur sur la posTraitementOF_SSE2 en testant avec SD sur l'image %d\n",i);
			flag++;
		}

		
		Copy(D, Et, nrl-2, nrh+2, ncl-2, nch+2);

		Copy(Dref, Et, nrl-2, nrh+2, ncl-2, nch+2);

		posTraitementFO(D, nrl, nrh, ncl, nch);


		posTraitementFO_SSE2(Dref, nrl, nrh, ncl, nch);


		sprintf(file, "hall_SD/ETC_SD%d.pgm", i*3);
		SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);


		sprintf(file, "hall_SD/ETC_SD%d.pgm", i*3+1);
		SavePGM_ui8matrix(D, nrl, nrh, ncl, nch, file);


		sprintf(file, "hall_SD/ETC_SD%d.pgm", i*3+2);
		SavePGM_ui8matrix(Dref, nrl, nrh, ncl, nch, file);



		if(compare_matrix(D, Dref, nrl+B2, nrh-B2, ncl+B2, nch-B2)){
			printf("Erreur sur la posTraitementFO_SSE2 en testant avec SD sur l'image %d\n",i);
			flag++;
		}
		
		Copy(It_1, It, nrl, nrh, ncl, nch);
		Copy(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy(Vt_1, Vt, nrl, nrh, ncl, nch);

	}


	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Vt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(D, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Dref, nrl-2, nrh+2, ncl-2, nch+2);
	

	if(flag==0){
		PRINT_OK();
	}
	PRINT_END();

	return flag;
}