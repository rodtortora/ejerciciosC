#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

int main()
{
    TPila pila;
    FILE *archivo;
    int n;
    archivo = fopen("enteros.txt","r");
    IniciaP(&pila);
    fscanf(archivo,"%d",&n);
    while (!feof(archivo)) {
        poneP(&pila, n);
        fscanf(archivo,"%d",&n);
    }
    recorrerPila(pila);
    printf("promedio: %f",promedio(pila));
    fclose(archivo);
    return 0;

}
