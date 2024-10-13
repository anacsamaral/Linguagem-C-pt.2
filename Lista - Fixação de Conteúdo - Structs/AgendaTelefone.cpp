#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>
#include <Windows.h>

#define TF 100

struct TpFone
{
	int DDD, Numero;	
};

struct TpData
{
	int Dia, Mes, Ano;	
};

struct TpEndereco
{
	char Rua[30], Complemento[20], Bairro[20], Cidade[40], Estado[3], Pais[30], CEP[10];
	int Numero;
};

struct TpAgenda
{
	char Nome[40], Obs[100], Email[80];
	TpEndereco Endereco;
	TpFone Fone;
	TpData Data;
	//Agenda; --> seria a variavel (global) sendo declarada logo depois da Struct (nao recomendado)
};

void CadAuto(TpAgenda Ag[TF], int &TLA, int i)
{
	if(i == 0)
	{
		strcpy(Ag[TLA].Nome, "Ana Caroline");
		strcpy(Ag[TLA].Email, "ana@gmail.com");
		strcpy(Ag[TLA].Endereco.Rua, "Carlos Raimundo");
		Ag[TLA].Endereco.Numero = 544;
		strcpy(Ag[TLA].Endereco.Complemento, "Frente");
		strcpy(Ag[TLA].Endereco.Bairro, "Jardim Sumare");
		strcpy(Ag[TLA].Endereco.CEP, "19042390");
		strcpy(Ag[TLA].Endereco.Cidade, "Presidente Prudente");
		strcpy(Ag[TLA].Endereco.Estado, "SP");
		strcpy(Ag[TLA++].Endereco.Pais, "Brasil");
		
		strcpy(Ag[TLA].Nome, "Lucas Roberto");
		strcpy(Ag[TLA].Email, "lucas@gmail.com");
		strcpy(Ag[TLA].Endereco.Rua, "Afonso Flores");
		Ag[TLA].Endereco.Numero = 700;
		strcpy(Ag[TLA].Endereco.Complemento, "Frente");
		strcpy(Ag[TLA].Endereco.Bairro, "Vila Flores");
		strcpy(Ag[TLA].Endereco.CEP, "19041150");
		strcpy(Ag[TLA].Endereco.Cidade, "Presidente Prudente");
		strcpy(Ag[TLA].Endereco.Estado, "SP");
		strcpy(Ag[TLA++].Endereco.Pais, "Brasil");
		
		strcpy(Ag[TLA].Nome, "Calebe");
		strcpy(Ag[TLA].Email, "calebe@gmail.com");
		strcpy(Ag[TLA].Endereco.Rua, "Agenor Ferreira");
		Ag[TLA].Endereco.Numero = 260;
		strcpy(Ag[TLA].Endereco.Complemento, "Frente");
		strcpy(Ag[TLA].Endereco.Bairro, "Joao Domingos");
		strcpy(Ag[TLA].Endereco.CEP, "19036064");
		strcpy(Ag[TLA].Endereco.Cidade, "Presidente Prudente");
		strcpy(Ag[TLA].Endereco.Estado, "SP");
		strcpy(Ag[TLA++].Endereco.Pais, "Brasil");
		
		i++;
		
		printf("\nCadastro automatico realizado!\n");
		getch();
	}
	else
	{
		printf("\nCadastro automatico ja realizado, nao pode ser feito novamente!\n");
		getch();
	}
}

void Cadastro(TpAgenda Ag[TF], int &TL)
{
	char Aux[40];
	system("cls");
	printf("\n### Cadastro de Pessoas ###\n");
	//NOME
	printf("Nome: "); fflush(stdin);
	gets(Aux);
	
	while (TL < TF && strcmp(Aux,"\0") != 0)
	{
		//E-MAIL
		strcpy(Ag[TL].Nome, Aux);
		printf("E-Mail: "); fflush(stdin);
		gets(Ag[TL].Email);
		
		//ENDEREÇO
		printf("Endereco:\n Rua: "); fflush(stdin);
		gets(Ag[TL].Endereco.Rua);
		printf("\n Numero: ");
		scanf("%d", &Ag[TL].Endereco.Numero);
		printf("\n Complemento: "); fflush(stdin);
		gets(Ag[TL].Endereco.Complemento);
		printf("\n Bairro: "); fflush(stdin);
		gets(Ag[TL].Endereco.Bairro);
		printf("\n CEP: "); fflush(stdin);
		gets(Ag[TL].Endereco.CEP);
		printf("\n Cidade: "); fflush(stdin);
		gets(Ag[TL].Endereco.Cidade);
		printf("\n Estado: "); fflush(stdin);
		gets(Ag[TL].Endereco.Estado);
		printf("\n Pais: "); fflush(stdin);
		gets(Ag[TL].Endereco.Pais);
		
		//TELEFONE E DATA DE NASCIMENTO
		printf("Telefone [xx xxxxxxxxx]:"); fflush(stdin);
		scanf("%d %d", &Ag[TL].Fone.DDD, &Ag[TL].Fone.Numero); //1º %d = &Ag[TL].Fone.DDD | 2º %d = &Ag[TL].Fone.Numero
		printf("Data de Nascimento [dd mm aaaa]: "); fflush(stdin);
		scanf("%d %d %d", &Ag[TL].Data.Dia, &Ag[TL].Data.Mes, &Ag[TL].Data.Ano);
		
		
		TL++;
		printf("\nOutro Nome: "); fflush(stdin);
		gets(Aux);
	}
}

void BuscaNome(TpAgenda Ag[TF], int TL)
{
	char PrimeiroNome[25];
	int i = 0;
	
	system("cls");
	printf("\n### Busca pelo Primeiro Nome ###\n");
	printf("Nome: "); fflush(stdin);
	gets(PrimeiroNome);
	
	while (i < TL && strcmp(PrimeiroNome,"\0")!=0)
	{
		while strcmp((Ag[i].Nome[i], " ") != 0) //procurar até ter um espaço
		{
			printf("Nome: %s\t E-Mail: %s\n Endereço: %s, %s, %s, %s, %s, %s, %s, %s.\n", Ag[i].Nome, Ag[i].Email, Ag[i].Endereco.Rua, Ag[i].Endereco.Numero, Ag[i].Endereco.Complemento, Ag[i].Endereco.Bairro, Ag[i].Endereco.CEP, Ag[i].Endereco.Cidade, Ag[i].Endereco.Pais);
			printf("Telefone: %s\nData de Aniversario: %s/%s/%s\n", Ag[i].Fone, Ag[i].Data.Dia, Ag[i].Data.Mes, Ag[i].Data.Ano);
			printf("Observacoes: %s\n");
		}
		else
		{
			printf("\nPessoa nao cadastrada\n");
			getch();
		}
		
		printf("Outro Nome: "); fflush(stdin);
		gets(PrimeiroNome);
	}
	getch();
}

void BuscaMes(TpAgenda Ag[TF], int TLD)
{
	TpData AgData[TF];
	int i, mes;
	
	system("cls");
	printf("\n### Busca pelo Mes ###\n");
	printf("Digite o Mes: ");
	scanf("%d", &mes);
	
	while (mes > 0 && mes < 13)
	{
		while (i < TLD && AgData[i].Mes != mes)
			i++;
	
		if(i == TLD)
		{
			printf("Dados nao cadastrados.");
			getch();
		}
		else
		{
			printf("Nome: %s\t E-Mail: %s\n Endereço: %s, %s, %s, %s, %s, %s, %s, %s.\n", Ag[i].Nome, Ag[i].Email, Ag[i].Endereco.Rua, 
			Ag[i].Endereco.Numero, Ag[i].Endereco.Complemento, Ag[i].Endereco.Bairro, Ag[i].Endereco.CEP, Ag[i].Endereco.Cidade, Ag[i].Endereco.Pais);
			printf("Telefone: %s\nData de Aniversario: %s/%s/%s\n", Ag[i].Fone, Ag[i].Data.Dia, Ag[i].Data.Mes, Ag[i].Data.Ano);
			printf("Observacoes: %s\n");
		}
			
		printf("\nOutro Mes para Busca: ");
		scanf("%d", &mes);
	}
	getch();
}

char Menu(void)
{
	system("cls");
	printf("\n===== M E N U  A G E N D A =====\n");
	printf("\n[A]: Cadastrar");
	printf("\n[B]: Busca por Primeiro Nome");
	printf("\n[C]: Busca por Mes de Aniversario");
	printf("\n[D]: Inserir Pessoa");
	printf("\n[E]: Excluir Pessoa");
	printf("\n[F]: Exibir Agenda");
	printf("\n[G]: Cadastro Automatico");
	printf("\n[ESC]: Sair\n");
	
	printf("\nOpcao Desejada: ");
	
	return toupper(getche());
}

void Executar(void)
{
	char Opcao;
	TpAgenda Agenda[TF];
	int TLAg = 0, i = 0;
	
	do
	{
		Opcao = Menu();
		
		switch(Opcao)
		{
			case 'A': Cadastro(Agenda, TLAg);
					  break;
					  
			case 'B': BuscaNome(Agenda, TLAg);
					  break;
					  
//			case 'C': BuscaMes(Agenda, TLAg);
//					  break;
//					  
//			case 'D': InserirPessoa(Agenda, TLAg);
//					  break;
//					  
//			case 'E': ExcluirPessoa(Agenda, TLAg);
//					  break;
//					  
//			case 'F': Exibir(Agenda, TLAg);
//					  break;

			case 'G': CadAuto(Agenda, TLAg, i);
					  break;
		}
	}while(Opcao != 27);
}

int main(void)
{
	Executar();
	return 0;
}
