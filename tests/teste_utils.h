#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>

void checar(int condicao, const char *nome) {
    if (condicao) printf("[PASSOU] %s\n", nome);
    else          printf("[FALHOU] %s\n", nome);
}

#endif