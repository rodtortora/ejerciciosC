void CreaDoble(TLista L, TlistaD *LD) {
    (*LD).pri = (*LD).ult = NULL;
    aux = L;
    while (aux != NULL) {
        nuevo = (PNodo)malloc(sizeof(nodoD));
        nuevo -> dato = aux -> dato;
        if ((*LD).pri == NULL) {
            nuevo->ant = nuevo->sig = NULL;
            (*LD).pri = (*LD).ult = nuevo;
        } else {
            if (aux -> dato < (*LD).pri -> dato) {
                nuevo -> ant = NULL;
                nuevo -> sig = (*LD).pri;
                (*LD).pri -> ant = nuevo;
                (*LD).pri = nuevo;
            } else {
                if (aux->dato > (*LD).ult -> dato) {
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
