#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int LeNumero(void) // int = saida; void = entrada
{
    int Decimal; // variaveis locais
    printf("\nDigite um valor decimal: ");
    scanf("%d", &Decimal);

    return Decimal; // valor lido sera retornado para alguem
}

int ConverteBinario(int Decimal)
{
    int Binario = 0, mult = 1, resto;

    while (Decimal > 0)
    {
        resto = Decimal % 2;      
        Binario += resto * mult;      
        mult = mult * 10;
        Decimal = Decimal / 2;          
    }

    return Binario;
}

void ExibeResultado(int valor) // nao tem return e eh chamada sozinha
{
    printf("\nResultado: %d", valor);
    getch();
}

int main(void)
{
    printf("\n### Conversao de Decimal para Binario ###\n");
    // ValorBin = ConverteBinario(LeNumero()); //poderia colocar LeNumero() dentro
    ExibeResultado(ConverteBinario(LeNumero())); //pode colocar ConverteBinario(LeNumero())

    return 0;
}
