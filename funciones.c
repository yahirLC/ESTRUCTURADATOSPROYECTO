#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"

// LIBROS --------------------------------------------------------------------------------

// agrega a una lista
void agregarLibro(Libro **lista, Libro *nuevoLibro)
{
    nuevoLibro->siguiente = *lista;
    nuevoLibro->estado = 1;
    *lista = nuevoLibro;
}

// leer txt
void leerLibrosDesdeArchivo(const char *nombreArchivo, Libro **lista)
{
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo: %s\n", nombreArchivo);
        return;
    }

    while (!feof(archivo))
    {

        Libro *nuevoLibro = (Libro *)malloc(sizeof(Libro));
        if (fscanf(archivo, "%99[^,], %99[^,], %49[^,], %d, %d\n", nuevoLibro->titulo, nuevoLibro->autor, nuevoLibro->genero, &nuevoLibro->isbn, &nuevoLibro->estado) == 5)
        {
            // agregar a la lista enlazada

            nuevoLibro->usuario = NULL; // se inicializa null por que aun no ha sido prestado
            agregarLibro(lista, nuevoLibro);
        }
        else
        {
            free(nuevoLibro); // se libera por si no se leyó bn
        }
    }

    fclose(archivo);
}

// imprime la lista enn consola
void imprimirLista(Libro *lista)
{

    while (lista != NULL)
    {

        printf("Título: %s\nAutor: %s\nGenero: %s\nISBN: %d\nEstado: %d\n\n",
               lista->titulo, lista->autor, lista->genero, lista->isbn, lista->estado);
        lista = lista->siguiente;
    }
}

// imprime pero con busqueda
void imprimirListaBusqueda(Libro *lista, const char *busqueda)
{
    while (lista != NULL)
    {

        // Comparar el título del libro con la cadena de búsqueda
        if ((strcmp(lista->titulo, busqueda) == 0) || (strcmp(lista->autor, busqueda) == 0) || (strcmp(lista->genero, busqueda) == 0))
        {
            printf("Título: %s\nAutor: %s\nGenero: %s\nISBN: %d\nEstado: %d\n\n",
                   lista->titulo, lista->autor, lista->genero, lista->isbn, lista->estado);
            lista = lista->siguiente;
        }
        lista = lista->siguiente;
    }
}

void imprimirListaBusquedaPorISBN(Libro *lista, int isbnBusqueda)
{
    while (lista != NULL)
    {

        if (lista->isbn == isbnBusqueda)
        {
            const char *estadoStr = (lista->estado == 1) ? "Disponible" : "No disponible";

            printf("Título: %s\nAutor: %s\nGenero: %s\nISBN: %d\nEstado: %s\n\n",
                   lista->titulo, lista->autor, lista->genero, lista->isbn, estadoStr);
            return;
        }
        lista = lista->siguiente;
    }

    printf("Libro con ISBN %d no encontrado.\n", isbnBusqueda);
}

// USUARIOS ----------------------------------------------------------------------------

void agregarUsuario(Usuario **lista, Usuario *nuevoUsuario)
{
    nuevoUsuario->siguiente = *lista;
    *lista = nuevoUsuario;
}

void imprimirListaUsuarios(Usuario *lista)
{
    while (lista != NULL)
    {
        printf("Nombre: %s\nDirección: %s\nTeléfono: %s\n\n",
               lista->nombre, lista->direccion, lista->telefono);
        lista = lista->siguiente;
    }
}

Usuario *crearUsuario(const char *nombre, const char *direccion, const char *telefono)
{
    Usuario *nuevoUsuario = (Usuario *)malloc(sizeof(Usuario));

    if (nuevoUsuario != NULL)
    {
        strcpy(nuevoUsuario->nombre, nombre);
        strcpy(nuevoUsuario->direccion, direccion);
        strcpy(nuevoUsuario->telefono, telefono);
        nuevoUsuario->siguiente = NULL;
    }

    return nuevoUsuario;
}

// TRANSACCIONES ------------------------------------------------------------------------

Transaccion *crearTransaccion(Libro libro, Usuario usuario, int tipoTransaccion)
{
    Transaccion *nuevaTransaccion = (Transaccion *)malloc(sizeof(Transaccion));
    nuevaTransaccion->libro = libro;
    nuevaTransaccion->usuario = usuario;
    nuevaTransaccion->tipoTransaccion = tipoTransaccion;
    nuevaTransaccion->fechaTransaccion = time(NULL);
    nuevaTransaccion->siguiente = NULL;
    return nuevaTransaccion;
}

void agregarTransaccion(Transaccion **lista, Libro *libro, Usuario *usuario, int tipoTransaccion)
{
    Transaccion *nuevaTransaccion = crearTransaccion(*libro, *usuario, tipoTransaccion);

    if (libro->estado == 1)
    {
        libro->estado = 0;
        nuevaTransaccion->siguiente = *lista;
        *lista = nuevaTransaccion;
    }
    else
    {
        printf("El libro ya ha sido prestado!\n\n");

        printf("Desea realizar una reserva para cuando este disponible? Y/N: ");

        char respuesta;
        scanf(" %c", &respuesta);

        if (respuesta == 'Y' || respuesta == 'y')
        {
            printf("Reserva realizada con éxito. Le notificaremos cuando el libro esté disponible.\n");
                }
        else if (respuesta == 'N' || respuesta == 'n')
        {
            printf("No se ha realizado ninguna reserva.\n");
        }
        else
        {
            printf("Respuesta no válida.\n");
        }
    }
}

void imprimirTransacciones(Transaccion *lista)
{
    while (lista != NULL)
    {
        printf("Usuario: %s, Libro: %s, isbn: %d, %s, Fecha: %s\n", lista->usuario.nombre, lista->libro.titulo, lista->libro.isbn,
               lista->tipoTransaccion ? "Préstamo" : "Devolución", ctime(&lista->fechaTransaccion));
        lista = lista->siguiente;
    }
}

Libro *buscarLibroPorISBN(Libro *lista, int isbn)
{
    while (lista != NULL)
    {
        if (lista->isbn == isbn)
        {
            // Se encontró el libro, se retorna
            return lista;
        }
        lista = lista->siguiente;
    }

    // Si no se encuentra el libro, se retorna NULL
    return NULL;
}

Usuario *buscarUsuarioPorNombre(Usuario *lista, const char *nombre)
{
    while (lista != NULL)
    {
        if (strcmp(lista->nombre, nombre) == 0)
        {
            // Se encontró el usuario, se retorna
            return lista;
        }
        lista = lista->siguiente;
    }

    // Si no se encuentra el usuario, se retorna NULL
    return NULL;
}
