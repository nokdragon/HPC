#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include "traitement.h"
#include "main.h"
#include "post_traitement.h"
#include "simd1.h"
#include "test_simd.h"

#include <unistd.h>

int main(){

	/*===================REMI===================
	test_if_else();
	test_abs_simd();
	*/



	/*===================CYPRIEN===================*/
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

	uint8 **Ot;
	Ot = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Et;
	Et = ui8matrix(nrl, nrh, ncl, nch);

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
	
	
	for(i=1 ; i<300 ; i++){

		sprintf(file,"hall/hall%06d.pgm",i);

		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		Frame_Difference_Matrix(It, It_1, Ot, Et, nrl, nrh, ncl, nch);

		
		Copy(tmp, Et, nrl, nrh, ncl, nch);

		//posTraitementOF(Et, nrl, nrh, ncl, nch);
		sprintf(file,"hall_FD/ETOF_FD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);



		//posTraitementFO(tmp, nrl, nrh, ncl, nch);
		//sprintf(file,"hall_FD/ETFO_FD%d.pgm",i);
		//SavePGM_ui8matrix(tmp,nrl, nrh, ncl, nch,file);

		SD(It, It_1, Ot, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);

		sprintf(file,"hall_SD/ET_SD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);



		Copy(tmp, Et, nrl, nrh, ncl, nch);



		posTraitementOF(Et, nrl, nrh, ncl, nch);
		sprintf(file,"hall_SD/ETOF_SD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);



		posTraitementFO(tmp, nrl, nrh, ncl, nch);
		sprintf(file,"hall_SD/ETFO_SD%d.pgm",i);
		SavePGM_ui8matrix(tmp,nrl, nrh, ncl, nch,file);

		Copy(It_1, It, nrl, nrh, ncl, nch);
		Copy(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy(Vt_1, Vt, nrl, nrh, ncl, nch);



	}
	
}


//quand on bouclera et que les Images de viendront des Images_1 on fera:
//free_ui8matrix(Images_1, nrl, nrh, ncl, nch);
//Images_1=Images;
//Images = ui8matrix(nrl, nrh, ncl, nch); marche pas mais a creuser

//ou une copie faudra voir ce qui est le plus économe