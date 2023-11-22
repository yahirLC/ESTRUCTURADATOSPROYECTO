typedef struct Libro
{
    char titulo[100];
    char autor[100];
    char genero[50];
    int ejemplares_disponibles; // podria quitarse y crear solo libros iguales
} Libro;

typedef struct Usuario
{
    char nombre[100];
    char direccion[200];
    char telefono[20];

} Usuario;

typedef struct Transaccion
{
    int id_usuario;
    int id_libro;
} Transaccion;