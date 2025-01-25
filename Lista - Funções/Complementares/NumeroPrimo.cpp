#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

float LeNumero(void)
{
    int num;
    printf("Digite o numero: ");
    scanf("%d", &num);
    return num;
}

int Calculo (int num)
{
    int cont = 0, i;

    for(i = num; i > 0; i--)
        if(num % i == 0)
            cont++;

    if(cont == 2)
        printf("\n1\n");
    else
        printf("\n0\n");
}

int main(void)
{
    Calculo(LeNumero());
    return 0;
}