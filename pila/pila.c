#include "pila.h"

void IniciaP (TPila *P) {
    *P = NULL;
}
void poneP(TPila *P, TElementoP valor) {
    TPila N;
    N = (TPila)malloc(sizeof(nodop));
    N->dato = valor;
    N->sig = *P;
    *P=N;
}
void sacaP(TPila *P, TElementoP *valor) {
    if ((*P).tope != -1) {
        *valor = (*P).dato[(*P).tope];
        (*P).tope--;
    }
}

TElementoP consultaP(TPila P) {
    if (P.tope != -1)
        return P.dato[P.tope];
}

int VaciaP (TPila P) {
    return P.tope == -1;
}
