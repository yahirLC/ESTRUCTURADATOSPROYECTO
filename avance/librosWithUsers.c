#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FUNCIONES.c"

int countUsers = 0;

void flush()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void principalMenu();

void booksMenu();
Arbol *creaNodo(char *isbn, char *titulo, char *autor, char *genero, int n_ejem);
Arbol *insertar(Arbol *raiz, Arbol *nuevo);
Arbol **buscar(Arbol **raiz, char *isbn);
Arbol *minim(Arbol *nodo);
Arbol *eliminar(Arbol **raiz, char *isbn);
void enOrden(Arbol *raiz);
Arbol *cargar(char *archivo, Arbol *raiz);
void agregar(char *archivo, Arbol *raiz);
void escribir(Arbol *nodo, FILE *file);

void userRegisterMenu();
void userRegisterNewUser(Node **DoubleList);
int userRegisterUniqueID(Node *DoubleList, int id);
void userRegisterInsert(Node **DoubleList, int id, char name[25], int age, char gender[15], char address[65], char phone[12]); // Función dedicada a la creación de un nodo dedicado por usuario
void userRegisterModify(Node **DoubleList);
Node *searchUserID(Node *DoubleList, int id);       // Función de búsqueda de usuario por ID
void userRegisterParticularPrint(Node *DoubleList); // Función dedicada a la impresión de un usuario en particular
void userRegisterTotalPrint(Node *DoubleList);      // Función dedicada a la impresión de todos los usuarios ingresados
void userRegisterParticularFree(Node **DoubleList); // Función dedicada a la eliminación de un usuario en particular
void userRegisterTotalFree(Node **DoubleList);      // Función dedicada a la eliminación de todos los usuarios ingresados

int main()
{
    principalMenu();
    return 0;
}

void principalMenu()
{
    int option = -1;
    while (option != 0 && option <= 5)
    {
        system("cls");
        puts("----------- MENU [PRINCIPAL] -----------\n");
        puts("1. Libros");
        puts("2. Usuarios");
        puts("3. Prestamos y devoluciones");
        puts("4. Reservas");
        puts("5. Multas y recordatorios");
        puts("0. Salir");
        puts("\nSeleccione una opcion: ");

        scanf("%d", &option);
        switch (option)
        {
        case 1:
            booksMenu();
            break;
        case 2:
            userRegisterMenu();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 0:
            puts("Saliendo del programa. Hasta luego!");
            break;
        default:
            puts("Opcion no valida. Intentelo de nuevo.");
        }
    }
}

void booksMenu()
{
    Arbol *raiz = NULL;
    raiz = cargar("libros.txt", raiz);
    int opc = -1, n_ejem;
    char isbn[14], titulo[40], autor[35], genero[20];
    while (opc != 0 && opc <= 5)
    {
        system("cls");
        puts("----------- MENU [LIBROS] -----------\n");
        printf("1. Ingresar libro\n");
        printf("2. Eliminar uno\n");
        printf("3. Visualizar todo :)\n");
        printf("4. Buscar uno\n");
        printf("0. Salir al menu principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            printf("Digite el ISBN: ");
            scanf("%14s", isbn);
            while (getchar() != '\n')
                ;
            printf("Digite el Titulo: ");
            fgets(titulo, sizeof(titulo), stdin);
            titulo[strcspn(titulo, "\n")] = '\0';
            printf("Digite el Autor: ");
            scanf("%35[^\n]", autor);
            while (getchar() != '\n')
                ;
            printf("Digite el Genero: ");
            scanf("%20s", genero);
            printf("Digite el numero de ejemplares: ");
            scanf("%d", &n_ejem);
            Arbol *nuevo = creaNodo(isbn, titulo, autor, genero, n_ejem);
            raiz = insertar(raiz, nuevo);
            break;
        case 2:
            printf("Digite el ISBN: ");
            scanf("%14s", isbn);
            raiz = eliminar(&raiz, isbn);
            printf("isbn eliminado con exito.\n");
            break;
        case 3:
            printf("|---------------|------------------------------------------|-------------------------------------|----------------------|------------|\n");
            printf("| %-13s | %-40s | %-35s | %-20s | %-8s |\n", "ISBN", "Titulo", "Autor", "Genero", "Ejemplares");
            printf("|---------------|------------------------------------------|-------------------------------------|----------------------|------------|\n");
            enOrden(raiz);
            printf("|---------------|------------------------------------------|-------------------------------------|----------------------|------------|\n\n");
            puts("");
            break;
        case 4:
            printf("Digite el ISBN: ");
            scanf("%14s", isbn);
            Arbol **bus = buscar(&raiz, isbn);
            if (*bus != NULL)
                printf("\nEl isbn %s fue encontrado en el arbol.\nDireccion de memoria: %p\nStock: %d\n", isbn, (void *)*bus, (*bus)->n_ejem);
            else
                printf("\nEl isbn %s no fue encontrado en el arbol.\n", isbn);
            break;
        case 0:
            agregar("libros.txt", raiz);
            printf("BYEE\n");
            break;
        default:
            printf("Opcion no valida. Intentelo de nuevo\n");
        }
    }
}

Arbol *creaNodo(char *isbn, char *titulo, char *autor, char *genero, int n_ejem)
{
    Arbol *nuevo = (Arbol *)malloc(sizeof(Arbol));
    strncpy(nuevo->isbn, isbn, sizeof(nuevo->isbn) - 1);
    nuevo->isbn[sizeof(nuevo->isbn) - 1] = '\0';
    strncpy(nuevo->titulo, titulo, sizeof(nuevo->titulo) - 1);
    nuevo->titulo[sizeof(nuevo->titulo) - 1] = '\0';
    strncpy(nuevo->autor, autor, sizeof(nuevo->autor) - 1);
    nuevo->autor[sizeof(nuevo->autor) - 1] = '\0';
    strncpy(nuevo->genero, genero, sizeof(nuevo->genero) - 1);
    nuevo->genero[sizeof(nuevo->genero) - 1] = '\0';
    nuevo->n_ejem = n_ejem;
    nuevo->izd = nuevo->der = NULL;
    return nuevo;
}

Arbol *insertar(Arbol *raiz, Arbol *nuevo)
{
    if (raiz == NULL)
        return nuevo;
    int comparar = strcmp(nuevo->isbn, raiz->isbn);
    if (comparar < 0)
        raiz->izd = insertar(raiz->izd, nuevo);
    else if (comparar > 0)
        raiz->der = insertar(raiz->der, nuevo);
    return raiz;
}

Arbol **buscar(Arbol **raiz, char *isbn)
{
    if (*raiz == NULL || strcmp(isbn, (*raiz)->isbn) == 0)
        return raiz;
    if (strcmp(isbn, (*raiz)->isbn) < 0)
        return buscar(&((*raiz)->izd), isbn);
    else
        return buscar(&((*raiz)->der), isbn);
}

Arbol *minim(Arbol *nodo)
{
    Arbol *actual = nodo;
    while (actual->izd != NULL)
        actual = actual->izd;
    return actual;
}

Arbol *eliminar(Arbol **raiz, char *isbn)
{
    Arbol **eli = buscar(raiz, isbn);
    if (*eli == NULL)
        return *raiz;
    if ((*eli)->izd == NULL)
    {
        Arbol *temp = (*eli)->der;
        free(*eli);
        *eli = temp;
    }
    else if ((*eli)->der == NULL)
    {
        Arbol *temp = (*eli)->izd;
        free(*eli);
        *eli = temp;
    }
    else
    {
        Arbol *temp = minim((*eli)->der);
        strcpy((*eli)->isbn, temp->isbn);
        (*eli)->der = eliminar(&((*eli)->der), temp->isbn);
    }
    return *raiz;
}

void enOrden(Arbol *raiz)
{
    if (raiz != NULL)
    {
        enOrden(raiz->izd);
        printf("| %-13s | %-40s | %-35s | %-20s | %-10d |\n", raiz->isbn, raiz->titulo, raiz->autor, raiz->genero, raiz->n_ejem);
        enOrden(raiz->der);
    }
}

Arbol *cargar(char *archivo, Arbol *raiz)
{
    FILE *file = fopen(archivo, "r");
    if (file == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo %s.\n", archivo);
        exit(EXIT_FAILURE);
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        char isbn[20], titulo[50], autor[30], genero[20];
        int ejemplares;
        sscanf(buffer, "%14[^,],%40[^,],%35[^,],%20[^,],%d", isbn, titulo, autor, genero, &ejemplares);
        Arbol *nuevo = creaNodo(isbn, titulo, autor, genero, ejemplares);
        raiz = insertar(raiz, nuevo);
    }
    fclose(file);
    return raiz;
}

void agregar(char *archivo, Arbol *raiz)
{
    FILE *file = fopen(archivo, "w");
    if (file == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo %s para escribir.\n", archivo);
        exit(EXIT_FAILURE);
    }
    escribir(raiz, file);
    fclose(file);
}

void escribir(Arbol *nodo, FILE *file)
{
    if (nodo != NULL)
    {
        escribir(nodo->izd, file);
        fprintf(file, "%s,%s,%s,%s,%d\n", nodo->isbn, nodo->titulo, nodo->autor, nodo->genero, nodo->n_ejem);
        escribir(nodo->der, file);
    }
}

void userRegisterMenu()
{

    Node *DoubleList = NULL;
    int option = -1;
    /*
        userRegisterInsert(&DoubleList, 1, "Raymundo", 20, "Masculino", "Cristobal Colon #24", "2291082629");
        userRegisterInsert(&DoubleList, 2, "Vanessa", 21, "Femenino", "H. Guiterrez #23", "2291498745");
        userRegisterInsert(&DoubleList, 3, "Victor", 35, "Masculino", "Miguel Aleman #343", "2139459335");
        userRegisterInsert(&DoubleList, 4, "Maria", 28, "Femenino", "Juarez #56", "2278901546");
        userRegisterInsert(&DoubleList, 5, "Javier", 30, "Masculino", "Reforma #102", "2287654321");
        userRegisterInsert(&DoubleList, 6, "Laura", 25, "Femenino", "Benito Juarez #78", "2212345678");
        userRegisterInsert(&DoubleList, 7, "Carlos", 40, "Masculino", "Hidalgo #45", "2345678901");
        userRegisterInsert(&DoubleList, 8, "Ana", 22, "Femenino", "Cuauhtemoc #11", "2298765432");
        userRegisterInsert(&DoubleList, 9, "Luis", 33, "Masculino", "Galeana #67", "2132145678");
        userRegisterInsert(&DoubleList, 10, "Rosa", 27, "Femenino", "Allende #89", "2289876543");
    */
    while (option != 0 && option <= 6)
    {
        system("cls");
        puts("----------- MENU [USUARIOS] -----------\n");
        puts("1. Agregar nuevo usuario");
        puts("2. Modificar un usuario");
        puts("3. Visualizar/Buscar un usuario");
        puts("4. Visualizar todos los usuarios");
        puts("5. Eliminar un usuario");
        puts("6. Eliminar todos los usuarios");
        puts("0. Salir del menu usuarios");
        puts("\nSeleccione una opcion: ");

        scanf("%d", &option);
        switch (option)
        {
        case 1:
            userRegisterNewUser(&DoubleList);
            break;
        case 2:
            userRegisterModify(&DoubleList);
            break;
        case 3:
            userRegisterParticularPrint(DoubleList);
            break;
        case 4:
            userRegisterTotalPrint(DoubleList);
            break;
        case 5:
            userRegisterParticularFree(&DoubleList);
            break;
        case 6:
            userRegisterTotalFree(&DoubleList);
            break;
        case 0:
            principalMenu();
            break;
        default:
            puts("Opcion no valida. Intentelo de nuevo.");
        }
    }
}

void userRegisterNewUser(Node **DoubleList)
{
    system("cls");
    int id;
    char name[25];
    int age;
    char gender[15];
    char address[65];
    char phone[12];

    puts("\nNUEVO USUARIO: ");
    puts("Ingresa los campos solicitados: ");
    Node *userInList;
    while (userInList)
    {
        flush();
        puts("ID: ");
        scanf("%d", &id);
        userInList = searchUserID(*DoubleList, id);
        if (userInList)
        {
            printf("Error: El ID #%d no esta disponible, te sugiero intentar con ID #%d\n", id, countUsers + 1);
        }
    }
    flush();
    puts("Nombre: ");
    scanf("%[^\n]", name);
    flush();
    puts("Edad: ");
    scanf("%d", &age);
    flush();
    puts("Genero: ");
    scanf("%[^\n]", gender);
    flush();
    puts("Domicilio: ");
    scanf("%[^\n]", address);
    flush();
    puts("Telefono: ");
    scanf("%[^\n]", phone);

    system("cls");
    puts("\nDATOS INGRESADOS: ");
    printf("ID: %d\n", id);
    printf("Nombre: %s\n", name);
    printf("Edad: %d\n", age);
    printf("Genero: %s\n", gender);
    printf("Domicilio: %s\n", address);
    printf("Telefono: %s\n\n", phone);

    int option = -1;
    puts("- - - - - MENU DE OPCIONES: - - - - -");
    puts("  1. Confirmar ");
    puts("  2. Editar ");
    puts("  3. Confirmar y agregar otro usuario ");
    puts("  0. Cancelar\n");
    puts("  Seleccione una opcion: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        userRegisterInsert(DoubleList, id, name, age, gender, address, phone);
        break;
    case 2:
        userRegisterNewUser(DoubleList);
        break;
    case 3:
        userRegisterInsert(DoubleList, id, name, age, gender, address, phone);
        userRegisterNewUser(DoubleList);
        break;
    case 0:
        break;
    default:
        puts("Opcion no valida. Intentelo de nuevo.");
    }
}

int userRegisterUniqueID(Node *DoubleList, int id)
{
    Node *userInList = searchUserID(DoubleList, id);
    if (userInList)
    {
        printf("Error: El ID #%d no esta disponible\n", id);
        return 1;
    }
    return 0;
}

void userRegisterInsert(Node **DoubleList, int id, char name[25], int age, char gender[15], char address[65], char phone[12])
{
    // Creación un nuevo nodo destinado a un nuevo usuario
    Node *newUser = (Node *)malloc(sizeof(Node));
    if (!newUser)
    {
        puts("No ha sido posible ingresar un nuevo usuario.");
        return;
    }

    // Inserción de datos de usuario en el nuevo nodo dedicado
    newUser->info.id = id;
    strcpy(newUser->info.name, name);
    newUser->info.age = age;
    strcpy(newUser->info.gender, gender);
    strcpy(newUser->info.address, address);
    strcpy(newUser->info.phone, phone);

    // Conexión del nuevo nodo agregado como lista enlazada doble
    newUser->prev = NULL;
    if (*DoubleList)
        (*DoubleList)->prev = newUser;
    newUser->next = *DoubleList;
    *DoubleList = newUser;

    countUsers++;
}

void userRegisterModify(Node **DoubleList)
{
    if (!*DoubleList)
        return;
    int option = -1;
    int id;
    system("cls");
    puts("- - - - - MODIFICAR INFORMACION DE USUARIO - - - - -\n");
    puts("Ingresa el ID del usuario a modificar: ");
    flush();
    scanf("%d", &id);
    Node *userInList = searchUserID(*DoubleList, id);
    if (!userInList)
    {
        system("cls");
        puts("- - - - - MODIFICAR INFORMACION DE USUARIO - - - - -\n");
        printf("No se ha ingresado el usuario con ID #%d", id);
    }
    system("cls");
    printf("- - - - - MODIFICAR INFORMACION DE USUARIO #%d - - - - -\n", id);
    puts("1. Nombre");
    puts("2. Edad");
    puts("3. Genero");
    puts("4. Domicilio");
    puts("5. Telefono");
    puts("Seleccione una opcion: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        system("cls");
        printf("- - - - - MODIFICAR INFORMACION DE USUARIO #%d - - - - -\n", id);
        puts("Nombre: ");
        flush();
        scanf("%[^\n]", userInList->info.name);
        break;
    case 2:
        system("cls");
        printf("- - - - - MODIFICAR INFORMACION DE USUARIO #%d - - - - -\n", id);
        puts("Edad: ");
        flush();
        scanf("%d", &userInList->info.age);
        break;
    case 3:
        system("cls");
        printf("- - - - - MODIFICAR INFORMACION DE USUARIO #%d - - - - -\n", id);
        puts("Genero: ");
        flush();
        scanf("%[^\n]", userInList->info.gender);
        break;
    case 4:
        system("cls");
        printf("- - - - - MODIFICAR INFORMACION DE USUARIO #%d - - - - -\n", id);
        puts("Domicilio: ");
        flush();
        scanf("%[^\n]", userInList->info.address);
        break;
    case 5:
        system("cls");
        printf("- - - - - MODIFICAR INFORMACION DE USUARIO #%d - - - - -\n", id);
        puts("Telefono: ");
        scanf("%[^\n]", userInList->info.phone);
        flush();
        break;
    case 0:
        break;
    default:
        puts("Opcion no valida. Intentelo de nuevo.");
        break;
    }
    system("cls");
    printf("- - - - - MODIFICAR INFORMACION DE USUARIO #%d - - - - -\n");
    printf("USUARIO #%d\n", userInList->info.id);
    printf("Nombre: %s\n", userInList->info.name);
    printf("Edad: %d\n", userInList->info.age);
    printf("Genero: %s\n", userInList->info.gender);
    printf("Domicilio: %s\n", userInList->info.address);
    printf("Telefono: %s\n\n", userInList->info.phone);

    int option2 = -1;
    puts("- - - - - MENU DE OPCIONES: - - - - -");
    puts("  1. Modificar otro dato o usuario");
    puts("  2. Visualizar todos los usuarios ");
    puts("  3. Eliminar un usuario en particular ");
    puts("  0. Regresar al menu usuarios\n");
    puts("  Seleccione una opcion: ");
    scanf("%d", &option2);
    switch (option2)
    {
    case 1:
        userRegisterModify(DoubleList);
        break;
    case 2:
        userRegisterTotalPrint(*DoubleList);
        break;
    case 3:
        userRegisterParticularFree(DoubleList);
        break;
    case 0:
        break;
    default:
        puts("Opcion no valida. Intentelo de nuevo.");
    }
}

Node *searchUserID(Node *DoubleList, int id)
{
    if (!DoubleList)
        return NULL;
    Node *temp = DoubleList;
    while (temp)
    {
        if (temp->info.id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void userRegisterParticularPrint(Node *DoubleList)
{
    system("cls");
    if (!DoubleList)
    {
        puts("No hay usuarios ingresados actualmente.");
        return;
    }
    int id;
    puts("- - - - - SOLICITAR UN USUARIO - - - - - \n");
    puts("Ingresa el ID del usuario requerido: ");
    scanf("%d", &id);

    Node *userInListID = searchUserID(DoubleList, id);
    if (!userInListID)
    {
        system("cls");
        puts("- - - - - SOLICITAR UN USUARIO - - - - - \n");
        printf("Usuario con ID #%d no encontrado\n", id);
        int option = -1;
        puts("\n- - - - - MENU DE OPCIONES: - - - - -");
        puts("  1. Visualizar otro usuario ");
        puts("  2. Visualizar todos los usuarios ");
        puts("  3. Eliminar un usuario en particular ");
        puts("  0. Regresar al menu usuarios\n");
        puts("  Seleccione una opcion: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            userRegisterParticularPrint(DoubleList);
            break;
        case 2:
            userRegisterTotalPrint(DoubleList);
            break;
        case 3:
            userRegisterParticularFree(&DoubleList);
            break;
        case 0:
            break;
        default:
            puts("Opcion no valida. Intentelo de nuevo.");
        }
        return;
    }

    system("cls");
    printf("- - - - - INFORMACION DE USUARIO #%d - - - - -\n", id);
    printf("USUARIO #%d\n", userInListID->info.id);
    printf("Nombre: %s\n", userInListID->info.name);
    printf("Edad: %d\n", userInListID->info.age);
    printf("Genero: %s\n", userInListID->info.gender);
    printf("Domicilio: %s\n", userInListID->info.address);
    printf("Telefono: %s\n\n", userInListID->info.phone);

    int option = -1;
    puts("- - - - - MENU DE OPCIONES: - - - - -");
    puts("  1. Visualizar otro usuario ");
    puts("  2. Visualizar todos los usuarios ");
    puts("  3. Eliminar un usuario en particular ");
    puts("  0. Regresar al menu usuarios\n");
    puts("  Seleccione una opcion: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        userRegisterParticularPrint(DoubleList);
        break;
    case 2:
        userRegisterTotalPrint(DoubleList);
        break;
    case 3:
        userRegisterParticularFree(&DoubleList);
        break;
    case 0:
        break;
    default:
        puts("Opcion no valida. Intentelo de nuevo.");
    }
}

void userRegisterTotalPrint(Node *DoubleList)
{
    if (!DoubleList)
    {
        puts("No hay usuarios ingresados actualmente\n");
        return;
    }
    system("cls");
    puts("- - - - - - - - - - USUARIOS [BIBLIOTECA] - - - - - - - - - -\n");
    printf("Total de usuarios: %d\n\n", countUsers);
    while (DoubleList)
    {
        printf("USUARIO #%d\n", DoubleList->info.id);
        printf("Nombre: %s\n", DoubleList->info.name);
        printf("Edad: %d\n", DoubleList->info.age);
        printf("Genero: %s\n", DoubleList->info.gender);
        printf("Domicilio: %s\n", DoubleList->info.address);
        printf("Telefono: %s\n\n", DoubleList->info.phone);
        DoubleList = DoubleList->next;
    }
    int option = -1;
    puts("- - - - - MENU DE OPCIONES: - - - - -");
    puts("  1. Visualizar un usuario en particular ");
    puts("  2. Eliminar un usuario en particular ");
    puts("  0. Regresar al menu usuarios\n");
    puts("  Seleccione una opcion: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        userRegisterParticularPrint(DoubleList);
        break;
    case 2:
        userRegisterParticularFree(&DoubleList);
        break;
    case 0:
        break;
    default:
        puts("Opcion no valida. Intentelo de nuevo.");
    }
}

void userRegisterParticularFree(Node **DoubleList)
{
    if (!DoubleList)
    {
        puts("No hay usuarios ingresados actualmente.");
        return;
    }
    int id;
    system("cls");
    puts("- - - - - ELIMINAR UN USUARIO - - - - - \n");
    puts("Ingresa el ID del usuario a eliminar: ");
    scanf("%d", &id);

    Node *userInListID = searchUserID(*DoubleList, id);
    if (!userInListID)
    {
        system("cls");
        puts("- - - - - ELIMINAR UN USUARIO - - - - - \n");
        printf("Usuario con ID #%d no encontrado\n", id);
        int option = -1;
        puts("\n- - - - - MENU DE OPCIONES: - - - - -");
        puts("  1. Eliminar otro usuario ");
        puts("  2. Visualizar un usuario en particular ");
        puts("  3. Visualizar todos los usuarios ");
        puts("  0. Regresar al menu usuarios\n");
        puts("  Seleccione una opcion: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            userRegisterParticularFree(DoubleList);
            break;
        case 2:
            userRegisterParticularPrint(*DoubleList);
            break;
        case 3:
            userRegisterTotalPrint(*DoubleList);
        case 0:
            break;
        default:
            puts("Opcion no valida. Intentelo de nuevo.");
        }
        return;
    }

    if (userInListID == *DoubleList)
    {
        *DoubleList = (*DoubleList)->next;
        (*DoubleList)->prev = NULL;
    }
    else
    {
        userInListID->prev->next = userInListID->next;
        if (userInListID->next)
            userInListID->next->prev = userInListID->prev;
    }
    free(userInListID);
    system("cls");
    printf("- - - - - ELIMINAR USUARIO #%d - - - - - \n", id);
    puts("\nUsuario eliminado exitosamente\n");

    int option = -1;
    puts("- - - - - MENU DE OPCIONES: - - - - -");
    puts("  1. Eliminar otro usuario ");
    puts("  2. Visualizar un usuario en particular ");
    puts("  3. Visualizar todos los usuarios ");
    puts("  0. Regresar al menu usuarios\n");
    puts("  Seleccione una opcion: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        userRegisterParticularFree(DoubleList);
        break;
    case 2:
        userRegisterParticularPrint(*DoubleList);
        break;
    case 3:
        userRegisterTotalPrint(*DoubleList);
    case 0:
        break;
    default:
        puts("Opcion no valida. Intentelo de nuevo.");
    }
    countUsers--;
}

void userRegisterTotalFree(Node **DoubleList)
{
    if (!*DoubleList)
        return;
    system("cls");
    int option = -1;
    puts("- - - - - ELIMINAR TODOS LOS USUARIOS - - - - - \n");
    puts("Desea eliminar todos los usuarios ingresados en biblioteca?");
    puts("1. Si");
    puts("2. No");

    while (option != 1)
    {
        scanf("%d", &option);
        if (option == 1)
        {
            Node *temp = *DoubleList;
            while (*DoubleList)
            {
                *DoubleList = (*DoubleList)->next;
                free(temp);
                temp = *DoubleList;
            }
            puts("Todos los usuarios han sido eliminados exitosamente\n");
            break;
        }
        else
        {
            puts("Eliminacion NO realizada\n");
            break;
        }
    }
    int option2 = -1;
    puts("- - - - - - - - - - - - - - -");
    puts("1. Volver al menu usuarios\n");
    while (option2 != 1)
    {
        scanf("%d", &option2);
        if (option2 == 1)
            return;
    }
    countUsers = 0;
}