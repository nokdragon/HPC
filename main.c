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

#define THETA 40 //séparateur de FD

#define VMIN 1
#define VMAX 254

#define N 3.5


//ui8matrix(long nrl, long nrh, long ncl, long nch)
//uint8 **m;
//m = ui8matrix(*nrl, *nrh, *ncl, *nch);

//void SavePGM_ui8matrix(uint8 **m, long nrl, long nrh, long ncl, long nch, char *filename)


//dilatation de carré de 3x3
void dilatation3(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch){
	int i, j, k, l;
	for(i=nrl+1; i<=nrh-1; i++) {
	    for(j=ncl+1; j<=nch-1; j++) {
	    	if(Et[i][j]==255){
	    		for(k=-1;k<2;k++){
		    		for(l=-1;l<2;l++){
		    			EtD[i+k][j+l]=255;
		    		}
		    	}
	    	}
	    }
  	}
}

//dilatation de carré de 5x5
void dilatation5(uint8 **EtD, uint8 **Et, long nrl, long nrh, long ncl, long nch){
	int i, j, k, l;
	for(i=nrl+2; i<=nrh-2; i++) {
	    for(j=ncl+2; j<=nch-2; j++) {
	    	if(Et[i][j]==255){
	    		for(k=-2;k<3;k++){
		    		for(l=-2;l<3;l++){
		    			EtD[i+k][j+l]=255;
		    		}
		    	}
	    	}
	    }
  	}
}

//erosion de carré de 3x3
void erosion3(uint8 **EtE, uint8 **Et, long nrl, long nrh, long ncl, long nch){
	int i, j, k, l;
	for(i=nrl+1; i<=nrh-1; i++) {
	    for(j=ncl+1; j<=nch-1; j++) {
	    	if(Et[i][j]==0){
	    		for(k=-1;k<2;k++){
		    		for(l=-1;l<2;l++){
		    			EtE[i+k][j+l]=0;
		    		}
		    	}
	    	}
	    }
  	}
}

//erosion de carré de 5x5
void erosion5(uint8 **EtE, uint8 **Et, long nrl, long nrh, long ncl, long nch){
	int i, j, k, l;
	for(i=nrl+2; i<=nrh-2; i++) {
	    for(j=ncl+2; j<=nch-2; j++) {
	    	if(Et[i][j]==0){
	    		for(k=-2;k<3;k++){
		    		for(l=-2;l<3;l++){
		    			EtE[i+k][j+l]=0;
		    		}
		    	}
	    	}
	    }
  	}
}

int frame;


//ouverture de carré 3x3
void ouverture3(uint8 **Et, long nrl, long nrh, long ncl, long nch){

	char file[255];

	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);

	sprintf(file,"hall_SD/ET_SD%d.pgm",frame);
	SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);

	erosion3(tmp, Et, nrl, nrh, ncl, nch);

	sprintf(file,"hall_SD/ETe_SD%d.pgm",frame);
	SavePGM_ui8matrix(tmp,nrl, nrh, ncl, nch,file);

	dilatation3(Et, tmp,nrl, nrh, ncl, nch);

	sprintf(file,"hall_SD/ETz_SD%d.pgm",frame);
	SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);

	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
	//teqsbhdi
}

//ouverture de carré 5x5
void ouverture5(uint8 **Et, long nrl, long nrh, long ncl, long nch){
	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	erosion5(tmp, Et, nrl, nrh, ncl, nch);
	dilatation5(Et, tmp,nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}

//fermeture de carré 3x3
void fermeture3(uint8 **Et, long nrl, long nrh, long ncl, long nch){
	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	dilatation3(tmp, Et,nrl, nrh, ncl, nch);
	erosion3(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}

//fermeture de carré 5x5
void fermeture5(uint8 **Et, long nrl, long nrh, long ncl, long nch){
	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	dilatation5(tmp, Et,nrl, nrh, ncl, nch);
	erosion5(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}


//post traitement ouverture puis fermeture
void posTraitementOF(uint8 **Et, long nrl, long nrh, long ncl, long nch){

	char file[255];

	sprintf(file,"hall_SD/ET_SD%d.pgm",frame);
	//SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);
	ouverture3(Et,nrl, nrh, ncl, nch);
	sprintf(file,"hall_SD/ETO_SD%d.pgm",frame);
	//SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);
	fermeture3(Et,nrl, nrh, ncl, nch);

	ouverture5(Et,nrl, nrh, ncl, nch);
	fermeture5(Et,nrl, nrh, ncl, nch);
}

//post traitement fermeture puis ouverture
void posTraitementFO(uint8 **Et, long nrl, long nrh, long ncl, long nch){

	fermeture3(Et,nrl, nrh, ncl, nch);
	ouverture3(Et,nrl, nrh, ncl, nch);

	fermeture5(Et,nrl, nrh, ncl, nch);
	ouverture5(Et,nrl, nrh, ncl, nch);
}



int main(){
	
	int i;
	long nrl, nrh, ncl, nch;
	uint8** m_1;
	m_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);

	uint8** m;

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


	char file[255];
	for(i=1;i<300;i++){
		frame=i;

		sprintf(file,"hall/hall%06d.pgm",i);

		m = LoadPGM_ui8matrix(file, &nrl, &nrh, &ncl, &nch);

		FD(m, m_1, Ot, Et, nrl, nrh, ncl, nch);

		sprintf(file,"hall_FD/OT_FD%d.pgm",i);
		SavePGM_ui8matrix(Ot,nrl, nrh, ncl, nch,file);
		sprintf(file,"hall_FD/ET_FD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);

		SD(m, m_1, Ot, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);

		/*
		sprintf(file,"hall_SD/OT_SD%d.pgm",i);
		SavePGM_ui8matrix(Ot,nrl, nrh, ncl, nch, file);
		sprintf(file,"hall_SD/ET_SD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);
		sprintf(file,"hall_SD/MT_SD%d.pgm",i);
		SavePGM_ui8matrix(Mt,nrl, nrh, ncl, nch,file);
		sprintf(file,"hall_SD/VT_SD%d.pgm",i);
		SavePGM_ui8matrix(Vt,nrl, nrh, ncl, nch,file);*/

		posTraitementOF(Et, nrl, nrh, ncl, nch);
		//sprintf(file,"hall_SD/ETOF_SD%d.pgm",i);
		//SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);

		posTraitementFO(Et, nrl, nrh, ncl, nch);
		//sprintf(file,"hall_SD/ETFO_SD%d.pgm",i);
		//SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);

		Copy(m_1, m, nrl, nrh, ncl, nch);
		Copy(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy(Vt_1, Vt, nrl, nrh, ncl, nch);


	}

	/*printf("*nrl = %ld\n", nrl);
  	printf("*nrh = %ld\n", nrh);
  	printf("*ncl = %ld\n", ncl);
  	printf("*nch = %ld\n", nch);

	printf("m00 = %d\n", m[0][0]);
	printf("m01 = %d\n", m[25][351]);

	display_ui8matrix(m, nrl, nrh, ncl, nch, "%d ", "Patate");
*/

}


//quand on bouclera et que les Images de viendront des Images_1 on fera:
//free_ui8matrix(Images_1, nrl, nrh, ncl, nch);
//Images_1=Images;
//Images = ui8matrix(nrl, nrh, ncl, nch); marche pas mais a creuser

//ou une copie faudra voir ce qui est le plus économe