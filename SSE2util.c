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
    Solution, avant la comparaison, on soustrait à a et b, 127
    */
    
    //c = _mm_cmplt_epi8(a ,b);//compare a and b
    c = _mm_cmplt_epi8(_mm_sub_epi8(a, init_vuint8(MAX_SINT8+1)), _mm_sub_epi8(b, init_vuint8(MAX_SINT8+1)));
    //display_vuint8(c, "%4.0d", "c\t"); puts("\n");
    z = _mm_or_si128(_mm_and_si128(c,y), _mm_andnot_si128(c,x));//select value
    return z;    
}

vsint16 vsint16_if_else(vsint16 a, vsint16 b, vsint8 x, vsint8 y)
{
    vsint16 c, z;
    c = _mm_cmplt_epi16(a ,b);//compare a and b
    z = _mm_or_si128(_mm_and_si128(c, y), _mm_andnot_si128(c,x));//select value
    return z;    
}

//complement à deux
vuint8 vuint8_ca2(vuint8 a)
{
     vuint8 _a;
     _a = _mm_xor_si128(a, init_vuint8(MAX_UINT8)); //_a = NOT a
     _a = _mm_add_epi8 (_a, init_vuint8(1)); // on ajoute 1
     //a = _mm_add_epi8 (_a, init_vuint8(1));
     return _a;
}

//complement à deux
vsint16 vuint16_ca2(vuint16 a)
{
     vuint16 _a;
     _a = _mm_xor_si128(a, init_vuint16(MAX_16B)); //_a = NOT a
     _a = _mm_add_epi16 (_a, init_vuint16(1));

     return _a;
}

//aide possible at : https://stackoverflow.com/questions/32408665/fastest-way-to-compute-absolute-value-using-sse
vuint16 vuint16_abs_simd(vsint16 a)
{   
    //si a > 0, return a, else return son complément à deux
    return vsint16_if_else(a, _mm_setzero_si128(), a, vuint16_ca2(a));
}

//if a > b return x, elif a < b return y, else return z
vuint8 vuint8_if_elif_else(vuint8 a, vuint8 b, vuint8 x, vuint8 y, vuint8 z)
{
    vuint8 c, d;
    /*
    Description du problème : l'opération c = _mm_cmplt_epi8(a,b) est signée
    ex : si a = {0,127} et b = {128, 255}, alors c considère a plus grand, car il prends b pour un négatif
    Solution, avant la comparaison, on soustrait à a et b, 127    */
    
    //c = _mm_cmplt_epi8(a ,b);//compare a and b
    c = _mm_cmpeq_epi8(_mm_sub_epi8(a, init_vuint8(MAX_SINT8+1)), _mm_sub_epi8(b, init_vuint8(MAX_SINT8+1)));
    //display_vuint8(c, "%4.0d", "c\t"); puts("\n");
    d = _mm_or_si128(_mm_and_si128(c,z), _mm_andnot_si128(c,vuint8_if_else(a,b,x,y)));//select value
    return d;    
}

vuint16 vuint16_if_elif_else(vuint16 a, vuint16 b, vuint8 x, vuint8 y, vuint8 z)
{
    vuint8 c, d;
    /*
    Description du problème : l'opération c = _mm_cmplt_epi8(a,b) est signée
    ex : si a = {0,127} et b = {128, 255}, alors c considère a plus grand, car il prends b pour un négatif
    Solution, avant la comparaison, on soustrait à a et b, 127    */
    
    //c = _mm_cmplt_epi8(a ,b);//compare a and b
    c = _mm_cmpeq_epi16(a,b);
    //display_vuint8(c, "%4.0d", "c\t"); puts("\n");
    d = _mm_or_si128(_mm_and_si128(c,z), _mm_andnot_si128(c,vsint16_if_else(a,b,x,y)));//select value
    return d;    
}

vuint8 vuint8_sub_abs(vuint8 a, vuint b)
{   
    /*
    display_vuint8(a, " %d ", "a\t"); puts("");
    display_vuint8(b, " %d ", "b\t"); puts("");
    display_vuint8(_mm_sub_epi8(a , b), " %d ", "a-b\t"); puts("");
    display_vuint8(_mm_sub_epi8(b , a), " %d ", "b-a\t"); puts("\n");
    display_vuint8(_mm_min_epu8(_mm_subs_epi8(a , b), _mm_subs_epi8(b , a)), " %d ", "res\t"); puts("\n");
    */
     vuint8 max, min;
    max = _mm_max_epu8(a, b);
    min = _mm_min_epu8(a, b); //Solution alternative, utiliser un if_else
    return _mm_sub_epi8(max , min);

    //return _mm_sub_epi8(_mm_max_epu8(a, b) , _mm_min_epu8(a, b));
    
}

vuint8 vuint8_sub_absv2(vuint8 a, vuint b)
{   
    /*
    vuint8 max, min;
    max = _mm_max_epu8(a, b);
    min = _mm_min_epu8(a, b); //Solution alternative, utiliser un if_else
    return _mm_sub_epi8(max , min);
    */
    return _mm_min_epu8(_mm_sub_epi8(a , b), _mm_sub_epi8(b , a));
}

vuint16 ext_8_16(vuint8 x)
{   
    vuint8 z8 = _mm_setzero_si128();
    vuint16 res;
    res = _mm_unpacklo_epi8(x,z8); 
    res = _mm_unpackhi_epi8(x,z8);
    return res;
}

void vector_to_scalar(vuint8 *v, uint8 ** res)
{
    //uint8 **res = ui8matrix(NRL, NRH, NCL, NCH);
    uint8 * p = (uint8 *) v;
    long i,j,k;
    k = 0;
    for(i=NRL; i<=NRH; i++) {
        for(j=NCL; j<=NCH; j++) {
            res[i][j] = p[k];
            //printf("res[%ld][%ld] = p[%ld] = %d\n",i,j,k,p[k]); 
            k++;
        }
    }
    //return res;
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

/*
int compare_matrix2(uint8 ** m1, uint8 ** m2, long nrl, long nrh, long ncl, long nch)
{

    long i, j, cpt;
    cpt = 0;
    for (i = nrl; i <= nrh; i++) {
        for (j = ncl; j <= nch; j++) {
            if (m1[i][j] != m2[i][j]) {
                cpt++;

                printf("m1[%ld][%ld] != m2[%ld][%ld]\n", i, j, i, j);
                //printf("%d != %d\n\n", m1[i][j], m2[i][j]);
                //return 1;
            }

        }
    }

    //printf("il y a %ld erreurs\n", cpt);

    if (cpt) {
        printf("il y a %ld erreurs\n", cpt);
        return 1;
    }
    //PRINT_OK();
    return 0;
}
*/

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
