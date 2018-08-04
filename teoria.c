Lista simple (con sublista)

typedef struct nodito {
    int mes;
    float monto;
    struct nodito *sig;
} nodito;

typedef struct nodo {
    int nro;
    char nombre[25];
    struct nodo *sig;
    struct nodito *sub;
} nodo;

typedef struct nodo *TLista;
