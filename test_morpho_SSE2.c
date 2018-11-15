
#include "test_morpho_SSE2.h"
#include "SSE2util.h"



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


	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(D, nrl, nrh, ncl, nch);
	free_ui8matrix(Dref, nrl, nrh, ncl, nch);

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


	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(D, nrl, nrh, ncl, nch);
	free_ui8matrix(Dref, nrl, nrh, ncl, nch);

	return compare_matrix2(Dref, D, nrl, nrh, ncl, nch);

}