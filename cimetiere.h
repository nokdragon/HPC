//Toutes les fonctions qui ne servent plus, mais on garde parce que on sait jamais
#pragma once
void part1_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);
void test_part1_sd();
void part1_sd_scalar(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);
void part1mix(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **sMt, uint8 **sMt_1,  uint8 **Ot,long nrl, long nrh, long ncl, long nch);
void part2_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);
void part2_sd_scalar(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);

void part3_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);
void part3_sd_scalar(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1,
					 uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);
void test_part2_sd();
vuint8 vuint8_abs_simd(vsint8 v);
void test_vuint8_abs_simd();