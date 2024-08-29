#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int LeNumero(void)
{
    int Num;
    printf("Digite um numero: ");
    scanf("%d", &Num);

    return Num;
}

void Perfeito (int Num)
{
    int SomaDiv = 0, Divisor;

    for(Divisor = 1; Divisor <= Num/2; Divisor++)
        if(Num % Divisor == 0)
            SomaDiv += Divisor;

    if(Num == SomaDiv)
        printf("\nNumero PERFEITO!\n");
    else
        printf("\nNumero NAO PERFEITO!\n");

    getch();
}

int main(void)
{
    printf("\n### Numero Perfeito ###\n");
    Perfeito(LeNumero()); 

    return 0;
}