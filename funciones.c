#include "tipos.h"

void mostrarMenu()
{
    int opcion;
    do
    {
        printf("\n=== Menú Principal ===\n");
        printf("1. Mostrar Catálogo de Libros\n");
        printf("2. Registrar Usuario\n");
        printf("3. Prestar Libro\n");
        printf("4. Devolver Libro\n");
        printf("5. Reservar Libro\n");
        printf("6. Calcular Multas\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            // mostrarCatalogo(catalogo, num_libros);
            break;
        case 2:
            // registrarUsuario(usuarios, &num_usuarios);
            break;
        case 3:
            // prestarLibro(catalogo, num_libros, usuarios, num_usuarios, transacciones, &num_transacciones);
            break;
        case 4:
            // devolverLibro(catalogo, num_libros, transacciones, &num_transacciones);
            break;
        case 5:
            // reservarLibro(catalogo, num_libros, usuarios, num_usuarios);
            break;
        case 6:
            // calcularMultas(transacciones, num_transacciones);
            break;
        case 0:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opción no válida. Por favor, seleccione una opción válida.\n");
        }
    } while (opcion != 0);
}

void mostrarCatalogo(Libro *catalogo, int num_libros);
void registrarUsuario(Usuario *usuarios, int *num_usuarios);
void prestarLibro(Libro *catalogo, int num_libros, Usuario *usuarios, int num_usuarios, Transaccion *transacciones, int *num_transacciones);
void devolverLibro(Libro *catalogo, int num_libros, Transaccion *transacciones, int *num_transacciones);
void reservarLibro(Libro *catalogo, int num_libros, Usuario *usuarios, int num_usuarios);
void calcularMultas(Transaccion *transacciones, int num_transacciones);