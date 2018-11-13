#pragma once

vuint16 vuint16_fd_simd(vuint16 It, vuint16 It_1);
void vuint16_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Ot, uint16 **Et);

void vuint8_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Et);
vuint8 vuint8_fd_simd(vuint8 It, vuint8 It_1);
void to_matrix(vuint8 *v, uint8 ** res);

