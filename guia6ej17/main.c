#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodoDoble {
    char NombreReceta[25];
    float costoRec;
    struct nodoDoble *ant, *sig;} nodoDoble;
typedef struct nodoDoble *pNodoDoble;

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
typedef struct TListaDoble {
    pNodoDoble pri, ult;
} TListaDoble;



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
    act = *TL;
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

float tomarProducto(char *nombreProd, int cantidadGr, TListaSt *TL) {
    TListaSt ant, act, elim;
    while (act != NULL && strcmp(nombreProd,act->nombreProd) == 1) {
        ant = act;
        act = act->sig;
    }
    if (act != NULL && strcmp(nombreProd,act->nombreProd) == 0) {
        if ((act->stock * 1000 - cantidadGr) >= 0) { // hay stock disponible?
            act->stock = act->stock * 1000 - cantidadGr; //resta stock
            if (act->stock == 0) { // elimina producto si stock llega a 0
                elim = act;
                act = act->sig;
                if (ant == NULL) {
                    *TL = act;
                } else {
                    ant->sig = act;
                }
                free(elim);
            }
            return act->precioKilo * act->stock;
        }
        act = act->sig;
    }
    return 0;
}

float calcularPrecio(TSubLista LSub, TListaSt *TL) { // Devuelve precio total de la sublista
    TSubLista act;
    float aux, precio;
    act = LSub;
    while (act != NULL) { //o sea que aun hay mas productos en la sublista de la receta
        aux = tomarProducto(act->nombreProd,act->cantidadGr,TL); // toma una cantidad de Grs del producto del stock
        if (aux != 0) { // si devuelve 0 es que no pudo calcular
            precio += aux;
        } else {
            return 0; // si aunque sea 1 de los productos no pudo sumarizarse, devuelve 0, es decir no se puede hacer la receta
        }
        act = act->sig;
    }
    return precio;
}

void crearDoble(TListaDoble *TD, TListaSt *TLS, TListaRec TLR) {
    pNodoDoble nuevo;
    TListaRec auxRec;
    auxRec = TLR;
    TD->pri = TD->ult = NULL;
    while (auxRec != NULL) {
        nuevo = (pNodoDoble)malloc(sizeof(nodoDoble));
        if (calcularPrecio(auxRec->sub,TLS) != 0) { // Devuelve precio total de la sublista, en caso de 0 es que no pudo hacerse porque no hay stock de un producto
            nuevo->costoRec = calcularPrecio(auxRec->sub,TLS);
            strcpy(nuevo->NombreReceta,auxRec->nombreReceta);
        } else {
            printf("No se puede crear esta receta. No hay suficientes ingredientes.\n");
        }
        if (TD->pri == NULL) {//
            nuevo->ant = nuevo->sig = NULL;
            TD->pri = TD->ult = nuevo;
        } else {
            TD->ult->sig = nuevo;
            TD->ult = nuevo;
        }
    }
}

int main()
{
    TListaSt TLS;
    TListaRec TLR;
    TListaDoble TD;
    //TSubLista TSub;
    TLS = NULL;
    TLR = NULL;
    //TSub = NULL;
    //insertarStock(TL,"NOMBRE",PRECIO,STOCK,IDProv)
    insertarStock(&TLS,"HARINA",10,2,1);
    insertarStock(&TLS,"HARINA",6,2,2);
    insertarStock(&TLS,"HARINA",8,2,3);
    insertarStock(&TLS,"AZUCAR",10,1,1);
    insertarStock(&TLS,"AZUCAR",17,4,3);
    insertarStock(&TLS,"AZUCAR",4,9,2);
    insertarStock(&TLS,"HARINA",8,2,4);
    insertarStock(&TLS,"ALMENDRA",50,2,2);
    insertarStock(&TLS,"ALMENDRA",51,1,5);
    insertarStock(&TLS,"CHOCLO",24,1,4);
    insertarStock(&TLS,"ARROZ",3,10,7);
    insertarStock(&TLS,"MAIZ",7,4,8);
    insertarStock(&TLS,"ARROZ",4,4,8);
    insertarReceta(&TLR,"Frijoles");
    insertarSub(&TLR,"Frijoles","MAIZ",1);
    insertarSub(&TLR,"Frijoles","HARINA",2);
    printf("Recorriendo lista stock\n");
    recorrerStList(TLS);
    printf("Fin Recorriendo lista stock\n");
    crearDoble(&TD,&TLS,TLR);
    printf("Doble creada\n");
    printf("Recorriendo lista stock\n");
    recorrerStList(TLS);
    printf("Fin Recorriendo lista stock\n");
    return 0;
}
