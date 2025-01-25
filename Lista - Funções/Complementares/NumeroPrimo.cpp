#include <stdio.h>
#include <stdlib.h>

int LeNumero(void)
{
    int num;
    printf("Digite o número: ");
    scanf("%d", &num);
    return num;
}

int Calculo(int num) {
    int cont = 0, i;

    for (i = 1; i <= num; i++)
        if (num % i == 0)
            cont++;

    if (cont == 2)
        return 1;
    else
        return 0;
}

int main(void) 
{
    int numero, ehPrimo;

    numero = LeNumero();
    ehPrimo = Calculo(numero);

    printf("\nResultado: %d\n", ehPrimo);

    return 0;
}
