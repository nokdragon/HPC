#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "simd1.h"
#include "traitement_simd.h"
#include "traitement.h"
#include "main.h"

//#define PRINT_BEGIN(msg) printf("\n\n==============================================BEGIN %s==============================================\n", msg);
//#define PRINT_END(msg) printf("==============================================END %s==============================================\n\n\n\n", msg);


int comp_vuint8(vuint8 v1, vuint8 v2)
{
	uint8 *pv1 = (uint8 *) &v1;
	uint8 *pv2 = (uint8 *) &v1;
	for (int i = 0; i < 16; ++i)
	{
		if (pv1[i] != pv2[i])
			return 1;
	}
	
	return 0;
}

//focntion de test unitaire exhaustif de vuint8_if_else
int test_vuint8_if_else()
{	

	PRINT_BEGIN();

	uint8 * tmp;
	vuint8 a, b, x, y, res;//,cmp;
	x = init_vuint8(7);
	y = init_vuint8(8);


	int i,j,k;

	for(i=MIN_UINT8;i<MAX_UINT8+1;i++){//parcours toutes les entrées possible de a
		for(j=MIN_UINT8;j<MAX_UINT8+1;j++){//et de b
			a=init_vuint8(i);
			b=init_vuint8(j);
			res = vuint8_if_else(a,b,x,y);
			if(i>=j){//si a est supérieur ou égale à b
				/*
				for(k=0;k<16;k++){//pour tous les uint8 du vuint8 on vérifie que le résultat est bon (res est bien égale a x)
					
					cmp=_mm_cmpeq_epi8 (x,res);
					tmp=(uint8 *)&cmp;
					if(tmp[k]){
					}
					else{
						printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
					}
				}*/
				if (comp_vuint8(x, res)){
					printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(x, "%4.0x", "x "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
				}
			}
			else{//si a n'est pas supérieur ou égale à b
				/*
				for(k=0;k<16;k++){//pour tous les uint8 du vuint8 on vérifie que le résultat est bon (res est bien égale a y)
					cmp=_mm_cmpeq_epi8 (y,res);
					tmp=(uint8 *)&cmp;
					if(tmp[k]){
					}
					else{
						printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						return 1;
					}
				}*/
					if (comp_vuint8(y, res)){
					printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(y, "%4.0x", "y "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
				}
			}

		}
	}

	PRINT_OK();
	PRINT_END();
	return 0;	

}


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

void test_vuint8_abs_simd()
{	
	PRINT_BEGIN();

	vuint8 a, abs_a;
	a = init_vuint8(-5);
	abs_a = vuint8_abs_simd(a);
	display_vsint8(a, " %d\t", "a\t"); puts("");
	display_vuint8(abs_a, " %d\t", "abs_a\t"); puts("\n");

	vuint8 b, abs_b;
	b = init_vuint8(8);
	abs_b = vuint8_abs_simd(b);
	display_vuint8(b, " %d\t", "b\t"); puts("");
	display_vuint8(abs_b, " %d\t", "abs_b\t"); puts("\n");

	vuint8 c, abs_c;
	c = init_vuint8(0);
	abs_c = vuint8_abs_simd(c);
	display_vuint8(c, " %d\t", "c\t"); puts("");
	display_vuint8(abs_c, " %d\t", "abs_c\t"); puts("\n");

	PRINT_END();

}

void test_vuint16_abs_simd()
{	
	PRINT_BEGIN();

	vuint16 a, abs_a;
	a = init_vuint16(-5);
	abs_a = vuint16_abs_simd(a);
	display_vsint16(a, " %d\t", "a\t"); puts("");
	display_vsint16(abs_a, " %d\t", "abs_a\t"); puts("\n");

	vuint16 b, abs_b;
	b = init_vuint16(16);
	abs_b = vuint16_abs_simd(b);
	display_vuint16(b, " %d\t", "b\t"); puts("");
	display_vuint16(abs_b, " %d\t", "abs_b\t"); puts("\n");

	vuint16 c, abs_c;
	c = init_vuint16(0);
	abs_c = vuint16_abs_simd(c);
	display_vuint16(c, " %d\t", "c\t"); puts("");
	display_vuint16(abs_c, " %d\t", "abs_c\t"); puts("\n");

	PRINT_END();

}

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

int compare_matrix(uint8 ** m1, uint8 ** m2, long nrl, long nrh, long ncl, long nch)
{
	
	long i,j, cpt;
	cpt = 0;
	for(i=nrl; i<=nrh; i++) {
	    for(j=ncl; j<=nch; j++) {
			if (m1[i][j] != m2[i][j]){
				cpt++;
				
				printf("m1[%ld][%ld] != m2[%ld][%ld]\n",i,j,i,j);
				printf("%d != %d\n\n", m1[i][j], m2[i][j]);
				return 1;
			}			
			
	    }
  	}
  	//PRINT_OK();
  	return 0;
  	printf("nb val différentes = %ld \n", cpt);
  	PRINT_END();
}

void test_vuint8_fd_simd_matrix()
{
	PRINT_BEGIN();
	long nrl, nrh, ncl, nch;
	char file[BUFFSIZE];
	uint8** It_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8** It = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **Ets = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Et = ui8matrix(nrl, nrh, ncl, nch);


	for(int i=1 ; i< 2 ; i++){

		sprintf(file,"hall/hall%06d.pgm",i);
		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

		Frame_Difference_Matrix(It,  It_1,  Et,  nrl,  nrh,  ncl, nch);
		vuint8_fd_simd_matrix(It, It_1, Ets);

		sprintf(file,"hall_FD/FD%d.pgm",i);
		SavePGM_ui8matrix(Et,nrl, nrh, ncl, nch,file);

		sprintf(file,"hall_FD/FD_simd%d.pgm",i);
		SavePGM_ui8matrix(Ets,nrl, nrh, ncl, nch,file);

		compare_matrix(Ets,Et, nrl,  nrh,  ncl, nch);

		PRINT_OK();

		PRINT_END();

		//display_ui8matrix(Ets, nrl, nrh, ncl,  nch, " %d ", "Et");

	}
}

int  test_vuint8_if_elif_else()
{
	/*
	PRINT_BEGIN();
	vuint8 a,b,x,y,z;
	a = init_vuint8(4);
	b = init_vuint8(5);
	x = init_vuint8(6);
	y = init_vuint8(7);
	z = init_vuint8(8);
	vuint8_if_elif_else( a,  b,  x,  y,  z);
	PRINT_END();
	*/



	PRINT_BEGIN();

	uint8 * tmp;
	vuint8 a, b, x, y, z, res;//,cmp;
	x = init_vuint8(7);
	y = init_vuint8(8);
	z = init_vuint8(9);


	int i,j,k;

	for(i=MIN_UINT8;i<MAX_UINT8+1;i++){//parcours toutes les entrées possible de a
		for(j=MIN_UINT8;j<MAX_UINT8+1;j++){//et de b
			a=init_vuint8(i);
			b=init_vuint8(j);
			res = vuint8_if_elif_else(a,b,x,y,z);
			if(i>j){//si a est supérieur ou égale à b
				/*
				for(k=0;k<16;k++){//pour tous les uint8 du vuint8 on vérifie que le résultat est bon (res est bien égale a x)
					cmp=_mm_cmpeq_epi8 (x,res);
					tmp=(uint8 *)&cmp;
					if(tmp[k]){
					}
					else{
						printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
					}
				}*/
				if (comp_vuint8(x, res)){
					printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(x, "%4.0x", "x "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
				}
			}
			else if(i == j){
				/*
				for(k=0;k<16;k++){//pour tous les uint8 du vuint8 on vérifie que le résultat est bon (res est bien égale a x)
					cmp=_mm_cmpeq_epi8 (z,res);
					tmp=(uint8 *)&cmp;
					if(tmp[k]){
					}
					else{
						printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
					}
				}*/
				if (comp_vuint8(z, res)){
					printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(z, "%4.0x", "z "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
				}
			}
			else{//si a n'est pas supérieur ou égale à b
				/*
				for(k=0;k<16;k++){//pour tous les uint8 du vuint8 on vérifie que le résultat est bon (res est bien égale a y)
					cmp=_mm_cmpeq_epi8 (y,res);
					tmp=(uint8 *)&cmp;
					if(tmp[k]){
					}
					else{
						printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res= "); puts("\n");
						display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						return 1;
					}
				}
				*/
				if (comp_vuint8(y, res)){
					printf("Erreur de if_else simd i=%d j=%d k=%d tmp[k]=%d\n",i,j,k,tmp[k]);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(y, "%4.0x", "y "); puts("\n");
						//display_vuint8(cmp, "%4.0x", "cmp\t"); puts("\n");
						//tmp=_mm_cmpeq_epi8 (x,res);
						return 1;
				}
			}

		}
	}

	PRINT_OK();
	PRINT_END();
	return 0;	
}

void test_ext_8_16()
{
	vuint8 v = init_vuint8(5);
	vuint16 v16 = ext_8_16(v);
	display_vuint8(v, "%4.0x", " v"); puts("\n");
	display_vuint16(v16, "%4.0x", " v16 "); puts("\n");
}

void test_part1_sd()
{
	PRINT_BEGIN();
	//============SIMD
	int i;
	long nrl, nrh, ncl, nch;

	uint8** It_1;
	It_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8** It = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Et = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Vt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Vt_1 = ui8matrix(nrl, nrh, ncl, nch);
	Init_V(Vt_1, nrl, nrh, ncl, nch);
	uint8 **sMt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **sMt_1 = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Mt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Mt_1 = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Ot = ui8matrix(nrl, nrh, ncl, nch);

	Init_M(Mt_1, It_1, nrl, nrh, ncl, nch);
	Init_M(sMt_1, It_1, nrl, nrh, ncl, nch);

	char file[255];

	
	for (i = 1; i<2; i++) {

		
		It = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);
		sprintf(file, "hall/hall%06d.pgm", i);
		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

	}	

	part1_sd_simd(It, It_1, Et, Vt, Vt_1, sMt, sMt_1, Ot, nrl,  nrh,  ncl,  nch);
	part1_sd_scalar(It, It_1, Et, Vt, Vt_1,Mt, Mt_1, Ot, nrl,  nrh,  ncl,  nch);
	//part1mix(It, It_1, Et, Vt, Vt_1,Mt, Mt_1, sMt, sMt_1, Ot, nrl,  nrh,  ncl,  nch);	
	if(compare_matrix(Mt, sMt, nrl,  nrh,  ncl,  nch)) return;
	//compare_matrix(Mt, sMt, nrl,  nrh,  ncl,  nch);
	PRINT_OK();
	PRINT_END();

	
}

void test_part2_sd() 
{
	
	//============SIMD
	int i;
	long nrl, nrh, ncl, nch;

	uint8** It_1;
	It_1 = LoadPGM_ui8matrix("hall/hall000000.pgm", &nrl, &nrh, &ncl, &nch);
	uint8** It = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Et = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Vt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Vt_1 = ui8matrix(nrl, nrh, ncl, nch);

	uint8 **sVt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **sVt_1 = ui8matrix(nrl, nrh, ncl, nch);

	Init_V(Vt_1, nrl, nrh, ncl, nch);
	uint8 **sMt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **sMt_1 = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Mt = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Mt_1 = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **Ot = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **sOt = ui8matrix(nrl, nrh, ncl, nch);

	Init_M(Mt_1, It_1, nrl, nrh, ncl, nch);
	Init_M(sMt_1, It_1, nrl, nrh, ncl, nch);

	

	char file[255];

	
	for (i = 1; i<2; i++) {

		sprintf(file, "hall/hall%06d.pgm", i);
		MLoadPGM_ui8matrix(file, nrl, nrh, ncl, nch, It);

	}	

	part1_sd_simd(It, It_1, Et, sVt, sVt_1, sMt, sMt_1, sOt, nrl,  nrh,  ncl,  nch);
	part1_sd_scalar(It, It_1, Et, Vt, Vt_1,Mt, Mt_1, Ot, nrl,  nrh,  ncl,  nch);

	
	part2_sd_simd(It, It_1, Et, sVt, sVt_1, sMt, sMt_1, sOt, nrl,  nrh,  ncl,  nch);
	part2_sd_scalar(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, Ot, nrl,  nrh,  ncl,  nch);



	if(compare_matrix(sVt, Vt, nrl,  nrh,  ncl,  nch)) return;
	PRINT_DEBUG
	if(compare_matrix(Ot, sOt, nrl,  nrh,  ncl,  nch)) return;

	PRINT_DEBUG
	part3_sd_simd(It, It_1, Et, sVt, sVt_1, sMt, sMt_1, sOt, nrl,  nrh,  ncl,  nch);
	part3_sd_scalar(It, It_1, Et, Vt, Vt_1, Mt, Mt_1, Ot, nrl,  nrh,  ncl,  nch);

	if(compare_matrix(Ot, sOt, nrl,  nrh,  ncl,  nch)) return;
	if(compare_matrix(sVt, Vt, nrl,  nrh,  ncl,  nch)) return;
	//compare_matrix(Mt, sMt, nrl,  nrh,  ncl,  nch);
	PRINT_OK();
	PRINT_END();
}