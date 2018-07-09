typedef int TElementoP;

typedef struct {
    TElementoP dato[50];
    int tope;} TPila;


void IniciaP (TPila *);
void poneP (TPila *, TElementoP );
void sacaP (TPila *, TElementoP *);
TElementoP consultaP(TPila);
int ConsultaVaciaP (TPila);
