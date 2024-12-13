#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <ctype.h>

struct TpAluno
{
	char RA[13], Nome[30];
};

struct TpDisciplina
{
	int Cod;
	char Nomedisc[30];
};

struct TpNota
{
	char RA[13];
	int Cod;
	float Nota;
};

char Menu1(void)
{
	system("cls");
	
	printf("\nM E N U\n");
	printf("\n[A] MENU CRUD\n");
	printf("\n[B] MENU RELATORIOS\n");
	printf("\n[ESC] FINALIZAR PROGRAMA\n");
	printf("\nOpcao Desejada: ");
	
	return toupper(getche());
}

char Menu2(void)
{
    system("cls");
    
	printf("\nM E N U   C R U D\n");
	printf("\n[A] [Dados para Teste]\n");
	printf("\n[B] CADASTRAR\n");
    printf("\n[C] CONSULTAR\n");
    printf("\n[D] ALTERAR\n");
    printf("\n[E] EXCLUIR\n");
    printf("\n[F] EXIBIR\n");
	printf("\n[TAB] VOLTAR\n");
	printf("\nOpcao Desejada: ");
	
	return toupper(getche());
}

char MenuCadastro(void)
{
    system("cls");
    
	printf("\nOPCOES DE CADASTRO\n");
	printf("\n[A] CADASTRAR ALUNO\n");
	printf("\n[B] CADASTRAR DISCIPLINA\n");
	printf("\n[C] CADASTRAR NOTA\n");
    printf("\n[ENTER] VOLTAR\n");
	printf("Opcao Desejada: ");
	
	return toupper(getche());
}

char MenuConsulta(void)
{
    system("cls");
	
	printf("\nOPCOES DE CONSULTA\n");
	printf("\n[A] CONSULTAR ALUNO\n");
	printf("\n[B] CONSULTAR DISCIPLINA\n");
	printf("\n[C] CONSULTAR NOTA\n");
    printf("\n[ENTER] VOLTAR\n");
	printf("Opcao Desejada: ");
	
	return toupper(getche());
}

char MenuAlterar (void)
{
    system("cls");
    
	printf("\nOPCOES PARA ALTERAR\n");
	printf("\n[A] ALTERAR ALUNO\n");
	printf("\n[B] ALTERAR DISCIPLINA\n");
	printf("\n[C] ALTERAR NOTA\n");
    printf("\n[ENTER] VOLTAR\n");
	printf("Opcao Desejada: ");
	
	return toupper(getche());
}

char MenuExcluir (void)
{
    system("cls");
    
	printf("\nOPCOES DE EXCLUSAO\n");
	printf("\n[A] EXCLUIR ALUNO\n");
	printf("\n[B] EXCLUIR DISCIPLINA\n");
	printf("\n[C] EXCLUIR NOTA\n");
    printf("\n[ENTER] VOLTAR\n");
	printf("Opcao Desejada: ");
	
	return toupper(getche());
}

char MenuExibir (void)
{
    system("cls");
	
	printf("\nOPCOES DE EXIBICAO\n");
	printf("\n[A] EXIBIR ALUNO\n");
	printf("\n[B] EXIBIR DISCIPLINA\n");
	printf("\n[C] EXIBIR NOTA\n");
    printf("\n[ENTER] VOLTAR\n");
	printf("Opcao Desejada: ");
	
	return toupper(getche());
}

char Menu3(void)
{
	system("cls");
	
	printf("\nM E N U    R E L A T O R I O S\n");
	printf("\n[A] REPROVADOS EM 2 OU MAIS DISCIPLINAS\n");
	printf("\n[B] CONSULTAR ALUNO POR LETRA INICIAL\n");
	printf("\n[C] CONSULTAR DISCIPLINA POR TERMO/PALAVRA\n");
	printf("\n[D] DISCIPLINAS MEDIA GERAL ABAIXO DE 6,00\n");
	printf("\n[E] RELATORIO GERAL\n");
	printf("\n[TAB] VOLTAR\n");
	printf("\nOpcao Desejada: ");
	
	return toupper(getche());
}

int BuscaAluno(FILE *PtrAluno, char ChaveRA[13])
{
	TpAluno R;
	rewind(PtrAluno); //POSICIONA O PONTEIRO NO INICIO.
	fread(&R,sizeof(TpAluno),1,PtrAluno);
	while(!feof(PtrAluno) && strcmp(ChaveRA, R.RA) !=0)
		fread(&R,sizeof(TpAluno),1,PtrAluno);
	if(strcmp(ChaveRA, R.RA) == 0)
		return ftell(PtrAluno)-sizeof(TpAluno); //Posição encontrada é a posição do arquivo menos os bits de uma estrutura.
	else
		return -1;
}

int BuscaDisciplina(FILE *PtrDisc, int Cod)
{
	TpDisciplina R;
	rewind(PtrDisc); //POSICIONA O PONTEIRO NO INICIO.
	fread(&R,sizeof(TpDisciplina),1,PtrDisc);
	while(!feof(PtrDisc) && Cod != R.Cod)
		fread(&R,sizeof(TpDisciplina),1,PtrDisc);
	if(Cod == R.Cod)
		return ftell(PtrDisc)-sizeof(TpDisciplina); //Posição encontrada é a posição do arquivo menos os bits de uma estrutura.
	else
		return -1;
}

void Teste()
{
	TpAluno Reg1;
	TpDisciplina Reg2;
	TpNota Reg3;
	
	FILE *PtrAluno = fopen("Alunos.dat","wb");
	FILE *PtrDisc = fopen("Disciplinas.dat","wb");
	FILE *PtrNota = fopen("Notas.dat","wb");
	
	strcpy(Reg1.RA,"26.09.1045-1");
	strcpy(Reg1.Nome,"Bertalia");
		    
	fwrite(&Reg1,sizeof(TpAluno), 1, PtrAluno);
		
	strcpy(Reg1.RA,"10.09.1055-3");
	strcpy(Reg1.Nome,"Creusa");
		
	fwrite(&Reg1,sizeof(TpAluno), 1, PtrAluno);
			
	strcpy(Reg1.RA,"26.09.2012-1");
	strcpy(Reg1.Nome,"Florisbela");
		
	fwrite(&Reg1,sizeof(TpAluno), 1, PtrAluno);
			
	strcpy(Reg1.RA,"10.09.3052-6");
	strcpy(Reg1.Nome,"Jurema");
		    
	fwrite(&Reg1,sizeof(TpAluno), 1, PtrAluno);
		
	strcpy(Reg1.RA,"26.09.3444-8");
	strcpy(Reg1.Nome,"Petronio");
			
	fwrite(&Reg1,sizeof(TpAluno), 1, PtrAluno);
		
	printf("\nAlunos cadastrados com sucesso [TESTE]!!\n");
	getch();		
	fclose(PtrAluno);
	


	Reg2.Cod = 100;
	strcpy(Reg2.Nomedisc,"ATP I");
		    
	fwrite(&Reg2,sizeof(TpDisciplina), 1, PtrDisc);
		
	Reg2.Cod = 105;
	strcpy(Reg2.Nomedisc,"ATP II");
		    
	fwrite(&Reg2,sizeof(TpDisciplina), 1, PtrDisc);
		
	Reg2.Cod = 120;
	strcpy(Reg2.Nomedisc,"Estrutura de Dados I");
	    
	fwrite(&Reg2,sizeof(TpDisciplina), 1, PtrDisc);
		
	Reg2.Cod = 150;
	strcpy(Reg2.Nomedisc,"Pesquisa e Ordenacao");
		    
	fwrite(&Reg2,sizeof(TpDisciplina), 1, PtrDisc);
		
	Reg2.Cod = 210;
	strcpy(Reg2.Nomedisc,"Ferramentas I");
		    
	fwrite(&Reg2,sizeof(TpDisciplina), 1, PtrDisc);
		
	Reg2.Cod = 230;
	strcpy(Reg2.Nomedisc,"Estatistica");
		    
	fwrite(&Reg2,sizeof(TpDisciplina), 1, PtrDisc);
		
	Reg2.Cod = 240;
	strcpy(Reg2.Nomedisc,"Matematica Discreta");
			
	fwrite(&Reg2,sizeof(TpDisciplina), 1, PtrDisc);
		
	printf("\nDisciplinas cadastradas com sucesso [TESTE]!!\n");
	getch();				
	fclose(PtrDisc);


		
	strcpy(Reg3.RA, "26.09.1045-1");
	Reg3.Cod = 120;
	Reg3.Nota = 8.0;
	
	fwrite(&Reg3,sizeof(TpNota), 1, PtrNota);
		
	strcpy(Reg3.RA, "26.09.1045-1");
	Reg3.Cod = 210;
	Reg3.Nota = 4.5;
	    
	fwrite(&Reg3,sizeof(TpNota), 1, PtrNota);
	
	strcpy(Reg3.RA, "26.09.1045-1");
	Reg3.Cod = 230;
	Reg3.Nota = 6.5;
	
	fwrite(&Reg3,sizeof(TpNota), 1, PtrNota);
	
	strcpy(Reg3.RA, "10.09.1055-3");
	Reg3.Cod = 150;
	Reg3.Nota = 5.0;
	    
	fwrite(&Reg3,sizeof(TpNota), 1, PtrNota);
	
	strcpy(Reg3.RA, "10.09.1055-3");
	Reg3.Cod = 240;
	Reg3.Nota = 4.5;
	    
	fwrite(&Reg3,sizeof(TpNota), 1, PtrNota);
	
	strcpy(Reg3.RA, "26.09.2012-1");
	Reg3.Cod = 100;
	Reg3.Nota = 7.0;
	    
	fwrite(&Reg3,sizeof(TpNota), 1, PtrNota);
	
	strcpy(Reg3.RA, "26.09.2012-1");
	Reg3.Cod = 210;
	Reg3.Nota = 6.0;
	    
	fwrite(&Reg3,sizeof(TpNota), 1, PtrNota);
	
	strcpy(Reg3.RA, "26.09.2012-1");
	Reg3.Cod = 290;
	Reg3.Nota = 9.0;
	    
	fwrite(&Reg3,sizeof(TpNota), 1, PtrNota);
	    
	printf("\nNotas cadastradas com sucesso [TESTE]!!\n");
	getch();
	fclose(PtrNota);
}

void GravarAluno()
{
	TpAluno Reg;
	
	FILE *PtrAluno = fopen("Alunos.dat","ab+"); //COM "wb" PERDE O ARQUIVO A CADA VEZ QUE ABRE. PARA NAO PERDER, SÓ TROCAR PARA "ab".
	clrscr();
	printf("\n## Cadastro de Alunos ##\n");
	printf("\nR.A.: "); 
	fflush(stdin);
	gets(Reg.RA);
	while(strcmp(Reg.RA, "\0") != 0)
	{
		if(BuscaAluno(PtrAluno,Reg.RA) == -1)
		{
			printf("Nome: ");
			fflush(stdin);
			gets(Reg.Nome);
				
			fwrite(&Reg, sizeof(TpAluno), 1, PtrAluno);
			printf("\nAluno Cadastrado com sucesso!\n");
		}
		else
			printf("\nAluno ja cadastrado!\n");
			
		getch();
		printf("\nR.A.: ");
		fflush(stdin);
		gets(Reg.RA);
	}
	fclose(PtrAluno);
}

void GravarDisciplina()
{
	TpDisciplina Reg;
	
	FILE *PtrDisc = fopen("Disciplinas.dat","ab+"); //COM "wb" PERDE O ARQUIVO A CADA VEZ QUE ABRE. PARA NAO PERDER, SÓ TROCAR PARA "ab".
	clrscr();
	printf("\n## Cadastro de Disciplinas ##\n");
	printf("\nCOD: "); 
	scanf("%d", &Reg.Cod);
	while(Reg.Cod != 0)
	{
		if(BuscaDisciplina(PtrDisc,Reg.Cod) == -1)
		{
			printf("Nome Disciplina: ");
			fflush(stdin);
			gets(Reg.Nomedisc);
				
			fwrite(&Reg, sizeof(TpDisciplina), 1, PtrDisc);
			printf("\nDisciplina Cadastrada com sucesso!\n");
		}
		else
			printf("\nDisciplina ja cadastrada!\n");
			
		getch();
		printf("\nCOD: ");
		scanf("%d", &Reg.Cod);
	}
	fclose(PtrDisc);
}

void GravarNotas()
{
	int DiscJaCadastrada;
	TpNota Reg, NotaExistente;
	
	FILE *PtrNota = fopen("Notas.dat","ab+"); //COM "wb" PERDE O ARQUIVO A CADA VEZ QUE ABRE. PARA NAO PERDER, SÓ TROCAR PARA "ab".
	FILE *PtrAluno = fopen("Alunos.dat","rb+");
	FILE *PtrDisc = fopen("Disciplinas.dat","rb+");
	clrscr();
	printf("\n## Cadastro de Notas ##\n");
	printf("\nR.A.: "); 
	fflush(stdin);
	gets(Reg.RA);
	while(strcmp(Reg.RA, "\0") != 0)
	{
		if(BuscaAluno(PtrAluno,Reg.RA) != -1)
		{
			printf("COD: ");
			scanf("%d", &Reg.Cod);
			
			while(Reg.Cod != 0)
			{
				if(BuscaDisciplina(PtrDisc,Reg.Cod) != -1)
				{
					rewind(PtrNota);
					DiscJaCadastrada = 0;
					while(fread(&NotaExistente, sizeof(TpNota),1,PtrNota) == 1)
					{
						if(strcmp(NotaExistente.RA,Reg.RA) == 0 && NotaExistente.Cod == Reg.Cod)
							DiscJaCadastrada = 1;
					}
					if(DiscJaCadastrada == 1)
					{
						printf("\nDisciplina ja cadastrada para este aluno!\n");
						getch();
					}
					else
					{
						printf("\nNota do aluno: ");
						scanf("%f", &Reg.Nota);
						fwrite(&Reg, sizeof(TpNota), 1, PtrNota);
						printf("\nNota Cadastrada com sucesso!\n");
						getch();
					}
				}
				else
					printf("\nDisciplina nao encontrada!\n");
					
				printf("\nCOD: ");
				scanf("%d", &Reg.Cod);
			}
		}
		else
			printf("\nAluno ja cadastrado!\n");
			
		getch();
		printf("\nR.A.: ");
		fflush(stdin);
		gets(Reg.RA);
	}
	fclose(PtrNota);
	fclose(PtrDisc);
	fclose(PtrAluno);
}

void ConsultarAluno(void)
{
	int pos;
	
	FILE *PtrAluno = fopen("Alunos.dat","rb");
	TpAluno RAluno;
	clrscr();
	printf("\n---CONSULTAR PELO RA---\n");
	
	if(PtrAluno == NULL)
		printf("\nErro de abertura!\n");
	else
	{
		printf("RA a consultar:");
		fflush(stdin);
		gets(RAluno.RA);
		while(strcmp(RAluno.RA,"\0")!=0)
		{
			pos = BuscaAluno(PtrAluno,RAluno.RA);//Passa como parametro- onde você procura e o que você procura 
			
			if (pos== -1)
				printf("\nR.A. nao encontrado!\n");
			else
			{
				fseek(PtrAluno,pos,0);
				fread(&RAluno, sizeof(TpAluno),1,PtrAluno);
				printf("\n---Dados Encontrados---\n");
				printf("\nR.A: %s", RAluno.RA);
				printf("\nNome: %s", RAluno.Nome);
			}
			getch();
			printf("\nRA a consultar:");
			fflush(stdin);
			gets(RAluno.RA);
		}
		fclose(PtrAluno);
	}
}

void ConsultarDisciplina(void)
{
	int pos;
	
	FILE *PtrDisc = fopen("Disciplinas.dat","rb");
	TpDisciplina RDisciplina;
	clrscr();
	printf("\n---CONSULTAR PELO CODIGO---\n");
	
	if(PtrDisc == NULL)
		printf("\nErro de abertura!\n");
	else
	{
		printf("Cod a consultar (0-SAIR):");
		scanf("%d", &RDisciplina.Cod);
		while(RDisciplina.Cod !=0)
		{
			pos = BuscaDisciplina(PtrDisc,RDisciplina.Cod);//Passa como parametro- onde você procura e o que você procura 
			
			if (pos == -1)
				printf("\nDisciplina nao encontrada!\n");
			else
			{
				fseek(PtrDisc,pos,0);
				fread(&RDisciplina, sizeof(TpDisciplina),1,PtrDisc);
				printf("\n---Dados Encontrados---\n");
				printf("\nCod: %d", RDisciplina.Cod);
				printf("\nNome: %s", RDisciplina.Nomedisc);
			}
			getch();
			printf("\nCod a consultar (0-SAIR):");
			scanf("%d", &RDisciplina.Cod);
		}
		fclose(PtrDisc);
	}
}

void ConsultarNota(void)
{
	FILE *PtrNota = fopen("Notas.dat", "rb");
	TpNota RNota;
	char RAConsulta[13];
	int encontrou;
	
	clrscr();
	printf("\n---CONSULTAR PELO RA---\n");

	if (PtrNota == NULL)
		printf("\nErro de abertura!\n");
	else
	{
		printf("RA a consultar: ");
		fflush(stdin);
		gets(RAConsulta);

		while (strcmp(RAConsulta, "\0") != 0)
		{
			encontrou = 0;
			rewind(PtrNota);
			printf("\n---Dados Encontrados---\n");

			while (fread(&RNota, sizeof(TpNota), 1, PtrNota) == 1)
			{
				if (strcmp(RNota.RA, RAConsulta) == 0)
				{
					printf("\nR.A: %s", RNota.RA);
					printf("\nCOD: %d", RNota.Cod);
					printf("\nNota: %.2f\n", RNota.Nota);
					encontrou = 1;
				}
			}

			if (!encontrou)
				printf("\nNenhuma nota encontrada para o R.A. informado.\n");

			getch();
			printf("\nRA a consultar: ");
			fflush(stdin);
			gets(RAConsulta);
		}
		fclose(PtrNota);
	}
}

void ExibirAluno(void)
{
	TpAluno R;
	FILE *PtrAluno = fopen("Alunos.dat","rb"); //ABRINDO O ARQUIVO COM "RB" DO ÍNICIO
	clrscr();
	if(PtrAluno == NULL) //SE ISSO FOR VERDADE, SIGNIFICA QUE O ARQUIVO FOI CORROMPIDO, NAO EXISTE, OU NAO SE ENCONTRA NO DIRETÓRIO.
		printf("\nNao ha alunos cadastrados!\n");
	else
	{
		fread(&R,sizeof(TpAluno),1,PtrAluno);
		while(!feof(PtrAluno)) //feof = fendoffile
		{
			printf("\nRA: %s", R.RA);
			printf("\nNome: %s", R.Nome);
			
			fread(&R,sizeof(TpAluno),1,PtrAluno);
		}
		fclose(PtrAluno);	
	}
	getch();
}

void ExibirDisciplina(void)
{
	TpDisciplina R;
	FILE *PtrDisc = fopen("Disciplinas.dat","rb"); //ABRINDO O ARQUIVO COM "RB" DO ÍNICIO
	clrscr();
	if(PtrDisc == NULL) //SE ISSO FOR VERDADE, SIGNIFICA QUE O ARQUIVO FOI CORROMPIDO, NAO EXISTE, OU NAO SE ENCONTRA NO DIRETÓRIO.
		printf("\nNao ha disciplinas cadastradas!\n");
	else
	{
		fread(&R,sizeof(TpDisciplina),1,PtrDisc);
		while(!feof(PtrDisc)) //feof = fendoffile
		{
			printf("\nCOD: %d", R.Cod);
			printf("\nNome: %s", R.Nomedisc);
			
			fread(&R,sizeof(TpDisciplina),1,PtrDisc);
		}
		fclose(PtrDisc);	
	}
	getch();
}

void ExibirNota(void)
{
	TpNota R;
	FILE *PtrNota = fopen("Notas.dat","rb"); //ABRINDO O ARQUIVO COM "RB" DO ÍNICIO
	clrscr();
	if(PtrNota == NULL) //SE ISSO FOR VERDADE, SIGNIFICA QUE O ARQUIVO FOI CORROMPIDO, NAO EXISTE, OU NAO SE ENCONTRA NO DIRETÓRIO.
		printf("\nNao ha notas cadastradas!\n");
	else
	{
		fread(&R,sizeof(TpNota),1,PtrNota);
		while(!feof(PtrNota)) //feof = fendoffile
		{
			printf("\nRA: %s", R.RA);
			printf("\nCOD: %d", R.Cod);
			printf("\nNota: %.2f", R.Nota);
			
			fread(&R,sizeof(TpNota),1,PtrNota);
		}
		fclose(PtrNota);	
	}
	getch();
}

void Executar (void)
{
    
	char opcao;
	
	do
	{	
		opcao = Menu1();
		switch(opcao)
		{
			case 'A':
				do
				{
					opcao = Menu2();
					switch(opcao)
					{
						case 'A':
							
							Teste();
							break;
						
						case 'B':
							
							do
							{
								opcao = MenuCadastro();
								switch(opcao)
								{
									case 'A':
										
										GravarAluno();
										break;
										
									case 'B':
										
										GravarDisciplina();
										break;
										
									case 'C':
										
										GravarNotas();
										break;
								}
								
							}while(opcao != 13);
							
							break;
		
			            case 'C':
			            	
			            	do
							{
								opcao = MenuConsulta();
								switch(opcao)
								{
									case 'A':
										
										ConsultarAluno();
										break;
										
									case 'B':
										
										ConsultarDisciplina();
										break;
										
									case 'C':
										
										ConsultarNota();
										break;
								}
								
							}while(opcao != 13);
							
							break;
							
			            case 'D':
			            	
			            	do
							{
								opcao = MenuAlterar();
								switch(opcao)
								{
									case 'A':
										
										
										break;
										
									case 'B':
										
										
										break;
										
									case 'C':
										
										
										break;
								}
								
							}while(opcao != 13);
							
							break;

			            case 'E':
			            	
			            	do
							{
								opcao = MenuExcluir();
								switch(opcao)
								{
									case 'A':
										
									
										break;
										
									case 'B':
										
										
										break;
										
									case 'C':
										
										
										break;
								}
								
							}while(opcao != 13);
							
							break;
							
			            case 'F':
			            	
			            	do
							{
								opcao = MenuExibir();
								switch(opcao)
								{
									case 'A':
										
										ExibirAluno();
										break;
										
									case 'B':
										
										ExibirDisciplina();
										break;
										
									case 'C':
										
										ExibirNota();
										break;
								}
								
							}while(opcao != 13);

			                break;
					}
				}while(opcao != 9);
				
				break;
				
			case 'B':
				
				do
				{	
					opcao = Menu3();
					switch(opcao)
					{
						case 'A':
							
							
							break;
							
						case 'B':
							
						
							break;
							
						case 'C':
							
							
							break;
						
						case 'D':
							
							
							break;
						
						case 'E':
							
							
							break;
					}
				}while(opcao != 9);
				
				break;
		}
	}while(opcao != 27);
}

int main (void)
{
	Executar();
	return 0;
}














