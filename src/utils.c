#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void error_y_salir(const char *msg) {
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(1);
}

int numero_valido(const char *str) {
    int i;
    int inicio;

    if (str == NULL || str[0] == '\0') {
        return 0;
    }

    inicio = 0;
    if (str[0] == '+' || str[0] == '-') {
        inicio = 1;
    }

    if (str[inicio] == '\0') {
        return 0;
    }

    for (i = inicio; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0;
        }
    }

    return 1;
}