//TRABALHO BIMESTRAL - ATP II - ANA AMARAL, ANA LIGIA, GUILHERME SALES
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio2.h>
#include <string.h>
#include <Windows.h>


#define TF 100

struct TpAlunos
{
	char RA[13], Nome[40];
};

struct TpDisca
{
	int CodDisc;
	char Discip[40];
};

struct TpNotas
{
	char RA[13];
	int CodDisc;
	float Nota;
};

// Cadastro automático
void CadAuto(TpAlunos TabAl[TF], TpDisc TabDi[TF], TpNotas TabNo[TF], int &TLA, int &TLA2, int &TLA3, int &cont)
{
	if(cont==0)
	{
		strcpy(TabAl[TLA].RA, "26.09.1045-1");
		strcpy(TabAl[TLA++].Nome, "Bertalia");
		strcpy(TabAl[TLA].RA, "10.09.1055-3");
		strcpy(TabAl[TLA++].Nome, "Creusa");
		strcpy(TabAl[TLA].RA, "26.09.2012-1");
		strcpy(TabAl[TLA++].Nome, "Florisbela");
		strcpy(TabAl[TLA].RA, "10.09.3052-6");
		strcpy(TabAl[TLA++].Nome, "Jurema");
		strcpy(TabAl[TLA].RA, "26.09.3444-8");
		strcpy(TabAl[TLA++].Nome, "Yuri");
		
		// Cadastro de disciplinas
		TabDi[TLA2].CodDisc = 100;
		strcpy(TabDi[TLA2++].Discip, "ATP I");
		TabDi[TLA2].CodDisc = 105;
		strcpy(TabDi[TLA2++].Discip, "ATP II");
		TabDi[TLA2].CodDisc = 120;
		strcpy(TabDi[TLA2++].Discip, "Estrutura de Dados I");
		TabDi[TLA2].CodDisc = 150;
		strcpy(TabDi[TLA2++].Discip, "Pesquisa e Ordenacao");
		TabDi[TLA2].CodDisc = 210;
		strcpy(TabDi[TLA2++].Discip, "Ferramentas I");
		TabDi[TLA2].CodDisc = 230;
		strcpy(TabDi[TLA2++].Discip, "Estatistica");
		TabDi[TLA2].CodDisc = 240;
		strcpy(TabDi[TLA2++].Discip, "Matematica Discreta");
		
		
		// Cadastro de notas
		strcpy(TabNo[TLA3].RA, "26.09.1045-1");
		TabNo[TLA3].CodDisc = 120;
		TabNo[TLA3++].Nota = 8.0;
		strcpy(TabNo[TLA3].RA, "26.09.1045-1");
		TabNo[TLA3].CodDisc = 210;
		TabNo[TLA3++].Nota = 4.5;
		strcpy(TabNo[TLA3].RA, "26.09.1045-1");
		TabNo[TLA3].CodDisc = 230;
		TabNo[TLA3++].Nota = 6.5;
		strcpy(TabNo[TLA3].RA, "10.09.1055-3");
		TabNo[TLA3].CodDisc = 150;
		TabNo[TLA3++].Nota = 5.0;
		strcpy(TabNo[TLA3].RA, "10.09.1055-3");
		TabNo[TLA3].CodDisc = 240;
		TabNo[TLA3++].Nota = 4.5;
		
		cont++;
		
		gotoxy(40,9);
		printf("Cadastro automatico realizado!");
		getch();
	}
	else
	{
		gotoxy(40,9);
		printf("Cadastro automatico ja realizado, nao pode ser feito novamente!");
		getch();
	}
}

int MaiorPos(TpAlunos Al[TF], int TLA)
{
	int pos;
	char maior[40];
	
	strcpy(maior, Al[0].Nome);
	pos = 0;
	
	for(int i=1; i<TLA; i++)
		if(stricmp(maior,Al[i].Nome) < 0)
		{
	 		strcpy(maior,Al[i].Nome);
			pos = i;
		}
	
	 return pos;
}

void OrdenaAluno(TpAlunos Al[TF], int TLA)
{
	 TpAlunos maior;
	 int pos;
	 
	 while (TLA > 0)
	 {
		pos = MaiorPos(Al, TLA);
		if (pos < TLA-1)
		{
		 maior = Al[pos];
		 Al[pos] = Al[TLA-1];
		 Al[TLA-1] = maior;
		}
		
		TLA--;
	 }
}

// Exibir tabelas
void Exibe(TpAlunos TabAl[TF], TpDisc TabDi[TF], TpNotas TabNo[TF], int Tla1, int Tla2, int Tla3)
{
	int i;
	if (Tla1 != 0 || Tla2 != 0 || Tla3 != 0)
	{
		for (i = 0; i < Tla1; i++)
		{
			gotoxy(40, i * 2 + 7);
			printf("RA: %s", TabAl[i].RA);	
			gotoxy(40, i * 2 + 8);
			printf("Nome: %s", TabAl[i].Nome);
		}
		for (i = 0; i < Tla2; i++)
		{
			gotoxy(60, i * 2 + 7);
			printf("Codigo da materia: %d", TabDi[i].CodDisc);	
			gotoxy(60, i * 2 + 8);
			printf("Disciplina: %s", TabDi[i].Discip);
		}
		for (i = 0; i < Tla3; i++)
		{
			gotoxy(95, i * 3 + 7);
			printf("RA: %s", TabNo[i].RA);	
			gotoxy(95, i * 3 + 8);
			printf("Disciplina: %d", TabNo[i].CodDisc);
			gotoxy(95, i * 3 + 9);
			printf("Nota: %.1f", TabNo[i].Nota);
		}
	}
	else
	{
		gotoxy(39, 7);
		printf("Nao possui dados salvos", 227);
	}
	getch();
}

// Entrada com animação para início
void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF, int temp)
{
	int i, j;
	
	textcolor(CorT);
	textbackground(CorF);
	gotoxy(CI, LI); printf("%c", 201);
	gotoxy(CF, LI); printf("%c", 187);
	gotoxy(CI, LF); printf("%c", 200);
	gotoxy(CF, LF); printf("%c", 188);
	for (i = CI + 1; i < CF; i++)
	{
		gotoxy(i, LI); printf("%c", 205);
		Sleep(temp);
		gotoxy(i, LF); printf("%c", 205);
	}
	for (j = LI + 1; j < LF; j++)
	{
		gotoxy(CI, j); printf("%c", 186);
		Sleep(temp);
		gotoxy(CF, j); printf("%c", 186);
	}
}

// Padronização das fontes
void Cor()
{
	textcolor(10);
	textbackground(16);
}

// Menu, print dos itens para selecionar
char Menu(void)
{
	gotoxy(5, 7);
	printf(" ===== M E N U =====");
	gotoxy(5, 10);
	printf("[A] Cadastro Manual");
	gotoxy(5, 11);
	printf("[B] Exibir Tabelas");
	gotoxy(5, 12);
	printf("[C] Consultar");
	gotoxy(5, 13);
	printf("[D] Excluir");
	gotoxy(5, 14);
	printf("[E] Cadastro Automatico");
	gotoxy(5, 15);
	printf("[F] Alterar");
	gotoxy(5, 16);
	printf("[G] Relatorio");
	gotoxy(5, 17);
	printf("[H] Ordenar");
	gotoxy(5, 18);
	printf("[ESC] Sair");
	gotoxy(5, 20);
	printf("Opcao desejada: ");
	gotoxy(5, 21);                                         
	return toupper(getche());
}
													
void LimpaMenu()
{
	//COLUNA 1 ATÉ 30
	//LINHA  7  ATÉ 20
	for(int i=3;i<29;i++)
		for(int j=6;j<23;j++)
		{
			gotoxy(i,j);
			printf("%c",32);
		}		
}
				
void LimpaExibe()
{
	//COLUNA 1 ATÉ 30
	//LINHA  7  ATÉ 20
	for(int i=32;i<118;i++)
		for(int j=6;j<23;j++)
		{
			gotoxy(i,j);
			printf("%c",32);
		}		
}

void LimpaExibe2()
{
	//COLUNA 1 ATÉ 30
	//LINHA  7  ATÉ 20
	for(int i=70;i<90;i++)
		for(int j=9;j<30;j++)
		{
			gotoxy(i,j);
			printf("%c",32);
		}		
}
										   
// Menu de consulta
char Menu2(void)
{
	
	LimpaMenu();
	gotoxy(5, 7);
	printf("===== M E N U =====");
	gotoxy(5, 10);
	printf("[A] Alunos");
	gotoxy(5, 11);
	printf("[B] Disciplinas");
	gotoxy(5, 12);
	printf("[C] Notas\n");
	gotoxy(5, 15);
	printf("[ESC] Sair\n");
	gotoxy(5, 17);
	return toupper(getche());
}
//Busca pelo cod da disciplina
int BuscaCod(TpDisc TabDi[TF],int TLA,int cod )
{
	
	int pos = 0;
	while (pos < TLA && TabDi[pos].CodDisc != cod)
		pos++; 
		
	if (pos<TLA)
		return pos;
	else
		return pos;
}

//Busca de RA para encontrar o aluno
int BuscaRA(TpAlunos Al[TF], int TLA, char AuxRA[13])
{
	int pos = 0;
	while (pos < TLA && strcmp(AuxRA, Al[pos].RA) != 0)
		pos++;
		
	if(pos < TLA)
		return pos;
	else
		return pos; // Retorna a posição encontrada ou o final da lista
}

//Busca pelo Nome
int BuscaNome(TpAlunos Al[TF], int TLA, char AuxNome[13])
{
	int pos = 0;
	while (pos<TLA && stricmp(AuxNome, Al[pos].Nome)!=0)
		pos++;
		
	if(pos < TLA)
		return pos;
	else
		return pos;
}

int BuscaAlunDisc(TpNotas TabNo[TF],char RA[13], int cod, int TLAd)
{
	
	int pos = 0;
	while (pos<TLAd && strcmp(RA, TabNo[pos].RA)!=0 || cod != TabNo[pos].CodDisc)
		pos++;
	
	if(pos < TLAd)
		return pos;
	else
		return -1;
}

int BuscaNota(TpNotas TabNo[TF],char RA[13], int cod, int TLAd, float nota)
{
	
	int pos = 0;
	while (pos<TLAd && strcmp(RA, TabNo[pos].RA)!=0 || cod != TabNo[pos].CodDisc)
		pos++;
	
	return pos;
}

int BuscaNota2(TpNotas notas[TF], char aux[13],int TL)
{
	int pos=0;
	while(pos<TL && stricmp(aux,notas[pos].RA)!=0)
		pos++;
		
	return pos;
}

void BuscaReprova(TpNotas AlunDisc[TF], TpDisc Disc[TF], int TLA, int TLA2)
{
	int cod, cont=0, pos, i = 0;
	float soma = 0;
	
	cod = AlunDisc[0].CodDisc;
	
	gotoxy(40,7);
	printf("Disciplinas com media abaixo de 6:");
	
	while(i < TLA)
	{
		if(AlunDisc[i].CodDisc == cod)
		{
			soma += AlunDisc[i].Nota;
			cont++;	
		}
		else
		{
			if(soma / cont < 6.0)
			{
				pos = BuscaCod(Disc,TLA2,cod);
				
				getch();
				printf("Disciplinas com media abaixo de 6:");
				
				printf("Nome: %s", Disc[pos].Discip);
			}
			
			soma = AlunDisc[i].Nota, cont = 1, cod = AlunDisc[i].CodDisc;
		}
		i++;
	}
	
	getch();	
}

float MediaGeral(TpNotas AlunDisc[TF],TpDisc Disc[TF],int TLA,int TLA2)
{
	int i, soma=0;
	float media_geral;
	for(i = 0; i < TLA2; i++)
		if(AlunDisc[i].Nota < 6.0)
			soma += AlunDisc[i].Nota;
	
	media_geral = soma / TLA;
	return media_geral;
}

int ConsultaNota(TpNotas notas[TF], char aux[13],int &TL, int cod)
{
	int pos=0;
	while(pos<TL && stricmp(aux,notas[pos].RA)!=0)
		pos++;
		
	return pos;
}

int ConsultaDisc(TpDisc disc[TF], int &TL, int cod)
{
	int pos = 0;
	while(pos < TL && cod != disc[pos].CodDisc)
		pos++;
		
	return pos;
}


// Função principal de consulta
void Consultar(TpAlunos TabAl[TF], TpDisc TabDi[TF], TpNotas TabNo[TF], int TLA, int TLA2, int TLA3)
{
	char Auxchar[13], opcao;
	int cod, pos, pos2;
	do{
	
		opcao = Menu2();
		switch (opcao)
		{
			case 'A':
					LimpaExibe();
					gotoxy(50,7);
					printf("Opcao Consulta de Alunos");
					if (TLA == 0)
					{
						gotoxy(50,9);
						printf("Nao ha alunos!");
						getch();
					}
					else
					{
						gotoxy(50,9);
						printf("RA do aluno para consulta: ");
						fflush(stdin);
						gets(Auxchar);
						pos = BuscaRA(TabAl,TLA, Auxchar); //BUSCA POR RA
						if (pos < TLA) //Achou
						{
							gotoxy(50,10);
							printf("Aluno cadastrado: %s | RA: %s", TabAl[pos].Nome, TabAl[pos].RA);
						}
						else
						{
							gotoxy(50,10);
							printf("Aluno nao encontrado:(");
						}
						getch();
					}
				break;
				
			case 'B':
				LimpaExibe();
				gotoxy(50,7);
				printf("Opcao Consulta de Disciplinas");
				if (TLA2 == 0)
				{
					gotoxy(50,9);
					printf("Nao ha disciplinas cadastradas!");
					getch();
				}
				else
				{
					gotoxy(50,9);
					printf("Digite o cod da disciplina para consulta: ");
					fflush(stdin);
					scanf("%d", &cod);
					int pos = 0;
					while (pos < TLA2 && cod != TabDi[pos].CodDisc )
						pos++;
					if (pos < TLA2)
					{
						gotoxy(50,10);
						printf("Disciplina cadastrada: %s | Codigo: %d", TabDi[pos].Discip, TabDi[pos].CodDisc);
					}
					else
					{
						gotoxy(50,10);
						printf("Disciplina nao encontrada:(");
					}
					getch();
				}
				break;
				
			case 'C':
				LimpaExibe();
				gotoxy(50,7);
				printf("Opcao Consulta de Notas");
				if (TLA3 == 0)
				{
					gotoxy(50,9);
					printf("Nao ha notas cadastradas!");
					getch();
				}	
				else
				{
					gotoxy(50,9);
					printf("Digite o RA do aluno para consulta de notas: ");
					fflush(stdin);
					gets(Auxchar);
					int pos = 0;
					gotoxy(50,10);
					printf("Digite o codigo da materia: ");
					scanf("%d", &cod);
					
					pos2 = ConsultaDisc(TabDi,TLA2,cod);
					pos = ConsultaNota(TabNo,Auxchar,TLA3,cod);
			
					while(pos == -1)
					{
						gotoxy(50,11);
						printf("Dados nao encontrados");
		
						LimpaExibe();
						gotoxy(50,9);
						printf("Insira o RA do aluno que deseja alterar a nota:");
						fflush(stdin);
						gets(Auxchar);
		
						gotoxy(50,10);
						printf("Digite o codigo da disciplina:");
						scanf("%d",&cod);
		
						pos = ConsultaNota(TabNo,Auxchar,TLA3,cod);
						pos2 = ConsultaDisc(TabDi,TLA2,cod);
					}
					gotoxy(50,15);
					printf("Disciplina: %s | Nota: %.1f", TabDi[pos2].Discip, TabNo[pos].Nota);
					getch();
				}
			break;
    	}
	} while (opcao!=27);
}

// Exclusão de aluno, disciplina e notas
void Excluir(TpAlunos TabAl[TF], TpDisc TabDi[TF], TpNotas TabNo[TF], int &TLA, int &TLA2, int &TLA3)
{
	char Auxchar[40], opcao;
	int i, cod;
	gotoxy(5,7);
	printf("Excluir por:");
	do{
	
	 opcao = Menu2();
				 
		switch (opcao)
		{
			case 'A': // Excluir aluno
				LimpaExibe();
				gotoxy(50,7);
				printf("Excluir aluno");
				if (TLA == 0)
				{
					gotoxy(50,9);
					printf("Nao ha alunos cadastrados");
					getch();
				}
				else
				{
					gotoxy(50,9);
					printf("Digite o RA para exclusao: ");
					fflush(stdin);
					gets(Auxchar);
					int pos = 0;
					pos = BuscaRA(TabAl ,TLA, Auxchar);
					if (pos < TLA)
					{
						for (i = pos; i < TLA - 1; i++)
							TabAl[i] = TabAl[i + 1];
						TLA--;
						gotoxy(50,10);
						printf("Aluno excluido com sucesso!");
					}
					else
					{
						gotoxy(50,10);
						printf("Aluno nao encontrado");
					}
					getch();
				}
				break;
				
			case 'B': // Excluir disciplina
				LimpaExibe();
				gotoxy(50,7);
				printf("Excluir disciplina");
				if (TLA2 == 0)
				{
					gotoxy(50,9);
					printf("Nao ha disciplinas cadastradas");
					getch();
				}
				else
				{
					gotoxy(50,9);
					printf("Digite o codigo da disciplina para exclusão: ");
					int codDisc;
					scanf("%d", &codDisc);
					int pos = 0;
					while (pos < TLA2 && TabDi[pos].CodDisc != codDisc)
						pos++;
					if (pos < TLA2)
					{
						for (i = pos; i < TLA2 - 1; i++)
							TabDi[i] = TabDi[i + 1];
						TLA2--;
						gotoxy(50,10);
						printf("Disciplina excluida com sucesso!");
					}
					else
					{
						gotoxy(50,10);
						printf("Disciplina nao encontrada");
					}
					getch();
				}
				break;
			case 'C': // Excluir notas
				LimpaExibe();
				gotoxy(50,7);
				printf("Excluir notas");
				if (TLA3 == 0)
				{	
					gotoxy(50,9);
					printf("Nao ha notas cadastradas");
					getch();
				}
				else
				{
					gotoxy(50,9);
					printf("Digite o RA do aluno para exclusao das notas: ");
					fflush(stdin);
					gets(Auxchar);
					int pos = 0;
					BuscaRA(TabAl,TLA, Auxchar);
					gotoxy(50,10);
					printf("Digite o codigo da materia: ");
					scanf("%d", &cod);
	
					pos = BuscaAlunDisc(TabNo,Auxchar,cod,TLA3);
	
					while(pos == -1)
					{
						gotoxy(50,11);
						printf("Dados nao encontrados");
		
						LimpaExibe();
						gotoxy(50,9);
						printf("Insira o RA do aluno que deseja excluir a nota: ");
						fflush(stdin);
						gets(Auxchar);
		
						gotoxy(50,10);
						printf("Digite o codigo da disciplina: ");		
						scanf("%d",&cod);
		
						pos = BuscaAlunDisc(TabNo,Auxchar,cod,TLA3);
					}
					if (pos < TLA3)
					{
						for (i = pos; i < TLA3 - 1; i++)
						TabNo[i] = TabNo[i + 1];
						TLA3--;
						gotoxy(50,11);
						printf("Notas excluidas com sucesso!");
					}
					else
					{
						gotoxy(50,11);
						printf("Notas nao encontradas");
					}
					getch();
				}
				break;
		}
    }while (opcao!=27);
}

//Cadastro manual, escolhendo qual é qual
void CadMan(TpAlunos TabAl[TF], TpDisc TabDi[TF], TpNotas TabNo[TF], int &TLA, int &TLA2, int &TLA3)
{
	LimpaExibe();
    char AuxNome[40], AuxRA[13], opcao;
	int i, pos, pos1, pos2, Col = 70, Lin = 5;
	
	gotoxy(5, 9);
	printf("Cadastrar por:");
	do{
	
	 	opcao = Menu2();
		switch (opcao)
		{
			case 'A': 	
					LimpaExibe();
					gotoxy(50,7);
					printf("===== Cadastro Manual de alunos =====");
					if (TLA==TF)
					{
						gotoxy(40,9);
						printf ("Vetor esta cheio! [ENTER - Sair]");
						getch();
					}
					else
					{
						//LimpaExibe();
						gotoxy(40,9);
						printf("Digite o RA [xx.xx.xxxx-x] ou [ENTER] - Sair: ");
						gotoxy(40,10);
						fflush(stdin);
						gets(AuxRA);
						
						int pos = 0;
						while (TLA < TF && strcmp(AuxRA,"\0")!=0) //Já existe?
						{	
							pos = BuscaRA(TabAl, TLA, AuxRA);
						
							if (pos<TLA) //Achou
							{ 
								gotoxy(40,15);
								printf ("Aluno ja esta Cadastrado! [ENTER - Voltar]");
								getch();
							}
							else
							{
								strcpy(TabAl[TLA].RA,AuxRA);
								gotoxy(40,11);
								printf("Digite o Nome do aluno: ");
								gets(AuxNome);
								strcpy(TabAl[TLA].Nome,AuxNome);
								TLA++;
							}
							if (TLA<TF)
							{
								LimpaExibe();
								gotoxy(50,7);
								printf("===== Cadastro Manual de alunos =====");
								gotoxy(40,9);
								printf("Digite o RA [xx.xx.xxxx-x] [ENTER] - Sair: ",TLA);
								fflush(stdin);
								gets(AuxRA);
							}
							else
							{
								printf ("Vetor esta cheio!");
								pos++;
							}
						}
					}
					break;
				
			case 'B':	
					int cod;
					LimpaExibe();
					gotoxy(50,7);
					printf("===== Cadastro Manual de disciplina =====");
					if (TLA2==TF)
					{
						gotoxy(40,15);
						printf ("Vetor esta cheio!");
						getch();
					}
					else
					{
						gotoxy(40,9);
						printf("Digite o codigo da disciplina [0 - Sair]: ");
						scanf("%d", &cod);
						
						int pos = 0;
						while (TLA2 < TF && cod != 0 ) //Já existe?
						{	
					
							pos = BuscaCod(TabDi,TLA2,cod);
														   
							if (pos<TLA2) //Achou
							{ 
								gotoxy(40,15);
								printf ("Esta Disciplina ja esta Cadastrada!");
								getch();
							}
							else
							{
								TabDi[TLA2].CodDisc = cod;
								gotoxy(40,10);
								printf("Digite o Nome da disciplina: ");
								fflush(stdin);
								gets(AuxNome);
								strcpy(TabDi[TLA2].Discip,AuxNome);
								TLA2++;
							}
							if (TLA2<TF)
							{
								LimpaExibe();
								gotoxy(50,7);
								printf("===== Cadastro Manual de disciplina =====");
								gotoxy(40,9);
								printf("Digite o codigo da disciplina [0 - Sair]: ");
								scanf("%d", &cod);
							}
							else
							{
								gotoxy(40,15);
								printf ("Vetor esta cheio!");
							}
						}
					}
				break;
				
			case 'C': 
					LimpaExibe();
					float nota;
					gotoxy(50,7);
					printf("===== Cadastrar Notas =====");
					
					if (TLA3 == TF)
					{	
						gotoxy(40,15);
						printf("Vetor cheio!");
						getch();
					}
					else
					{
						gotoxy(40,9);
						printf("Digite o RA do aluno para lancar a nota. [ENTER] - Sair: ");
						gotoxy(40,10);
						fflush(stdin);
						gets(AuxRA);
						
						cod =1;
						while (TLA3 < TF && strcmp(AuxRA,"\0")!=0 && cod != 0) // É um RA válido?
							{
								pos = BuscaRA(TabAl,TLA,AuxRA);
								if(pos == TLA) // RA não xiste
								{
									gotoxy(40,15);
									printf("Aluno nao cadastrado. [ENTER - Sair]");
									getch();
								}
								else
								{
									gotoxy(40,11);
									printf("Digite o codigo da materia [0 - Sair]: ");
									scanf("%d", &cod);
							
									pos1 = BuscaCod(TabDi, TLA2, cod);
									if(pos1 == TLA2) // RA não xiste
									{
										gotoxy(40,15);
										printf("Disciplina nao cadastrada. [ENTER - Sair]");
										getch();
									}
									else
									{
										gotoxy(40,12);
										printf("Digite a nota do aluno: ");
										scanf ("%f", &nota);
										
										pos2 = BuscaNota(TabNo, AuxRA, cod, TLA3, nota);
										if(pos2 < TLA3)
										{
											gotoxy(40,15);
											printf("Nota ja cadastrada. [ENTER - Sair]");
											getch();
											
											LimpaExibe();
											gotoxy(50,7);
											printf("===== Cadastrar Notas =====");
											gotoxy(40,9);
											printf("Insira o RA do aluno que deseja colocar a nota. [Enter] - Sair:");
											gotoxy(40,10);
											fflush(stdin);
											gets(AuxRA);
										}
										else
										{
											TabNo[TLA3].Nota = nota;
											TabNo[TLA3].CodDisc = TabDi[pos1].CodDisc;
											strcpy(TabNo[TLA3].RA,TabAl[pos].RA);
											gotoxy(40,15);
											printf("Nota cadastrada![ENTER - Voltar]");
												
											getch();
											LimpaExibe();
											gotoxy(50,7);
											printf("===== Cadastrar Notas =====");
											gotoxy(40,9);
											printf("Insira o RA do aluno que deseja colocar a nota. [Enter] - Sair:");
											gotoxy(40,10);
											fflush(stdin);
											gets(AuxRA);
											TLA3++;
										}
							
									}//else
								}		
							}
					}
					break;
		}//switch	
	} while (opcao != 27); //do while
}

// Montagem principal
void PainelPrincipal(void)
{
	system("cls");
	Moldura(1, 1, 120, 35, 2, 4, 10);
	Moldura(2, 2, 119, 4, 2, 4, 10);
	Moldura(2, 5, 30, 34, 2, 4, 10);
	Moldura(31, 5, 119, 34, 2, 4, 10);
	gotoxy(28, 3);
	Cor();
	printf("<<<===== NOTAS =====>>>");
}

// Montagem secundária
void PainelPrincipal2(void)
{
	system("cls");
	Moldura(1, 1, 120, 35, 2, 4, 0);
	Moldura(2, 2, 119, 4, 2, 4, 0);
	Moldura(2, 5, 30, 34, 2, 4, 0);
	Moldura(31, 5, 119, 34, 2, 4, 0);
	gotoxy(50, 3);
	Cor();
	printf("<<<===== NOTAS ======>>>");
}

//Menu relatorio de teste
 char ExecutarMenuRelatorio()
{
    LimpaMenu();
    gotoxy(5, 7);
    printf("== B I B L I O T E C A ==");
    gotoxy(5, 10);
    printf("[A] Cadastrar");
    gotoxy(5, 12);
    printf("[B] Excluir ");
	gotoxy(5, 14);
    printf("[C] Alterar");
    gotoxy(5, 15);
    printf("disciplina");
    gotoxy(5, 16);
    printf("[D] Media geral ");
    gotoxy(5, 17);
    printf("abaixo de 6,0");
    gotoxy(5, 18);
    printf("[E]Situacao");
    gotoxy(5, 19);
    printf("[ESC] Sair");
    gotoxy(5, 20);
    return toupper(getch());
}



void AlteraAlunDisc(TpNotas AlDi[TF],int TLAd)
{	
	int pos, cod;
	char RA[13];
	LimpaExibe();
	gotoxy(50,9);
	printf("Insira o RA do aluno que deseja alterar a nota:");
	fflush(stdin);
	gets(RA);
	
	gotoxy(50,10);
	printf("Digite o codigo da materia");
	scanf("%d", &cod);
	
	pos = BuscaAlunDisc(AlDi,RA,cod,TLAd);
	
	while(pos == -1)
	{
		gotoxy(50,11);
		printf("Dados nao encontrados");
		
		LimpaExibe();
		gotoxy(50,9);
		printf("Insira o RA do aluno que deseja alterar a nota:");
		fflush(stdin);
		gets(RA);
		
		gotoxy(50,10);
		printf("Digite o codigo da disciplina:");
		scanf("%d",&cod);
		
		pos = BuscaAlunDisc(AlDi,RA,cod,TLAd);
	}
	
	
	gotoxy(50,12);
	printf("RA: %s	Disciplina: %d	Nota: %.1f\n",AlDi[pos].RA, AlDi[pos].CodDisc, AlDi[pos].Nota);
	
	gotoxy(50,15);
	printf("Digite a nova nota");
	scanf("%f",&AlDi[pos].Nota);
	gotoxy(50,16);
	printf("Nota atualizada");
	
	getch();
}

 void Alterar(TpAlunos TabAl[TF], TpDisc TabDi[TF], TpNotas TabNo[TF], int&Tlg, int &Tlag2,int &Tlag3)
 {
 	char Auxchar[40],AuxNovNome[40], opcao;
	int pos;
	gotoxy(5,7);
	printf("Alterar: ");
	do{
	
	 	opcao = Menu2();
		switch (opcao)
		{
			case 'A': // Alterar o nome do aluno
					LimpaExibe();
					gotoxy(50,7);
					printf("Alterar Nome do aluno");
					
				if (Tlg == 0)
				{	
					gotoxy(50,9);
					printf("Sem alunos cadastrados para alterar");
					getch();
				}
				else
				{
					gotoxy(50,9);
					printf("Digite o nome para alterar:");
					fflush(stdin);
					gets(Auxchar);
					int pos = 0;
					pos = BuscaNome(TabAl, Tlg, Auxchar);
					if (pos < Tlg)
					{	gotoxy(50,10);
						printf("RA:%s\t Nome:%s", TabAl[pos].RA, TabAl[pos].Nome);
						gotoxy(50,11);
						printf("Novo nome: ");
						gets(AuxNovNome);
						gotoxy(50,12);
						printf("Nome atualizado:");
						fflush(stdin);
						strcpy(TabAl[pos].Nome,AuxNovNome);
       				}
				}
				break;
				
			case 'B': 	
			LimpaExibe();
			gotoxy(50,7);
			printf("Alterar disciplina ");
				if(Tlag2 == 0)
				{
					gotoxy(50,9);
					printf("Sem disciplina cadastradas para alterar");
					getch();
				}
				else
				{
					gotoxy(50,10);
					printf("Digite a disciplina para alterar:");
					fflush(stdin);
					gets(Auxchar);
					
					int pos = 0;
					while (pos < Tlag2 && strcmp(Auxchar, TabDi[pos].Discip) != 0)
						pos++;
						
					if (pos < Tlag2)
					{
						gotoxy(50,11);
						printf("Codigo:%d Diciplina:%s Novo nome:", TabDi[pos].CodDisc, TabDi[pos].Discip);
						gets(AuxNovNome);
						gotoxy(50,12);
						printf("Nome atualizado:\n");
						fflush(stdin);
						strcpy(TabDi[pos].Discip,AuxNovNome);
       				}
				}
				break;
				
				case 'C':
						LimpaExibe();
						gotoxy(50,7);
						printf("Alterar Nota ");
						if (Tlg == 0)
						{	
							gotoxy(50,9);
							printf("Sem notas cadastrados para alterar");
							getch();
						}
						else
							AlteraAlunDisc(TabNo , Tlag3);
							
						break;		
		}				
	}while(opcao != 27);
	
}
		
// Gerar relatorios
void GerarRelatorio (TpAlunos TabAl[TF], TpDisc TabDi[TF], TpNotas TabNo[TF], int &Tlag, int &Tlag2, int &Tlag3)
{
    char opcao;
    char termo[40], situ[10];
    int i, j, aux, pos, x, countReprovado, qtdDisciplinas;
    float somaNotas, mediaGeral;

    do
    {
        opcao = ExecutarMenuRelatorio();  // Correção da chamada do menu
        switch (opcao)
        {
            case 'A':
					LimpaExibe();
					gotoxy(40,7);
	                // Listar alunos reprovados em 2 ou mais disciplinas
	                printf("Relatório: Alunos reprovados em 2 ou mais disciplinas");
	                countReprovado = 0;
                    
                    for(i = 0; i < Tlag3; i++)
                    	if(TabNo[i].Nota < 6.0)
                    	{
                    		gotoxy(40,9);
                    		printf("Aluno: %s\t", TabNo[i].RA);
							gotoxy(40,10);
							printf("Disc.: %d\t Nota: %.1f", TabNo[i].CodDisc, TabNo[i].Nota);
						}
                    
					break;

            case 'B':
					LimpaExibe();
			 		gotoxy(40,7);
            		countReprovado = 0;
                	// Buscar alunos com determinada letra no nome
	                printf("Digite a letra inicial do nome do aluno: ");
	                fflush(stdin);
	                gets(termo);  // Entrada da letra ou termo

					gotoxy(40,9);
	                printf("Alunos encontrados:");
	                for (i = 0; i < Tlag; i++)
	                    if (strstr(TabAl[i].Nome, termo))
						{
							gotoxy(40,10);
	                        printf("Aluno: %s", TabAl[i].Nome);
	                    }
            		break;

            case 'C':
                // Buscar disciplinas com determinada palavra no nome
                LimpaExibe();
				gotoxy(40,7);
                printf("Digite a palavra para buscar nas disciplinas: ");
                fflush(stdin);
                gets(termo);  // Entrada da palavra para busca

				gotoxy(40,9);
                printf("Disciplinas encontradas:");
                
                for (i = 0; i < Tlag2; i++)
                    if (strstr(strlwr(TabDi[i].Discip), strlwr(termo)))
					{
						gotoxy(40,10);
                        printf("Disciplina: %s", TabDi[i].Discip);
                    }
                    
				break;

            case 'D':
            		float media;
	            	LimpaExibe();
					gotoxy(40,7);
	                media = MediaGeral(TabNo,TabDi,Tlag3,Tlag2);
	                
	                gotoxy(40,8);
	                printf("Media Geral dos Alunos: %.1f", media);
	                break;
	                
	        case 'E':
	                LimpaExibe();
					gotoxy(40,7);
	                // Aprovado ou reprovado
	                printf("Situacao dos alunos");
                	x=9;
	
					for(i=0;i<Tlag;i++) 
					{
						pos=BuscaNota2(TabNo,TabAl[i].RA,Tlag3);
						if(pos<Tlag3)
						{
							gotoxy(40,x++);
    						printf("RA: %s Nome: %s",TabNo[i].RA,TabAl[i].Nome);
    						for(j=0;j<Tlag3;j++) 
							{
  	 					     	if(strcmp(TabNo[j].RA,TabAl[i].RA)==0) 
								{
					            
   					             	if(TabNo[j].Nota>=6) 			
           				 	        	strcpy(situ,"Aprovado");
									else 
                    					strcpy(situ,"Reprovado");
                    					
									pos = BuscaCod(TabDi,Tlag3,TabNo[j].CodDisc);
									gotoxy(40,x++);
                					printf("Disciplina: %d - %s Nota: %.1f  Situacao: %s",TabNo[j].CodDisc,TabDi[pos].Discip,TabNo[j].Nota,situ);
        						}
    						}
	    				}
	    			}
        			x++;
        			break;

            case 27: // Tecla ESC
	            	LimpaExibe();
					gotoxy(40,9);
	                printf("Saindo do menu de relatórios...");
	                break;

            default:
	            	LimpaExibe();
					gotoxy(40,9);
	                printf("Opção inválida! Tente novamente.[ESC] para sair");
        }
    } while (opcao != 27);  // Enquanto  tecla ESC não for pressionada
}


// Execução do menu
	void ExecutarMenu(void)
	{
		TpAlunos TabAl[TF];
		TpDisc TabDi[TF];
		TpNotas TabNo[TF];
		
		int Tlag = 0, Tlag2 = 0, Tlag3 = 0, cont = 0; 
		char opcao;
		do
		{
			PainelPrincipal2();
			opcao = Menu();
			switch (opcao)
			{
				case 'A': CadMan(TabAl, TabDi, TabNo, Tlag, Tlag2, Tlag3); break;
				case 'B': Exibe(TabAl, TabDi, TabNo, Tlag, Tlag2, Tlag3); break;
				case 'C': Consultar(TabAl, TabDi, TabNo, Tlag, Tlag2, Tlag3); break;
				case 'D': Excluir(TabAl, TabDi, TabNo, Tlag, Tlag2, Tlag3); break;
				case 'E': CadAuto(TabAl, TabDi, TabNo, Tlag, Tlag2, Tlag3, cont); break;
				case 'F': Alterar(TabAl, TabDi, TabNo, Tlag, Tlag2, Tlag3); break;
				case 'G': GerarRelatorio(TabAl, TabDi, TabNo, Tlag, Tlag2, Tlag3); break;
				case 'H': OrdenaAluno(TabAl, Tlag); break;
				case 27: break;
				default:gotoxy(5,21);
						printf("Invalido!");
						break;
			}
		} while (opcao != 27);
	}

// Função principal
int main()
{
	PainelPrincipal();
	ExecutarMenu();
	getch();
	printf("\n\n\n\n\n\n");
	return 0;
}
