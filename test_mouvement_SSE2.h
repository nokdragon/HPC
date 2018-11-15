#pragma once

//vuint8
void test_vuint8_if_else();
void test_vuint8_abs_simd();
void test_vuint8_fd_simd();
void test_vuint8_fd_simd_matrix();
void  test_vuint8_if_elif_else();
void test_ext_8_16();


//vuint16
void test_vuint16_abs_simd();
void test_vuint16_fd_simd();

int compare_matrix(uint8 ** m1, uint8 ** m2, long nrl, long nrh, long ncl, long nch);
void test_sd_simd();



