
#include <stdio.h>
#include <string.h>
#include "patio.h"

void patioInicializar(Patio *patio) {
    patio->frente = 0;
    patio->cantidad = 0;
}

int patioEstaLleno(const Patio *patio) {
    return patio->cantidad == MAX_CONTENEDORES;
}

int patioEstaVacio(const Patio *patio) {
    return patio->cantidad == 0;
}

int patioInsertar(Patio *patio, Contenedor contenedor) {
    if (patioEstaLleno(patio)) {
        return 0;
    }

    int posicion = (patio->frente + patio->cantidad)
                   % MAX_CONTENEDORES;

    patio->elementos[posicion] = contenedor;
    patio->cantidad++;

    return 1;
}

int patioBuscar(const Patio *patio, const char codigo[],
                Contenedor *encontrado) {
    for (int i = 0; i < patio->cantidad; i++) {
        int posicion = (patio->frente + i)
                       % MAX_CONTENEDORES;

        if (strcmp(patio->elementos[posicion].codigo,
                   codigo) == 0) {
            *encontrado = patio->elementos[posicion];
            return 1;
        }
    }

    return 0;
}

int patioRetirar(Patio *patio, Contenedor *retirado) {
    if (patioEstaVacio(patio)) {
        return 0;
    }

    *retirado = patio->elementos[patio->frente];

    patio->frente = (patio->frente + 1)
                    % MAX_CONTENEDORES;

    patio->cantidad--;

    return 1;
}

void patioMostrar(const Patio *patio) {
    if (patioEstaVacio(patio)) {
        printf("\nEl patio esta vacio.\n");
        return;
    }

    printf("\n===== CONTENEDORES EN EL PATIO =====\n");

    for (int i = 0; i < patio->cantidad; i++) {
        int posicion = (patio->frente + i)
                       % MAX_CONTENEDORES;

        Contenedor actual = patio->elementos[posicion];

        printf("\nCodigo: %s\n", actual.codigo);
        printf("Peso: %.2f toneladas\n", actual.peso);
        printf("Tipo de mercancia: %s\n", actual.tipo);
    }

    printf("\nContenedores activos: %d/%d\n",
           patio->cantidad, MAX_CONTENEDORES);
}