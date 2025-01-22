#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

float LeMedida(void)
{
    float medida;
    printf("Digite a medida em polegadas: ");
    scanf("%f", &medida);
    return medida;
}

float ConvertePolegada(float medida)
{
    float conversao;
    conversao = medida * 2.54;
    return conversao;
}

void ExibeConversao(float valor)
{
    printf("\nConversao = %.1f centimetros\n", valor);
    getch();
}

int main(void)
{
    printf("### Conversao Polegadas ###\n");
    ExibeConversao(ConvertePolegada(LeMedida()));
    return 0;
}