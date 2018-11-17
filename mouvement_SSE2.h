#pragma once

//vuint16 vuint16_fd_simd(vuint16 It, vuint16 It_1);//TO DEL
//void vuint16_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Ot, uint16 **Et);// TO DEL

//void vuint8_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Et);
vuint8 vuint8_fd_simd(vuint8 It, vuint8 It_1);
void vuint8_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Et, long nrl, long nrh, long ncl, long nch);
void vuint8_sd_simd(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);
void vuint8_sd_simd_vnul(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);
void vuint8_fd_simd_row(uint8 *It, uint8 *It_1, uint8 *Et, long ncl, long nch);
void vuint8_fd_simd_matrixv2(uint8 **It, uint8 **It_1, uint8 **Et, long nrl, long nrh, long ncl, long nch);
void vuint8_fd_simd_iteration(vuint8 vIt, vuint8 vIt_1, vuint8 Et);
