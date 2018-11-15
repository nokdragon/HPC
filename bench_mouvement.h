#pragma once

//calcule le temps dexecution d'une fonction FD moyenné sur n execution
double chrono_FD(int n);

//calcule le temps dexecution d'une fonction SD moyenné sur n execution
double chrono_SD(int n);

//calcule le temps de chargement et déchargement des images pour une fonction FD moyenné sur n execution
double chrono_FD_vide(int n);

//calcule le temps de chargement et déchargement des images pour une fonction SD moyenné sur n execution
double chrono_SD_vide(int n);
