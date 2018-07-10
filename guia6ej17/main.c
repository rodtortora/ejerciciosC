#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodito {
    char nombreProd[25];
    int cantidadGr;
    struct nodito *sig;
} nodito;

typedef struct nodostock {
    char nombreProd[25];
    float precioKilo;
    int stock;
    int id;
    struct nodostock *sig;
} nodostock;

typedef struct nodoreceta {
    char nombreReceta[25];
    struct nodoreceta *sig;
    struct nodito *sub;
} nodoreceta;

typedef struct nodonuevo {
    char nombreReceta[25];
    float costoReceta;
    struct nodonuevo *sig;
    struct nodonuevo *ant;
} nodonuevo;

typedef struct nodito *TSubLista;
typedef struct nodostock *TListaSt;
typedef struct nodoreceta *TListaRec;
typedef struct nodonuevo *TListaNew;

void insertarStock(TListaSt *TL, char *nombreProd, float precioKilo, int stock, int id) {
    TListaSt act, ant, nuevo;
    nuevo = (TListaSt)malloc(sizeof(nodostock));
    act = *TL;
    ant = NULL;
    nuevo->id = id;
    strcpy(nuevo->nombreProd,nombreProd);
    nuevo->precioKilo = precioKilo;
    nuevo->stock = stock;
    while (act != NULL && strcmp(nombreProd,act->nombreProd) == 1) {
        ant = act;
        act = act->sig;
    }
    while (act != NULL && strcmp(nombreProd,act->nombreProd) == 0 && precioKilo > act->precioKilo) {
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

void insertarReceta(TListaRec *TL, char *nombreReceta) {
    TListaRec act, ant, nuevo;
    ant = NULL;
    nuevo = (TListaRec)malloc(sizeof(nodoreceta));
    strcpy(nuevo->nombreReceta,nombreReceta);
    nuevo->sub = NULL;
    while (act != NULL) {
        ant = act;
        act = act->sig;
    }
    if (ant == NULL) {
        *TL = nuevo;
        nuevo->sig = act;
    } else {
        ant->sig = nuevo;
        nuevo->sig = act;
    }
}

void insertarSub(TListaRec *TL, char *nombreRec, char *nombreProd, int cantidad) {
    TListaRec act;
    TSubLista subact, subant, nuevo;
    subant = NULL;
    nuevo = (TSubLista)malloc(sizeof(nodito));
    nuevo->cantidadGr = cantidad;
    strcpy(nuevo->nombreProd,nombreProd);
    while (act != NULL && strcmp(nombreRec,act->nombreReceta) != 0) {
        act = act->sig;
    }
    if (act != NULL) {
        subact = act->sub;
        while (subact != NULL) {
            subant = subact;
            subact = subact->sig;
        }
        if (subant == NULL) {
            act->sub = nuevo;
        } else {
            subant->sig = nuevo;
        }
    }

}

void recorrerStList(TListaSt TL) {
    TListaSt aux;
    aux = TL;
    while (aux != NULL ) {
        printf("Nombre prod: %s. Precio por kg: %f. Stock: %d. IdProv: %d\n",aux->nombreProd,aux->precioKilo,aux->stock,aux->id);
        aux = aux->sig;
    }

}

int main()
{
    TListaSt TLS;
    TListaRec TLR;
    TSubLista TSub;
    TLS = NULL;
    TLR = NULL;
    TSub = NULL;
    //insertarStock(TL,"NOMBRE",PRECIO,STOCK,IDProv)
    insertarStock(&TLS,"HARINA",10,2,1);
    insertarStock(&TLS,"HARINA",6,24,2);
    insertarStock(&TLS,"HARINA",8,20,3);
    insertarStock(&TLS,"AZUCAR",10,12,1);
    insertarStock(&TLS,"AZUCAR",17,40,3);
    insertarStock(&TLS,"AZUCAR",4,90,2);
    insertarStock(&TLS,"HARINA",8,21,4);
    insertarStock(&TLS,"ALMENDRA",50,24,2);
    insertarStock(&TLS,"ALMENDRA",51,12,5);
    insertarStock(&TLS,"CHOCLO",24,1,4);
    insertarStock(&TLS,"ARROZ",3,109,7);
    insertarStock(&TLS,"MAIZ",7,4,8);
    insertarStock(&TLS,"ARROZ",4,4,8);
    insertarReceta(&TLR,"Frijoles");
    insertarSub(&TLR,"Frijoles","MAIZ",1);
    insertarSub(&TLR,"Frijoles","HARINA",2);
    recorrerStList(TLS);
}
