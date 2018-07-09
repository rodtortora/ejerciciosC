#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    char nombre[25], apellido[25];
    char dni[9];
    int edad;
    struct nodo *sig;} nodo;
typedef struct nodo * TLista;

void inicializar(TLista *TL) {
    *TL = NULL;
}

void recorrer(TLista TL) {
    TLista aux;
    aux = TL;
    while (aux != NULL) {
        printf("%s  ",aux->nombre);
        printf("%s  ",aux->dni);
        printf("%d\n",aux->edad);
        aux = aux->sig;
    }
}

// Lista null
// El item a insertar se inserte el 1ero
// El item a insertar se inserte en el medio o al final
void insertar(TLista *TL, char dni[9], char nombre[25], char apellido[25], int edad) {
    TLista nuevo, aux, ant;
    aux = *TL;
    ant = NULL;
    nuevo = (TLista)malloc(sizeof(nodo));
    strcpy(nuevo->nombre,nombre);
    strcpy(nuevo->apellido,apellido);
    strcpy(nuevo->dni,dni);
    nuevo->edad = edad;
    while(aux != NULL && strcmp(nuevo->dni,aux->dni) == 1) {
        ant = aux;
        aux = aux->sig;
    }
    if (ant != NULL) {
        ant->sig = nuevo;
        nuevo->sig = aux;
    } else {
        (*TL) = nuevo;
        nuevo->sig = aux;
    }
}


int main()
{
    TLista TL;
    inicializar(&TL);
    insertar(&TL, "100", "Rodrigo", "Tortora", 21);
    insertar(&TL, "050", "Jose", "Aaaa", 30);
    insertar(&TL, "075", "Juan", "BBBB", 22);
    insertar(&TL, "060", "Pepe", "CCCCC", 70);
    insertar(&TL, "100", "Rodrigo2", "Tortora", 70);
    recorrer(TL);
    return 0;
}
