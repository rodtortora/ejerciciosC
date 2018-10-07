#include <stdio.h>
#include <stdlib.h>

//LISTASIMPLE
typedef struct nodo {
    int x;
    struct nodo *sig;
} nodo;
typedef struct nodo *TLista;

//LISTADOBLE
typedef struct nodoD {
    int x;
    struct nodoD *ant, *sig;
} nodoD;
typedef struct nodoD *pNodoD;
typedef struct TListaD {
    pNodoD pri, ult;
} TListaD;


void insertarNro(TLista *L, int X) {
    TLista aux, nuevo;
    aux = *L;
    nuevo = (TLista)malloc(sizeof(nodo));
    nuevo->x = X;
    *L = nuevo;
    nuevo->sig = aux;
}

void creaDoble (TLista L, TListaD *LD) {
    TLista act;
    pNodoD nuevo, actd;
    LD->pri = LD->ult = NULL;
    act = L;
    while (act != NULL) {
        nuevo = (pNodoD)malloc(sizeof(nodoD));
        nuevo->x = act->x;
        printf("nro evaluando: %d\n",act->x);
        if (LD->pri == NULL) {
            nuevo->ant = nuevo->sig = NULL;
            LD->pri = LD->ult = nuevo;
        } else {
            if (act->x < LD->pri->x) {
                nuevo->sig = LD->pri;
                nuevo->ant = NULL;
                LD->pri->ant = nuevo;
                LD->pri = nuevo;
            } else {
                if (act->x > LD->ult->x) {
                    nuevo->sig = NULL;
                    nuevo->ant = LD->ult;
                    LD->ult->sig = nuevo;
                    LD->ult = nuevo;
                } else {
                    actd = LD->pri;
                    while (actd != NULL && act->x > actd->x) {
                        actd = actd->sig;
                    }
                    if (actd != NULL) {
                        nuevo->ant = actd->ant;
                        nuevo->sig = actd;
                        actd->ant->sig = nuevo;
                        actd->ant = nuevo;
                    }
                }
            }
        }
        act = act->sig;
    }

}

void recorrerDoble(TListaD L) {
    pNodoD aux;
    aux = L.pri;
    while (aux != NULL) {
        printf("%d\n",aux->x);
        aux = aux->sig;
    }
}

int main()
{
    TLista L;
    TListaD LD;
    L = NULL;
    insertarNro(&L,2);
    insertarNro(&L,4);
    insertarNro(&L,3);
    insertarNro(&L,1);
    creaDoble(L,&LD);
    recorrerDoble(LD);
    return 0;
}
