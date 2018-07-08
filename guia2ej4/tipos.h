#include <stdio.h>
#include <stdlib.h>

typedef struct strPersona {
    char Nombre[21];
    int Edad;
    struct strPersona *sig; } strPersona;
typedef struct strPersona *ptPersona;

