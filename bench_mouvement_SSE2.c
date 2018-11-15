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
#include "morpho_SSE2.h"
#include "SSE2util.h"
#include "mouvement_SSE2.h"
#include "bench_mouvement_SSE2.h"



double chrono_FD_SSE2(int n){
	int it;

	double total_fd;

	total_fd = 0;

	struct timespec start, end;
	//######################################### initialisation de tous les paramètres #########################################
	int i;

	long nrl, nrh, ncl, nch;
	uint8** It_1;
	It_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);

	uint8** It;
	It = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Et;
	Et = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);

	char file[255];

	clock_gettime(CLOCK_MONOTONIC, &start);

	for(it=0;it<n;it++){
		

		//######################################### parcours de toutes les photos avec traitement FD #########################################

		
		for (i = 1; i < 300; i++) {

			sprintf(file, "hall/hall%06d.pgm", i);

			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

			//######################################### traitement fd #########################################


			vuint8_fd_simd_matrix(It, It_1, Et, nrl, nrh, ncl, nch);



			//######################################### Itération #########################################

			Copy_simd(It_1, It, nrl, nrh, ncl, nch);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	total_fd = (end.tv_sec - start.tv_sec);
	total_fd += (end.tv_nsec - start.tv_nsec) / 1000000000.0;

	return (double)(total_fd/n);
}


double chrono_SD_SSE2(int n){
	int it;

	double total_sd;

	total_sd = 0;

	struct timespec start, end;
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


	uint8 **Ot;
	Ot = ui8matrix(nrl, nrh, ncl, nch);


	char file[255];

	clock_gettime(CLOCK_MONOTONIC, &start);

	for(it=0;it<n;it++){
		

		//######################################### parcours de toutes les photos avec traitement FD #########################################

		
		for (i = 1; i < 300; i++) {

			sprintf(file, "hall/hall%06d.pgm", i);

			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

			//######################################### traitement sd #########################################


			vuint8_sd_simd(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, Ot, nrl, nrh, ncl, nch);


			//######################################### Itération #########################################

			Copy_simd(It_1, It, nrl, nrh, ncl, nch);
			Copy_simd(Mt_1, Mt, nrl, nrh, ncl, nch);
			Copy_simd(Vt_1, Vt, nrl, nrh, ncl, nch);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	total_sd = (end.tv_sec - start.tv_sec);
	total_sd += (end.tv_nsec - start.tv_nsec) / 1000000000.0;

	return (double)(total_sd/n);
}
