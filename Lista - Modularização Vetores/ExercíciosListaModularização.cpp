#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define TF 100

// sera passado por referencia (Vetor e TL)
// toda variavel indexada, como Vetor[TF] nao precisa de '&', pois ja ha um endereco por padrao.

//EXERCÍCIO [1]

void LeVetor(int Vetor[TF], int &TL) //por referencia = altera o valor da origem (vetor nao precisa pq ja eh passado por referencia
{
    int aux;
    system("cls");
    printf("\n### Inserir no Vetor ###\n");
    printf("Numero [%d]: ", TL);
    scanf("%d", &aux);

    while (TL < TF && aux > 0)
    {
        Vetor[TL++] = aux; // (1)Vetor[TL] = aux e depois (2)incrementa TL++ ou TL = TL + 1
        // Vetor[TL++] -> vetor na posicao TL recebe aux, apos o ';', vai fazer receber TL++
        // TL++
        if (TL == TF)
        {
            printf("VETOR CHEIO!!!\n");
            getch();
        }
        else
        {
            printf("Numero [%d]: ", TL);
            scanf("%d", &aux);
        }
    }
}

// Nao eh recomendado usar variavel global
void ExibeVetor(int Vet[TF], int Qtde) // Se fosse um TL em 'Qtde', ele nao possuiria nenhuma relacao com o da funcao anterior
{
    int i;
    system("cls");
    printf("\n### Conteudo do Vetor ###\n");
    if (Qtde == 0)
        printf("\nVetor Vazio!\n");
    else
        for (i = 0; i < Qtde; i++)
            printf("\nVetor[%d]: %d", i, Vet[i]);

    getch();
}

void Frequencia(int V[TF], int TL, int &MaisAparece, int &QtdeVezes)
{
    int i, j, cont = 0;
    QtdeVezes = 0;
    for (i = 0; i < TL - 1; i++)
    {
        cont = 0;
        for (j = i; j < TL; j++)
        {
            if (V[i] == V[j])
                cont++;

            if (cont > QtdeVezes)
            {
                MaisAparece = V[i];
                QtdeVezes = cont;
            }
        }
    }
}

//EXERCÍCIO [2]
void SomaVetor(int Vet[TF], int TLS)
{
	int i, Soma = 0;
	if (TLS == 0)
	{
		printf("Nao ha elementos para somar!!!\n");
		getch();
	}
	else
		for(i = 0; i < TLS; i++)
			Soma += Vet[i];
}


//EXERCICIO [5]
int Contido(int Vetor[TF], int &TL, int Valor)
{
	int i = 0;
	while (i < TL && Valor != Vetor[i])
		i++;
		
	if (i < TL)
		return 1;
	else
		return 0;
}

void Subtracao(int VetA[TF], int TA, int VetB, int TB, int VetC[TF], int TC)
{
    int i;
    for (i = 0; i < TA; i++)
        if (!Contido(VetB, TB, VetA[i])) //não achou vetA[i] dentro de B
            if (!Contido(VetC, TC, VetA[i])) // == 0 faz um valor falso retornar verdadeiro, da mesma forma que o sinal de '!'
                VetC[TC++] = VetA[i];

    printf("Subtracao Concluida!\n");
    getch();
}

void Interseccao(int VetA[TF], int TA, int VetB, int TB, int VetC[TF], int TC)
{
    int i;
    for (i = 0; i < TA; i++)
        if (Contido(VetB, TB, VetA[i])) //não achou vetA[i] dentro de B
            if (!Contido(VetC, TC, VetA[i])) // == 0 faz um valor falso retornar verdadeiro, da mesma forma que o sinal de '!'
                VetC[TC++] = VetA[i];

    printf("Interseccao Concluida!\n");
    getch();
}

void Uniao(int VetA[TF], int TA, int VetB, int TB, int VetC[TF], int TC)
{
    int i;
    for (i = 0; i < TA; i++)
        if(!Contido(VetC, TC, VetA[i]))


    printf("Uniao Concluida!\n");
    getch();
}

int main(void)
{
	//EXERCICIO [1]
    int VA[TF], TLA = 0, Elemento, QtVezes, VetorSoma[TF], TLS = 0, Soma, i, VA5[TF], TLA5 = 0, VB5[TF], TLB5 = 0, VC5[TF * 2], TLC5 = 0;
    LeVetor(VA, TLA);
    ExibeVetor(VA, TLA);
    Frequencia(VA, TLA, Elemento, QtVezes); // Na ordem de void Frequencia (V, TL, MA, QV)
    if (TLA > 0)
    {
        printf("\nElemento de maior frequencia: %d", Elemento);
        printf("\nQtde de Vezes: %d\n", QtVezes);
    }
    
    //EXERCICIO [2]
    LeVetor(VetorSoma, TLS);
    ExibeVetor(VetorSoma, TLS);
    SomaVetor(VetorSoma, TLS); // Na ordem de void Frequencia (V, TL, MA, QV)
    if (TLS > 0)
    {
        for(i = 0; i < TLS; i++)
            Soma += VetorSoma[i];
            
        printf("\nA soma dos elementos do vetor eh: %d\n", Soma);
        getch();
    }
    else
        printf("\nNao ha elementos no vetor, portanto nao ha elementos para exibir\n");
    
    //EXERCICIO [5]
    system("cls");
    printf("Inserir Elementos no Vetor A: \n");
    LeVetor(VA5, TLA5);
    printf("Inserir Elementos no Vetor A: \n");
    LeVetor(VB5, TLB5);

    Subtracao(VA5, TLA5, VB5, TLB5, VC5, TLC5);
    printf("Resultado da Subtracao: \n");
    ExibeVetor(VC5, TLC5);

    Interseccao(VA5, TLA5, VB5, TLB5, VC5, TLC5);
    printf("Resultado da Interseccao: \n");
    ExibeVetor(VC5, TLC5);

    Uniao(VA5, TLA5, VB5, TLB5, VC5, TLC5);
    printf("Resultado da Uniao: \n");
    ExibeVetor(VC5, TLC5);
    return 0;
}