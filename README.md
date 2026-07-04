# Calculadora de Precisión Arbitraria (Bigint en C)

Este proyecto consiste en una biblioteca desarrollada en lenguaje C estándar orientada al procesamiento aritmético de precisión arbitraria (`Bigint`). El sistema supera las limitaciones nativas de los tipos de datos primitivos del hardware (como `long long int`), permitiendo almacenar y operar de manera exacta números enteros de hasta 1000 dígitos mediante manipulación dinámica de vectores y algoritmos matemáticos basados en acarreos físicos.

## Características Técnicas
* **Representación en Memoria:** Modelado mediante estructuras tradicionales que encapsulan el vector de dígitos (en orden inverso para optimización posicional), longitud efectiva y banderas de signo.
* **Algoritmos Aritméticos Implementados:**
  * **Suma y Resta Avanzada:** Manejo analítico de signos opuestos mediante comparadores absolutos y gestión explícita de préstamos (*borrows*) y acarreos (*carries*).
  * **Multiplicación Escalar Semidirecta:** Algoritmo polinomial por capas con control de sobreflujo sobre el límite estricto de representación estática (`MAX_DIGITS`).
* **CLI Robusta:** Interfaz por línea de comandos encargada de la validación estricta de cadenas numéricas de gran tamaño y encadenamiento acumulativo de operaciones.

## Requisitos y Compilación

### Prerrequisitos
* Compilador GCC con soporte para el estándar C11.
* Utilidad de automatización `make`.

### Compilación
Para construir el motor aritmético, ejecuta el archivo de automatización desde el directorio raíz:
```bash
make
```

### Ejemplos de Ejecución
Suma acumulativa de múltiples operandos masivos:
```bash
./ent sumar 999999999999999999999 1 12345678901234567890
```

Multiplicación masiva:
```bash
./ent multiplicar 123456789123456789 987654321987654321
```

## Estructura del Proyecto

```text
calculadora-precision-infinita/
├── src/
│   ├── main.c        # Punto de entrada y análisis de argumentos (CLI)
│   ├── bigint.c      # Funciones base de inicialización y carga binaria
│   ├── bigint.h      # Definición estructural del tipo de dato Bigint
│   ├── ops.c         # Implementación de sumas, restas y multiplicaciones absolutas
│   └── utils.c       # Validaciones auxiliares de tipos y salida de errores
├── Makefile          # Script de compilación modularizado
└── .gitignore        # Exclusiones de binarios compilados
```
