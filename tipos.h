#include <time.h>

typedef struct Libro
{
    char titulo[100];
    char autor[100];
    char genero[50];
    int isbn;
    int estado; // 1 disponible, 0 no disponible
    struct Usuario *usuario;
    struct Libro *siguiente;
} Libro;

typedef struct Usuario
{
    char nombre[100];
    char direccion[200];
    char telefono[20];
    struct Usuario *siguiente;

} Usuario;

typedef struct Transaccion
{
    struct Libro libro;
    struct Usuario usuario;
    time_t fechaTransaccion;
    int tipoTransaccion; // 1 prestamo, 0 devolucion
    struct Transaccion *siguiente;

} Transaccion;