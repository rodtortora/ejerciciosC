/*Ejercicio Se tiene una lista simplemente enlazada que almacena números enteros sin repeticiones.
Armar una lista doblemente enlazada ordenada de forma ascendente.
A partir de la lista generada, eliminar nodos de tal modo que en la misma no aparezcan dos valores
pares o impares consecutivos.
Ejemplo: 10 7 13 8 12 5  5 7 8 10 12 13  5 8 13*/

//Definicion lista simple
typedef struct nodo {
	int num;
	struct nodo * sig;} nodo;
typedef struct nodo * TLista;

//Definicion lista doble
typedef struct nodoD {
	int num;
	struct nodoD *ant, * sig;} nodoD;
	
typedef struct nodoD * PnodoD;

typedef struct {
	PnodoD pri, ult;} TListaD; // Cabezas de la lista


void CreaDoble(TLista L, TlistaD *LD) {
    (*LD).pri = (*LD).ult = NULL; // Cabezas de la lista doble (se inicializan)
    aux = L; // Recorredor lista simple
    while (aux != NULL) { // Mientras la lista simple exista
        nuevo = (PNodo)malloc(sizeof(nodoD));
        nuevo -> dato = aux -> dato; // Copia el dato actual de la lista simple en el nuevo nodo doble
        if ((*LD).pri == NULL) { // Si la lista doble esta vacia al no tener a donde apunta la cabeza
            nuevo->ant = nuevo->sig = NULL; // Null sig y ant porque es el unico nodo
            (*LD).pri = (*LD).ult = nuevo; // Ambas cabezas de la LD apuntan al unico nodo creado
        } else { // Si existe aunque sea LD.pri
            if (aux -> dato < (*LD).pri -> dato) { // Si el dato es menor que el de la 1era posicion (por lo tanto se tiene que insertar en la 1era posicion al ser orden ascendente)
                nuevo -> ant = NULL;
                nuevo -> sig = (*LD).pri;
                (*LD).pri -> ant = nuevo;
                (*LD).pri = nuevo;
            } else {
                if (aux->dato > (*LD).ult -> dato) { // Si el dato es mayor q el de la ult posicion (por lo tanto se tendria q insertar al final al ser orden asc)
                    nuevo -> ant = (*LD).ult;
                    nuevo -> sig = NULL;
                    (*LD).ult -> sig = nuevo;
                    (*LD).ult = nuevo;
                } else {
                    act = (*LD).pri;
                    while(aux->dato > act -> dato)
                        act = act->sig;
                    nuevo->sig = act;
                    nuevo->ant = actual->ant;
                    act -> ant -> sig = nuevo;
                    act -> ant = nuevo
                    // falta aux = aux -> sig ver donde va xd
                }
            }
        }
    }
}



void eliminarVarios(TListaD *LD) {
    if ((*LD).pri != NULL) {
        act = (*LD).pri -> sig;
        while (act != NULL) {
            if (act-> dato %2 != act -> ant -> dato %2) {
                act = act -> sig;
            } else {
                elim = act;
                act = act -> sig;
                if (act == NULL) {
                    elim -> ant -> sig = NULL;
                    (*LD).ult = elim -> ant;
                } else {
                    elim -> ant -> sig = act;
                    act -> ant = elim -> ant;
                }
                free(elim);
            }
        }
    }
}

LISTAS CIRCULARES

void mostrar (TListaC TC) {
    TListaC aux;
    if (aux != NULL) {
        aux = TC -> sig;
        while (aux != TC)
            printf("%d",aux->dato);

    }
}


void insertarPal(TListaC *LC, char *pal) {
    nuevo = (TListaC) malloc (sizeof(nodo));
    nuevo -> cant = 1;
    strcpy (nuevo -> pal.pal);
    if (*LC == NULL) {
        nuevo -> sig = nuevo;
        *LC = nuevo;
    } else {
        if strcmp(pal, (*LC)->pal == 1) {
            nuevo -> sig = (*LC) -> sig;
            (*LC) -> sig = nuevo;
            (*LC) = nuevo;
        } else {
            ant = *LC;
            act = (*LC) -> sig;
            while (strcmp(pal,act->pal)==1) {
                ant = act;
                act = act -> sig;
            }
            if (strcmp(pal,act->pal) == 0) {
                act -> cant ++;
                free(nuevo);
            } else {
                nuevo -> sig = act;
                ant -> sig = nuevo;
            }
        }
    }
}
