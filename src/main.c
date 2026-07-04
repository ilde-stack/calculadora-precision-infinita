#include "bigint.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int i;
    Bigint acumulado;
    Bigint actual;
    Bigint resultado;
    int ok;

    if (argc < 2) {
        error_y_salir("faltan argumentos");
    }

    if (strcmp(argv[1], "sumar")       != 0 &&
        strcmp(argv[1], "restar")      != 0 &&
        strcmp(argv[1], "multiplicar") != 0) {
        error_y_salir("operacion invalida");
    }

    if (strcmp(argv[1], "restar") == 0 && argc != 4) {
        error_y_salir("restar necesita exactamente 2 operandos");
    }

    if (strcmp(argv[1], "sumar") == 0 && argc < 4) {
        error_y_salir("sumar necesita al menos 2 operandos");
    }
    if (strcmp(argv[1], "multiplicar") == 0 && argc < 4) {
        error_y_salir("multiplicar necesita al menos 2 operandos");
    }

    for (i = 2; i < argc; i++) {
        if (!numero_valido(argv[i])) {
            error_y_salir("operando invalido");
        }
    }

    bigint_init(&acumulado);
    ok = bigint_cargar(&acumulado, argv[2]);
    if (!ok) {
        error_y_salir("operando demasiado grande");
    }

    for (i = 3; i < argc; i++) {
        bigint_init(&actual);
        ok = bigint_cargar(&actual, argv[i]);
        if (!ok) {
            error_y_salir("operando demasiado grande");
        }

        bigint_init(&resultado);

        if (strcmp(argv[1], "sumar") == 0) {
            ok = bigint_sumar(&acumulado, &actual, &resultado);
        } else if (strcmp(argv[1], "restar") == 0) {
            ok = bigint_restar(&acumulado, &actual, &resultado);
        } else if (strcmp(argv[1], "multiplicar") == 0) {
            ok = bigint_multiplicar(&acumulado, &actual, &resultado);
        }

        if (!ok) {
            error_y_salir("resultado demasiado grande");
        }

        acumulado = resultado;
    }

    bigint_imprimir(&acumulado);

    return 0;
}