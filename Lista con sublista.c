//ENUNCIADO GUIA6EJ9

typedef struct nodito {
    int mes;
    float monto;
    struct nodito *sig;
} nodito;

typedef struct nodito *TSubLista;

typedef struct nodo {
    int nro;
    char nombre[25];
    struct nodo *sig;
    struct nodito *sub;
} nodo;

typedef struct nodo *TLista;

//Insertar en lista

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

//Insertar en sublista

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
    }
    
//Recorrer  
    
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
    
//Eliminar

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
