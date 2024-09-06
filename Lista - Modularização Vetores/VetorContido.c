//EXERCICIO [5]
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define TF 100

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

void ExibeVetor(int Vet[TF], int &Qtde) // Se fosse um TL em 'Qtde', ele nao possuiria nenhuma relacao com o da funcao anterior
{
    int i;
    printf("\n### Conteudo do Vetor ###\n");
    if (Qtde == 0)
        printf("\nVetor Vazio!\n");
    else
        for (i = 0; i < Qtde; i++)
            printf("\nVetor[%d]: %d", i, Vet[i]);
    printf("\n");

    getch();
}

void LeVetor(int Vetor[TF], int &TL) //por referencia = altera o valor da origem (vetor nao precisa pq ja eh passado por referencia
{
    int aux;
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

void Subtracao(int VetA[TF], int TA, int VetB[TF], int TB, int VetC[TF], int &TC)
{
    int i;
    TC = 0;
    for (i = 0; i < TA; i++)
        if (!Contido(VetB, TB, VetA[i])) //não achou vetA[i] dentro de B
            if (!Contido(VetC, TC, VetA[i])) // == 0 faz um valor falso retornar verdadeiro, da mesma forma que o sinal de '!'
                VetC[TC++] = VetA[i];
                
    for (i = 0; i < TA; i++)
        if (!Contido(VetB, TB, VetA[i])) //não achou vetA[i] dentro de B
            if (!Contido(VetC, TC, VetB[i])) // == 0 faz um valor falso retornar verdadeiro, da mesma forma que o sinal de '!'
                VetC[TC++] = VetB[i];

    printf("\n### Subtracao Concluida! ###\n");
    getch();
}

void Interseccao(int VetA[TF], int TA, int VetB[TF], int TB, int VetC[TF], int &TC)
{
    int i;
    TC = 0;
    for (i = 0; i < TA; i++)
        if (Contido(VetB, TB, VetA[i])) //não achou vetA[i] dentro de B
            if (!Contido(VetC, TC, VetA[i])) // == 0 faz um valor falso retornar verdadeiro, da mesma forma que o sinal de '!'
                VetC[TC++] = VetA[i];

    printf("\nInterseccao Concluida!\n");
    getch();
}

void Uniao(int VetA[TF], int TA, int VetB[TF], int TB, int VetC[TF], int &TC)
{
    int i;
    TC = 0;
    for (i = 0; i < TA; i++)
        if(!Contido(VetC, TC, VetA[i]))
        	VetC[TC++] = VetA[i];


    printf("\nUniao Concluida!\n");
    getch();
}

int main(void)
{
	int VA5[TF], TLA5 = 0, VB5[TF], TLB5 = 0, VC5[TF * 2], TLC5 = 0;
    system("cls");
    printf("\n\n### Inserir Elementos no Vetor A: ###\n");
    LeVetor(VA5, TLA5);
    ExibeVetor(VA5, TLA5);
    printf("\n\n### Inserir Elementos no Vetor B: ###\n");
    LeVetor(VB5, TLB5);
    ExibeVetor(VB5, TLB5);

    Subtracao(VA5, TLA5, VB5, TLB5, VC5, TLC5);
    printf("\nResultado da Subtracao: \n");
    ExibeVetor(VC5, TLC5);

    Interseccao(VA5, TLA5, VB5, TLB5, VC5, TLC5);
    printf("\nResultado da Interseccao: \n");
    ExibeVetor(VC5, TLC5);

    Uniao(VA5, TLA5, VB5, TLB5, VC5, TLC5);
    printf("\nResultado da Uniao: \n");
    ExibeVetor(VC5, TLC5);
    return 0;
}
    
//MERGE = compara o elemento fixo de vetA com os elemenetos de vetB, o que for menor é inserido no vetC