#include <stdio.h>

void LeIdade(int &a, int &m, int &d)
{
    printf("Sua idade (aa mm dd):\n");
    scanf("%d %d %d", &a, &m, &d);
}

int IdadeDias(int a, int m, int d)
{
    int resultado;
    resultado = a * 365 + m * 30 + d;
    return resultado;
}

void Resultado(int resultado)
{
    printf("Idade em dias: %d\n", resultado);
}

int main(void)
{
    int a, m, d, idade;

    LeIdade(a, m, d);
    idade = IdadeDias(a, m, d);
    Resultado(idade);
}