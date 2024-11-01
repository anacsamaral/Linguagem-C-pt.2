#include <stdio.h>

void LeNumero(int &num)
{
	printf("Digite o numero: [0 para sair]\n");
	scanf("%d", &num);
}

int Fatorial(int &numero, int &mult)
{
    mult = 1;

    while(numero > 0)
    {
    	mult = mult * numero;
    	numero--;
	}

	return mult;
}

void Resultado (int valor)
{
	printf("Fatorial: %d\n", valor);
}

int main(void)
{
	int num, mult, i;
	
	LeNumero(num);
	Fatorial(num, mult);
	Resultado(mult);
	
	return 0;
}


















