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
#include "test_SSE2.h"

//focntion de test unitaire exhaustif de vuint8_if_else
int test_vuint8_if_else()
{	

	PRINT_BEGIN();
	printf("Test exhaustif\n");

	
	vuint8 a, b, x, y, res;
	x = init_vuint8(7);
	y = init_vuint8(8);


	int i,j;

	for(i=MIN_UINT8;i<MAX_UINT8+1;i++){//parcours toutes les entrées possible de a
		for(j=MIN_UINT8;j<MAX_UINT8+1;j++){//et de b
			a=init_vuint8(i);
			b=init_vuint8(j);
			res = vuint8_if_else(a,b,x,y);
			if(i>=j){//si a est supérieur ou égale à b
				if (comp_vuint8(x, res)){//comparaison du résltat
					printf("Erreur de if_else simd i=%d j=%d\n",i,j);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(x, "%4.0x", "x "); puts("\n");
						return 1;
				}
			}
			else{//si a n'est pas supérieur ou égale à b
					if (comp_vuint8(y, res)){
					printf("Erreur de if_else simd i=%d j=%d\n",i,j);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(y, "%4.0x", "y "); puts("\n");
						return 1;
				}
			}

		}
	}

	PRINT_OK();
	PRINT_END();
	return 0;	

}




int  test_vuint8_if_elif_else()
{
	
	PRINT_BEGIN();
	printf("Test exhaustif\n");

	//uint8 * tmp;
	vuint8 a, b, x, y, z, res;//,cmp;
	x = init_vuint8(7);
	y = init_vuint8(8);
	z = init_vuint8(9);


	int i,j;

	for(i=MIN_UINT8;i<MAX_UINT8+1;i++){//parcours toutes les entrées possible de a
		for(j=MIN_UINT8;j<MAX_UINT8+1;j++){//et de b
			a=init_vuint8(i);
			b=init_vuint8(j);
			res = vuint8_if_elif_else(a,b,x,y,z);
			if(i>j){//si a est supérieur ou égale à b
				if (comp_vuint8(x, res)){
					printf("Erreur de if_else simd i=%d j=%d\n",i,j);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(x, "%4.0x", "x "); puts("\n");
						return 1;
				}
			}
			else if(i == j){
				if (comp_vuint8(z, res)){
					printf("Erreur de if_else simd i=%d j=%d\n",i,j);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(z, "%4.0x", "z "); puts("\n");
						return 1;
				}
			}
			else{//si a n'est pas supérieur ou égale à b
				if (comp_vuint8(y, res)){
					printf("Erreur de if_else simd i=%d j=%d\n",i,j);
						display_vuint8(res, "%4.0x", "res "); puts("\n");
						display_vuint8(y, "%4.0x", "y "); puts("\n");
						return 1;
				}
			}

		}
	}

	PRINT_OK();
	PRINT_END();
	return 0;	
}

