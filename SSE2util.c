/* --------------- */
/* --- simd1.c --- */
/* --------------- */
//https://software.intel.com/sites/landingpage/IntrinsicsGuide/

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "SSE2util.h"
#include "main.h"


//if a >= b return x, else return y
vuint8 vuint8_if_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y)
{
    vuint8 c, z;
    /*
    Description du problème : l'opération c = _mm_cmplt_epi8(a,b) est signée
    ex : si a = {0,127} et b = {128, 255}, alors c considère a plus grand, car il prends b pour un négatif
    Solution, avant la comparaison, on soustrait à a et b, 128
    */

    c = _mm_cmplt_epi8(_mm_sub_epi8(a, init_vuint8(MAX_SINT8+1)), _mm_sub_epi8(b, init_vuint8(MAX_SINT8+1)));
    z = _mm_or_si128(_mm_and_si128(c,y), _mm_andnot_si128(c,x));//select value
    return z;    
}


//if a > b return x, elif a < b return y, else return z
vuint8 vuint8_if_elif_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y, vuint8 z)
{
    vuint8 c, d;
    /*
    Description du problème : l'opération c = _mm_cmplt_epi8(a,b) est signée
    ex : si a = {0,127} et b = {128, 255}, alors c considère a plus grand, car il prends b pour un négatif
    Solution, avant la comparaison, on soustrait à a et b, 128    
    */
    
    c = _mm_cmpeq_epi8(_mm_sub_epi8(a, init_vuint8(MAX_SINT8+1)), _mm_sub_epi8(b, init_vuint8(MAX_SINT8+1)));
    d = _mm_or_si128(_mm_and_si128(c,z), _mm_andnot_si128(c,vuint8_if_else(a,b,x,y)));//select value
    return d;    
}


vuint8 vuint8_sub_abs(vuint8 a, vuint b)
{   
    vuint8 max, min;
    max = _mm_max_epu8(a, b);
    min = _mm_min_epu8(a, b); //Solution alternative, utiliser un if_else
    return _mm_sub_epi8(max , min);    
}


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
