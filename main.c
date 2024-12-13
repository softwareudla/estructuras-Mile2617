#include <stdio.h>
#include <string.h>
#include "funciones.h"

#define MaxLibros 20

int main() {
    int NumLibros = 0;
    struct Libro libros[MaxLibros];
    int opc;

    printf("\n");
    printf("  -------- SISTEMA DE GESTION DE BIBLIOTECA -------- \n\n");
    printf(" Bienvenido al sistema de gestion de libros.\n");
    printf(" Ingrese el numero de la opcion deseada: \n");

    do {
        printf("\n-------- Menu de opciones --------\n");
        printf("1. Agregar un libro\n");
        printf("2. Buscar y editar un libro\n");
        printf("3. Eliminar un libro\n");
        printf("4. Imprimir datos de libros\n");
        printf("5. Salir del programa\n");
        printf("Seleccione el numero de la opcion: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                agregarLibro(&NumLibros, libros);
                imprimirLibros(NumLibros, libros);
                break;
            case 2:
                if (NumLibros == 0) {
                    printf("\nNo hay libros registrados.\n");
                } else {
                    if (buscarYEditarLibro(NumLibros, libros)) {
                        imprimirLibros(NumLibros, libros);
                    }
                }
                break;
            case 3:
                if (NumLibros == 0) {
                    printf("\nNo hay libros registrados.\n");
                } else {
                    if (eliminarLibro(&NumLibros, libros)) {
                        imprimirLibros(NumLibros, libros);
                    }
                }
                break;
            case 4:
                imprimirLibros(NumLibros, libros);
                break;
            case 5:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while (opc != 5);

    return 0;
}