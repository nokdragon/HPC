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

//Paramètre de FD
#define THETA 40 

//Paramètres de SD
#define VMIN 1
#define VMAX 254
#define N 3.5

//fonction Frame Difference (FD) 
/*It est la matrice de l'image courante (a l'instant t)
It_1 est la matrice a l'instant t-1
Ot est l'image de différence en niveau de gris
Et est l'image d'etiquette binaire. {0,255} <=> {fond,mouvement}
nrl et nrh : premiere et derniere ligne
ncl et nch : premiere et derniere colonne
dans notre cas on a : nrl = ncl = 0 nrh = 239 nch = 351 pour prendre toute l'image
*/
void FD(uint8 **It, uint8 **It_1, uint8 **Ot, uint8 **Et, long nrl, long nrh, long ncl, long nch)
{
	long i,j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
	    	Ot[i][j] = abs(It[i][j] - It_1[i][j]);
	    	if(Ot[i][j] < THETA){
	    		Et[i][j]=0;
	    	}
	    	else{
	    		Et[i][j]=255;
	    	}
	    }
  	}
}


void create_FD_folder()
{
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

	char file[STR_SIZE]; // current filename

	for(i=1;i<NB_IMAGE;i++){

		sprintf(file,"hall/hall%06d.pgm",i);

		m = LoadPGM_ui8matrix(file, &nrl, &nrh, &ncl, &nch);

		FD(m, m_1, Ot, Et, nrl, nrh, ncl, nch);

		sprintf(file,"hall_FD/OT_FD%d.pgm",i);
		SavePGM_ui8matrix(Ot,nrl, nrh, ncl, nch,file);
		sprintf(file,"hall_FD/ET_FD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);
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
nrl et nrh : premiere et derniere ligne
ncl et nch : premiere et derniere colonne
dans notre cas on a : nrl = ncl = 0 nrh = 239 nch = 351 pour prendre toute l'image
*/
void SD(uint8 **It, uint8 **It_1, uint8 **Ot, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, long nrl, long nrh, long ncl, long nch)
{
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

//Initialise la matrice Mt avec It
void Init_M(uint8 **Mt, uint8 **It, long nrl, long nrh, long ncl, long nch)
{
	int i, j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
	    	Mt[i][j]=It[i][j];
	    }
  	}
}

//Initialise la matrice Vt à VMIN
void Init_V(uint8 **Vt, long nrl, long nrh, long ncl, long nch)
{
	int i, j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
	    	Vt[i][j]=VMIN;
	    }
  	}
}


//Copie It dans Mt
void Copy(uint8 **Mt, uint8 **It, long nrl, long nrh, long ncl, long nch)
{
	int i, j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
	    	Mt[i][j]=It[i][j];
	    }
  	}
}