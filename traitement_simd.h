#pragma once

vuint8 fd_simd(vuint8 It, vuint8 It_1);

void fd_simd_matrix(uint8 **It, uint8 **It_1, uint8 **Ot, uint8 **Et);

uint8 ** to_matrix(vuint8 *v);