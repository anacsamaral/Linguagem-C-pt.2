#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define TF 5

struct TpPessoa
{
	char Nome[20], Endereco[100], Telefone[20];
};

void Cadastro(TpPessoa Dados[TF], int &TL)
{
	char AuxNome[20];
	system("cls");
	
	printf("\nCadastro de Pessoas\n");
	printf("\nNome: "); fflush(stdin);
	gets(AuxNome);
	
	while(TL < TF && strcmp(AuxNome,"\0") != 0)
	{
		strcpy(Dados[TL].Nome, AuxNome);
		printf("\nEndereco: "); fflush(stdin);
		gets(Dados[TL].Endereco);
		printf("\nTelefone: "); fflush(stdin);
		gets(Dados[TL].Telefone);
		TL++;
		
		system("cls");
		printf("\nCadastro de Pessoas\n");
		printf("\nNome: "); fflush(stdin);
		gets(AuxNome);
		
	}
}

void Exibe(TpPessoa Dados[TF], int TL)
{
    for (int i = 0; i < TL; i++) 
	{
        printf("\n### Cadastro [%d] ###\n", i + 1);
        printf("Nome: %s\n", Dados[i].Nome);
        printf("Endereco: %s\n", Dados[i].Endereco);
        printf("Telefone: %s\n", Dados[i].Telefone);
    }
}

void OrdenaNome(TpPessoa Dados[TF], int TL)
{
	int a, b;
	
	TpPessoa AuxOrdem;
	
	if(TL == 0)
		printf("\nNao ha dados para exibir!\n");
	else
	{
		for(a = 0; a < TL - 1; a++)
			for(b = a + 1; b < TL; b++)
			if(stricmp(Dados[a].Nome, Dados[b].Nome) > 0)
			{
				AuxOrdem = Dados[a];
				Dados[a] = Dados[b];
				Dados[b] = AuxOrdem;
			}
		printf("\nNomes Ordenados!\n"); getch();
	}
}

int main(void)
{
	TpPessoa Dados[TF];
	int TLD = 0;
	
	Cadastro(Dados, TLD);
	Exibe(Dados, TLD);
	OrdenaNome(Dados, TLD);
	Exibe(Dados, TLD);
	
	return 0;
}
