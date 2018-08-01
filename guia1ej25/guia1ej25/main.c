#include <stdio.h>
#include <stdlib.h>

typedef struct nodito {
    int codArt;
    float precioArt;
    int cantArt;
    struct nodito *sig;
} nodito;

typedef struct nodo {
    int nroFactura;
    float importeTotal;
    int cantArt;
    struct nodo *sig;
    struct nodito *sub;
} nodo;

typedef struct nodito *TSubLista;
typedef struct nodo *TLista;

void abrirFactura(TLista *TL, int nroFactura);
void insertarSublista(TLista *TL, int nroArt, float precioArt, int cantArt);
void recorrerListaConSublista(TLista TL);

int main()

{
    FILE *archEntrada, *archSalida;
    int nroFactura;
    char nombreCliente[30];
    char descripcionArt[20];
    float precioArt;
    int cantArt;
    int nroArt;
    char indice;
    TLista TL;
    TL = NULL;
    archEntrada = fopen("facturas.txt","r");
    archSalida = fopen("facturasS.dat","wb");
    if (archEntrada == NULL) {
        return 10;
    }
    while (!feof(archEntrada)) {
        fscanf(archEntrada,"%c",&indice);
        if (indice == 'F') {
            fscanf(archEntrada,"%12d",&nroFactura);
            fscanf(archEntrada,"%30s",nombreCliente);

            abrirFactura(&TL,nroFactura);

        } else {
            fscanf(archEntrada,"%6d",&nroArt);

            fscanf(archEntrada,"%20s",descripcionArt);
            fscanf(archEntrada,"%f7.2",&precioArt);
            fscanf(archEntrada,"%5d",&cantArt);

            insertarSublista(&TL,nroArt,precioArt,cantArt);
        }
    }
    recorrerListaConSublista(TL);
}

void abrirFactura(TLista *TL, int nroFactura) {
    TLista aux, nuevo;
    aux = *TL;
    nuevo = (TLista)malloc (sizeof(nodo));
    nuevo->cantArt = 0;
    nuevo->importeTotal = 0;
    nuevo->nroFactura = nroFactura;
    nuevo->sig = aux;
    nuevo->sub = NULL;
    *TL = nuevo;
}

void insertarSublista(TLista *TL, int nroArt, float precioArt, int cantArt) {
    TLista aux;
    TSubLista subAux, nuevoSub;

    aux = *TL;
    subAux = aux->sub;
    printf("%d",aux->cantArt);

    nuevoSub = (TSubLista)malloc(sizeof(nodito));

    nuevoSub->cantArt = cantArt;

    nuevoSub->precioArt = precioArt;
    nuevoSub->codArt = nroArt;
    aux->sub = NULL;
    nuevoSub->sig = NULL;
    nuevoSub->sig = subAux;
    aux->sub = nuevoSub;
    aux->cantArt += nuevoSub->cantArt;
    aux->importeTotal += nuevoSub->precioArt;
}

void recorrerListaConSublista(TLista TL) {
    TLista aux;
    TSubLista auxSublista;
    aux = TL;
    auxSublista = aux->sub;
    while (aux != NULL) {
        printf("\nNro Factura: %d\n", aux->nroFactura);
        printf("Importe total %f\n", aux->importeTotal);
        printf("Total de articulos %d\n", aux->cantArt);
        while (auxSublista != NULL) {
            printf("Articulo: %d  ",auxSublista->codArt);
            auxSublista = auxSublista -> sig;
        }
        aux = aux->sig;
    }
}
