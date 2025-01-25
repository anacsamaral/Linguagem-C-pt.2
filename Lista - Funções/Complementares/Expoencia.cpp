#include <stdio.h>

void LeNumero(int &x, int &y)
{
    printf("Digite a base e o expoente:\n");
    scanf("%d%d", &x, &y);
}

int Expoencia(int x, int y)
{
    int i, resultado = 1;

    for(i = 0; i < y; i++)
        resultado *= x;

    return resultado;
}

void Exibe(int resultado)
{
    printf("Resultado: %d\n", resultado);
}

int main(void)
{
    int x, y, resultado;

    LeNumero(x, y);
    resultado = Expoencia(x, y);
    Exibe(resultado);

    return 0;
}