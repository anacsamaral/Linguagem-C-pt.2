#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

struct Aluno //int tem 4 bytes, string 44 bytes = 48 bytes
{
	char RA[14], Nome[30]; //cada char tem 1 byte
	int AnoNasc;
	char flag; 
};

char Menu(void)
{
	system("cls");
	printf("### M E N U ###");
	printf("\n[A] Cadastrar");
	printf("\n[B] Exibir");
	printf("\n[C] Consultar");
	printf("\n[D] Alterar por R.A.");
	printf("\n[E] Ordenar por R.A.");
	printf("\n[F] Excluir Fisicamente por R.A.");
	printf("\n[ESC] Finalizar");
	printf("\nOpcao Desejada: ");
	return toupper(getche());
}

int BuscaAlunoRA(FILE *PtrAluno, char RA[14]) //arquivo passa aberto
{
	Aluno Reg;
	rewind(PtrAluno); //Posiciona o PtrAluno no INï¿½CIO DO ARQUIVO;
	fread(&Reg, sizeof(Aluno), 1, PtrAluno);
	while(!feof(PtrAluno) && strcmp(RA, Reg.RA)!=0)
		fread(&Reg, sizeof(Aluno), 1, PtrAluno);
	
	if(strcmp(RA, Reg.RA)==0)
		return ftell(PtrAluno)-sizeof(Aluno); 
		//tell diz onde esta o deslocamentoponteiro;
		//onde esta o ponteiro, menos uma estrutura;
	else
		return -1;
}

void OrdenarAlunos(void)
{
	int a, b, QtdeReg;
	Aluno RegA, RegB;
	FILE *PtrAlu = fopen("Alunos.dat", "rb+");
	if(PtrAlu == NULL)
		printf("\nErro de Abertura\n");
	else
	{
		fseek(PtrAlu, 0, 2);
		QtdeReg = ftell(PtrAlu)/sizeof(Aluno);
		for(a=0; a<QtdeReg-1; a++) //a++ --> a += sizeof(TpAluno); b < QtdeReg - sizeof
			for(b = a+1; b<QtdeReg; b++) 
			/*b<feof(PtrAlu) = numero menor que verdadeiro ou falso????? nao da p usar assim
			O TL representa a quantidade de registros
			ftell retorna quantos bytes o ponteiro andou para estar onde esta atualmente
			*/
			{
				fseek(PtrAlu,a*sizeof(Aluno), 0);//fseek nï¿½o funciona sozinho
				fread(&RegA,sizeof(Aluno), 1, PtrAlu);
				
				fseek(PtrAlu,b*sizeof(Aluno), 0);
				fread(&RegB,sizeof(Aluno),1,PtrAlu);
				
				if(strcmp(RegA.RA,RegB.RA)>0) //stricmp(RegA.Nome,RegB.Nome)>0
				//T[a*sizeof(TpAluno)].Campo > T[b*sizeof(TpAluno)].Campo
				{
					fseek(PtrAlu,a*sizeof(Aluno), 0);
					fwrite(&RegB,sizeof(Aluno),1,PtrAlu);
					
					fseek(PtrAlu,b*sizeof(Aluno), 0);
					fwrite(&RegA,sizeof(Aluno),1,PtrAlu);
				}
			}
				
		fclose(PtrAlu);
		printf("\nArquivo Ordenado por Nome\n");
	}
	getch();
	
}

void GravarAluno(void)
{
	Aluno Reg;
	printf("%d", sizeof(Aluno)); //qtd de bytes q tem na struct
	//Ponteiro sï¿½ vai existir se a funï¿½ï¿½o for chamada;
	FILE *Ptr = fopen("Alunos.dat", "ab+"); //Sempre serï¿½ esse nome
	//ab+ para deixar ler, da para usar a busca dentro;
	//ï¿½ recomendado abrir com rb ou rb+
	printf("\n## Cadastro de Alunos ##\n");
	printf("\nR.A.: "); fflush(stdin);
	gets(Reg.RA);
	while (strcmp(Reg.RA, "\0")!=0)
	{
		if(BuscaAlunoRA(Ptr, Reg.RA) == -1)
		{
			printf("\nNome: "); fflush(stdin);
			gets(Reg.Nome);
			printf("\nAno de Nascimento: ");
			scanf("%d", &Reg.AnoNasc);
			
			Reg.flag = '1';
			fwrite(&Reg, sizeof(Aluno),  1, Ptr); //da memoria pro arquivo
			//O arquivo comeï¿½a nesse endereï¿½o;
			//Da para usar o nome da variavel ou o tipo dela (recomendado);
			//vai pegar 48 bytes a partir desse endereï¿½o;
			
			//vai gravar sï¿½ 1, ou seja, 1 * 48 a partir de onde comeï¿½a o registro na memï¿½ria;	
			printf("\nDados Cadastrados!\n");
		}
		else
		{
			printf("\nAluno ja esta Cadastrado!");
			getch();
		}
		printf("R.A.: "); fflush(stdin);
		gets(Reg.RA);
	}
	fclose(Ptr);
}



void ExibirAluno(void)
{
	Aluno R;
	FILE *PtrAlu = fopen("Alunos.dat", "rb"); //ponteiro esta no inicio;
	//para abrir com rb, tem que ja existir um arquivo;
	
	//VALIDANDO SE O ARQUIVO EXISTE (nï¿½o tem comando, mas)
	if(PtrAlu == NULL) //null = endereï¿½o nulo/vazio;
	//se sim, significa que foi corrompido ou nï¿½o existe.
		printf("\nErro de Abertura!\n");
	else
	{
		fread(&R, sizeof(Aluno), 1, PtrAlu);
		while(!feof(PtrAlu)) //feof = end of file, nï¿½o ï¿½ fim de arquivo? vc leu o fim de arquivo?
		//esta testando onde executou o fread
		{
			//onde esta parado o ponteiro, pega o sizeof e joga para o &R;
			printf("\nRA: %s", R.RA);
			printf("\nNome: %s", R.Nome);
			printf("\nAno Nasc.: %d\n", R.AnoNasc);
			
			fread(&R, sizeof(Aluno), 1, PtrAlu);
		}
		//se nao foi aberto, nao pode ser fechado, sï¿½ da fclose se foi aberto
		fclose(PtrAlu);
	}
	getch();
	//EOF ï¿½ usado com arquivo texto;
}

void ConsultarAluno(void)
{
	int pos;
	FILE *PtrAlu = fopen("Alunos.dat", "rb");
	//O arquivo precisa existir;
	Aluno RegAluno; //Funciona como auxiliar
	system("cls");
	printf("\n## Consultar pelo RA: ##\n");
	if(PtrAlu == NULL)
		printf("\nErro de Abertura\n");
	else
	{
		printf("RA a consultar: ");
		fflush(stdin);
		gets(RegAluno.RA);
		
		while(strcmp(RegAluno.RA, "\0")!=0)
		{
			//pos ja pega em bytes (deslocamento)
			pos = BuscaAlunoRA(PtrAlu, RegAluno.RA); //Manda o arquivo pra busca
			
			if(pos == -1)
				printf("\nR.A. nao encontrado!");
			else
			{
				fseek(PtrAlu, pos, 0);
				/* === fseek(ponteiro, Qtd de Bytes de Desloc., SEEK_SET);
				//SEEK_SET ï¿½ a partir do inicio do arq; 
				//SEEK_CUR ï¿½ a partir de onde o ponteiro esta;
				//SEEK_END ï¿½ um valor positivo para tras, tipo, 96 bytes para tras;
				eles sï¿½o constantes e precisam ser maiusculas
				
				SEEK_SET SENDO 0
				SEEK_CUR SENDO 1
				SEEK_END SENDO 2 === */
				
				fread(&RegAluno, sizeof(Aluno), 1, PtrAlu);
				printf("\n*** Dados Encontrados ***");
				printf("\nR.A: %s", RegAluno.RA);
				printf("\nNome: %s", RegAluno.Nome);
				printf("\nAno Nasc: %d\n", RegAluno.AnoNasc);
			}
			
			getch();
			printf("\nRA a consultar: ");
			fflush(stdin);
			gets(RegAluno.RA);
		}
		
		fclose(PtrAlu);
	}
}

void AlterarAluno(void)
{
	FILE *PtrAluno = fopen("Alunos.dat", "rb+");//arquivo tem q existir
	Aluno RegAluno;
	int pos;
	system("cls");
	printf("## Alterar Aluno ##");
	
	if(PtrAluno == NULL)
		printf("\nErro de Abertura:(\n");
	else
	{
		printf("\nAluno a ser alterado [R.A.]: ");
		fflush(stdin);
		gets(RegAluno.RA);
		
		while(strcmp(RegAluno.RA, "\0")!=0)
		{
			pos = BuscaAlunoRA(PtrAluno, RegAluno.RA);
		
			if (pos == -1)
				printf("\nAluno nao encontrado!\n");
			else
			{
				fseek(PtrAluno, pos, 0);//bytes a partir do inicio
				fread(&RegAluno, sizeof(Aluno), 1, PtrAluno);//de onde o ponteiro esta parado e joga pro registro
				printf("\n*** Dados Encontrados ***");
				printf("\nR.A: %s", RegAluno.RA);
				printf("\nNome: %s", RegAluno.Nome);
				printf("\nAno Nasc: %d\n", RegAluno.AnoNasc);
				
				printf("\nDeseja alterar os dados deste RA? [S/N]:\n");
				if (toupper(getche()) == 'S')
				{
					printf("\nNovo Nome: "); fflush(stdin);
					gets(RegAluno.Nome);
					printf("Novo Ano de Nascimento: ");
					scanf("%d", &RegAluno.AnoNasc);
					
					fseek(PtrAluno, pos, 0);
					fwrite(&RegAluno, sizeof(Aluno), 1, PtrAluno);
					
					fseek(PtrAluno, pos, 0); //ponteiro vai para a posiï¿½ï¿½o que achou na busca
					fread(&RegAluno, sizeof(Aluno), 1, PtrAluno); //fread e fwrite ponteiro vai para frente
					printf("\n*** Dados Alterados ***");
					printf("\nR.A: %s", RegAluno.RA);
					printf("\nNome: %s", RegAluno.Nome);
					printf("\nAno Nasc: %d\n", RegAluno.AnoNasc);
					
					printf("\nDados do aluno %s alterados com sucesso!\n", RegAluno.RA);
					getch();
				}
			}
			printf("\nAluno a ser alterado [R.A.]: ");
			fflush(stdin);
			gets(RegAluno.RA);
		}
	}
}

// === EXCLUSÃO ===
/*	Criar um arquivo novo que receberá as informações do antigo arquivo
	Deletar o antigo arquivo e renomear o atual -> remove("Alunos.dat")
	Renomear o arquivo atual -> rename("Temp.dat", "Alunos.dat"))
	
	
	 
*/
	
void ExclusaoFisica(void)
{
	Aluno RegAlu;
	char AuxRA[14];
	int pos;
	
	FILE *PtrAlu = fopen("Alunos.dat", "rb");
	clrscr();
	printf("\n### Exclusao Fisica de um Aluno ###\n");
	if(PtrAlu ==  NULL)
		printf("\nErro de Abertura\n");
	else
	{
		printf("\nR.A. a Excluir: ");
		fflush(stdin);
		gets(RegAlu.RA);
		pos = BuscaAlunoRA(PtrAlu, AuxRA);
		
		if(pos == -1)
		{
			printf("\nAluno nao Cadastrado!\n");
			fclose(PtrAlu);
		}
			
		else
		{
			fseek(PtrAlu, pos,0);
			fread(&RegAlu, sizeof(Aluno),1,PtrAlu);
			
			printf("\nDados do Aluno:\n");
			printf("R.A.: %s\n", RegAlu.RA);
			printf("Nome: %s\n", RegAlu.Nome);
			printf("Ano Nasc.: %d\n", RegAlu.AnoNasc);
			
			printf("\nConfirma Exclusao? (S/N): ");
			if(toupper(getche()) == 'S')
			{
				rewind(PtrAlu); //fseek(PtrAlu, 0, 0);
				FILE *PtrTemp = fopen("Temp.dat", "wb"); //wb abre o arq zerado
				fread(&RegAlu, sizeof(Aluno),1,PtrAlu);
				
				while(!feof(PtrAlu)) //enquanto arq nao acabou
				{
					if(strcmp(AuxRA,RegAlu.RA)!=0)
						//Se diferente, grava
						fwrite(&RegAlu, sizeof(Aluno), 1, PtrTemp);
					
					fread(&RegAlu, sizeof(Aluno), 1, PtrAlu);
				}
				fclose(PtrAlu);
				fclose(PtrTemp);
				remove("Alunos.dat");
				rename("Temp.dat", "Alunos.dat");
				printf("\nAluno Excluido Fisicamente!\n");
			}
			else
				fclose(PtrAlu);
		}
	}
}

/*quantos registros a gente tem: ponteiro no final, 
pega o ftell do ponteiro, divide por sizeof;*/
int main(void)
{
	FILE *PtrAlu;  //nao tem vinculo com ninguem
	char opcao;
	
	do
	{
		opcao = Menu();
		switch(opcao)
		{
			case 'A': 
					GravarAluno();
					break;
				
			case 'B':
					ExibirAluno();
					break;
				
			case 'C':
					ConsultarAluno();
					break;
			
			case 'D':
					AlterarAluno();
					break;
				
			case 'E':
					OrdenarAlunos();
					break;
			case 'F':
					ExclusaoFisica();
					break;
		}
		
	}while(opcao != 27);
	
	return 0;
}
