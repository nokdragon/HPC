#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "traitement.h"
#include "main.h"

int main(){

	//Initialisation 
	int i;
	long nrl, nrh, ncl, nch;
	uint8** m;
	uint8** m_1;
	m_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);
	
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
	Init_M(Mt_1, m_1, nrl, nrh, ncl, nch);


	char file[STR_SIZE]; // current filename

	for(i=1;i<NB_IMAGE;i++){

		sprintf(file,"hall/hall%06d.pgm",i);

		m = LoadPGM_ui8matrix(file, &nrl, &nrh, &ncl, &nch);

		FD(m, m_1, Ot, Et, nrl, nrh, ncl, nch);

		sprintf(file,"hall_FD/OT_FD%d.pgm",i);
		SavePGM_ui8matrix(Ot,nrl, nrh, ncl, nch,file);
		sprintf(file,"hall_FD/ET_FD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);

		SD(m, m_1, Ot, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);


		sprintf(file,"hall_SD/OT_SD%d.pgm",i);
		SavePGM_ui8matrix(Ot,nrl, nrh, ncl, nch, file);
		sprintf(file,"hall_SD/ET_SD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);
		sprintf(file,"hall_SD/MT_SD%d.pgm",i);
		SavePGM_ui8matrix(Mt,nrl, nrh, ncl, nch,file);
		sprintf(file,"hall_SD/VT_SD%d.pgm",i);
		SavePGM_ui8matrix(Vt,nrl, nrh, ncl, nch,file);

		Copy(m_1, m, nrl, nrh, ncl, nch);
		Copy(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy(Vt_1, Vt, nrl, nrh, ncl, nch);


	}
}