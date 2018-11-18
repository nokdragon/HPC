#pragma once


//====================FD====================
vuint8 vuint8_fd_SSE2(vuint8 It, vuint8 It_1);
void vuint8_fd_SSE2_matrix(uint8 **It, uint8 **It_1, uint8 **Et, long nrl, long nrh, long ncl, long nch);

void vuint8_fd_SSE2_row(uint8 *It, uint8 *It_1, uint8 *Et, long ncl, long nch);
void vuint8_fd_SSE2_matrixv2(uint8 **It, uint8 **It_1, uint8 **Et, long nrl, long nrh, long ncl, long nch);

void vuint8_fd_SSE2_iteration(vuint8 vIt, vuint8 vIt_1, vuint8 Et);


//====================SD====================
void vuint8_sd_SSE2(uint8 **It, uint8 **It_1, uint8 **Et, uint8 **Vt, uint8 **Vt_1, uint8 **Mt, uint8 **Mt_1, uint8 **Ot,long nrl, long nrh, long ncl, long nch);
