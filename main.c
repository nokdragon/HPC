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




void get_image_directory()
{	

  FILE *file;
  char * buffer = NULL;
  char filename[255] = "images_directory_path.txt";
  buffer = (char*) calloc(256, sizeof(char));
  /* ouverture du fichier */
  file = fopen(filename,"rb");
  if (file==NULL){
    printf("\nPas de fichier %s à lire. Sortie de fonction\n", filename);
    exit(1);
  }
  //nrerror("ouverture du fichier %s impossible\n", filename);
  buffer = fgets( buffer, 256, file );
  fclose(file);

  //on teste que le fichier est bien remplit
  if(buffer == NULL){
  	printf("\nLe fichier %s ne contient rien ! Indiquez votre path personnalisé, ou celui par défaut:\nhall/hall%%06d.pgm\n\n",filename);
  	exit(1);
  }

  //on supprime les  \n et \t  et espace à la fin de la chaine
  char * pos;
  if ((pos=strchr(buffer, ' ')) != NULL)
    *pos = '\0';
  if ((pos=strchr(buffer, '\n')) != NULL)
    *pos = '\0';
  if ((pos=strchr(buffer, '\t')) != NULL)
    *pos = '\0';
  free(pos);

  //on copie dans la variable globale le path indiqué 
  strcpy(image_directory,buffer);


   //on teste que le path renseigné est correct
  sprintf(buffer, image_directory, 0); 
  file = fopen(buffer,"rb");
  if (file==NULL){
  	printf("\nImpossible d'ouvrir le fichier %s\n",buffer);
  	printf("Le fichier %s contient un path invalide\n",filename);
  	printf("Lisez le readme.txt pour plus d'infos, ou utilisez le path par défaut:\nhall/hall%%06d.pgm\n\n");
  	exit(1);
  }
  fclose(file); 
  //printf("%s\n", image_directory);
}



void execution() {
	int i;
	long nrl, nrh, ncl, nch;
	uint8** It_1;
	char dir[255];
	sprintf(dir, image_directory, 0);
	It_1 = LoadPGM_ui8matrix(dir, &nrl, &nrh, &ncl, &nch);


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

		sprintf(file, image_directory, i);

		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		vuint8_fd_SSE2_matrix(It, It_1, Et, nrl,  nrh,  ncl, nch);
		

		posTraitementFO(Et, nrl, nrh, ncl, nch);
		sprintf(file, "hall_FD/ETFO_FD%d.pgm", i);
		SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);


		vuint8_sd_SSE2(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, Ot, nrl, nrh, ncl, nch);

		posTraitementOF(Et, nrl, nrh, ncl, nch);
		sprintf(file, "hall_SD/ETOF_SD%d.pgm", i);
		SavePGM_ui8matrix(Et, nrl, nrh, ncl, nch, file);


		Copy_SSE2(It_1, It, nrl, nrh, ncl, nch);
		Copy_SSE2(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy_SSE2(Vt_1, Vt, nrl, nrh, ncl, nch);

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
	printf("copy_SSE2 :%f reduction de  %f%%\n",chrono_copy_SSE2(100),(1-chrono_copy_SSE2(100)/chrono_copy(100))*100);


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

	bench_fd(10, 1);

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


void test_all(){
	test_vuint8_if_else();
	test_vuint8_if_elif_else();
	test_dilatation_erosion_SSE2();
	test_morpho_SSE2();
	test_erosion3();
	test_dilatation3();
	test_vuint8_fd_SSE2();
	test_vuint8_fd_SSE2_matrix();
	test_sd_SSE2();
}



int main()
{
	get_image_directory();
	test_all();//lance tous les tests
	chrono(10);//lance la mesure des temps d'execution des focntions
	validation();//calcule les matrices roc
	execution();//sauvegardes le image de sortie pour fd et sd avec post-traitement suivant les paramètres présent dans main.h
}


