#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "main.h"
#include "traitement.h"
#include "post_traitement.h"

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


//ouverture de carré 3x3
void ouverture3(uint8 **Et, long nrl, long nrh, long ncl, long nch){


	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	Copy(tmp,Et, nrl, nrh, ncl, nch);
	erosion3(tmp, Et, nrl, nrh, ncl, nch);

	Copy(Et,tmp,nrl, nrh, ncl, nch);
	dilatation3(Et, tmp,nrl, nrh, ncl, nch);

	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}

//ouverture de carré 5x5
void ouverture5(uint8 **Et, long nrl, long nrh, long ncl, long nch){
	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	Copy(tmp,Et, nrl, nrh, ncl, nch);
	erosion5(tmp, Et, nrl, nrh, ncl, nch);

	Copy(Et,tmp,nrl, nrh, ncl, nch);
	dilatation5(Et, tmp,nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}

//fermeture de carré 3x3
void fermeture3(uint8 **Et, long nrl, long nrh, long ncl, long nch){
	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	Copy(tmp,Et, nrl, nrh, ncl, nch);
	dilatation3(tmp, Et,nrl, nrh, ncl, nch);

	Copy(Et,tmp,nrl, nrh, ncl, nch);
	erosion3(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}

//fermeture de carré 5x5
void fermeture5(uint8 **Et, long nrl, long nrh, long ncl, long nch){
	uint8 **tmp;
	tmp = ui8matrix(nrl, nrh, ncl, nch);
	Copy(tmp,Et, nrl, nrh, ncl, nch);
	dilatation5(tmp, Et,nrl, nrh, ncl, nch);

	Copy(Et,tmp,nrl, nrh, ncl, nch);
	erosion5(Et, tmp, nrl, nrh, ncl, nch);
	free_ui8matrix(tmp, nrl, nrh, ncl, nch);
}


//post traitement ouverture puis fermeture
void posTraitementOF(uint8 **Et, long nrl, long nrh, long ncl, long nch){

	ouverture3(Et,nrl, nrh, ncl, nch);
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