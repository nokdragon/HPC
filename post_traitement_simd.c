#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"
#include "post_traitement.h"
#include "main.h"

#include "vnrdef.h"
#include "vnrutil.h"
#include "simd1.h"

uint8 dilatation3_simd(vuint8 Et) {
	int tmp;
	tmp = Et1;
	tmp += Et2;
	tmp += Et3;
	tmp += Et4;
	tmp += Et5;
	tmp += Et6;
	tmp += Et7;
	tmp += Et8;
	tmp += Et9;
	if (tmp == 0) {
		return 0;
	}
	else {
		return 255;
	}
}