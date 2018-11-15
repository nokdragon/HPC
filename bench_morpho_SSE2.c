#include <time.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "nrdef.h"

#include "mouvement.h"
#include "SSE2util.h"
#include "morpho_SSE2.h"
#include "bench_morpho_SSE2.h"

double chrono_morpho_SSE2(int n){

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


	char file[255];


	for (i = 1; i<300; i++) {

		sprintf(file, "hall/hall%06d.pgm", i);

		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

	
		SD(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);

		sprintf(file, "hall_SD/ET_SD%d.pgm", i);
		SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);

		Copy(It_1, It, nrl, nrh, ncl, nch);
		Copy(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy(Vt_1, Vt, nrl, nrh, ncl, nch);
	}


	int it;

	double total_morpho_SSE2;

	total_morpho_SSE2 = 0;

	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start);

	for(it=0;it<n;it++){
		

		//######################################### parcours de toutes les photos #########################################

		
		for (i = 1; i < 300; i++) {

			sprintf(file, "hall_SD/ET_SD%d.pgm", i);

			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, Et);

			//######################################### morpho #########################################


			posTraitementOF_simd(Et, nrl, nrh, ncl, nch);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	total_morpho_SSE2 = (end.tv_sec - start.tv_sec);
	total_morpho_SSE2 += (end.tv_nsec - start.tv_nsec) / 1000000000.0;


	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Vt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);

	return (double)(total_morpho_SSE2/n);
}