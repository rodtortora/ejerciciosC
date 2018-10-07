#include <stdio.h>
#include <stdlib.h>

//PILAESTATICA
/*typedef struct {
    int dato[50];
    int tope;
} TPila;

void iniciaP(TPila *P) {
    P->tope = -1;
}

void poneP(TPila *P, int x) {
    if (P->tope != 49) {
        P->tope++;
        P->dato[P->tope] = x;
    }
}

int vacia(TPila P) {
    return (P.tope == -1);
}



void sacaP (TPila *P, int *x) {
    if (!vacia(*P)) {
        *x = P->dato[P->tope];
        P->tope--;
    }
}

int consultaP(TPila P) {
    return P.dato[P.tope];
}*/



//PILADINAMICA
/*typedef struct nodop {
    int dato;
    struct nodop *sig;
} nodop;
typedef nodop *TPila;

void iniciaP(TPila *P) {
    *P = NULL;
}

void poneP(TPila *P, int x) {
    TPila nuevo;
    nuevo = (TPila)malloc(sizeof(nodop));
    nuevo->dato = x;
    nuevo->sig = *P;
    *P = nuevo;
}

void sacaP(TPila *P, int *x) {
    TPila elim;
    if (*P != NULL) {
        elim = *P;
        *x = (*P)->dato;
        *P = (*P)->sig;
        free(elim);
    }
}*/

//COLAESTATICA

typedef struct TCola {
    int x[50], pri, ult;
} TCola;

void iniciaC(TCola *C) {
    C->pri = C->ult = -1;
}

int vaciaC(TCola C) {
    return C.pri == -1;
}

int consultaC (TCola C) {
    if (!vaciaC(C)) {
        return C.x[C.pri];
    }
    return -1;
}

void sacaC(TCola *C, int *x) {
    if (!vaciaC(*C)) {
        *x = C->x[C->pri];
        if (C->pri == C->ult)
            iniciaC(C);
    }
}

void poneC(TCola *C, int x) {
    if (C->ult != 49) {
        if (vacia(C))
            C->pri = 0;
        C->ult++
        C->x[C.ult] = x;
    }
}


int main()
{
    //PILAESTATICA
    /*TPila P;
    int r;
    iniciaP(&P);
    poneP(&P,2);
    poneP(&P,3);
    poneP(&P,1);
    poneP(&P,7);
    sacaP(&P,&r);
    printf("%d %d",consultaP(P),r);*/
}
