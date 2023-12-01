#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funciones.c"

int main(int argc, char const *argv[])
{
    Transaccion *listaTransacciones = NULL;
    Libro *listaLibros = NULL;
    Usuario *listaUsuarios = NULL;

    leerLibrosDesdeArchivo("libros.txt", &listaLibros);

    imprimirListaBusquedaPorISBN(listaLibros, 17474728);

    agregarUsuario(&listaUsuarios, crearUsuario("Juan", "Calle A, Ciudad", "123-456-7890"));
    agregarUsuario(&listaUsuarios, crearUsuario("Maria", "Calle B, Ciudad", "987-654-3210"));
    agregarUsuario(&listaUsuarios, crearUsuario("Carlos", "Calle C, Ciudad", "555-123-4567"));

    // imprimirListaUsuarios(listaUsuarios);

    int isbnBuscado = 17474728;
    Libro *libroEncontrado = buscarLibroPorISBN(listaLibros, isbnBuscado);

    const char *nombreBuscado = "Juan";
    Usuario *usuarioEncontrado = buscarUsuarioPorNombre(listaUsuarios, nombreBuscado);

    if (libroEncontrado != NULL && usuarioEncontrado != NULL)
    {
        // Agregar la transacción con el libro y el usuario encontrados
        agregarTransaccion(&listaTransacciones, libroEncontrado, usuarioEncontrado, 1);
    }
    else
    {
        printf("Libro o usuario no encontrado. No se pudo agregar la transacción.\n");
    }

    imprimirTransacciones(listaTransacciones);

    isbnBuscado = 17474728;
    libroEncontrado = buscarLibroPorISBN(listaLibros, isbnBuscado);

    nombreBuscado = "Maria";
    usuarioEncontrado = buscarUsuarioPorNombre(listaUsuarios, nombreBuscado);

    if (libroEncontrado != NULL && usuarioEncontrado != NULL)
    {
        // Agregar la transacción con el libro y el usuario encontrados
        agregarTransaccion(&listaTransacciones, libroEncontrado, usuarioEncontrado, 1);
    }
    else
    {
        printf("Libro o usuario no encontrado. No se pudo agregar la transacción.\n");
    }

    imprimirTransacciones(listaTransacciones);

    imprimirListaBusquedaPorISBN(listaLibros, 17474728);

    imprimirLista(listaLibros);

    return 0;
}
