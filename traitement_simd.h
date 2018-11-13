#pragma once

vuint16 vuint16_fd_simd(vuint16 It, vuint16 It_1);

void vuint16_fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Ot, uint16 **Et);

uint8 ** to_matrix(vuint8 *v);