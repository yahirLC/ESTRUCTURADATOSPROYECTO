#include <time.h>

typedef struct Arbol
{
    char isbn[14];
    char titulo[40];
    char autor[35];
    char genero[20];
    int n_ejem;
    struct Arbol *izd;
    struct Arbol *der;
} Arbol;

typedef struct dataUser
{
    int id;
    char name[25];
    int age;
    char gender[15];
    char address[65];
    char phone[12];
} dataUser;

typedef struct node
{
    dataUser info;
    struct node *prev;
    struct node *next;
} Node;

typedef struct transaction
{
    struct Arbol libro; // libro
    struct dataUser datauser;
    time_t fechaTransaccion;
    int tipoTransaccion; // 1 prestamo, 0 devolucion
    struct transaction *siguiente;

} transaction;
