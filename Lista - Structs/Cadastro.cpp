#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#define TF 100

struct TpAgenda
{
	char Nome[25], Endereco[40], Fone[15];
};

char Menu(void)
{
	system("cls");
	gotoxy(5,1);
	printf("\n===== M E N U  A G E N D A =====\n");
	gotoxy(5,3);
	printf("\n[A]: Cadastrar");
	gotoxy(5,4);
	printf("\n[B]: Exibir");
	gotoxy(5,5);
	printf("\n[C]: Consultar por Nome");
	gotoxy(5,6);
	printf("\n[D]: Ordenar por Nome");
	gotoxy(5,7);
	printf("\n[E]: Excluir por Telefone");
	gotoxy(5,8);
	printf("\n[F]: Alterar pelo Telefone");
	gotoxy(5,9);
	printf("\n[ESC]: Sair\n");
	gotoxy(5,10);
	
	printf("\nOpcao Desejada: ");
	
	return toupper(getche());
}

void Cadastro(TpAgenda TabAgenda[TF], int &TL)
{
	char AuxNome[30];
	system("cls");
	
	printf("\nCadastro de Pessoas\n");
	printf("\nNome: "); fflush(stdin);
	gets(AuxNome);
	
	while(TL < TF && strcmp(AuxNome,"\0") != 0)
	{
		strcpy(TabAgenda[TL].Nome, AuxNome);
		printf("\nEndereco: "); fflush(stdin);
		gets(TabAgenda[TL].Endereco);
		printf("\nTelefone: "); fflush(stdin);
		gets(TabAgenda[TL].Fone);
		TL++;
		
		printf("\nNome: "); fflush(stdin);
		gets(AuxNome);
	}
}

void Exibir(TpAgenda TabAg[TF], int TL)
{
	int i;
	system("cls");
	printf("===== Conteudo da Agenda =====\n");
	if(TL == 0)
		printf("\nNao ha Dados:[\n");
	else
	{
		printf("--------------------------------------------------------------------------------\n");
		printf(" Nome\t\t\t Endereco\t\t Telefone\n");
		printf("--------------------------------------------------------------------------------\n");
		
		for(i = 0; i < TL; i++)
			printf("%s\t\t\t %s\t\t\t %s\n", TabAg[i].Nome, TabAg[i].Endereco, TabAg[i].Fone);
	}
	getch();
}

void OrdenarNome(TpAgenda Ag[TF], int TL)
{
	int a, b;
	
	TpAgenda AuxOrdem;
	
	if(TL == 0)
		printf("\nNao ha Dados:[\n");
	else
	{
		for(a = 0; a < TL - 1; a++)
			for(b = a + 1; b < TL; b++)
				if(stricmp(Ag[a].Nome, Ag[b].Nome) > 0)
				{
					AuxOrdem = Ag[a];
					Ag[a] = Ag[b];
					Ag[b] = AuxOrdem;
				}
		printf("\nAgenda Ordenada!\n");
	}
}

int BuscarNome(TpAgenda Ag[TF], int TL, char NomePessoa[30])
{
	int i = 0;
	while(i < TL && stricmp(NomePessoa, Ag[i].Nome)!=0)
		i++;
	if(i < TL)
		return i;
	else
		return -1; //posição que não existe no vetor
}

int BuscarFone(TpAgenda Ag[TF], int TL, char Telefone[15])
{
	int i = 0;
	while(i < TL && stricmp(Telefone, Ag[i].Fone)!=0)
		i++;
	if(i < TL)
		return i;
	else
		return -1; //posição que não existe no vetor
}

void ConsultarNome(TpAgenda Ag[TF], int TL)
{
	char AuxNome[30];
	int pos;
	system("cls");
	printf("### Consultar por Nome ###\n");
	printf("\nNome: "); fflush(stdin);
	gets(AuxNome);
	
	while(strcmp(AuxNome, "\0")!=0)
	{
		pos = BuscarNome(Ag, TL, AuxNome);
		if(pos == 1)
			printf("\nNome Nao Encontrado!\n");
		else
		{
			printf("\n### Dados Encontrados ###\n");
			printf("\nNome: %s\n", Ag[pos].Nome);
			printf("Endereco: %s\n", Ag[pos].Endereco);
			printf("Telefone: %s\n", Ag[pos].Fone);
		}
		getch();
		printf("\nNome: "); fflush(stdin);
		gets(AuxNome);
	}
}

void ExcluirFone(TpAgenda Ag[TF], int &TL)
{
	char AuxFone[15];
	int pos;
	system("cls");
	printf("### Excluir por Telefone ###\n");
	printf("\nTelefone: "); fflush(stdin);
	gets(AuxFone);
	
	while(strcmp(AuxFone, "\0")!=0)
	{
		pos = BuscarFone(Ag, TL, AuxFone);
		if(pos == 1)
			printf("\nTelefone Nao Encontrado!\n");
		else
		{
			printf("\n### Dados Encontrados ###\n");
			printf("Nome: %s\n", Ag[pos].Nome);
			printf("Endereco: %s\n", Ag[pos].Endereco);
			printf("Telefone: %s\n", Ag[pos].Fone);
		}

		printf("\nConfirma Exclusao? [S/N]: ");
		if(toupper(getche()) == 'S')
		{
			for(; pos < TL - 1; pos++)
				Ag[pos] = Ag[pos + 1];
			TL--;
			printf("\n===Dados Excluidos!===\n");
		}
		printf("\nTelefone: "); fflush(stdin);
		gets(AuxFone);
	}
	
}

void AlterarFone(TpAgenda Ag[TF], int TL)
{
	char AuxFone[15];
	int pos;
	system("cls");
	printf("### Alterar por Telefone ###\n");
	printf("\nTelefone: "); fflush(stdin);
	gets(AuxFone);
	
	while(strcmp(AuxFone, "\0")!=0)
	{
		pos = BuscarFone(Ag, TL, AuxFone);
		if(pos == 1)
			printf("\nTelefone Nao Encontrado!\n");
		else
		{
			printf("\n### Dados Encontrados ###\n");
			printf("Nome: %s\n", Ag[pos].Nome);
			printf("Endereco: %s\n", Ag[pos].Endereco);
			printf("Telefone: %s\n", Ag[pos].Fone);
		}

		printf("\nConfirma Alteracao? [S/N]: ");
		if(toupper(getche()) == 'S')
		{
			printf("\nDigite o Novo Telefone: "); fflush(stdin);
			gets(AuxFone);
			strcpy(Ag[pos].Fone, AuxFone);
			printf("\n Telefone Alterado! \n");
		}
		printf("\nDigite outro telefone para alterar: "); fflush(stdin);
		gets(AuxFone);
	}
}

void Executar(void)
{
	char Opcao;
	TpAgenda Agenda[TF];
	int TLAg = 0;
	
	do
	{
		Opcao = Menu();
		
		switch(Opcao)
		{
			case 'A': Cadastro(Agenda, TLAg);
					  break;
					  
			case 'B': Exibir(Agenda, TLAg);
					  break;
					  
			case 'C': ConsultarNome(Agenda, TLAg);
					  break;
					  
			case 'D': OrdenarNome(Agenda, TLAg);
					  break;
					  
			case 'E': ExcluirFone(Agenda, TLAg);
					  break;
					  
			case 'F': AlterarFone(Agenda, TLAg);
					  break;
		}
		
	}while(Opcao != 27);
}

int main(void)
{
	Executar();
	return 0;
}
