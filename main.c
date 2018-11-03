#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"


#define THETA 40 //séparateur de FD

#define VMIN 1
#define VMAX 254

#define N 3.5


//ui8matrix(long nrl, long nrh, long ncl, long nch)
//uint8 **m;
//m = ui8matrix(*nrl, *nrh, *ncl, *nch);

//void SavePGM_ui8matrix(uint8 **m, long nrl, long nrh, long ncl, long nch, char *filename)




//fonction Frame Difference (FD) 
/*It est la matrice de l'image courante (a l'instant t)
It_1 est la matrice a l'instant t-1
Ot est l'image de diférence en niveau de gris
Et est l'image d'etiquette binaire jai mis ou 255 comme ca on peut le mettre en image
nrl est la première que l'on va traiter
nrh est la dernière que l'on va traiter
ncl est la première colone que l'on va traiter
nch est la dernière colone que l'on va traiter
dans notre cas on a : nrl = ncl = 0 nrh = 239 nch = 351 pour prendre toute l'image
*/
void FD(uint8 **It, uint8 **It_1, uint8 **Ot, uint8 **Et, long nrl, long nrh, long ncl, long nch){
	long i,j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
	    	Ot[i][j]=abs( It[i][j] - It_1[i][j] );
	    	if(Ot[i][j] < THETA){
	    		Et[i][j]=0;
	    	}
	    	else{
	    		Et[i][j]=255;
	    	}
	    }
  	}
}


//fonction Sigma-Delta (SD) 
/*It est la matrice de l'image courante (a l'instant t)
It_1 est la matrice a l'instant t-1
Ot est l'image de diférence en niveau de gris
Et est l'image d'etiquette binaire jai mis ou 255 comme ca on peut le mettre en image
Mt est l'image de fond (image moyenne) à l'instant t
Mt_1 est l'image de fond (image moyenne) à l'instant t-1
Vt est l'image de variance (ecart type) à l'instant t
Vt_1 est l'image de variance (ecart type) à l'instant t-1
nrl est la première que l'on va traiter
nrh est la dernière que l'on va traiter
ncl est la première colone que l'on va traiter
nch est la dernière colone que l'on va traiter
dans notre cas on a : nrl = ncl = 0 nrh = 239 nch = 351 pour prendre toute l'image
*/
void SD(uint8 **It, uint8 **It_1, uint8 **Ot, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, long nrl, long nrh, long ncl, long nch){
	long i,j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {

	    	if(Mt_1[i][j]<It[i][j]){
	    		Mt[i][j] = Mt_1[i][j] + 1;
	    	}
	    	else if(Mt_1[i][j]>It[i][j]){
	    		Mt[i][j] = Mt_1[i][j] - 1;
	    	}
	    	else{
	    		Mt[i][j] = Mt_1[i][j];
	    	}

	    	Ot[i][j]=abs( Mt[i][j] - It[i][j] );

	    	if(Vt_1[i][j] < N * Ot[i][j]){
	    		Vt[i][j] = Vt_1[i][j] + 1;
	    	}
	    	else if(Vt_1[i][j] > N * Ot[i][j]){
	    		Vt[i][j] = Vt_1[i][j] - 1;
	    	}
	    	else{
	    		Vt[i][j] = Vt_1[i][j];
	    	}

	    	if(Vt[i][j]<VMIN){
	    		Vt[i][j]=VMIN;
	    	}
	    	else if(Vt[i][j]>VMAX){
	    		Vt[i][j]=VMAX;
	    	}

	    	if(Ot[i][j] < Vt[i][j]){
	    		Et[i][j]=0;
	    	}
	    	else{
	    		Et[i][j]=255;
	    	}
	    }
  	}
}

//cette fonction initialisela matrice Mt avec It
void Init_M(uint8 **Mt, uint8 **It, long nrl, long nrh, long ncl, long nch){
	int i, j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
	    	Mt[i][j]=It[i][j];
	    }
  	}
}

//cette fonction initialisela matrice Vt à VMIN
void Init_V(uint8 **Vt, long nrl, long nrh, long ncl, long nch){
	int i, j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
	    	Vt[i][j]=VMIN;
	    }
  	}
}


void Copy(uint8 **Mt, uint8 **It, long nrl, long nrh, long ncl, long nch){
	int i, j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
	    	Mt[i][j]=It[i][j];
	    }
  	}
}

int main(){
	


/*
	long nrl, nrh, ncl, nch;
	uint8** m_1;
	m_1 = LoadPGM_ui8matrix("hall/hall000024.pgm", &nrl, &nrh, &ncl, &nch);

	uint8** m;
	m = LoadPGM_ui8matrix("hall/hall000025.pgm", &nrl, &nrh, &ncl, &nch);

	uint8 **Ot;
	Ot = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Et;
	Et = ui8matrix(nrl, nrh, ncl, nch);

	FD(m, m_1, Ot, Et, nrl, nrh, ncl, nch);

	SavePGM_ui8matrix(Ot,nrl, nrh, ncl, nch,"hall_FD/OT_FD.pgm");
	SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,"hall_FD/ET_FD.pgm");

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

	

	SD(m, m_1, Ot, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);

	SavePGM_ui8matrix(Ot,nrl, nrh, ncl, nch,"hall_SD/OT_SD.pgm");
	SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,"hall_SD/ET_SD.pgm");
	SavePGM_ui8matrix(Mt,nrl, nrh, ncl, nch,"hall_SD/MT_SD.pgm");
	SavePGM_ui8matrix(Vt,nrl, nrh, ncl, nch,"hall_SD/VT_SD.pgm");
*/


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


		sprintf(file,"hall/hall%6d.pgm",i);
		char c;
		int j=8;
		c= file[j];
		while(c!='.'){
			if (file[j]==' '){
				file[j]='0';
			}
			j++;
			c= file[j];
		}

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