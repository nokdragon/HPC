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

//#define PRINT_BEGIN(msg) printf("\n\n==============================================BEGIN %s==============================================\n", msg);
//#define PRINT_END(msg) printf("==============================================END %s==============================================\n\n\n\n", msg);




/*
void test_vuint8_if_else()
{	

	//PRINT_BEGIN("test_if_else");
	PRINT_BEGIN();

	vuint8 a, b, x, y, res;
	b = init_vuint8(5);
	x = init_vuint8(7);
	y = init_vuint8(8);

	printf("On fixe :\n");
	display_vuint8(b, "%4.0x", "b"); puts("");
	display_vuint8(x, "%4.0x", "x"); puts("");
	display_vuint8(y, "%4.0x", "y"); puts("");

	printf("\nOn teste pour differentes valeurs de a, la fonction if_else : \"if a >= b return x, else return y\" :\n\n");

	printf("Si a < b, on retourne bien y :\n");
	a = init_vuint8(4);
	display_vuint8(a, "%4.0x", "a\t"); puts("");
	res = vuint8_if_else(a,b,x,y);
	display_vuint8(res, "%4.0x", "res\t"); puts("\n");

	printf("Si a = b, on retourne bien x : \n");
	a = init_vuint8(5);
	display_vuint8(a, "%4.0x", "a\t"); puts("");
	res = vuint8_if_else(a,b,x,y);
	display_vuint8(res, "%4.0x", "res\t"); puts("\n");

	printf("Si a > b, on retourne bien x : \n");
	a = init_vuint8(6);
	display_vuint8(a, "%4.0x", "a\t"); puts("");
	res = vuint8_if_else(a,b,x,y);
	display_vuint8(res, "%4.0x", "res\t"); puts("\n");

	PRINT_END();

}
*/

/*
void test_vuint8_fd_simd()
{
	PRINT_BEGIN();

	vuint8 It, It_1, res;

	It =  init_vuint8(40);
	It_1 =  init_vuint8(41);
	res = vuint8_fd_simd(It, It_1);
	display_vuint8(It, " %d\t", "It\t"); puts("");
	display_vuint8(It_1, " %d\t", "It_1\t"); puts("");
	//display_vsint8(_mm_sub_epi8(It , It_1), " %d\t", "It - It_1"); puts("");
	//display_vsint16(vuint8_abs_simd(_mm_sub_epi16(It , It_1)), " \t%d\t", "|It - It_1|"); puts("\n");
	printf("La soustraction absolue des deux vecteurs est bien inférieur à theta =  %d, donc on retourne :\n",  THETA);
	display_vuint8(res, " %d\t", "res\t"); puts("\n");
	puts("\n\n");

	It =  init_vuint8(40);
	It_1 =  init_vuint8(240);
	res = vuint8_fd_simd(It, It_1);
	display_vuint8(It, " %d\t", "It\t"); puts("");
	display_vuint8(It_1, " %d\t", "It_1\t"); puts("");
	//display_vsint8(_mm_sub_epi8(It , It_1), " %d\t", "It - It_1"); puts("");
	//display_vsint16(vuint8_abs_simd(_mm_sub_epi16(It , It_1)), " \t%d\t", "|It - It_1|"); puts("\n");
	printf("La soustraction absolue des deux vecteurs est bien supérieur à theta =  %d, donc on retourne :\n",  THETA);
	display_vuint8(res, " %d\t", "res\t"); puts("\n");
	puts("\n\n");

	It =  init_vuint8(40);
	It_1 =  init_vuint8(40);
	res = vuint8_fd_simd(It, It_1);
	display_vuint8(It, " %d\t", "It\t"); puts("");
	display_vuint8(It_1, " %d\t", "It_1\t"); puts("");
	//display_vsint8(_mm_sub_epi8(It , It_1), " %d\t", "It - It_1"); puts("");
	//display_vsint16(vuint8_abs_simd(_mm_sub_epi16(It , It_1)), " \t%d\t", "|It - It_1|"); puts("\n");
	printf("La soustraction absolue des deux vecteurs est bien inférieur à theta = %d, donc on retourne :\n",  THETA);
	display_vuint8(res, " %d\t", "res\t"); puts("\n");

	PRINT_END();
}*/

int test_vuint8_fd_simd()
{
	//PRINT_BEGIN("test_if_else");
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
			res = vuint8_fd_simd(It, It_1);
			pIt = (uint8 *) &It;
			pIt_1 = (uint8 *) &It_1;
			res2 = Frame_Difference(pIt[0], pIt_1[0]);
			p_res = (uint8 *)&res;

			if(abs(i - j) >= THETA){
				for(k=0;k<16;k++){
					//cmp =_mm_cmpeq_epi8 (x,res);
					p_right_value=(uint8 *)&right_value_1;
					if(p_right_value[k] == p_res[k] && (p_res[k] == res2)){
					}
					else{
						printf("Erreur de fd_simd  i=%d j=%d k=%d p_right_value[k]=%d\n",i,j,k,p_right_value[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
					}
				}
			}
			else{
				for(k=0;k<16;k++){
					//cmp=_mm_cmpeq_epi8 (y,res);
					p_right_value=(uint8 *)&right_value_2;
					if(p_right_value[k] == p_res[k] && (p_res[k] == res2)){
					}
					else{
						printf("Erreur de fd_simd i=%d j=%d k=%d p_right_value[k]=%d\n",i,j,k,p_right_value[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
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

/*TO DEL
void test_vuint16_fd_simd()
{
	PRINT_BEGIN();

	vuint16 It, It_1, res;

	It =  init_vuint16(40);
	It_1 =  init_vuint16(41);
	res = vuint16_fd_simd(It, It_1);
	display_vuint16(It, " \t%d\t", "It\t"); puts("");
	display_vuint16(It_1, " \t%d\t", "It_1\t"); puts("");
	display_vsint16(_mm_sub_epi16(It , It_1), " \t%d\t", "It - It_1"); puts("");
	display_vsint16(vuint16_abs_simd(_mm_sub_epi16(It , It_1)), " \t%d\t", "|It - It_1|"); puts("\n");
	printf("La soustraction absolue des deux vecteurs est bien inférieure à theta =  %d, donc on retourne :\n",  THETA);
	display_vuint16(res, " \t%d\t", "res\t"); puts("\n");
	puts("\n\n");

	It =  init_vuint16(40);
	It_1 =  init_vuint16(240);
	res = vuint16_fd_simd(It, It_1);
	display_vuint16(It, " \t%d\t", "It\t"); puts("");
	display_vuint16(It_1, " \t%d\t", "It_1\t"); puts("");
	display_vsint16(_mm_sub_epi16(It , It_1), " \t%d\t", "It - It_1"); puts("");
	display_vsint16(vuint16_abs_simd(_mm_sub_epi16(It , It_1)), " \t%d\t", "|It - It_1|"); puts("\n");
	printf("La soustraction absolue des deux vecteurs est bien supérieure à theta =  %d, donc on retourne :\n",  THETA);
	display_vuint16(res, " \t%d\t", "res\t"); puts("\n");
	puts("\n\n");

	It =  init_vuint16(40);
	It_1 =  init_vuint16(40);
	res = vuint16_fd_simd(It, It_1);
	display_vuint16(It, " \t%d\t", "It\t"); puts("");
	display_vuint16(It_1, " \t%d\t", "It_1\t"); puts("");
	display_vsint16(_mm_sub_epi16(It , It_1), " \t%d\t", "It - It_1"); puts("");
	display_vsint16(vuint16_abs_simd(_mm_sub_epi16(It , It_1)), " \t%d\t", "|It - It_1|"); puts("\n");
	printf("La soustraction absolue des deux vecteurs est bien inférieure à theta = %d, donc on retourne :\n",  THETA);
	display_vuint16(res, " \t%d\t", "res\t"); puts("\n");

	PRINT_END();
}
*/

void test_vuint8_fd_simd_matrix()
{
	PRINT_BEGIN();
	long nrl, nrh, ncl, nch;
	char file[BUFFSIZE];
	uint8** It_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8** It = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Ets = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	uint8 **Et = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	uint8 **Ets2 = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	for(int i=1 ; i< 300 ; i++){

		sprintf(file,"hall/hall%06d.pgm",i);
		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		Frame_Difference_Matrix(It,  It_1,  Et,  nrl,  nrh,  ncl, nch);
		vuint8_fd_simd_matrix(It, It_1, Ets, nrl,  nrh,  ncl, nch);
		vuint8_fd_simd_matrixv2(It, It_1, Ets2, nrl,  nrh,  ncl, nch);
		//vuint8_sd_simd_vnul(It, It_1, Ets, nrl,  nrh,  ncl, nch);

		sprintf(file,"hall_FD/FD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);

		sprintf(file,"hall_FD/FD_simd%d.pgm",i);
		SavePGM_ui8matrix(Ets,nrl, nrh, ncl, nch,file);

		if(compare_matrix(Ets,Et, nrl,  nrh,  ncl, nch))
			return;

		if(compare_matrix(Ets2,Et, nrl,  nrh,  ncl, nch))
			return;

		Copy(It_1, It, nrl, nrh, ncl, nch);

		

		//display_ui8matrix(Ets, nrl, nrh, ncl,  nch, " %d ", "Et");

	}
	PRINT_OK();

	PRINT_END();
	free_ui8matrix(It, nrl, nrh, ncl, nch);
	free_ui8matrix(It_1, nrl, nrh, ncl, nch);
	free_ui8matrix(Et, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(Ets, nrl-2, nrh+2, ncl-2, nch+2);
}




void test_sd_simd()
{
	PRINT_BEGIN();
	int i;
	long nrl, nrh, ncl, nch;

	//scalar et simd traitent la même image
	uint8** It_1;
	It_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);	
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

		sprintf(file, "hall/hall%06d.pgm", i);
		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		SD(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, nrl, nrh, ncl, nch);
		vuint8_sd_simd(It, It_1, sEt, sVt, sVt_1, sMt, sMt_1, sOt, nrl, nrh, ncl, nch);
		//vuint8_sd_simd_vnul(It, It_1, sEt, sVt, sVt_1, sMt, sMt_1, sOt, nrl, nrh, ncl, nch);
		//part1_sd_simd(It, It_1, sEt, sVt, sVt_1, sMt, sMt_1, sOt, nrl,  nrh,  ncl,  nch);
		//part2_sd_simd(It, It_1, sEt, sVt, sVt_1, sMt, sMt_1, sOt, nrl,  nrh,  ncl,  nch);
		//part3_sd_simd(It, It_1, sEt, sVt, sVt_1, sMt, sMt_1, sOt, nrl,  nrh,  ncl,  nch);


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