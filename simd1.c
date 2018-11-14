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

#include "simd1.h"
#include "main.h"

#define PRINT_BUG() printf("ATTENTION : Utilisation de la fonction %s, non valide à l'heure actuelle\n", __func__);

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

//aide possible at : https://stackoverflow.com/questions/32408665/fastest-way-to-compute-absolute-value-using-sse
vuint8 vuint8_abs_simd(vuint8 a)
{   
    //si a > 0, return a, else return son complément à deux

    PRINT_BUG();
    return vuint8_if_else(a, _mm_setzero_si128(), a, vuint8_ca2(a));
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
    vuint8 max, min;
    max = _mm_max_epu8(a, b);
    min = _mm_min_epu8(a, b); //Solution alternative, utiliser un if_else
    return _mm_sub_epi8(max , min);
}

vuint16 ext_8_16(vuint8 x)
{   
    vuint8 z8 = _mm_setzero_si128();
    vuint16 res;
    res = _mm_unpacklo_epi8(x,z8); 
    res = _mm_unpackhi_epi8(x,z8);
    return res;
}