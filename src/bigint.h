#ifndef BIGINT_H
#define BIGINT_H

#include <stdbool.h>

#define MAX_DIGITS 1000

typedef struct {
    int digits[MAX_DIGITS]; 
    int length;             
    int negativo;           
} Bigint;

void bigint_init(Bigint *b);
int  bigint_cargar(Bigint *b, const char *str);
void bigint_imprimir(const Bigint *b);

int bigint_sumar(const Bigint *a, const Bigint *b, Bigint *resultado);
int bigint_restar(const Bigint *a, const Bigint *b, Bigint *resultado);
int bigint_multiplicar(const Bigint *a, const Bigint *b, Bigint *resultado);

int  numero_valido(const char *str);
void error_y_salir(const char *msg);

#endif