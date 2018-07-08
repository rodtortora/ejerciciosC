#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"

int main()
{
    ptPersona p1, p2;
    p1 = (ptPersona)malloc(sizeof(strPersona));
    p2 = (ptPersona)malloc(sizeof(strPersona));
    strcpy(p1->Nombre,"Pepe");
    strcpy(p2->Nombre,"Juan");
    p1->Edad = 10;
    p2->Edad = 20;
    p1->sig = p2;
    printf(p1->sig->Nombre);
    return 0 ;
}
