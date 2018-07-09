#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodito {
    int mes;
    float monto;
    struct nodito *sig;
} nodito;
typedef struct nodo {
    int nro;
    char nombre[25];
    struct nodo *sig;
    struct nodito *sub;
} nodo;

typedef struct nodo *TLista;
typedef struct nodito *TSubLista;

void insertarContrib(TLista *TL, int nro, char *nombre) {
    TLista act, ant, nuevo;
    act = *TL;
    ant = NULL;
    nuevo = (TLista)malloc(sizeof(nodo));
    nuevo->nro = nro;
    strcpy(nuevo->nombre,nombre);
    nuevo->sub = NULL;
    while (act != NULL && nro > act->nro) {
        ant = act;
        act = act->sig;
    }
    if (ant == NULL) {
        *TL = nuevo;
    } else {
        ant->sig = nuevo;
    }
    nuevo->sig = act;

}

int main()
{

}
