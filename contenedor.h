
#ifndef CONTENEDOR_H
#define CONTENEDOR_H

#define MAX_CONTENEDORES 5
#define MAX_CODIGO 4
#define MAX_TIPO 50

typedef struct {
    char codigo[MAX_CODIGO + 1];
    float peso;
    char tipo[MAX_TIPO];
} Contenedor;

int validarCodigo(const char codigo[]);
int validarPeso(float peso);
int validarTipo(const char tipo[]);

#endif