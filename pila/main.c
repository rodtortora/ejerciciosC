#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

int main()
{
    TPila P;
    TElementoP elemento;
    elemento = 1;
    IniciaP(&P);
    poneP(&P,elemento);
    elemento = 8;
    poneP(&P,elemento);
    elemento = 2;
    poneP(&P,elemento);
    while (!VaciaP(P)) {
        sacaP(&P,&elemento);
        printf("%d\n",elemento);
    }
    return 0;
}
