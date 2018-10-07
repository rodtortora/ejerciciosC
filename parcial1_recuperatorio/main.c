#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Pilas.h
typedef struct TElementoP {
    int id;
    char codigo[4];
    char descripcion[20];
    int cantidad;
    float importeAdelantado;
}TElementoP;

typedef struct TPila {
    TElementoP datos[50];
    int tope;
} TPila;
//fin pilas.h

//Pilas.c
TElementoP consultaP(TPila P);
int VaciaP(TPila P);
void IniciaP (TPila *P);
void sacaP(TPila *P, TElementoP *datos);
void poneP(TPila *P, TElementoP datos);

TElementoP consultaP(TPila P)
{

	if ((P.tope) != -1)
		return P.datos[P.tope];

}

int VaciaP(TPila P)
{

	return (P.tope == -1);

}

void IniciaP (TPila *P)
{

	(*P).tope = -1;

}

void sacaP(TPila *P, TElementoP *datos) {
    if (P->tope != -1) {
        *datos = P->datos[P->tope];
        P->tope--;
    }
}
void poneP(TPila *P, TElementoP datos) {
    if (P->tope != 49) {
        P->tope++;
        P->datos[P->tope] = datos;
    }
}
//Fin pilas.c

typedef struct nodoS {
    int idCliente;
    char codMaterial[4];
    int cantSolicitada;
    float difMonto;
    struct nodoS *sig;
} nodoS;
typedef struct nodoS *TListaSimple;

typedef struct nodoC {
    char codigo[4], descripcion[20];
    float precio;
    int cantidad;
    struct nodoC *sig;
}nodoC;
typedef struct nodoC *TListaC;

void insertarLC(TListaC *LC, char codigo[4], char descripcion[20], float precio, int cantidad);
void recorrerLC(TListaC LC);
void insertarPedidoSatisfecho(TListaSimple *LS, int id, char codigo[4],int cantidad, float difMonto);
void procesarPila(TPila P, TListaC *LC, TListaSimple *LS);


int main()
{
    TListaC LC;
    TPila P;
    TListaSimple LS;
    LS = NULL;
    FILE *archivo, *archivoTexto;
    LC = NULL;
    int cantidadSolicitada,idCliente;
    float  importeAdelantado;
    char codigo[4], descripcion[20];
    float precio;
    int cantidad;
    archivo = fopen("Materiales.dat","rb");
    archivoTexto  =fopen("movscli.txt","r");
    if (!archivo || !archivoTexto){
        return 1;
    }
    fread(codigo,4,1,archivo);
    fread(descripcion,20,1,archivo);
    fread(&precio,sizeof(float),1,archivo);
    fread(&cantidad,sizeof(int),1,archivo);
    while (!feof(archivo)) {
        insertarLC(&LC,codigo,descripcion,precio,cantidad);
        fread(codigo,4,1,archivo);
        fread(descripcion,20,1,archivo);
        fread(&precio,sizeof(float),1,archivo);
        fread(&cantidad,sizeof(int),1,archivo);
    }
    insertarLC(&LC,codigo,descripcion,precio,cantidad);
    fclose(archivo);
    IniciaP(&P);
    fscanf(archivoTexto,"%d %s %d %f",&idCliente,codigo, &cantidadSolicitada, &importeAdelantado);
    while(!feof(archivoTexto)) {
        TElementoP nuevoPila;
        nuevoPila.id = idCliente;
        nuevoPila.codigo[4] = codigo[4];
        nuevoPila.cantidad = cantidadSolicitada;
        nuevoPila.importeAdelantado = importeAdelantado;
        fscanf(archivoTexto,"%d %s %d %f",&idCliente,codigo, &cantidadSolicitada, &importeAdelantado);
        poneP(&P, nuevoPila);
    }
    fclose(archivoTexto);
    recorrerLC(LC);
    procesarPila(P, &LC, &LS);
    printf("------");
    recorrerLC(LC);

    return 0;

}

void procesarPila(TPila P, TListaC *LC, TListaSimple *LS) {
    int n = 0;
    TElementoP datosPila;
    TListaC aux, ant, elim;
    aux = (*LC)->sig;
    while (n != P.tope) {
        datosPila = consultaP(P);
        while (aux != *LC && strcmp(datosPila.codigo,aux->codigo) > 0) {
            ant = aux;
            aux = aux->sig;
        }
    printf("\n%s y %s\n",datosPila[n].codigo,aux->codigo);
        if (strcmp(datosPila[n].codigo,aux->codigo) == 0 && aux->cantidad - datosPila.cantidad >= 0) {

            aux->cantidad -= datosPila.cantidad;
            insertarPedidoSatisfecho(LS, datosPila.id, aux->codigo, datosPila.cantidad, datosPila.importeAdelantado - aux->precio);
            if (aux->cantidad == 0) {
                elim = aux;
                ant = aux->sig;
                if (aux == *LC) {
                    *LC = aux->sig;
                }
                free(elim);
                sacaP(&P,&datosPila);
            }
        }
        n++;

    }

}

void insertarPedidoSatisfecho(TListaSimple *LS, int id, char codigo[4],int cantidad, float difMonto){
    TListaSimple aux, nuevo;
    aux = *LS,
    nuevo =(TListaSimple)malloc(sizeof(nodoS));
    nuevo->cantSolicitada = cantidad;
    strcpy(nuevo->codMaterial,codigo);
    nuevo->difMonto = difMonto;
    nuevo->idCliente = id;
    nuevo->sig = aux;
    *LS = nuevo;
}

void insertarLC(TListaC *LC, char codigo[4], char descripcion[20], float precio, int cantidad) {

    TListaC nuevo, aux, ant;
    nuevo = (TListaC)malloc(sizeof(nodoC));
    strcpy(nuevo->codigo,codigo);
    strcpy(nuevo->descripcion,descripcion);
    nuevo->precio = precio;
    nuevo->cantidad = cantidad;
    if (*LC != NULL) {
        if (strcmp(codigo,(*LC)->codigo) > 0) {
            nuevo->sig = (*LC)->sig;
            (*LC)->sig = nuevo;
            (*LC) = nuevo;
        } else {
            aux = (*LC)->sig;
            while (aux->sig != *LC && strcmp(codigo,aux->codigo) > 0) {
                ant = aux;
                aux = aux->sig;
            }
            nuevo->sig = aux;
            ant->sig = nuevo;
        }

    } else {
        *LC = nuevo;
        nuevo->sig = nuevo;
    }

}

void recorrerLC(TListaC LC) {
    TListaC aux;
    aux = LC->sig;
    while (aux != LC){
        printf("Codigo: %s. Descr: %s. Precio: %f. Cantidad: %d\n",aux->codigo,aux->descripcion,aux->precio,aux->cantidad);
        aux = aux->sig;
    }
}
