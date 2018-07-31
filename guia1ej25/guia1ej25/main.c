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

int main()

{
    FILE *archEntrada, *archSalida;
    archEntrada = fopen("facturas.txt","r");
    archSalida = fopen("facturasS.dat","wb");
    if (archEntrada == NULL) {
        return 1;
    }
    while (!feof(archEntrada)) {
        char indice;
        scanf("%c",&indice);
        if (indice == F) {
            scanf("%12d",&nroFactura);
            scanf("%30s",nombreCliente);
            abrirFactura(&TL,nroFactura);
        } else {
            scanf("%6d",&nroArt);
            scanf("%20s",descripcionArt);
            scanf("%f7.2",precioArt);
            scanf("%5d",cantArt);
            insertarSublista(&TL,nroArt,precioArt,cantArt);
        }
    }
    fprintf("%c",",indice);
}

void abrirFactura(TLista *TL, int nroFactura) {
    TLista aux;
    aux = *TL;


}
