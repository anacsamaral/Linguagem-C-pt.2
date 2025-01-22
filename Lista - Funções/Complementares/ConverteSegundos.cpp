#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void LeValores(int &h, int &m, int &s)
{
    printf("Hora (hh mm ss): ");
    scanf("%d %d %d", &h, &m, &s);
}

int ConverteSegundos(int h, int m, int s)
{
    int soma = 0;
    soma = h * 3600 + m * 60 + s;
    return soma;
}

void Exibe(int soma)
{
    printf("\nTotal em segundos: %d", soma);
    getch();
}

int main(void)
{
    int h, m, s, total;
    LeValores(h, m, s);
    total = ConverteSegundos(h, m, s);
    Exibe(total);
    return 0;
}