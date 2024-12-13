
#define FUNCIONES_H

#define MaxLibros 20

struct Libro {
    int id;
    char titulo[100];
    char autor[50];
    int aa;
    char estado[20];
};

void agregarLibro(int *NumLibros, struct Libro libros[]);
int buscarYEditarLibro(int NumLibros, struct Libro libros[]);
int eliminarLibro(int *NumLibros, struct Libro libros[]);
void imprimirLibros(int NumLibros, struct Libro libros[]);
int buscarLibroPorID(int id, int NumLibros, struct Libro libros[]);
int buscarLibroPorTitulo(const char *titulo, int NumLibros, struct Libro libros[]);
