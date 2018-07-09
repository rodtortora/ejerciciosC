#include <stdio.h>
#include <stdlib.h>

typedef struct nodito {
    int mes;
    float monto;
    struct nodito *sig;
} nodito;
typedef struct nodito *sublista;

typedef struct nodo {
    int nroContrib;
    char nombre[30];
    struct sublista *sub;
    struct nodo *sig;
} nodo;
typedef struct nodo *TLista;

int main()
{
    return 0;
}

void insertarContrib(TLista *TL, int nroContrib, char *nombre, float importe[12]) {
    int i;
    TLista act, ant, nodo;
    sublista acts, ants, nodito;
    act = *TL;
    ant = NULL;
    while (act != NULL && act-> nroContrib < nroContrib) {
        ant = act;
        act = act -> sig;
    }
    if (act != NULL && act->nroContrib == nroContrib) {

        for (i=0;i<12;i++) {
            ants = NULL;
            acts = act->sub;
            if (importe[i] > 0) { // Hay que insertar o actualizar el mes i porque hay un importe
                while (acts != NULL && acts->mes < (i+1)) {
                    ants = acts;
                    acts = acts->sig;
                }
                if (acts != NULL && acts->mes == (i+1)) { // Ya existia el mes, se suma el monto
                    acts->monto += importe[i];
                    acts->mes = i+1;
                } else {
                    if (ants != NULL) {
                        nodito = (sublista)malloc(sizeof(nodito));
                        nodito->mes = i+1;
                        nodito->sig = acts;
                        ants->sig = nodito;
                        nodito->monto = importe[i];
                    } else {
                        nodito = (sublista)malloc(sizeof(nodito));
                        act->sub = nodito;
                        nodito->mes = i+1;
                        nodito->sig = acts;
                        nodito->monto = importe[i];
                    }

                }

            }

        }
    }


}


