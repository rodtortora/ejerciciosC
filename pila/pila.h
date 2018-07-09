
typedef int TElementoP;
typedef struct nodop {
    TElementoP dato;
    struct nodop* sig;} nodop;
typedef nodop *TPila;



void IniciaP (TPila *);
void poneP (TPila *, TElementoP );
void sacaP (TPila *, TElementoP *);
TElementoP consultaP(TPila);
int VaciaP (TPila);
void VaciarP
