#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define TF 10

int BuscaBinaria(int V[TF], int TL, int Chave)
{
	int inicio = 0, fim = TL - 1, meio;
	meio = TL / 2;
	
	while(inicio < fim && Chave != V[meio])
	{
		if(Chave > V[meio])
			inicio = meio + 1;
		
		else
			fim = meio - 1;
		
		meio = (inicio + fim) / 2;
	}
	
	if(Chave == V[meio])
		return meio;
	else
		return -1;
}

void InsercaoDireta(int V[TF], int TL)
{
	int aux, i = TL - 1;
	
	while(i > 0 && V[i] < V[i-1])
	{
		aux = V[i-1];
		V[i-1] = V[i];
		V[i] = aux;
		i--;
	}
}

void Exibir(int V[TF], int TL)
{
	int i = 0;
	system("cls");
	
	printf("\nConteudo do Vetor:\n");
	if (TL == 0)
		printf("\nVetor Vazio");
	else
		for(i = 0; i < TL; i++)
			printf("Vetor[%d]: %d\n", i, V[i]);
	
	getch();
}

void LeVetor(int V[TF], int &TL)
{
	int aux;
	
	printf("\n ** Inserir Elemento **\n");
	printf("\nVetor[%d]: ", TL);
	scanf("%d", &aux);
	
	while(TL < TF && aux != 0)
	{
		V[TL++] = aux;
		InsercaoDireta(V, TL);
		//Pega o ultimo elemento que inseriu e vai colocar em ordem; comparando com o vizinho, se nao tiver mais ninguem, acaba;
		//pega o proximo, na posicao TL - 1, olha o vizinho, compara se � menor, um vai pro lugar do outro, e assim sucessivamente;
		
		printf("\nVetor[%d]: ", TL);
		scanf("%d", &aux);
	}
	
}

int main(void)
{
	int Vetor[TF], Qtd = 0;
	LeVetor(Vetor, Qtd);
	Exibir(Vetor, Qtd);
	
	return 0;
}
