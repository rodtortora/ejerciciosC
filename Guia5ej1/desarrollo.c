//#include "cabecera.h"

void IniciaP (TPila *P) {
    (*P).tope = -1;
}
void poneP(TPila *P, TElementoP valor) {
    if ((*P).tope != 49) {
        (*P).tope ++;
        (*P).dato[(*P).tope] = valor;
    }
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

int ConsultaVaciaP (TPila P) {
    return P.tope == -1;
}
