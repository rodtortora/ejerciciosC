#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

void IniciaP(TPila *P) {
*P = NULL;
}

void poneP(TPila *P, ElementoP x) {
    TPila N;
    N = (TPila)malloc(sizeof(nodop));
    N->dato = x;
    N->sig = *P;
    *P = N;
}

void sacaP(TPila *P, ElementoP *x) {
    TPila N;
    if (*P != NULL) {
        N = (*P);
        *x = (*P)->dato;
        *P = (*P)->sig;
        free(N);
    }
}

ElementoP consultaP(TPila P) {
    if (P != NULL) {
        return P->dato;
    }
    return 0;
}

int VaciaP(TPila P) {
    return (P == NULL);
}


float promedio(TPila P) {
    TPila aux;
    int sum, i;
    i = sum = 0;
    if (P!=NULL) {
        aux = P;
        while (aux != NULL) {
            sum += aux->dato;
            aux = aux->sig;
        }
        return sum/i;
    }
    return 0;
}

ElementoP ultimo(TPila P);
int cantMayoresPromedio(TPila P);
void intercambiarPrUl(TPila *P);

void recorrerPila(TPila P) {
    TPila aux;
    if (P!=NULL) {
        aux = P;
        while (aux != NULL) {
            printf("\nElemento pila: %d",aux->dato);
            aux = aux->sig;
        }
    }
}
