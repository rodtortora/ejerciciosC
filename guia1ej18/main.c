#include <stdio.h>
#include <stdlib.h>

void writeInBinaryFile(FILE *f, int *datoEscribir);
void readFromBinaryFile(FILE *f, int *datoLeido);
int validateFile(FILE *);

int main()
{
    FILE *f;
    int x, antx;
    int datoLeido;
    f = fopen("archivonrosconfxd.dat","wb+");
    x = 234;
    if (validateFile(f)) {
        while (x != antx) {
            writeInBinaryFile(f,&x);
            antx = x;
            scanf("%d",&x);
        }
        printf("Finaliza xq ingreso dos numeros iguales: %d",x);
        printf("Los numeros ingresados son: ");
        fseek(f,0,0);
        while (!feof(f)) {
            readFromBinaryFile(f,&datoLeido);
            printf("%d - ",datoLeido);
        }

    } else {
    printf("Errorxd");
    return 1;
    }
    fclose(f);

}

int validateFile(FILE *f) {
    if (f == NULL) {
        return 0;
    }
    return 1;
}

void writeInBinaryFile(FILE *f, int *datoEscribir) {
        fwrite(datoEscribir,sizeof(*datoEscribir),1,f);
}

void readFromBinaryFile(FILE *f, int *datoLeido) {
    /*while (!feof(f)) {*/
    fread(datoLeido,sizeof(*datoLeido),1,f);

    //}

}
