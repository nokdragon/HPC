#pragma once

vuint16 vuint16_fd_simd(vuint16 It, vuint16 It_1);
void vuint16_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Ot, uint16 **Et);

void vuint8_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Et);
vuint8 vuint8_fd_simd(vuint8 It, vuint8 It_1);
void to_matrix(vuint8 *v, uint8 ** res);
void vuint8_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);
void part1_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);
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