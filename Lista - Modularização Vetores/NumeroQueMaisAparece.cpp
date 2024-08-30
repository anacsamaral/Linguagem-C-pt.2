#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define TF 100

// será passado por referência (Vetor e TL)
// toda variável indexada, como Vetor[TF] não precisa de '&', pois já é um endereço por padrão.
void LeVetor(int Vetor[TF], int &TL)
{
    int aux;
    system("cls");
    printf("\n### Inserir no Vetor ###\n");
    printf("Numero [%d]: ", TL);
    scanf("%d", &aux);

    while (TL < TF && aux > 0)
    {
        Vetor[TL++] = aux;
        // Vetor[TL++] -> vetor na posição TL recebe aux, após o ';', vai fazer receber TL++
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

// Não é recomendado usar variável global
void ExibeVetor(int Vet[TF], int Qtde) // Se fosse um TL em 'Qtde', ele não possuiria nenhuma relação com o da função anterior
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
    int i, j, MaiorCont = 0;
    for (i = 0; i < TL - 1; i++)
    {
        QtdeVezes = 1;
        for (j = i; j < TL; j++)
        {
            if (V[i] == V[j])
                QtdeVezes++;

            if (QtdeVezes > MaiorCont)
            {
                MaisAparece = V[i];
                MaiorCont = QtdeVezes;
            }
        }
    }
}

int main(void)
{
    int VA[TF], TLA = 0, Elemento, QtVezes;
    LeVetor(VA, TLA);
    ExibeVetor(VA, TLA);
    Frequencia(VA, TLA, Elemento, QtVezes); // Na ordem de void Frequencia (V, TL, MA, QV)
    if (TLA > 0)
    {
        printf("\nElemento de maior frequencia: %d", Elemento);
        printf("\nQtde de Vezes: %d\n", QtVezes);
    }

    return 0;
}