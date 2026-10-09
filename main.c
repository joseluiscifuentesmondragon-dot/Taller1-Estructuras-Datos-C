
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contenedor.h"
#include "patio.h"

void leerTexto(const char mensaje[], char destino[], int capacidad) {
    printf("%s", mensaje);

    if (fgets(destino, capacidad, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }

    size_t longitud = strlen(destino);

    if (longitud > 0 && destino[longitud - 1] == '\n') {
        destino[longitud - 1] = '\0';
    } else {
        int caracter;
        while ((caracter = getchar()) != '\n' &&
               caracter != EOF) {
        }
    }
}

int leerOpcion(void) {
    char entrada[30];
    char extra;
    int opcion;

    leerTexto("Seleccione una opcion: ", entrada,
              sizeof(entrada));

    if (sscanf(entrada, "%d %c", &opcion, &extra) != 1) {
        return -1;
    }

    return opcion;
}

void registrarContenedor(Patio *patio) {
    if (patioEstaLleno(patio)) {
        printf("\nEl patio esta lleno. No se puede registrar.\n");
        return;
    }

    Contenedor nuevo;
    char pesoTexto[50];
    char extra;
    float peso;

    leerTexto("Codigo alfanumerico de 4 caracteres: ",
              nuevo.codigo, sizeof(nuevo.codigo));

    if (!validarCodigo(nuevo.codigo)) {
        printf("Error: el codigo debe tener 4 letras o numeros.\n");
        return;
    }

    Contenedor existente;

    if (patioBuscar(patio, nuevo.codigo, &existente)) {
        printf("Error: ya existe un contenedor con ese codigo.\n");
        return;
    }

    leerTexto("Peso en toneladas: ", pesoTexto,
              sizeof(pesoTexto));

    if (sscanf(pesoTexto, "%f %c", &peso, &extra) != 1 ||
        !validarPeso(peso)) {
        printf("Error: ingrese un peso numerico mayor que cero.\n");
        return;
    }

    nuevo.peso = peso;

    leerTexto("Tipo de mercancia: ", nuevo.tipo,
              sizeof(nuevo.tipo));

    if (!validarTipo(nuevo.tipo)) {
        printf("Error: el tipo de mercancia no puede estar vacio.\n");
        return;
    }

    if (patioInsertar(patio, nuevo)) {
        printf("\nContenedor registrado correctamente.\n");
    } else {
        printf("No fue posible registrar el contenedor.\n");
    }
}

void buscarContenedor(const Patio *patio) {
    char codigo[MAX_CODIGO + 1];
    Contenedor encontrado;

    leerTexto("Ingrese el codigo que desea buscar: ",
              codigo, sizeof(codigo));

    if (!validarCodigo(codigo)) {
        printf("Error: el codigo debe tener 4 caracteres.\n");
        return;
    }

    if (patioBuscar(patio, codigo, &encontrado)) {
        printf("\nContenedor encontrado:\n");
        printf("Codigo: %s\n", encontrado.codigo);
        printf("Peso: %.2f toneladas\n", encontrado.peso);
        printf("Mercancia: %s\n", encontrado.tipo);
    } else {
        printf("No se encontro ese contenedor.\n");
    }
}

void retirarContenedor(Patio *patio) {
    Contenedor retirado;

    if (patioRetirar(patio, &retirado)) {
        printf("\nContenedor retirado mediante FIFO:\n");
        printf("Codigo: %s\n", retirado.codigo);
    } else {
        printf("\nNo hay contenedores para retirar.\n");
    }
}

int main(void) {
    Patio patio;
    patioInicializar(&patio);

    int opcion;

    do {
        printf("\n===== PUERTO MANAGER =====\n");
        printf("1. Registrar contenedor\n");
        printf("2. Mostrar contenedores\n");
        printf("3. Buscar contenedor\n");
        printf("4. Retirar primer contenedor (FIFO)\n");
        printf("5. Consultar ocupacion del patio\n");
        printf("0. Salir\n");

        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                registrarContenedor(&patio);
                break;

            case 2:
                patioMostrar(&patio);
                break;

            case 3:
                buscarContenedor(&patio);
                break;

            case 4:
                retirarContenedor(&patio);
                break;

            case 5:
                printf("\nOcupacion: %d de %d contenedores.\n",
                       patio.cantidad, MAX_CONTENEDORES);
                break;

            case 0:
                printf("\nCerrando Puerto Manager...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente nuevamente.\n");
        }

    } while (opcion != 0);

    return 0;
}