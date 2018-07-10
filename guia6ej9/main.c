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
    nuevo->sub = NULL;
    strcpy(nuevo->nombre,nombre);
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

void  insertarGanancia(TLista *TL, int nro, int mes, float monto) {
    TLista act;
    TSubLista subant, subact, nuevo;
    act = *TL;
    subant = NULL;
    while (act != NULL && nro > act->nro) {
        act = act->sig;
    }
    if (act != NULL && nro == act->nro) {
        nuevo = (TSubLista)malloc(sizeof(nodito));
        nuevo->mes = mes;
        nuevo->monto = monto;
        subact = act->sub;
        while (subact != NULL && mes > subact->mes) {
            subant = subact;
            subact = subact->sig;
        }
        if (subant == NULL) {
            act->sub = nuevo;
            nuevo->sig = subact;
        } else {
            subant->sig = nuevo;
            nuevo->sig = subact;
        }
    } // else: no existe el contrib.

}

void recorrer(TLista TL) {
    TLista aux;
    TSubLista subAux;
    aux = TL;
    while (aux != NULL) {
        subAux = aux->sub;
        printf("--------------------\nNro: %d. Contrib: %s.\n",aux->nro,aux->nombre);
        while(subAux != NULL) {
            printf("Mes: %d. Ganancia: %f\n",subAux->mes,subAux->monto);
            subAux = subAux->sig;
        }
        aux = aux->sig;
    }

}

void eliminar(TLista *TL, int nro) {
    TLista elim, act, ant;
    TSubLista subelim, subact;
    ant = NULL;
    subact = NULL;
    elim = NULL;
    subelim = NULL;
    act = *TL;
    while (act != NULL && nro > act->nro) {
        ant = act;
        act = act->sig;
    }
    if (act != NULL && nro == act->nro) {
        elim = act;
        subact = act->sub;
        subelim = subact;
        act = act->sig;
        if (ant == NULL) {
            *TL = act;
        } else {
            ant->sig = act;
        }
        while (subact != NULL) {
            subelim = subact;
            subact = subact->sig;
            free(subelim);
        }
        free(elim);
    }
}



int main()
{
    TLista TL;
    TL = NULL;
    insertarContrib(&TL,2,"Rodrigo");
    insertarContrib(&TL,5,"Juan");
    insertarContrib(&TL,3,"Clara");
    insertarContrib(&TL,7,"Jose");
    insertarGanancia(&TL,5,2,1500);
    insertarGanancia(&TL,5,5,11000);
    insertarGanancia(&TL,1,12,6500);
    insertarGanancia(&TL,3,4,77);
    insertarGanancia(&TL,3,1,11000);
    insertarGanancia(&TL,3,3,660);
    insertarGanancia(&TL,5,3,1400);
    insertarGanancia(&TL,5,1,175);
    insertarGanancia(&TL,1,12,4500);
    insertarContrib(&TL,1,"Fran");
    insertarGanancia(&TL,1,12,4500);
    insertarContrib(&TL,0,"Carlos");
    insertarGanancia(&TL,1,10,1500);
    insertarContrib(&TL,4,"Marcela");
    insertarGanancia(&TL,1,11,1500);
    insertarGanancia(&TL,0,7,477);
    recorrer(TL);
    eliminar(&TL,0);
    eliminar(&TL,3);
    insertarGanancia(&TL,3,9,45);
    eliminar(&TL,7);
    printf("\nTras eliminar:\n");
    recorrer(TL);
}
