#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodito {
    int nroSocio;
    struct nodito *sig;
}nodito;

typedef nodito *TSubLista;

typedef struct nodo {
    char nombreActiv[25];
    int codigo, legajoProf, capMax, cantInsc;
    struct nodo *sig;
    struct nodito *sub;
}nodo;

typedef nodo *TLista;
void insertarActividad(TLista *TL, int codigo, char* nombre, int legajo, int capMax, int cantInsc) {
    TLista act, ant, nuevo;
    act = *TL;
    nuevo = (TLista)malloc(sizeof(nodo));
    nuevo->codigo = codigo;
    strcpy(nuevo->nombreActiv,nombre);
    nuevo->legajoProf = legajo;
    nuevo->capMax = capMax;
    nuevo->cantInsc = cantInsc;
    nuevo->sub = NULL;
    while (act != NULL && codigo > act->codigo){
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

void insertarSocioAct(TLista *TL, int NroSocio,int codAct) {
    TLista act;
    act = *TL;
    TSubLista actsub, antsub, nuevito;
    actsub = NULL;
    antsub = NULL;
    nuevito = (TSubLista)malloc(sizeof(nodito));
    nuevito->nroSocio = NroSocio;
    nuevito->sig = NULL;
    while (act != NULL && codAct > act->codigo) {
        act = act->sig;
    }
    if (act != NULL && codAct == act->codigo){
        if (act->capMax - act->cantInsc == 0) {
            // meter en cola pendiente
        } else {
            act->cantInsc++;
            actsub = act->sub;
            while (actsub != NULL) {
                antsub = actsub;
                actsub = actsub->sig;
            }
            if (antsub == NULL) {
                act->sub = nuevito;
            } else {
                antsub ->sig = nuevito;
            }
        }

    }
}


void crearMatriz(TLista TL, int *matrizActividades) {
    TLista act;
    TSubLista actsub;
    act = TL;
    while (act != NULL) {
        actsub = act->sub;
        while (actsub != NULL) {
            //matrizActividades[act->codigo][actsub->nroSocio] = 1;
            actsub = actsub -> sig;
        }
        act = act->sig;
    }

}

void recorrer(TLista L){
    TLista aux;
    TSubLista subaux;
    aux = L;
    while (aux != NULL) {
        printf("Nro activ: %d. Nombre: %s\n",aux->codigo,aux->nombreActiv);
        subaux = aux->sub;
        while (subaux != NULL) {
            printf("   nro Socio %d\n",subaux->nroSocio);
            subaux = subaux->sig;
        }
        aux = aux->sig;
    }
}



int main()
{
    FILE *archCarga, *archInscr;
    int i,NroSocInscr, CodActInscr, codActiv, legajo, capMax, cantInscr;
    char nombreActiv[25];
    int matrizActividades[40][300];
    TLista L;
    L=NULL;

    //crearMatriz(L,matrizActividades);
    archCarga = fopen("CARGAACTUAL.TXT","r");
    if (archCarga != NULL) {
        fscanf(archCarga,"%d %s %d %d %d",&codActiv,nombreActiv,&legajo,&capMax,&cantInscr);
        printf("Insercion actividad xd: %d %s %d %d %d\n",codActiv,nombreActiv,legajo,capMax,cantInscr);
        while(!feof(archCarga)){
            insertarActividad(&L,codActiv,nombreActiv,legajo,capMax,cantInscr);
            for (i=0;i<cantInscr;i++) {
                fscanf(archCarga,"%d",&NroSocInscr);
                insertarSocioAct(&L,NroSocInscr,codActiv);
                printf("insercion socio jaja: %d, %d\n",NroSocInscr,codActiv);
            }
            fscanf(archCarga,"%d %s %d %d %d",&codActiv,nombreActiv,&legajo,&capMax,&cantInscr);
            printf("Insercion actividad 2 xd: %d %s %d %d %d\n",codActiv,nombreActiv,legajo,capMax,cantInscr);
        }

    } else {
        printf("problema lectura archibo XD");
    }

    archInscr = fopen("INSCRIPTOS.TXT","r");
    if (archInscr != NULL) {
        fscanf(archInscr,"%d %d",&NroSocInscr,&CodActInscr);
        while (!feof(archInscr)){
        insertarSocioAct(&L,NroSocInscr,CodActInscr);
        fscanf(archInscr,"%d %d",&NroSocInscr,&CodActInscr);
        }
    }

    recorrer(L);

    return 0;
}
