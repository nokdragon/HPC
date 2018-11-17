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
#include "bench_mouvement.h"

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


	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);

	return (double)(total_fd/n);
}

double chrono_FD_SSE2v2(int n){
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


			vuint8_fd_simd_matrixv2(It, It_1, Et, nrl, nrh, ncl, nch);



			//######################################### Itération #########################################

			Copy_simd(It_1, It, nrl, nrh, ncl, nch);
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

	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Vt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);

	return (double)(total_sd/n);
}

void bench_fd(int n, int nb_iterations)
{

	double fd_vide, fd, fd_SSE2;
	double res_fd, res_fd_sse2,fd_gain, fd_percent;
	fd_vide=chrono_FD_vide(n);

	for (int i = 0; i < nb_iterations; ++i)
	{
		// FD
		fd=chrono_FD(n);
		res_fd = fd-fd_vide;	
		//printf("FD: %f secs\n", res_fd);


		fd_SSE2=chrono_FD_SSE2(n);
		res_fd_sse2 = fd_SSE2-fd_vide;
		//printf("FD_SSE2: %f secs\n", res_fd_sse2);
		fd_gain = res_fd / res_fd_sse2;
		fd_percent = (res_fd - res_fd_sse2) * 100 / res_fd;
		printf("v1 : Gain = %f, réduction du temps d'execution = %f %%\n", fd_gain, fd_percent);

		fd_SSE2=chrono_FD_SSE2v2(n);
		res_fd_sse2 = fd_SSE2-fd_vide;
		fd_gain = res_fd / res_fd_sse2;
		fd_percent = (res_fd - res_fd_sse2) * 100 / res_fd;
		printf("v2 : Gain = %f, réduction du temps d'execution = %f %%\n", fd_gain, fd_percent);

		fd_vide=chrono_FD_SoAoS_vide(n);
		fd_SSE2=chrono_fd_SoAoS(n);
		res_fd_sse2 = fd_SSE2-fd_vide;
		fd_gain = res_fd / res_fd_sse2;
		fd_percent = (res_fd - res_fd_sse2) * 100 / res_fd;
		printf("v3 : Gain = %f, réduction du temps d'execution = %f %%\n", fd_gain, fd_percent);

		fd_vide=chrono_FD_SoAoS_vide(n);
		fd_SSE2=chrono_fd_SoAoSv2(n);
		res_fd_sse2 = fd_SSE2-fd_vide;
		fd_gain = res_fd / res_fd_sse2;
		fd_percent = (res_fd - res_fd_sse2) * 100 / res_fd;
		printf("v4 : Gain = %f, réduction du temps d'execution = %f %%\n", fd_gain, fd_percent);

		puts("\n");

	
	}
}

double chrono_fd_SoAoS(int n)
{

	int it;

	double total_fd;

	total_fd = 0;

	struct timespec start, end;
	//######################################### initialisation de tous les paramètres #########################################
	int i, lig ;

	long nrl, nrh, ncl, nch;
	uint8** It_moins_1;
	It_moins_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);

	uint8** It;
	It = ui8matrix(nrl, nrh, ncl, nch);

	uint8** It_plus_1;
	It_plus_1 = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Et;
	Et = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);

	uint8 **Et_plus_1;
	Et_plus_1 = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);

	char file[255];

	clock_gettime(CLOCK_MONOTONIC, &start);

	for(it=0;it<n;it++){
		

		//######################################### parcours de toutes les photos avec traitement FD #########################################

		//#pragma omp parallel for
		for (i = 1; i < NB_IMAGE - 1 ; i+=2) {

			sprintf(file, "hall/hall%06d.pgm", i);
			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

			sprintf(file, "hall/hall%06d.pgm", i+1);
			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It_plus_1);

			#pragma omp parallel for
			for(lig = 0;lig <= nrh; lig++){
			

			//######################################### traitement fd #########################################


			vuint8_fd_simd_row(It[lig], It_moins_1[lig], Et[lig], ncl, nch);
			vuint8_fd_simd_row(It_plus_1[lig], It[lig], Et_plus_1[lig], ncl, nch);


			//######################################### Itération #########################################

			}

			Copy_simd(It_moins_1, It, nrl, nrh, ncl, nch);
			Copy_simd(It, It_plus_1, nrl, nrh, ncl, nch);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	total_fd = (end.tv_sec - start.tv_sec);
	total_fd += (end.tv_nsec - start.tv_nsec) / 1000000000.0;


	/*
	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	*/

	return (double)(total_fd/n);
	
}



double chrono_FD_SoAoS_vide(int n)
{
	int it;

	double total_fd_vide;

	total_fd_vide = 0;

	struct timespec start, end;
	//######################################### initialisation de tous les paramètres #########################################
	int i, lig;

	long nrl, nrh, ncl, nch;
	uint8** It_moins_1;
	It_moins_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);

	uint8** It;
	It = ui8matrix(nrl, nrh, ncl, nch);

	uint8** It_plus_1;
	It_plus_1 = ui8matrix(nrl, nrh, ncl, nch);


	char file[255];

	clock_gettime(CLOCK_MONOTONIC, &start);

	for(it=0;it<n;it++){
		

		//######################################### parcours de toutes les photos avec traitement FD #########################################

		
		for (i = 1; i < NB_IMAGE - 1 ; i+=2) {

			sprintf(file, "hall/hall%06d.pgm", i);
			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

			sprintf(file, "hall/hall%06d.pgm", i+1);
			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It_plus_1);

			for(lig = 0;lig <= nrh; lig++){
			


			//######################################### Itération #########################################

			}

			Copy_simd(It_moins_1, It, nrl, nrh, ncl, nch);
			Copy_simd(It, It_plus_1, nrl, nrh, ncl, nch);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	total_fd_vide = (end.tv_sec - start.tv_sec);
	total_fd_vide += (end.tv_nsec - start.tv_nsec) / 1000000000.0;

	/*
	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	*/
	return (double)(total_fd_vide/n);
}

double chrono_fd_SoAoSv2(int n)
{

	int it;

	double total_fd;

	total_fd = 0;

	struct timespec start, end;
	//######################################### initialisation de tous les paramètres #########################################
	int i, lig, col ;

	long nrl, nrh, ncl, nch;
	uint8** It_moins_1;
	It_moins_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);

	uint8** It;
	It = ui8matrix(nrl, nrh, ncl, nch);

	uint8** It_plus_1;
	It_plus_1 = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Et;
	Et = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);

	uint8 **Et_plus_1;
	Et_plus_1 = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);


	vuint8 vIt, vIt_plus_1 , vIt_moins_1, vEt, vEt_plus_1;
	vEt = vEt_plus_1 =_mm_setzero_si128();

	char file[255];

	clock_gettime(CLOCK_MONOTONIC, &start);

	for(it=0;it<n;it++){		

		//######################################### parcours de toutes les photos avec traitement FD #########################################

		for (i = 1; i < NB_IMAGE - 1 ; i+=2) {

			sprintf(file, "hall/hall%06d.pgm", i);
			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

			sprintf(file, "hall/hall%06d.pgm", i+1);
			MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It_plus_1); 

			#pragma omp parallel for //change pas trop la vitesse du programme
			for(lig = 0;lig <= nrh; lig++){
				//#pragma omp parallel for // ralentit le programme
				for(col = 0; col <= nch; col+=16){

					vIt = _mm_loadu_si128((__m128i *)&It[lig][col]);
					vIt_plus_1 = _mm_loadu_si128((__m128i *)&It_plus_1[lig][col]);
					vIt_moins_1 = _mm_loadu_si128((__m128i *)&It_plus_1[lig][col]);

					vuint8_fd_simd_iteration(vIt, vIt_moins_1, vEt);
					vuint8_fd_simd_iteration(vIt_plus_1, vIt, vEt_plus_1);

					_mm_storeu_si128((__m128i *)&Et[lig][col], vEt);
					_mm_storeu_si128((__m128i *)&Et_plus_1[lig][col], vEt_plus_1);
					//vuint8_fd_simd_row(It[lig], It_moins_1[lig], Et[lig], ncl, nch);
					//vuint8_fd_simd_row(It_plus_1[lig], It[lig], Et_plus_1[lig], ncl, nch);

				}

			}

			Copy_simd(It_moins_1, It, nrl, nrh, ncl, nch);
			Copy_simd(It, It_plus_1, nrl, nrh, ncl, nch);
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	total_fd = (end.tv_sec - start.tv_sec);
	total_fd += (end.tv_nsec - start.tv_nsec) / 1000000000.0;


	/*
	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	*/

	return (double)(total_fd/n);
	
}