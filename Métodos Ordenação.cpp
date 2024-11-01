#include <stdio.h>
// M E T O D O S   D E   O R D E N A Ç Ã O
#define TF 10
//INSERÇÃO DIRETA
//por permutação = troca;
//pega o ultimo elemento inserido e desloca no vetor
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

void LeVetor(int V[TF], int &TL)
{
	int aux;
	
	printf("\n ** Inserir Elemento **\n");
	scanf("%d", &aux);
	
	while(TL < TF && aux != 0)
	{
		V[TL++] = aux;
		InsercaoDireta(V, TL);
		//Pega o ultimo elemento que inseriu e vai colocar em ordem; comparando com o vizinho, se nao tiver mais ninguem, acaba;
		//pega o proximo, na posicao TL - 1, olha o vizinho, compara se é menor, um vai pro lugar do outro, e assim sucessivamente;
		
		
		printf("\nVetor[%d]:", TL);
		scanf("%d", &aux);
		
	}
	
}


//ORDENAÇÃO POR BOLHA
// - método de ordenação da categoria por troca (mais lento)
// - olha e troca, faz trocas desnecessárias para depois chegar na definitiva
// para um pequeno volume de dados
// se tem 7 elementos, será 7² de passos de ordenação
//ele sempre vai ordenar colocando o maior valor na ultima posição, portanto, na proxima busca, será até o antepenúltimo elemento
//DETALHE = se ja estiver ordenado em um determinado momento, tem que usar uma flag

void OrdenaBolha(int V[TF], int TL)
{
	int a, b, aux;
	
	while(TL > 1 && flag == 1) //tem pelo menos 2 elementos para comparar
	{
		flag = 0; //Vê se o vetor ja ta ordenado
		for(a = 0, b = a + 1; a < TL - 1; a++)
		if(V[a] > V[b])
		{
			aux = V[a]; //SEMPRE COMEÇA COM AUX
			V[a] = V[b];
			V[b] = aux;
			flag = 1;
		}	
		TL--;
	}
}

void Exibe(int V[TF], int TL)
{
	int i;
	for(i = 0; i < TL; i++)
		printf("%d, ", V[i]);
}

int main(void)
{
	int V[TF], TL = 0;
	
	LeVetor(V, TL);
	//InsercaoDireta(V, TL);
	OrdenaBolha(V, TL);
	Exibe(V, TL);
	
	return 0;
}

//SELEÇÃO DIRETA
// - precisa do vetor ordenado
// - seleciona quem é pra ser trocado e troca o elemento
//qual o maior elemento e em que posição ele está

void OrdenaSelDir(int V[TF], int TL)
{
	int a, maior, posmaior, aux;
	while (TL > 1)	
	{
		maior = V[0]; // ou TL - 1;
		posmaior = 0;
		
		for(a = 0; a < TL; a++)
			if (V[a] > maior)
			{
				maior = V[a];
				posmaior = a;	
			}
		//T R O C A
		V[posmaior] = V[TL - 1];
		V[TL - 1] = maior;
		TL--;
	}
}






