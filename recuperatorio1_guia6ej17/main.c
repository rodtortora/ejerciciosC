#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//LISTASIMPLE
typedef struct nodoStock {
    char nombreProducto[25];
    float precioKilo, stock;
    int idProveedor;
    struct nodoStock *sig;
} nodoStock;
typedef struct nodoStock *TListaStock;

//LISTA CON SUBLISTA
typedef struct nodito {
    char nombreProducto[25];
    float cantidadGramos;
    struct nodito *sig;
} nodito;
typedef struct nodito *TSLista;
typedef struct nodoRecetas {
    char nombreReceta[25];
    struct nodoRecetas *sig;
    struct nodito *sub;
} nodoRecetas;
typedef struct nodoRecetas *TListaRecetas;


//LISTADOBLE
typedef struct nodoDoble {
    char nombreReceta[25];
    float costoReceta;
    struct nodoDoble *sig, *ant;
} nodoDoble;
typedef struct nodoDoble *pNodoDoble;
typedef struct TListaD {
    pNodoDoble pri, ult;
} TListaD;

void insertarStock (TListaStock *L, char *nombreProducto, float precio, float stock, int idProv);
void insertarReceta(TListaRecetas *L, char *nombreReceta);
void insertarSecos(TListaRecetas *L, TSLista *SL, char nombreReceta[25], char nombreProducto[25], float cantGramos);
void crearDoble(TListaD *LD, TListaStock *LStock, TListaRecetas LRec);
float calcularCostoTotal(TListaRecetas LRec, TListaStock *LStock);
float calcularCostoProd(TListaStock *LStock, char nombreProducto[25], float cantGramos);
void recorrerDoble(TListaD LD);
void recorrerLStock(TListaStock LStock);
void recorrerRecetas(TListaRecetas LRec);


int main()
{
    TListaRecetas LRec;
    TListaStock LStock;
    TSLista LSub;
    TListaD LD;
    LRec = NULL;
    LStock = NULL;
    LSub = NULL;
    insertarStock(&LStock, "YERBA",80,6,2);
    insertarStock(&LStock, "HARINA",70,4,1);
    insertarStock(&LStock, "YERBA",50,0.5,2);
    insertarStock(&LStock, "AZUCAR",10,1,1);
    insertarStock(&LStock, "AZUCAR",17,4,3);
    insertarStock(&LStock, "AZUCAR",400,9,2);
    insertarStock(&LStock, "HARINA",60,2,4);
    insertarStock(&LStock, "ALMENDRAS",50,2,2);
    insertarStock(&LStock, "ALMENDRAS",51,1,5);
    insertarStock(&LStock, "CHOCLO",24,1,4);
    insertarStock(&LStock, "ARROZ",3,1,7);
    insertarStock(&LStock, "MAIZ",7,4,8);
    insertarStock(&LStock, "ARROZ",4,4,8);
    insertarStock(&LStock, "ARROZ",20,5,8);
    insertarStock(&LStock, "AZUCAR",15,3,44);
    insertarStock(&LStock, "ALMENDRAS",57,4,52);
    insertarReceta(&LRec,"RECETA1");
    insertarReceta(&LRec,"RECETA2");
    insertarReceta(&LRec,"RECETA3");
    insertarSecos(&LRec,&LSub, "RECETA2","HARINA",500);
    insertarSecos(&LRec,&LSub, "RECETA1","HARINA",2000);
    insertarSecos(&LRec,&LSub, "RECETA1","YERBA",5000);
    insertarSecos(&LRec,&LSub, "RECETA1","ARROZ",5000);//ok
    insertarSecos(&LRec,&LSub, "RECETA2","AZUCAR",1000);
    insertarSecos(&LRec,&LSub, "RECETA2","ALMENDRAS",21000);
    insertarSecos(&LRec,&LSub, "RECETA3","AZUCAR",1000);
    insertarSecos(&LRec,&LSub, "RECETA1","MAIZ",1000);
    crearDoble(&LD, &LStock, LRec);
    recorrerLStock(LStock);
    recorrerRecetas(LRec);
    recorrerDoble(LD);
}

void insertarStock (TListaStock *L, char *nombreProducto, float precio, float stock, int idProv) {
    TListaStock act, ant, nuevo;
    act = *L;
    ant = NULL;
    nuevo = (TListaStock)malloc(sizeof(nodoStock));
    nuevo->idProveedor = idProv;
    strcpy(nuevo->nombreProducto,nombreProducto);
    nuevo->precioKilo = precio;
    nuevo->stock = stock;

    while (act != NULL && strcmp(nombreProducto,act->nombreProducto) > 0) {
        ant = act;
        act = act->sig;
    }
    while (act != NULL && strcmp(nombreProducto,act->nombreProducto) == 0 && precio > act->precioKilo) { // si el prod. a insertar ya existe y su precio es mayor al de la lista
        ant = act;
        act = act->sig;
    }
    if (ant == NULL) { // si es el primero o todavia no existe la lista
        *L = nuevo;
    } else { //no es el primero Y ya existe la lista
        ant->sig = nuevo;
    }
    nuevo->sig = act;
}

void insertarReceta(TListaRecetas *L, char *nombreReceta) {
    TListaRecetas act, nuevo;
    act = *L;
    nuevo = (TListaRecetas)malloc(sizeof(nodoRecetas));
    strcpy(nuevo->nombreReceta,nombreReceta);
    *L = nuevo;
    nuevo->sig = act;
}


void insertarSecos(TListaRecetas *L, TSLista *SL, char nombreReceta[25], char nombreProducto[25], float cantGramos) {
    TListaRecetas act;
    TSLista nuevo;
    act = *L;
    while (act != NULL && strcmp(nombreReceta,act->nombreReceta) != 0) {
        act = act->sig;
    }
    if (act != NULL && strcmp(nombreReceta,act->nombreReceta) == 0) {
        nuevo = (TSLista)malloc(sizeof(nodito));
        nuevo->cantidadGramos = cantGramos;
        strcpy(nuevo->nombreProducto,nombreProducto);
        nuevo->sig = act->sub;
        act->sub = nuevo;
    }
}

void crearDoble(TListaD *LD, TListaStock *LStock, TListaRecetas LRec) {
    TListaRecetas actRecetas;
    TListaStock actStock;
    pNodoDoble nuevo;
    actRecetas = LRec;
    actStock = *LStock;
    float costoReceta;
    LD->pri = LD->ult = NULL;
    while (actRecetas != NULL) {
        costoReceta = calcularCostoTotal(actRecetas, &actStock);
        if (costoReceta != -1) {
            nuevo = (pNodoDoble)malloc(sizeof(nodoDoble));
            nuevo->costoReceta = costoReceta;
            strcpy(nuevo->nombreReceta,actRecetas->nombreReceta);
            nuevo->ant = NULL;
            nuevo->sig = NULL;
            if (LD->pri == NULL) {
                LD->pri = LD->ult = nuevo;
            } else {
                nuevo->sig = LD->pri;
                LD->pri->ant = nuevo;
                LD->pri = nuevo;
            }
        }
        actRecetas = actRecetas->sig;
    }
}

float calcularCostoTotal(TListaRecetas LRec, TListaStock *LStock) {
    TListaRecetas actRecetas;
    TSLista actRecetasSub;
    float costoProducto;
    actRecetas = LRec;
    actRecetasSub = actRecetas->sub;
    float suma = 0;
    while (actRecetasSub != NULL) {
        costoProducto = calcularCostoProd(LStock, actRecetasSub->nombreProducto, actRecetasSub->cantidadGramos);
        if (costoProducto != -1) {
            suma += costoProducto;
        } else {
            return -1;
        }
        actRecetasSub = actRecetasSub->sig;
    }
    return suma;
}

float calcularCostoProd(TListaStock *LStock, char nombreProducto[25], float cantGramos) {
    TListaStock actStock, antStock;
    actStock = *LStock;
    antStock = NULL;
    while (actStock != NULL && strcmp(nombreProducto,actStock->nombreProducto) > 0) {
        antStock = actStock;
        actStock = actStock->sig;
    }
    while (actStock != NULL && strcmp(nombreProducto,actStock->nombreProducto) == 0 && cantGramos/1000 > actStock->stock) {
        antStock = actStock;
        actStock = actStock->sig;
    }
    if (actStock != NULL && strcmp(nombreProducto,actStock->nombreProducto) == 0) { // hay stock del producto
        actStock->stock -= cantGramos/1000;
        if (actStock->stock == 0) {
            if (antStock == NULL) {
                *LStock = actStock->sig;
            } else {
                antStock->sig = actStock->sig;
            }
            free(actStock);
        }
        return actStock->precioKilo * cantGramos/1000;
    } else { // no hay stock
        return -1;
    }
}

void recorrerLStock(TListaStock LStock) {
    TListaStock act;
    act = LStock;
    printf("STOCK:\n");
    while (act != NULL) {
        printf("ID Prov: %d. Nombre Producto: %s. Precio por kilo: %f. Stock en kg: %f\n",act->idProveedor, act->nombreProducto, act->precioKilo, act->stock);
        act = act->sig;
    }
}

void recorrerDoble(TListaD LD) {
    pNodoDoble aux;
    aux = LD.pri;
    printf("\nPRECIO RECETAS:\n");
    while (aux != NULL) {
        printf("Costo: %f. Nombre: %s\n", aux->costoReceta, aux->nombreReceta);
        aux = aux->sig;
    }
}

void recorrerRecetas(TListaRecetas LRec) {
    TListaRecetas aux;
    TSLista auxSub;
    aux = LRec;
    printf("\nRECETAS:\n");
    while (aux != NULL) {
        printf("----------------------------\nNombre Receta: %s\n",aux->nombreReceta);
        auxSub = aux->sub;
        while (auxSub != NULL) {
            printf(" - Producto: %s. Cant. Gramos: %f\n",auxSub->nombreProducto, auxSub->cantidadGramos);
            auxSub = auxSub->sig;
        }
        aux = aux->sig;
    }
}

