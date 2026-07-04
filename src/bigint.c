#include "bigint.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void bigint_init(Bigint *b) {
    int i;
    for (i = 0; i < MAX_DIGITS; i++) {
        b->digits[i] = 0;
    }
    b->length   = 1;
    b->negativo = 0;
}

int bigint_cargar(Bigint *b, const char *str) {
    int i;
    int inicio;
    int len;
    int pos = 0;

    bigint_init(b);

    len = (int)strlen(str);
    inicio = 0;

    if (str[0] == '-') {
        b->negativo = 1;
        inicio = 1;
    } else if (str[0] == '+') {
        b->negativo = 0;
        inicio = 1;
    }

    int cantidad_digitos = len - inicio;

    if (cantidad_digitos <= 0) {
        return 0;
    }
    if (cantidad_digitos > MAX_DIGITS) {
        return 0;
    }

    for (i = len - 1; i >= inicio; i--) {
        b->digits[pos] = str[i] - '0';
        pos++;
    }
    b->length = cantidad_digitos;

    int es_cero = 1;
    for (i = 0; i < b->length; i++) {
        if (b->digits[i] != 0) {
            es_cero = 0;
            break;
        }
    }
    if (es_cero) {
        b->negativo = 0;
        b->length   = 1;
    }

    return 1;
}

void bigint_imprimir(const Bigint *b) {
    int i;
    if (b->negativo) {
        printf("-");
    }
    for (i = b->length - 1; i >= 0; i--) {
        printf("%d", b->digits[i]);
    }
    printf("\n");
}