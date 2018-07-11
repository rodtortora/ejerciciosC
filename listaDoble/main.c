#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *sig; } nodo;
typedef struct nodo *TLista;

typedef struct nodoD {
    int dato;
    struct nodoD *ant, *sig; } nodoD;
typedef struct nodoD *pNodoD;

typedef struct TListaD {
    pNodoD pri, ult; } TListaD;

void insertarLista(TLista *TL, int X) {
    TLista act, ant, nuevo;
    act = *TL;
    ant = NULL;
    nuevo = (TLista)malloc(sizeof(nodo));
    nuevo->dato = X;
    while (act != NULL) {
        ant = act;
        act = act->sig;
    }


    if (ant == NULL) {
        *TL = nuevo;
    } else {
        ant->sig = nuevo;
    }
    nuevo->sig = NULL;
}

void crearDoble(TLista TL, TListaD *TD) {
    TLista act;
    pNodoD nuevo, actd;
    act = TL;
    TD->pri = TD->ult = NULL;
    while (act != NULL) {
        nuevo = (pNodoD)malloc(sizeof(nodoD));
        nuevo->dato = act->dato;
        if (TD->pri == NULL) {
            TD->pri = TD->ult = nuevo;
        } else {
            if (act->dato < TD->pri->dato) {
                TD->pri->ant = nuevo;
                nuevo->sig = TD->pri;
                TD->pri = nuevo;
            } else {
                if (act->dato > TD->ult->dato) {
                    TD->ult->sig = nuevo;
                    nuevo->ant = TD->ult;
                    TD->ult = nuevo;
                } else {
                    actd = TD->pri;
                    while (act->dato > actd->dato) {
                            actd = actd->sig;
                    }
                    nuevo->sig = actd;
                    nuevo->ant = actd->ant;
                    actd->ant->sig = nuevo;
                    actd->ant = nuevo;
                }
            }
        }
        act = act->sig;
    }

}

void recorrerDoble(TListaD *LD) {
    pNodoD actd;
    actd = LD->pri;
    while (actd != NULL) {
        printf("%d\n",actd->dato);
        actd = actd->sig;
    }

}

void eliminarVarios(TListaD *LD) {
    pNodoD act;
    if (LD->pri != NULL) {
        act = LD->pri->sig;
        while (act != NULL) {
            if (act->dato %2 != act->ant->dato %2) {
                act = act->sig;
            } else {
                elim = act;
                act = act->sig;
                if (act == NULL) {
                    elim->ant->sig = NULL;
                    LD->ult = elim->ant;
                } else {
                    elim->ant->sig = act;
                    act->ant = elim->ant;
                }
                free(elim);
            }
        }
    }
}

int main()
{
    TLista L;
    TListaD LD;
    L = NULL;
    insertarLista(&L,2);
    insertarLista(&L,4);
    insertarLista(&L,3);
    crearDoble(L,&LD);
    recorrerDoble(&LD);
    return 0;
}
