#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void LeVetor(int a, int b, int c, int d, int e, int f)
{
    printf("Digite a hora inicial:\n");
    scanf("%d%d%d", &a, &b, &c);
    printf("Digite a hora final:\n");
    scanf("%d%d%d", &d, &e, &f);
}

int ConverteSegundos(int horaI, int minI, int segI, int horaF, int minF, int segF)
{
    int SomaSegundosI, SomaSegundosF, Diferenca;
    horaI = horaI * 3600;
    minI = minI * 60;
    segI = segI;
    horaF = horaF * 3600;
    minF = minF * 60;
    segF = segF;

    SomaSegundosI = horaI + minI + segI;
    SomaSegundosF = horaF + minF + segF;

    Diferenca = SomaSegundosF - SomaSegundosI;

    return Diferenca;
}

void ExibeDiferenca(int Diferenca)
{
    printf("A diferenca em segundos da hora final para a inicial é de %d segundos\n", Diferenca);
    getch();
}

int main(void)
{
    int horaI, minI, segI, horaF, minF, segF;

    LeVetor(&horaI, &minI, &segI, &horaF, &minF, &segF);
}