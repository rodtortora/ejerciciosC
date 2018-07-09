#include <stdio.h>
#include <stdlib.h>

int sumadores(int,int);

int main()
{
    int n;
    printf("Ingresa un nro");
    scanf("%d",&n);
    printf("%d",sumadores(n,1));
    return 0;
}

int sumadores(int n, int s) {
    if (s > n/2)
        return s;
    else
        return s+sumadores(n-1,s+1);
}
