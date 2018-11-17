#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include "mouvement.h"
#include "main.h"
#include "morpho.h"
#include "test_morpho_SSE2.h"
#include "SSE2util.h"
#include "test_mouvement_SSE2.h"
#include "mouvement_SSE2.h"
#include "test_mouvement.h"
#include "bench_mouvement.h"
#include "bench_mouvement_SSE2.h"
#include "bench_morpho.h"
#include "bench_morpho_SSE2.h"
#include "test_SSE2.h"
#include "test_mouvement.h"




void execution() {
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

	uint8 **Ot;
	Ot = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Mt_1;
	Mt_1 = ui8matrix(nrl, nrh, ncl, nch);

	Init_M(Mt_1, It_1, nrl, nrh, ncl, nch);


	char file[255];


	for (i = 1; i<300; i++) {

		sprintf(file, "hall/hall%06d.pgm", i);

		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		vuint8_fd_simd_matrix(It, It_1, Et, nrl,  nrh,  ncl, nch);



		posTraitementFO(Et, nrl, nrh, ncl, nch);
		sprintf(file, "hall_FD/ETFO_FD%d.pgm", i);
		SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);


		vuint8_sd_simd(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, Ot, nrl, nrh, ncl, nch);

		posTraitementOF(Et, nrl, nrh, ncl, nch);
		sprintf(file, "hall_SD/ETC_SD%d.pgm", i);
		SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);


		Copy_simd(It_1, It, nrl, nrh, ncl, nch);
		Copy_simd(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy_simd(Vt_1, Vt, nrl, nrh, ncl, nch);

	}

	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Vt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Ot, nrl, nrh, ncl, nch);
}

void chrono(int n){


	printf("copy :%f\n",chrono_copy(100));
	printf("copy_simd :%f reduction de  %f%%\n",chrono_copy_simd(100),(1-chrono_copy_simd(100)/chrono_copy(100))*100);





	double fd_vide,sd_vide,fd,sd,fd_SSE2,sd_SSE2,morpho_vide,morpho,morpho_SSE2;	
	fd_vide=chrono_FD_vide(n*n);
	sd_vide=chrono_SD_vide(n*n);
	morpho_vide=chrono_morpho_vide(n*n);

	// FD
	fd=chrono_FD(n);
	fd=fd-fd_vide;
	printf("FD: %f secs\n", fd);

	fd_SSE2=chrono_FD_SSE2(n);
	fd_SSE2=fd_SSE2-fd_vide;
	printf("FD_SSE2: %f secs : reduction de %f%%\n", fd_SSE2, (1-fd_SSE2/fd)*100);

	// SD
	sd=chrono_SD(n);
	sd=sd-sd_vide;
	printf("SD: %f secs\n", sd);	

	sd_SSE2=chrono_SD_SSE2(n);
	sd_SSE2=sd_SSE2-sd_vide;
	printf("SD_SSE2: %f secs : reduction de %f%%\n", sd_SSE2, (1-sd_SSE2/sd)*100);
	
	// morpho
	morpho=chrono_morpho(n);
	morpho=morpho-morpho_vide;
	printf("morpho %f secs\n", morpho);

	morpho_SSE2=chrono_morpho_SSE2(n);
	morpho_SSE2=morpho_SSE2-morpho_vide;
	printf("morpho_SSE2 %f secs : reduction de %f%%\n", morpho_SSE2, (1-morpho_SSE2/morpho)*100);
}


void test_tot(){
	test_vuint8_if_else();
	test_vuint8_if_elif_else();
	test_dilatation_erosion_simd();
	test_morpho_simd();
	test_erosion3();
	test_dilatation3();
	test_vuint8_fd_simd();
	test_vuint8_fd_simd_matrix();
	test_sd_simd();
}


void cyprien()
{
	test_tot();
	validation();
	chrono(10);
	execution();
	
	
}


void remi()
{	
	test_vuint8_if_else();
	//test_vuint8_abs_simd();
	//test_vuint16_abs_simd();
	test_vuint8_fd_simd();
	test_vuint8_fd_simd_matrix();
	test_vuint8_if_elif_else();
	//test_ext_8_16();
	//test_part1_sd();
	//test_part2_sd();
	test_sd_simd();
	//test_dilatation_erosion_simd(); // bug 
	//test_morpho_simd(); //bug
	//bench_fd(100, 30);
}


int main()
{
	//remi();
	cyprien();
}


