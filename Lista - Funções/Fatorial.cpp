#include <stdio.h>

void LeNumero(int &num)
{
	printf("Digite o numero: [0 para sair]\n");
	scanf("%d", &num);
}

int Fatorial(int &numero, int &soma)
{
    soma = 0;

    while(numero > 0)
    {
    	soma += numero;
    	numero--;
	}

	return soma;
}

void Resultado (int valor)
{
	printf("Fatorial: %d\n", valor);
}

int main(void)
{
	int num, soma, i;
	
	LeNumero(num);
	Fatorial(num, soma);
	Resultado(soma);
	
	return 0;
}


















