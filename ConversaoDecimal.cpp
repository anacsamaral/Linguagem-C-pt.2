#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

int LeNumero(void)
{
    int Binario;
    printf("Digite um numero binario: ");
    scanf("%d", &Binario);

    return Binario;
}

int ConverteDecimal(int Binario)
{
    int Decimal = 0, expo = 0;
    
    while (Binario > 0)
    {
        Decimal += Binario % 10* pow(2,expo);
        Binario = Binario / 10;
        expo++;
    }
    
    return Decimal;
}

void ExibeResultado(int valor)
{
    printf("Resultado: %d\n", valor);
    getch();
}

int main(void)
{
    printf("\n### Conversao de Decimal para Binario ###\n");
    ExibeResultado(ConverteDecimal(LeNumero())); 

    return 0;
}