#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *sig;
} nodo;
typedef struct nodo *TLista;

void insertarLista(TLista *TL, int x) {
    TLista aux, ant, nuevo;
    nuevo = (TLista)malloc(sizeof(nodo));
    nuevo->dato = x;
    aux = *TL;
    ant = NULL;
    while (aux != NULL) {
        ant = aux;
        aux = aux->sig;
    }
    if (ant == NULL) {
        *TL = nuevo;
        nuevo->sig = NULL;
    } else {
        ant->sig = nuevo;
        nuevo->sig = NULL;
    }
}

void recorrerLista(TLista TL) {
    TLista aux;
    aux = TL;
    while (aux != NULL) {
        printf("\n%d",aux->dato);
        aux = aux->sig;
    }
}

int contarPares(TLista TL) {
    TLista aux;
    int cantPar = 0;
    aux = TL;
    while (aux != NULL) {
        if (aux->dato %2 == 0) {
            cantPar++;
        }
        aux = aux->sig;
    }
    return cantPar;
}

void contarParesRecursivo(TLista TL, int *pares) {
    TLista aux;
    aux = TL;
    while (aux != NULL) {
        if (aux->dato %2 == 0) {
            *pares += 1;
            printf("\nPares hasta ahora: %d",*pares);
        }
        return contarParesRecursivo(aux->sig,pares);
    }
}

int main() {
    TLista TL;
    TL = NULL;
    int cantPar = 0;
    insertarLista(&TL, 10);
    insertarLista(&TL, 40);
    insertarLista(&TL, 50);
    insertarLista(&TL, 10);
    insertarLista(&TL, 10);
    insertarLista(&TL, 10);
    insertarLista(&TL, 10);
    printf("insertado");
    recorrerLista(TL);
    contarParesRecursivo(TL,&cantPar);
    printf("\nCant pares: %d",cantPar);

    return 0;
}
