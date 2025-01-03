#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct TpAluno
{
	char RA[14], Nome[30];
	int AnoNasc, Status;
};

int BuscaRAAluno(FILE *PtrAluno, char ChaveRA[14])
{
	TpAluno R;
	rewind(PtrAluno); //Posiciona o PtrAluno no INÍCIO
	//fseek(PtrAluno,0,0);
	fread(&R,sizeof(TpAluno),1,PtrAluno);
	//while (!feof(PtrAluno) && !(strcmp(ChaveRA,R.RA)==0 && R.Status))
	while (!feof(PtrAluno) && (strcmp(ChaveRA,R.RA)!=0 || R.Status!=0))
		fread(&R,sizeof(TpAluno),1,PtrAluno);

	if (strcmp(ChaveRA,R.RA)==0 && R.Status)
		return ftell(PtrAluno)-sizeof(TpAluno);
	else
		return -1;
}

void GravarAluno(void)
{
	TpAluno Reg;
	clrscr();
	FILE *PtrAlu = fopen("AlunosLOG.dat","ab+");
	printf("\n## Cadastro de Alunos ##\n");
	printf("\nR.A.: "); fflush(stdin);
	gets(Reg.RA);
	while (strcmp(Reg.RA,"\0")!=0)
	{
		if (BuscaRAAluno(PtrAlu,Reg.RA) == -1)  //Não achou!
		{
			printf("Nome: "); fflush(stdin);
			gets(Reg.Nome);
			printf("Ano Nasc.: ");
			scanf("%d",&Reg.AnoNasc);
			Reg.Status = 1;
			
			fwrite(&Reg,sizeof(TpAluno),1,PtrAlu);
			printf("\nDados Cadastrados!\n");
		}
		else
			printf("\nR.A. ja Cadastrado!\n");
			
		getch();
		printf("\nR.A.: "); fflush(stdin);
		gets(Reg.RA);
	}
	fclose(PtrAlu);
}

void ExibirAluno(void)
{
	TpAluno R;
	FILE *PtrAlu = fopen("AlunosLOG.dat","rb");
	clrscr();
	if (PtrAlu == NULL)
		printf("\nErro de abertura!\n");
	else
		{
			fread(&R,sizeof(TpAluno),1,PtrAlu);
			while(!feof(PtrAlu))
			{
				if (R.Status)
				{
					printf("\nRA: %s",R.RA);
					printf("\nNome: %s",R.Nome);
					printf("\nAno Nasc.: %d\n",R.AnoNasc);
				}
				fread(&R,sizeof(TpAluno),1,PtrAlu);
			}
			fclose(PtrAlu);
		}
	getch();
}

void ConsultarAluno(void)
{
	FILE *PtrAlu = fopen("AlunosLOG.dat","rb");
	TpAluno RAluno;
	int pos;
	clrscr();
	printf("\n## Consultar pelo R.A. ##\n");
	if(PtrAlu == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("R.A. a consultar: ");
			fflush(stdin);
			gets(RAluno.RA);
			while (strcmp(RAluno.RA,"\0")!=0)
			{
				pos = BuscaRAAluno(PtrAlu,RAluno.RA);
				if (pos == -1)
					printf("\nR.A. nao encontrado!\n");
				else
					{
						fseek(PtrAlu,pos,0);
						fread(&RAluno,sizeof(TpAluno),1,PtrAlu);
						printf("\n*** Dados Encontrados ***\n");
						printf("\nR.A.: %s",RAluno.RA);
						printf("\nNome: %s",RAluno.Nome);
						printf("\nAno Nasc.: %d\n",RAluno.AnoNasc);
					}
				
				getch();
				printf("\nR.A. a consultar: ");
				fflush(stdin);
				gets(RAluno.RA);
			}			
			fclose(PtrAlu);
		}
}

void AlterarAluno(void)
{
	FILE *PtrAlu = fopen("AlunosLOG.dat","rb+");
	TpAluno RAluno;
	int pos;
	clrscr();
	printf("\n## Alterar pelo R.A. ##\n");
	if(PtrAlu == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("R.A. a alterar: ");
			fflush(stdin);
			gets(RAluno.RA);
			while (strcmp(RAluno.RA,"\0")!=0)
			{
				pos = BuscaRAAluno(PtrAlu,RAluno.RA);
				if (pos == -1)
					printf("\nR.A. nao encontrado!\n");
				else
					{
						fseek(PtrAlu,pos,0);
						fread(&RAluno,sizeof(TpAluno),1,PtrAlu);
						printf("\n*** Dados Encontrados ***\n");
						printf("\nR.A.: %s",RAluno.RA);
						printf("\nNome: %s",RAluno.Nome);
						printf("\nAno Nasc.: %d\n",RAluno.AnoNasc);
						printf("\nDeseja Alterar (S/N)? ");
						if (toupper(getche())=='S')
						{
							printf("\nNovo Nome: ");
							fflush(stdin);
							gets(RAluno.Nome);
							printf("\nNovo Ano Nasc.: ");
							scanf("%d",&RAluno.AnoNasc);
							
							fseek(PtrAlu,pos,0);
							fwrite(&RAluno,sizeof(TpAluno),1,PtrAlu);
							printf("\nDados Atualizados!\n");
						
							fseek(PtrAlu,pos,0);
							fread(&RAluno,sizeof(TpAluno),1,PtrAlu);
							printf("\n*** Dados Atualizados ***\n");
							printf("\nR.A.: %s",RAluno.RA);
							printf("\nNome: %s",RAluno.Nome);
							printf("\nAno Nasc.: %d\n",RAluno.AnoNasc);
						}
					}
				
				getch();
				printf("\nR.A. a Alterar: ");
				fflush(stdin);
				gets(RAluno.RA);
			}
			
			fclose(PtrAlu);
		}
}

void OrdenarAlunos(void)
{
	int a, b, QtdeReg;
	TpAluno RegA, RegB;
	FILE *PtrAlu = fopen("AlunosLOG.dat","rb+");
	clrscr();
	if (PtrAlu==NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			fseek(PtrAlu,0,2);
			QtdeReg = ftell(PtrAlu)/sizeof(TpAluno);
			
			for(a=0; a<QtdeReg-1; a++)
				for(b=a+1; b<QtdeReg; b++)
				{
					fseek(PtrAlu,a*sizeof(TpAluno),0);
					fread(&RegA,sizeof(TpAluno),1,PtrAlu);
					
					fseek(PtrAlu,b*sizeof(TpAluno),0);
					fread(&RegB,sizeof(TpAluno),1,PtrAlu);
					
					if (strcmp(RegA.RA,RegB.RA) > 0)
					{
						fseek(PtrAlu,a*sizeof(TpAluno),0);
						fwrite(&RegB,sizeof(TpAluno),1,PtrAlu);
						
						fseek(PtrAlu,b*sizeof(TpAluno),0);
						fwrite(&RegA,sizeof(TpAluno),1,PtrAlu);
					}
				}
			fclose(PtrAlu);
			printf("\nArquivo Ordenado!\n");
		}
		getch();
}

void ExclusaoFisica(void)
{
	TpAluno RegAlu;
	char AuxRA[14];
	int pos;
	FILE *PtrAlu = fopen("AlunosLOG.dat","rb");
	clrscr();
	printf("\n### Exclusao (Fisica) de um Aluno ###\n");
	if (PtrAlu==NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("\nR.A. a Excluir: ");
			fflush(stdin);
			gets(AuxRA);
			pos = BuscaRAAluno(PtrAlu,AuxRA);
			if (pos==-1)
			{
				printf("\nAluno nao Cadastrado!\n");
				fclose(PtrAlu);
			}
			else
				{
					fseek(PtrAlu,pos,0);
					fread(&RegAlu,sizeof(TpAluno),1,PtrAlu);
					printf("\nDados do Aluno:\n");
					printf("R.A.: %s\n",RegAlu.RA);
					printf("Nome: %s\n",RegAlu.Nome);
					printf("Ano Nasc.: %d\n",RegAlu.AnoNasc);
					
					printf("\nConfirma Exclusao (S/N)? ");
					if (toupper(getche())=='S')
					{
						rewind(PtrAlu);  // fseek(PtrAlu,0,0);
						FILE *PtrTemp = fopen("Temp.dat","wb");
						fread(&RegAlu,sizeof(TpAluno),1,PtrAlu);
						while (!feof(PtrAlu))
						{
							if (strcmp(AuxRA,RegAlu.RA)!=0)
								fwrite(&RegAlu,sizeof(TpAluno),1,PtrTemp);
							
							fread(&RegAlu,sizeof(TpAluno),1,PtrAlu);
						}
						fclose(PtrAlu);
						fclose(PtrTemp);
						remove("Alunos.dat");
						rename("Temp.dat","Alunos.dat");
						printf("\nAluno excluido fisicamente!\n");
					}
					else
						fclose(PtrAlu);
				}
		}
	getch();
}

void ExcluirLogicaAlunos(void)
{
	FILE *PtrAlu = fopen("AlunosLOG.dat","rb+");
	TpAluno RAluno;
	int pos;
	clrscr();
	printf("\n## Excluir pelo R.A. (Logica) ##\n");
	if(PtrAlu == NULL)
		printf("\nErro de Abertura!\n");
	else
		{
			printf("R.A. a excluir: ");
			fflush(stdin);
			gets(RAluno.RA);
			while (strcmp(RAluno.RA,"\0")!=0)
			{
				pos = BuscaRAAluno(PtrAlu,RAluno.RA);
				if (pos == -1)
					printf("\nR.A. nao encontrado!\n");
				else
					{
						fseek(PtrAlu,pos,0);
						fread(&RAluno,sizeof(TpAluno),1,PtrAlu);
						printf("\n*** Dados Encontrados ***\n");
						printf("\nR.A.: %s",RAluno.RA);
						printf("\nNome: %s",RAluno.Nome);
						printf("\nAno Nasc.: %d\n",RAluno.AnoNasc);
						printf("\nConfirma Exclusao (S/N)? ");
						if (toupper(getche())=='S')
						{
							RAluno.Status = 0;
							fseek(PtrAlu,pos,0);
							fwrite(&RAluno,sizeof(TpAluno),1,PtrAlu);
							printf("\nRegistro excluido!\n");
						}
					}
				
				getch();
				printf("\nR.A. a Excluir: ");
				fflush(stdin);
				gets(RAluno.RA);
			}
			
			fclose(PtrAlu);
		}
}

void ExclusaoFisicaTODOS(void)
{
	TpAluno RegAlu;
	FILE *PtrAlu = fopen("AlunosLOG.dat","rb");
	
	if (PtrAlu==NULL)
		printf("\nErro de Abertura!\n");
	else
		{							
			FILE *PtrTemp = fopen("Temp.dat","wb");
			fread(&RegAlu,sizeof(TpAluno),1,PtrAlu);
			while (!feof(PtrAlu))
			{
				if (RegAlu.Status)
					fwrite(&RegAlu,sizeof(TpAluno),1,PtrTemp);
				
				fread(&RegAlu,sizeof(TpAluno),1,PtrAlu);
			}
			fclose(PtrAlu);
			fclose(PtrTemp);
			remove("AlunosLOG.dat");
			rename("Temp.dat","AlunosLOG.dat");					
		}
}


char Menu(void)
{
	clrscr();
	printf("\n ###  M E N U   A L U N O S ###\n");
	printf("\n[A] Cadastrar");
	printf("\n[B] Exibir");
	printf("\n[C] Consultar por R.A.");
	printf("\n[D] Alterar por R.A.");
	printf("\n[E] Ordenar por R.A.");
	printf("\n[F] Exclusao pelo R.A. (Fisica)");
	printf("\n[G] Exclusao pelo R.A. (Logica)");
	printf("\n[ESC] Finalizar");
	printf("\nOpcao desejada: ");
	return toupper(getche());
}

void CriaArquivos(void)
{
	FILE *Ptr;
	
	Ptr = fopen("Livros.dat","ab");
	fclose(Ptr);
	Ptr = fopen("Autor.dat","ab");
	fclose(Ptr);
	Ptr = fopen("Emprestimos.dat","ab");
	fclose(Ptr);
	Ptr = fopen("AutorLivro.dat","ab");
	fclose(Ptr);
	Ptr = fopen("Pessoas.dat","ab");
	fclose(Ptr);
}

int main(void)
{
	char opcao;
	CriaArquivos();
	do
	{
		opcao = Menu();
		switch(opcao)
		{
			case 'A':	GravarAluno();
						break;
			case 'B':	ExibirAluno();
						break;
			case 'C':	ConsultarAluno();
						break;
			case 'D':	AlterarAluno();
						break;
			case 'E':	OrdenarAlunos();
						break;
			case 'F':	ExclusaoFisica();
						break;
			case 'G':	ExcluirLogicaAlunos();
						break;
		}
	}while (opcao!=27);
	ExclusaoFisicaTODOS();
	return 0;
}
