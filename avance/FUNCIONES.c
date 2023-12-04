#include "TIPOS.h"

transaction *crearTransaccion(Arbol arbol, dataUser usuario, int tipoTransaccion)
{
    transaction *nuevaTransaccion = (transaction *)malloc(sizeof(transaction));
    nuevaTransaccion->libro = arbol;
    nuevaTransaccion->datauser = usuario;
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
