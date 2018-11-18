#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "SSE2util.h"
#include "mouvement_SSE2.h"
#include "mouvement.h"
#include "main.h"

int test_vuint8_fd_SSE2()
{
	PRINT_BEGIN();

	uint8 * p_right_value; 
	uint8 * p_res;
	uint8 *pIt ;
	uint8 *pIt_1;
	vuint8 It, It_1, right_value_1, right_value_2, res;
	uint8 res2;
	right_value_1 = init_vuint8(0xff);	
	right_value_2 = init_vuint8(0);

	int i,j,k;// i pour It, j pour It_1, k pour parcourir les vecteurs

	for(i=MIN_UINT8;i<MAX_UINT8;i++){
		for(j=MIN_UINT8;j<MAX_UINT8;j++){

			It = init_vuint8(i);
			It_1 = init_vuint8(j);
			res = vuint8_fd_SSE2(It, It_1);
			pIt = (uint8 *) &It;
			pIt_1 = (uint8 *) &It_1;
			res2 = Frame_Difference(pIt[0], pIt_1[0]);
			p_res = (uint8 *)&res;

			if(abs(i - j) >= THETA){
				for(k=0;k<16;k++){
					p_right_value=(uint8 *)&right_value_1;
					if(p_right_value[k] == p_res[k] && (p_res[k] == res2)){
					}
					else{
						printf("Erreur de fd_SSE2  i=%d j=%d k=%d p_right_value[k]=%d\n",i,j,k,p_right_value[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						return 1;
					}
				}
			}
			else{
				for(k=0;k<16;k++){
					p_right_value=(uint8 *)&right_value_2;
					if(p_right_value[k] == p_res[k] && (p_res[k] == res2)){
					}
					else{
						printf("Erreur de fd_SSE2 i=%d j=%d k=%d p_right_value[k]=%d\n",i,j,k,p_right_value[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						return 1;
					}
				}
			}

		}
	}

	PRINT_OK();
	PRINT_END();
	return 0;	
}

void test_vuint8_fd_SSE2_matrix()
{
	PRINT_BEGIN();
	long nrl, nrh, ncl, nch;
	char file[BUFFSIZE];
		
	char dir[255];
	sprintf(dir, image_directory, 0);
	uint8**  It_1 = LoadPGM_ui8matrix(dir, &nrl, &nrh, &ncl, &nch);
	uint8** It = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Ets = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	uint8 **Et = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	uint8 **Ets2 = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	for(int i=1 ; i< 300 ; i++){

		sprintf(file, image_directory, i);
		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		Frame_Difference_Matrix(It,  It_1,  Et,  nrl,  nrh,  ncl, nch);
		vuint8_fd_SSE2_matrix(It, It_1, Ets, nrl,  nrh,  ncl, nch);
		vuint8_fd_SSE2_matrixv2(It, It_1, Ets2, nrl,  nrh,  ncl, nch);
		//vuint8_sd_SSE2_vnul(It, It_1, Ets, nrl,  nrh,  ncl, nch);

		sprintf(file,"hall_FD/FD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);

		sprintf(file,"hall_FD/FD_SSE2%d.pgm",i);
		SavePGM_ui8matrix(Ets,nrl, nrh, ncl, nch,file);

		if(compare_matrix(Ets,Et, nrl,  nrh,  ncl, nch))
			return;

		if(compare_matrix(Ets2,Et, nrl,  nrh,  ncl, nch))
			return;

		Copy(It_1, It, nrl, nrh, ncl, nch);

	}


	PRINT_OK();
	PRINT_END();
	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Ets, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Ets2, nrl-2, nrh+2, ncl-2, nch+2);
}


void test_sd_SSE2()
{
	PRINT_BEGIN();
	int i;
	long nrl, nrh, ncl, nch;

	//scalar et simd traitent la même image
	uint8** It_1;
		char dir[255];
	sprintf(dir, image_directory, 0);
	It_1 = LoadPGM_ui8matrix(dir, &nrl, &nrh, &ncl, &nch);	
	uint8** It = ui8matrix(nrl, nrh, ncl, nch);
	char file[255];

	//Scalar init
	uint8 **Et = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	uint8 **Vt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Vt_1 = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Mt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Mt_1 = ui8matrix(nrl, nrh, ncl, nch);
	Init_M(Mt_1, It_1, nrl, nrh, ncl, nch);
	Init_V(Vt_1, nrl, nrh, ncl, nch);

	//SIMD init
	uint8 **sEt = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	uint8 **sVt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **sVt_1 = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **sMt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **sMt_1 = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **sOt = ui8matrix(nrl, nrh, ncl, nch);
	Init_M(sMt_1, It_1, nrl, nrh, ncl, nch);
	Init_V(sVt_1, nrl, nrh, ncl, nch);

	
	for (i = 1; i< NB_IMAGE; i++) {

		sprintf(file, image_directory, i);
		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		SD(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);
		vuint8_sd_SSE2(It, It_1, sEt, sVt, sVt_1, sMt, sMt_1, sOt, nrl, nrh, ncl, nch);

		Copy(It_1, It, nrl, nrh, ncl, nch);

		Copy(Mt_1, Mt, nrl, nrh, ncl, nch);
		Copy(Vt_1, Vt, nrl, nrh, ncl, nch);

		Copy(sMt_1, sMt, nrl, nrh, ncl, nch);
		Copy(sVt_1, sVt, nrl, nrh, ncl, nch);

		if(compare_matrix(Et, sEt, nrl,  nrh,  ncl,  nch)) return;


	}	

	PRINT_OK();
	PRINT_END();

	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Vt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt, nrl, nrh, ncl, nch);
	free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);
	
	free_ui8matrix(sOt, nrl, nrh, ncl, nch);
	free_ui8matrix(sEt, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(sVt_1, nrl, nrh, ncl, nch);
	free_ui8matrix(sVt, nrl, nrh, ncl, nch);
	free_ui8matrix(sMt, nrl, nrh, ncl, nch);
	free_ui8matrix(sMt_1, nrl, nrh, ncl, nch);

}