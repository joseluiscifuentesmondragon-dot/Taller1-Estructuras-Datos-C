
#ifndef PATIO_H
#define PATIO_H

#include "contenedor.h"

typedef struct {
    Contenedor elementos[MAX_CONTENEDORES];
    int frente;
    int cantidad;
} Patio;

void patioInicializar(Patio *patio);
int patioEstaLleno(const Patio *patio);
int patioEstaVacio(const Patio *patio);
int patioInsertar(Patio *patio, Contenedor contenedor);
int patioBuscar(const Patio *patio, const char codigo[],
                Contenedor *encontrado);
int patioRetirar(Patio *patio, Contenedor *retirado);
void patioMostrar(const Patio *patio);

#endif