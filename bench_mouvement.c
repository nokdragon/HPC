#include <time.h>
#include "mouvement.h"
#include "morpho_SSE2.h"
#include "bench_mouvement.h"
#include "SSE2util.h"


double chrono_FD_vide(int n){
	int it;

	double total_fd_vide;

	total_fd_vide = 0;

	struct timespec start, end;
	//######################################### initialisation de tous les paramètres #########################################
	int i;

	long nrl, nrh, ncl, nch;
	uint8** It_1;
		char dir[255];
	sprintf(dir, image_directory, 0);
	It_1 = LoadPGM_ui8matrix(dir, &nrl, &nrh, &ncl, &nch);

	uint8** It;
	It = ui8matrix(nrl, nrh, ncl, nch);

	char file[255];

	clock_gettime(CLOCK_MONOTONIC, &start);

	for(it=0;it<n;it++){
		

		//######################################### parcours de toutes les photos avec traitement FD #########################################

		
		for (i = 1; i < 300; i++) {

			sprintf(file, image_directory, i);

			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

			//######################################### Itération #########################################

			Copy_SSE2(It_1, It, nrl, nrh, ncl, nch);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	total_fd_vide = (end.tv_sec - start.tv_sec);
	total_fd_vide += (end.tv_nsec - start.tv_nsec) / 1000000000.0;


	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);

	return (double)(total_fd_vide/n);
}

double chrono_FD(int n){
	int it;

	double total_fd;

	total_fd = 0;

	struct timespec start, end;
	//######################################### initialisation de tous les paramètres #########################################
	int i;

	long nrl, nrh, ncl, nch;
	uint8** It_1;
		char dir[255];
	sprintf(dir, image_directory, 0);
	It_1 = LoadPGM_ui8matrix(dir, &nrl, &nrh, &ncl, &nch);

	uint8** It;
	It = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Et;
	Et = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);

	char file[255];

	clock_gettime(CLOCK_MONOTONIC, &start);

	for(it=0;it<n;it++){
		

		//######################################### parcours de toutes les photos avec traitement FD #########################################

		
		for (i = 1; i < 300; i++) {

			sprintf(file, image_directory, i);

			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

			//######################################### traitement fd #########################################


			Frame_Difference_Matrix(It, It_1, Et, nrl, nrh, ncl, nch);


			//######################################### Itération #########################################

			Copy_SSE2(It_1, It, nrl, nrh, ncl, nch);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	total_fd = (end.tv_sec - start.tv_sec);
	total_fd += (end.tv_nsec - start.tv_nsec) / 1000000000.0;


	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);

	return (double)(total_fd/n);
}


double chrono_SD_vide(int n){
	int it;

	double total_sd_vide;

	total_sd_vide = 0;

	struct timespec start, end;
	//######################################### initialisation de tous les paramètres #########################################
	int i;

	long nrl, nrh, ncl, nch;
	uint8** It_1;
		char dir[255];
	sprintf(dir, image_directory, 0);
	It_1 = LoadPGM_ui8matrix(dir, &nrl, &nrh, &ncl, &nch);

	uint8** It;
	It = ui8matrix(nrl, nrh, ncl, nch);


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

	clock_gettime(CLOCK_MONOTONIC, &start);

	for(it=0;it<n;it++){
		

		//######################################### parcours de toutes les photos avec traitement FD #########################################

		
		for (i = 1; i < 300; i++) {

			sprintf(file, image_directory, i);

			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);


			//######################################### Itération #########################################

			Copy_SSE2(It_1, It, nrl, nrh, ncl, nch);
			Copy_SSE2(Mt_1, Mt, nrl, nrh, ncl, nch);
			Copy_SSE2(Vt_1, Vt, nrl, nrh, ncl, nch);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	total_sd_vide = (end.tv_sec - start.tv_sec);
	total_sd_vide += (end.tv_nsec - start.tv_nsec) / 1000000000.0;


	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Vt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);

	return (double)(total_sd_vide/n);
}



double chrono_SD(int n){
	int it;

	double total_sd;

	total_sd = 0;

	struct timespec start, end;
	//######################################### initialisation de tous les paramètres #########################################
	int i;

	long nrl, nrh, ncl, nch;
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


	char file[255];

	clock_gettime(CLOCK_MONOTONIC, &start);

	for(it=0;it<n;it++){
		

		//######################################### parcours de toutes les photos avec traitement FD #########################################

		
		for (i = 1; i < 300; i++) {

			sprintf(file, image_directory, i);

			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

			//######################################### traitement sd #########################################


			SD(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);


			//######################################### Itération #########################################

			Copy_SSE2(It_1, It, nrl, nrh, ncl, nch);
			Copy_SSE2(Mt_1, Mt, nrl, nrh, ncl, nch);
			Copy_SSE2(Vt_1, Vt, nrl, nrh, ncl, nch);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	total_sd = (end.tv_sec - start.tv_sec);
	total_sd += (end.tv_nsec - start.tv_nsec) / 1000000000.0;


	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Vt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);

	return (double)(total_sd/n);
}