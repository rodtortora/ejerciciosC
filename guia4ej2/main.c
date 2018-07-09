#include <stdio.h>
#include <stdlib.h>

int Func (int);

int main()
{
    int n;;
    printf("Ingrese un nro: ");
    scanf("%d",&n);
    Func(n);
    return 0;
}

int Func (int n) {
    if (n<10) {
        printf("%d",n);
        return 0;
    }
    else
        printf("%d",n%10);
        return Func(n/10);
}
