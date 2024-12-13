#include <stdio.h>
#include <string.h>
#include "funciones.h"

void agregarLibro(int *NumLibros, struct Libro libros[]) {
    if (*NumLibros >= MaxLibros) {
        printf("No se pueden agregar mas libros.\n");
        return;
    }

    int id;
    printf("\nIngrese el ID del libro: ");
    scanf("%d", &id);

    if (buscarLibroPorID(id, *NumLibros, libros) != -1) {
        printf("El ID ya existe. No se puede registrar el libro.\n");
        return;
    }

    libros[*NumLibros].id = id;

    printf("Ingrese el titulo del libro: ");
    getchar();
    fgets(libros[*NumLibros].titulo, 100, stdin);
    size_t length = strlen(libros[*NumLibros].titulo);
    if (length > 0 && libros[*NumLibros].titulo[length - 1] == '\n') {
        libros[*NumLibros].titulo[length - 1] = '\0';
    }

    printf("Ingrese el autor del libro: ");
    fgets(libros[*NumLibros].autor, 50, stdin);
    length = strlen(libros[*NumLibros].autor);
    if (length > 0 && libros[*NumLibros].autor[length - 1] == '\n') {
        libros[*NumLibros].autor[length - 1] = '\0';
    }

    do {
        printf("Ingrese el anio de publicacion: ");
        scanf("%d", &libros[*NumLibros].aa);
    } while (libros[*NumLibros].aa <= 0);

    strcpy(libros[*NumLibros].estado, "Disponible");
    (*NumLibros)++;
    printf("\nLibro agregado exitosamente.\n");
}

int buscarLibroPorID(int id, int NumLibros, struct Libro libros[]) {
    for (int i = 0; i < NumLibros; i++) {
        if (libros[i].id == id) {
            return i;
        }
    }
    return -1;
}

int buscarLibroPorTitulo(const char *titulo, int NumLibros, struct Libro libros[]) {
    for (int i = 0; i < NumLibros; i++) {
        if (strcmp(libros[i].titulo, titulo) == 0) {
            return i;
        }
    }
    return -1;
}

int buscarYEditarLibro(int NumLibros, struct Libro libros[]) {
    int opcion;
    printf("\nBuscar libro por: 1. ID, 2. Titulo: ");
    scanf("%d", &opcion);

    int bandera = -1;
    if (opcion == 1) {
        int id;
        printf("\nIngrese el ID del libro: ");
        scanf("%d", &id);
        bandera = buscarLibroPorID(id, NumLibros, libros);
    } else if (opcion == 2) {
        char titulo[100];
        printf("\nIngrese el titulo del libro: ");
        getchar();
        fgets(titulo, 100, stdin);
        size_t length = strlen(titulo);
        if (length > 0 && titulo[length - 1] == '\n') {
            titulo[length - 1] = '\0';
        }
        bandera = buscarLibroPorTitulo(titulo, NumLibros, libros);
    } else {
        printf("Opcion no valida.\n");
        return 0;
    }

    if (bandera == -1) {
        printf("\nLibro no encontrado.\n");
        return 0;
    }

    printf("\nLibro encontrado:\n");
    printf("ID: %d\n", libros[bandera].id);
    printf("Titulo: %s\n", libros[bandera].titulo);
    printf("Autor: %s\n", libros[bandera].autor);
    printf("Anio de publicacion: %d\n", libros[bandera].aa);
    printf("Estado: %s\n", libros[bandera].estado);

    int deseaEditar;
    printf("\nDesea editar este libro? 1. Si, 2. No: ");
    scanf("%d", &deseaEditar);

    if (deseaEditar != 1) {
        printf("\nVolviendo al menu principal.\n");
        return 0;
    }

    int editarOpc;
    do {
        printf("\nOpciones para editar:\n");
        printf("1. Titulo\n");
        printf("2. Autor\n");
        printf("3. Anio de publicacion\n");
        printf("4. Estado\n");
        printf("5. Salir de edicion\n");
        printf("Seleccione el numero de la opcion: ");
        scanf("%d", &editarOpc);

        switch (editarOpc) {
            case 1:
                printf("Ingrese el nuevo titulo del libro: ");
                getchar();
                fgets(libros[bandera].titulo, 100, stdin);
                size_t length = strlen(libros[bandera].titulo);
                if (length > 0 && libros[bandera].titulo[length - 1] == '\n') {
                    libros[bandera].titulo[length - 1] = '\0';
                }
                break;
            case 2:
                printf("Ingrese el nuevo autor del libro: ");
                getchar();
                fgets(libros[bandera].autor, 50, stdin);
                length = strlen(libros[bandera].autor);
                if (length > 0 && libros[bandera].autor[length - 1] == '\n') {
                    libros[bandera].autor[length - 1] = '\0';
                }
                break;
            case 3:
                do {
                    printf("Ingrese el nuevo Anio de publicacion: ");
                    scanf("%d", &libros[bandera].aa);
                } while (libros[bandera].aa <= 0);
                break;
            case 4:
                if (strcmp(libros[bandera].estado, "Disponible") == 0) {
                    strcpy(libros[bandera].estado, "Prestado");
                } else {
                    strcpy(libros[bandera].estado, "Disponible");
                }
                printf("\nEl estado del libro ha sido cambiado a: %s\n", libros[bandera].estado);
                break;
            case 5:
                printf("Saliendo de la edicion.\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while (editarOpc != 5);

    printf("\nEdicion finalizada.\n");
    return 1;
}

int eliminarLibro(int *NumLibros, struct Libro libros[]) {
    int id;
    printf("\nIngrese el ID del libro a eliminar: ");
    scanf("%d", &id);

    int bandera = buscarLibroPorID(id, *NumLibros, libros);
    if (bandera == -1) {
        printf("\nLibro no encontrado.\n");
        return 0;
    }

    for (int i = bandera; i < *NumLibros - 1; i++) {
        libros[i] = libros[i + 1];
    }
    (*NumLibros)--;
    printf("\nLibro eliminado exitosamente.\n");
    return 1;
}

void imprimirLibros(int NumLibros, struct Libro libros[]) {
    if (NumLibros == 0) {
        printf("\nNo hay libros registrados.\n");
        return;
    }
    int largoID = strlen("ID");
    int largoTit = strlen("Titulo");
    int largoAut = strlen("Autor");
    int largoAnio = strlen("Anio");
    int largoEst = strlen("Estado");

    for (int i = 0; i < NumLibros; i++) {
        if (largoID < snprintf(NULL, 0, "%d", libros[i].id)) {
            largoID = snprintf(NULL, 0, "%d", libros[i].id);
        }
        if (largoTit < strlen(libros[i].titulo)) {
            largoTit = strlen(libros[i].titulo);
        }
        if (largoAut < strlen(libros[i].autor)) {
            largoAut = strlen(libros[i].autor);
        }
        if (largoAnio < snprintf(NULL, 0, "%d", libros[i].aa)) {
            largoAnio = snprintf(NULL, 0, "%d", libros[i].aa);
        }
        if (largoEst < strlen(libros[i].estado)) {
            largoEst = strlen(libros[i].estado);
        }
       
    }
    printf("\n ------------- Lista de Libros ----------- \n");
    printf("%-*s\t%-*s\t%-*s\t%-*s\t%-*s\n", 
           largoID, "ID", 
           largoTit, "TITULO", 
           largoAut, "AUTOR", 
           largoAnio, "ANIO", 
           largoEst, "ESTADO");
           
    for (int i = 0; i < NumLibros; i++) {
        printf("%-*d\t%-*s\t%-*s\t%-*d\t%-*s \n", largoID,libros[i].id, largoTit,libros[i].titulo, largoAut,libros[i].autor, largoAnio,libros[i].aa, largoEst,libros[i].estado);
}
}