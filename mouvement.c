#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mouvement.h"
#include "main.h"

#include "vnrdef.h"
#include "vnrutil.h"
#include "SSE2util.h"

//fonction Frame Difference (FD) 
/*It est la matrice de l'image courante (a l'instant t)
It_1 est la matrice a l'instant t-1
Ot est l'image de différence en niveau de gris
Et est l'image d'etiquette binaire. {0,255} <=> {fond,mouvement}
nrl et nrh : premiere et derniere ligne
ncl et nch : premiere et derniere colonne
dans notre cas on a : nrl = ncl = 0 nrh = 239 nch = 351 pour prendre toute l'image
*/
void Frame_Difference_Matrix(uint8 **It, uint8 **It_1, uint8 **Et, long nrl, long nrh, long ncl, long nch)
{
	long i,j;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
			Et[i][j] = Frame_Difference(It[i][j], It_1[i][j]);
	    }
  	}
}


//cette fonction ne necessite pas de teste unitaire comme elle est suffisament simple il faut juste s'assurer que la fonction abs fait bien se que l'on attend et que ses arguments ne sont correcte
uint8 Frame_Difference(uint8 It, uint8 It_1) {
	uint8 Ot;
	Ot= abs(It - It_1);//prend un int en paramètre or It-It_1 sera toujours castable en int. Cette fonction retourne bien la valeur absolue de (It - It_1) quelle que soit la valeur de It et It_1
	if (Ot < THETA) {
		return 0;
	}
	else {
		return 255;
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
void SD(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, long nrl, long nrh, long ncl, long nch)
{
	long i,j;
	uint8 Ot;

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

	    	Ot=abs( Mt[i][j] - It[i][j] );

	    	if(Vt_1[i][j] < N * Ot){
	    		Vt[i][j] = Vt_1[i][j] + 1;
	    	}
	    	else if(Vt_1[i][j] > N * Ot){
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

	    	if(Ot < Vt[i][j]){
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