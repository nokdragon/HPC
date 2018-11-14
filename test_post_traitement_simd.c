
#include "test_post_traitement_simd.h"


int compare_matrix2(uint8 ** m1, uint8 ** m2, long nrl, long nrh, long ncl, long nch)
{

	long i, j, cpt;
	cpt = 0;
	for (i = nrl; i <= nrh; i++) {
		for (j = ncl; j <= nch; j++) {
			if (m1[i][j] != m2[i][j]) {
				cpt++;

				printf("m1[%ld][%ld] != m2[%ld][%ld]\n", i, j, i, j);
				//printf("%d != %d\n\n", m1[i][j], m2[i][j]);
				//return 1;
			}

		}
	}

	//printf("il y a %ld erreurs\n", cpt);

	if (cpt) {
		printf("il y a %ld erreurs\n", cpt);
		return 1;
	}
	PRINT_OK();
	return 0;
}

int test_dilatation_erosion_simd() {
	long nrl, nrh, ncl, nch;
	uint8** It_1;
	It_1 = LoadPGM_ui8matrix("hall/hall000024.pgm", &nrl, &nrh, &ncl, &nch);


	uint8** It;
	It = LoadPGM_ui8matrix("hall/hall000025.pgm", &nrl, &nrh, &ncl, &nch);

	uint8 **Et;
	Et = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);

	Frame_Difference_Matrix(It, It_1, Et, nrl, nrh, ncl, nch);

	uint8 **D;
	D = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Dref;
	Dref = ui8matrix(nrl, nrh, ncl, nch);

	dilatation3_matrix(D, Et, nrl, nrh, ncl, nch);
	dilatation3_matrix_simd(Dref, Et, nrl, nrh, ncl, nch);

	char file[255];
	sprintf(file, "hall_SD/%d.pgm", 0);
	SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);

	sprintf(file, "hall_SD/%d.pgm", 1);
	SavePGM_ui8matrix(D, nrl, nrh, ncl, nch, file);

	sprintf(file, "hall_SD/%d.pgm", 2);
	SavePGM_ui8matrix(Dref, nrl, nrh, ncl, nch, file);

	compare_matrix2(Dref, D, nrl, nrh, ncl, nch);

	erosion3_matrix(D, Et, nrl, nrh, ncl, nch);
	erosion3_matrix_simd(Dref, Et, nrl, nrh, ncl, nch);

	sprintf(file, "hall_SD/%d.pgm", 3);
	SavePGM_ui8matrix(D, nrl, nrh, ncl, nch, file);

	sprintf(file, "hall_SD/%d.pgm", 4);
	SavePGM_ui8matrix(Dref, nrl, nrh, ncl, nch, file);

	return compare_matrix2(Dref, D, nrl, nrh, ncl, nch);

}

int test_morpho_simd() {
	long nrl, nrh, ncl, nch;
	uint8** It_1;
	It_1 = LoadPGM_ui8matrix("hall/hall000024.pgm", &nrl, &nrh, &ncl, &nch);


	uint8** It;
	It = LoadPGM_ui8matrix("hall/hall000025.pgm", &nrl, &nrh, &ncl, &nch);

	uint8 **Et;
	Et = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);

	Frame_Difference_Matrix(It, It_1, Et, nrl, nrh, ncl, nch);

	uint8 **D;
	D = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);

	uint8 **Dref;
	Dref = ui8matrix(nrl - 2, nrh + 2, ncl - 2, nch + 2);

	Copy(D, Et, nrl, nrh, ncl, nch);

	posTraitementOF_simd(D, nrl, nrh, ncl, nch);

	Copy(Dref, Et, nrl, nrh, ncl, nch);

	posTraitementOF_simd(Dref, nrl, nrh, ncl, nch);

	char file[255];
	sprintf(file, "hall_SD/%d.pgm", 0);
	SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);

	sprintf(file, "hall_SD/%d.pgm", 1);
	SavePGM_ui8matrix(D, nrl, nrh, ncl, nch, file);

	sprintf(file, "hall_SD/%d.pgm", 2);
	SavePGM_ui8matrix(Dref, nrl, nrh, ncl, nch, file);

	compare_matrix2(Dref, D, nrl, nrh, ncl, nch);

	Copy(D, Et, nrl, nrh, ncl, nch);

	posTraitementFO_simd(D, nrl, nrh, ncl, nch);

	Copy(Dref, Et, nrl, nrh, ncl, nch);

	posTraitementFO_simd(Dref, nrl, nrh, ncl, nch);

	sprintf(file, "hall_SD/%d.pgm", 3);
	SavePGM_ui8matrix(D, nrl, nrh, ncl, nch, file);

	sprintf(file, "hall_SD/%d.pgm", 4);
	SavePGM_ui8matrix(Dref, nrl, nrh, ncl, nch, file);

	return compare_matrix2(Dref, D, nrl, nrh, ncl, nch);

}