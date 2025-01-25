#include <stdio.h>

int LeNumero(void)
{
    int num;
    printf("Digite o número: ");
    scanf("%d", &num);
    return num;
}

int Divisores(int num)
{
    int cont = 0, i;
    
    for(i = 1; i <= num; i++)
        if(num % i == 0)
            cont++;
    return cont;
}

void Exibe(int div)
{
    printf("Numero de Divisores: %d\n", div);
}

int main(void)
{
    Exibe(Divisores(LeNumero()));
    return 0;
}