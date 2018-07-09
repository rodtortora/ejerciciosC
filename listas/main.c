#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    char nombre[25];
    char apellido[25];
    char DNI[10];
    int edad;
    struct nodo *sig;
} nodo;
typedef struct nodo *TLista;

void inicializarL(TLista *TL) {
    *TL = NULL;
}

void recorrerL(TLista TL) {
    TLista aux;
    aux = TL;
    while (aux != NULL) {
        printf("DNI: %s. Nombre: %s. Apellido: %s. Edad: %d\n",aux->DNI,aux->nombre,aux->apellido,aux->edad);
        aux = aux->sig;
    }
}

void insertar(TLista *TL, char *dni, char *nombre, char *apellido, int edad) {
    TLista act, ant, nuevo;
    act = *TL;
    ant = NULL;
    nuevo = (TLista)malloc(sizeof(nodo));
    strcpy(nuevo->nombre,nombre);
    strcpy(nuevo->apellido,apellido);
    strcpy(nuevo->DNI,dni);
    nuevo->edad = edad;
    // Si es el primero: ant == NULL hay que mover la cabeza
    // Si esta en el medio o al final, ant existira, el act-sig existira
    // Si es el unico ant == NULL hayq ue mover la cabeza
    while(act != NULL && strcmp(nuevo->DNI,act->DNI) == 1) {
        ant = act;
        act = act->sig;
    }
    if (ant == NULL) {
        *TL = nuevo;
        nuevo -> sig = act;
    } else {
        ant->sig = nuevo;
        nuevo->sig = act;
    }
}

void eliminar(TLista *TL, char *dni) {
    TLista act, ant, elim;
    act = *TL;
    ant = NULL;
    while (act != NULL && strcmp(dni,act->DNI) != 0) {
        ant = act;
        act = act->sig;
    }
    //if (strcmp(dni,act->DNI) == 0) {
    if (act != NULL) {
        elim = act;
        if (ant == NULL) {
            *TL = act->sig;
        } else {
            ant->sig = act->sig;
        }
        free(elim);
    }
}

void cambiarEdad(TLista TL, int nuevaEdad, char *dni) {
    TLista aux;
    aux = TL;
    while (aux != NULL && strcmp(aux->DNI,dni) != 0) {
        aux = aux->sig;
    }
    if (aux != NULL) {
        aux->edad = nuevaEdad;
    }
}

int main()
{
    TLista TL;
    inicializarL(&TL);
    insertar(&TL, "100", "Rodrigo", "Tortora", 21);
    insertar(&TL, "050", "Jose", "Aaaa", 30);
    insertar(&TL, "050", "Jose", "Aaaa", 30);
    insertar(&TL, "075", "Juan", "BBBB", 22);
    insertar(&TL, "060", "Pepe", "CCCCC", 70);
    insertar(&TL, "190", "Dalmiro", "Sarate", 70);
    recorrerL(TL);
    eliminar(&TL,"0456456465");
    printf("\nDespues de eliminar:\n");
    recorrerL(TL);
    cambiarEdad(TL,40,"075");
    printf("\nDespues de cambiar edad:\n");
    recorrerL(TL);
    return 0;
}


