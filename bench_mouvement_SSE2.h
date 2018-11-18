#pragma once

//calcule le temps dexecution d'une fonction FD moyenner sur n execution
double chrono_FD_SSE2(int n);

//calcule le temps dexecution d'une fonction SD moyenner sur n execution
double chrono_SD_SSE2(int n);

double chrono_FD_SSE2v2(int n);

void bench_fd(int n, int nb_iterations);

double chrono_fd_AoSoS(int n);

double chrono_FD_AoSoS_vide(int n);

double chrono_fd_AoSoSv2(int n);