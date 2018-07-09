typedef int ElementoP;
typedef struct nodop {
    ElementoP dato;
    struct nodop *sig; } nodop;
typedef nodop *TPila;

void IniciaP(TPila *P);
void poneP(TPila *P, ElementoP x);
void sacaP(TPila *P, ElementoP *x);
ElementoP consultaP(TPila P);
int VaciaP(TPila P);
float promedio(TPila P);
ElementoP ultimo(TPila P);
int cantMayoresPromedio(TPila P);
void intercambiarPrUl(TPila *P);
void recorrerPila(TPila P);
