#pragma once
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"

#define NB_IMAGE 300 
#define STR_SIZE 255

#define PRINT_BEGIN() printf("\n\n==============================================BEGIN %s==============================================\n", __func__);
#define PRINT_END() printf("==============================================END %s==============================================\n\n\n\n", __func__);
#define PRINT_OK() printf("\nLa fonction ne contient pas d'erreur\n\n");

#define MAX_SINT8 127
#define MIN_SINT8 -128

#define MAX_PIXEL_VALUE 255
#define MIN_PIXEL_VALUE 0

#define THETA 40
#define BUFFSIZE 255
#define NB_IMAGE 300

#define MAX_PIXEL_VALUE 255

//E pour Entier, R pour restant, O pour octet
#define NB_UINT8_IMAGE 83889 //351 * 239
#define NBE_UINT16_IMAGE 41944 //(int) NB_UINT8_IMAGE / 2
#define NBOR_UINT16_IMAGE 1 // NB_UINT8_IMAGE - (NBE_UINT16_IMAGE * 2)

#define NBE_VUINT8_IMAGE 5243//(int) NB_UINT8_IMAGE / (128/8), avec 128/8 = 16
#define NBOR_VUINT8_IMAGE 1//NB_UINT8_IMAGE - (NBE_VUINT8_IMAGE * 16)

#define NBE_VUINT16_IMAGE 10486//(int) NBE_VUINT8_IMAGE  2 = 
#define NBOR_VUINT16_IMAGE 1//NB_UINT8_IMAGE - NBE_VUINT16_IMAGE * 8 = 83889 - (10486 * 8)

#define NRL 0
#define NRH 239
#define NCL 0
#define NCH 351

#define MAX_32B 0xffffffff //2 pow 32 - 1
#define MAX_UINT8 255
#define MIN_UINT8 0
#define MAX_SINT8 127 
#define MAX_16B 0xffff //2 pow 16 -1



