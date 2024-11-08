#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct Aluno //int tem 4 bytes, string 44 bytes = 48 bytes
{
	char RA[14], Nome[30]; //cada char tem 1 byte
	int AnoNasc; 
};

int BuscaAlunoRA(FILE *PtrAluno, char RA[14]) //arquivo passa aberto
{
	Aluno Reg;
	rewind(PtrAluno); //Posiciona o PtrAluno no INÍCIO DO ARQUIVO;
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
				fseek(PtrAlu,a*sizeof(Aluno), 0);//fseek não funciona sozinho
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
	//Ponteiro só vai existir se a função for chamada;
	FILE *Ptr = fopen("Alunos.dat", "ab+"); //Sempre será esse nome
	//ab+ para deixar ler, da para usar a busca dentro;
	//É recomendado abrir com rb ou rb+
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
			
			fwrite(&Reg, sizeof(Aluno),  1, Ptr); //da memoria pro arquivo
			//O arquivo começa nesse endereço;
			//Da para usar o nome da variavel ou o tipo dela (recomendado);
			//vai pegar 48 bytes a partir desse endereço;
			
			//vai gravar só 1, ou seja, 1 * 48 a partir de onde começa o registro na memória;	
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
	
	//VALIDANDO SE O ARQUIVO EXISTE (não tem comando, mas)
	if(PtrAlu == NULL) //null = endereço nulo/vazio;
	//se sim, significa que foi corrompido ou não existe.
		printf("\nErro de Abertura!\n");
	else
	{
		fread(&R, sizeof(Aluno), 1, PtrAlu);
		while(!feof(PtrAlu)) //feof = end of file, não é fim de arquivo? vc leu o fim de arquivo?
		//esta testando onde executou o fread
		{
			//onde esta parado o ponteiro, pega o sizeof e joga para o &R;
			printf("\nRA: %s", R.RA);
			printf("\nNome: %s", R.Nome);
			printf("\nAno Nasc.: %d\n", R.AnoNasc);
			
			fread(&R, sizeof(Aluno), 1, PtrAlu);
		}
		//se nao foi aberto, nao pode ser fechado, só da fclose se foi aberto
		fclose(PtrAlu);
	}
	getch();
	//EOF é usado com arquivo texto;
}

void ConsultarAluno(void)
{
	int pos;
	FILE *PtrAlu = fopen("Alunos.dat", "rb");
	//O arquivo precisa existir;
	Aluno RegAluno; //Funciona como auxiliar
	clrscr();
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
				//SEEK_SET é a partir do inicio do arq; 
				//SEEK_CUR é a partir de onde o ponteiro esta;
				//SEEK_END é um valor positivo para tras, tipo, 96 bytes para tras;
				eles são constantes e precisam ser maiusculas
				
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
	clrscr();
	printf("## Alterar Aluno ##");
	
	if(PtrAluno == NULL)
		printf("\Erro de Abertura:(\n");
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
					
					fseek(PtrAluno, pos, 0); //ponteiro vai para a posição que achou na busca
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

char Menu(void)
{
	clrscr();
	printf("### M E N U ###");
	printf("\n[A] Cadastrar");
	printf("\n[B] Exibir");
	printf("\n[C] Consultar");
	printf("\n[D] Alterar por R.A.");
	printf("\n[E] Ordenar por R.A.");
	printf("\n[ESC] Finalizar");
	printf("\nOpcao Desejada: ");
	return toupper(getche());
}

/*quantos registros a gente tem: ponteiro no final, 
pega o ftell do ponteiro, divide por sizeof;*/
int main(void)
{
	FILE *PtrAluno;  //Não tem vínculo com ninguém
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
		}
		
	}while(opcao != 27);
	
	return 0;
}
