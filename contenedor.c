
#include <ctype.h>
#include <string.h>
#include "contenedor.h"

int validarCodigo(const char codigo[]) {
    if (strlen(codigo) != MAX_CODIGO) {
        return 0;
    }

    for (int i = 0; i < MAX_CODIGO; i++) {
        if (!isalnum((unsigned char)codigo[i])) {
            return 0;
        }
    }

    return 1;
}

int validarPeso(float peso) {
    return peso > 0.0f;
}

int validarTipo(const char tipo[]) {
    return tipo[0] != '\0';
}