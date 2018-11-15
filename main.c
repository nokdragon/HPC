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


void remi()
{
	//test_vuint8_if_else();
	//test_vuint8_abs_simd();
	//test_vuint16_abs_simd();
	//test_vuint8_fd_simd();
	//test_vuint8_fd_simd_matrix(); // pas de seg fault
	//test_vuint8_if_elif_else();
	//test_ext_8_16();
	//test_part1_sd();
	//test_part2_sd();
	test_sd_simd();

	/*
	vuint8 a,b,x,y,z, one;
	one = init_vuint8(1);
	vuint8 pVt;//init_vuint8(3);
	vuint8 pVt_1 = init_vuint8(3);
	vuint8 pOt = init_vuint8(1);

	a = pVt_1;
	b = pOt;
	for (int j = 0; j < N -1; j++){
			b = _mm_adds_epu8(b, pOt);
		}
	x = _mm_sub_epi8(pVt_1, one);//Mt plus grand
	y = _mm_add_epi8(pVt_1, one);//Mt plus petit
	z = pVt_1;
	pVt = vuint8_if_elif_else(a, b, x, y ,z);
	display_vuint8(pVt_1, "%4.0x", "pVt_1= "); puts("\n");
	display_vuint8(pOt, "%4.0x", "pOt= "); puts("\n");
	display_vuint8(b, "%4.0x", "n*OT= "); puts("\n");
	display_vuint8(pVt, "%4.0x", "pVt= "); puts("\n");
	*/



	/*
			vuint8 * pOt = (vuint8 *) Ot[0];

	//vuint8 *pOt = (vuint8*) Ot[0];
	//uint8 *pIt = (vuint8*) It[0];
	//vuint8 *pIt_1 = (vuint8*) It_1[0];
	vuint8 *pEt = (vuint8 *) Et[0];
	vuint8 *pVt = (vuint8*) Vt[0];
	vuint8 *pVt_1 = (vuint8*) Vt_1[0];
	//vuint8 *pMt = (vuint8*) Mt[0];
	//vuint8 *pMt_1 = (vuint8*) Mt_1[0];
	//uint8 ** mb = ui8matrix(nrl,nrh,ncl,nch);

	vuint8 a,b,x,y,z, one;
	int i,j;
	one = init_vuint8(1);
	for (i = 0; i < NBE_VUINT8_IMAGE; i++)
	{
		a = pVt_1[i];
		b = pOt[i];
		for (j = 0; j < N; j++){
			b = _mm_adds_epu8(b, pOt[i]);
		}

		x = _mm_sub_epi8(pVt_1[i], one);//Mt plus grand
		y = _mm_add_epi8(pVt_1[i], one);//Mt plus petit
		z = pVt_1[i];
		pVt[i] = vuint8_if_elif_else(a, b, x, y ,z);
	*/


	/*
		//Initialisation
	int i;
	long nrl, nrh, ncl, nch;
	uint8** It_1;
	It_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);

	printf("nrl = %ld\n",nrl);
	printf("nrh = %ld\n",nrh);
	printf("ncl = %ld\n",ncl);
	printf("nch = %ld\n",nch);


	uint8** It;
	It = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Ot = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Et = ui8matrix(nrl, nrh, ncl, nch);


	char file[255];

	//uint8 **tmp;
	//tmp = ui8matrix(nrl, nrh, ncl, nch);

	for(i=1 ; i < 2 ; i++){

		sprintf(file,"hall/hall%06d.pgm",i);

		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		fd_simd_matrix(It, It_1, Ot, Et);

		display_ui8matrix(Et, nrl, nrh, ncl,  nch,  "%d ", "Et");


	}
	*/
	
}


void execution() {
	int i;
	long nrl, nrh, ncl, nch;
	uint8** It_1;
	It_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);

	printf("nrl = %ld\n", nrl);
	printf("nrh = %ld\n", nrh);
	printf("ncl = %ld\n", ncl);
	printf("nch = %ld\n", nch);


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

	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);


	for (i = 1; i<300; i++) {

		sprintf(file, "hall/hall%06d.pgm", i);

		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		Frame_Difference_Matrix(It, It_1, Et, nrl, nrh, ncl, nch);


		Copy(tmp, Et, nrl, nrh, ncl, nch);

		//posTraitementOF(Et, nrl, nrh, ncl, nch);
		sprintf(file, "hall_FD/ETOF_FD%d.pgm", i);
		SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);



		//posTraitementFO(tmp, nrl, nrh, ncl, nch);
		//sprintf(file,"hall_FD/ETFO_FD%d.pgm",i);
		//SavePGM_ui8matrix(tmp,nrl, nrh, ncl, nch,file);

		SD(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);

		sprintf(file, "hall_SD/ET_SD%d.pgm", i);
		//SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);



		Copy(tmp, Et, nrl, nrh, ncl, nch);



		posTraitementOF(Et, nrl, nrh, ncl, nch);
		sprintf(file, "hall_SD/ETC_SD%d.pgm", i);
		SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);


		/*
		posTraitementFO(tmp, nrl, nrh, ncl, nch);
		sprintf(file,"hall_SD/ETFO_SD%d.pgm",i);
		SavePGM_ui8matrix(tmp,nrl, nrh, ncl, nch,file);*/

		Copy(It_1, It, nrl, nrh, ncl, nch);
		Copy(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy(Vt_1, Vt, nrl, nrh, ncl, nch);
		//quand on bouclera et que les Images de viendront des Images_1 on fera:
		//free_ui8matrix(Images_1, nrl, nrh, ncl, nch);
		//Images_1=Images;
		//Images = ui8matrix(nrl, nrh, ncl, nch); marche pas mais a creuser

		//ou une copie faudra voir ce qui est le plus économe

	}
}

void cyprien()
{
	//validation();
	chrono();
	//execution();
	//test_dilatation_erosion_simd();
	//test_morpho_simd();
	
}

int main()
{
	//remi();
	cyprien();
}


