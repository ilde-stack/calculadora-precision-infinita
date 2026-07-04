#include "bigint.h"
#include <string.h>

int comparar_abs(const Bigint *a, const Bigint *b) {
    int i;

    if (a->length > b->length) return  1;
    if (a->length < b->length) return -1;

    for (i = a->length - 1; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) return  1;
        if (a->digits[i] < b->digits[i]) return -1;
    }
    return 0;
}

int sumar_abs(const Bigint *a, const Bigint *b, Bigint *r) {
    int i;
    int acarreo;
    int max_len;
    int suma;

    bigint_init(r);

    acarreo = 0;
    max_len = a->length;
    if (b->length > max_len) {
        max_len = b->length;
    }

    for (i = 0; i < max_len || acarreo != 0; i++) {
        if (i >= MAX_DIGITS) {
            return 0; 
        }

        suma = acarreo;
        if (i < a->length) {
            suma = suma + a->digits[i];
        }
        if (i < b->length) {
            suma = suma + b->digits[i];
        }

        r->digits[i] = suma % 10;
        acarreo      = suma / 10;
        r->length    = i + 1;
    }

    return 1;
}

void restar_abs(const Bigint *a, const Bigint *b, Bigint *r) {
    int i;
    int prestamo;
    int dif;

    bigint_init(r);

    prestamo = 0;
    for (i = 0; i < a->length; i++) {
        dif = a->digits[i] - prestamo;
        if (i < b->length) {
            dif = dif - b->digits[i];
        }

        if (dif < 0) {
            dif     = dif + 10;
            prestamo = 1;
        } else {
            prestamo = 0;
        }

        r->digits[i] = dif;
    }

    r->length = a->length;

    while (r->length > 1 && r->digits[r->length - 1] == 0) {
        r->length--;
    }
}

int bigint_sumar(const Bigint *a, const Bigint *b, Bigint *resultado) {
    int cmp;
    int ok;

    bigint_init(resultado);

    if (a->negativo == b->negativo) {
        ok = sumar_abs(a, b, resultado);
        if (!ok) return 0;
        resultado->negativo = a->negativo;
        return 1;
    }

    cmp = comparar_abs(a, b);

    if (cmp == 0) {
        bigint_init(resultado);
        return 1;
    }

    if (cmp > 0) {
        restar_abs(a, b, resultado);
        resultado->negativo = a->negativo;
    } else {
        restar_abs(b, a, resultado);
        resultado->negativo = b->negativo;
    }

    return 1;
}

int bigint_restar(const Bigint *a, const Bigint *b, Bigint *resultado) {
    Bigint b_negado;
    int i;

    bigint_init(&b_negado);
    b_negado.length   = b->length;
    b_negado.negativo = b->negativo;
    for (i = 0; i < b->length; i++) {
        b_negado.digits[i] = b->digits[i];
    }

    if (b_negado.negativo == 0) {
        b_negado.negativo = 1;
    } else {
        b_negado.negativo = 0;
    }

    int es_cero = 1;
    for (i = 0; i < b->length; i++) {
        if (b->digits[i] != 0) {
            es_cero = 0;
            break;
        }
    }
    if (es_cero) {
        b_negado.negativo = 0;
    }

    return bigint_sumar(a, &b_negado, resultado);
}

int bigint_multiplicar(const Bigint *a, const Bigint *b, Bigint *resultado) {
    int i;
    int j;
    int acarreo;
    int prod;
    int largo_resultado;

    bigint_init(resultado);

    int a_es_cero = 1;
    for (i = 0; i < a->length; i++) {
        if (a->digits[i] != 0) { a_es_cero = 0; break; }
    }
    int b_es_cero = 1;
    for (i = 0; i < b->length; i++) {
        if (b->digits[i] != 0) { b_es_cero = 0; break; }
    }
    if (a_es_cero || b_es_cero) {
        return 1; 
    }

    largo_resultado = a->length + b->length;
    if (largo_resultado > MAX_DIGITS) {
        return 0;
    }

    for (i = 0; i < a->length; i++) {
        acarreo = 0;
        for (j = 0; j < b->length || acarreo != 0; j++) {
            if (i + j >= MAX_DIGITS) {
                return 0;
            }

            prod = resultado->digits[i + j] + acarreo;
            if (j < b->length) {
                prod = prod + a->digits[i] * b->digits[j];
            }

            resultado->digits[i + j] = prod % 10;
            acarreo                  = prod / 10;
        }
    }

    resultado->length = largo_resultado;

    while (resultado->length > 1 && resultado->digits[resultado->length - 1] == 0) {
        resultado->length--;
    }

    if (a->negativo != b->negativo) {
        resultado->negativo = 1;
    } else {
        resultado->negativo = 0;
    }

    return 1;
}