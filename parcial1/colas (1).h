
typedef  TElementoC;

typedef struct {
	TElementoC datos[50];
	int pri;
	int ult; } TCola;

int vaciaC(TCola C);

void sacaC(TCola *C, TElementoC* dato);

TElementoC consultaC (TCola C);
