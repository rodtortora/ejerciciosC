#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, i;
    FILE *archivo;
    archivo = fopen("enteros.txt","r");
    fscanf(archivo,"%d",&N);
    printf("%d",N);
    int *intVector[N];
    i = 0;
    fscanf(archivo,"%d",intVector[i]);
    printf("%d",intVector[i]);
    while (feof(archivo)) {
        if (*intVector[i] > 0) {
            printf("%d",*intVector[i]);
        }
        i++;
        fscanf(archivo,"%d",intVector[i]);
    }
}

