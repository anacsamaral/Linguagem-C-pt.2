#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void LeHoras(int &a, int &b, int &c, int &d, int &e, int &f)
{
    printf("Digite a hora inicial (hh : mm : ss):\n");
    scanf("%d %d %d", &a, &b, &c);
    printf("Digite a hora final (hh : mm : ss):\n");
    scanf("%d %d %d", &d, &e, &f);
}

int ConverteSegundos(int horaI, int minI, int segI, int horaF, int minF, int segF)
{
    int SomaSegundosI, SomaSegundosF, Diferenca;
    
    SomaSegundosI = horaI * 3600 + minI * 60 + segI;
    SomaSegundosF = horaF * 3600 + minF * 60 + segF;
    
    Diferenca = SomaSegundosF - SomaSegundosI;

    return Diferenca;
}

void ExibeDiferenca(int Diferenca)
{
    printf("A diferença em segundos da hora final para a inicial eh de %d segundos.\n", Diferenca);
    getch();
}

int main(void)
{
    int hi, mi, si, hf, mf, sf, diferenca;
    
    LeHoras(hi, mi, si, hf, mf, sf);
    diferenca = ConverteSegundos(hi, mi, si, hf, mf, sf);
    ExibeDiferenca(diferenca);
    
    return 0;
}