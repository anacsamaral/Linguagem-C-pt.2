#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

struct TpLivros
{
	int id_livro, ano_publicacao, status;
	char titulo[50];
	
};

struct TpAutores
{
	int id_autor, status;
	char nome[50], nacionalidade[30];
};

struct TpEmprestimos
{
	int id_emprestimo, id_livro, id_pessoa, status;
	char data_emprestimo[11], data_devolucao[11];
};

struct TpPessoas
{
	int id_pessoa, status;
	char nome[50], fone[17], endereco[120];	
};

struct TpLivroAutor
{
	int id_livro, id_autor, status;
};

// ================= INTERFACES E MENUS ================== //
void LimpaMenu()
{
	//COLUNA 3 ATÉ 49
	//LINHA  7  ATÉ 25
	for(int i = 3; i < 50; i++)
		for(int j = 6; j <26; j++)
		{
			gotoxy(i,j);
			printf("%c",32);
		}
}

void LimpaExibe()
{
	// COLUNA 52 A 113
	// LINHA 7  ATÉ 25
	int i,j;
	for(int i = 53; i < 114; i++)
		for(int j = 6; j <26; j++)
		{
			gotoxy(i, j);
			printf("%c", 32);
		}		
}
void LimpaMensagem()
{
	//COLUNA 13 ATÉ 113
	int i=28, j;
	for(int j = 13; j <113; j++)
	{
		gotoxy(i,j);
		printf("%c",32);
	}
}


void Moldura (int CI, int LI, int CF, int LF, int CorT, int CorL)
{
	int i;
	textcolor(CorT);
	textbackground(CorL);
	gotoxy(CI,LI);
	printf("%c", 201);
	gotoxy(CF,LI);
	printf("%c", 187);
	gotoxy(CI,LF);
	printf("%c", 200);
	gotoxy(CF,LF);
	printf("%c", 188);
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI);
		printf("%c",205);
	//	Sleep(10);
		gotoxy(i,LF);
		printf("%c",205);
	}
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
//		Sleep(10);
		gotoxy(CF,i);
		printf("%c",186);
	}
	textcolor(7);
	textbackground(0);
}
void PainelPrincipal (void)
{
	Moldura(1,1,115,30,1,7); // BRANCO
	Moldura(2,2,114,4,2,6); // AMARELO SUPERIOR
	textcolor(RED);
	gotoxy(34,3);
	printf("### BIBLIOTECA ###");
	Moldura(2,5,50,26,3,5); // ROXO
	Moldura(51,5,114,26,5,4); // ROSA
	Moldura(2,27,114,29,3,6); // AMARELO INFERIOR
	textcolor(RED);
	gotoxy(3,28);
	printf("Mensagem: ");
}


char Menu1(void)
{
	textcolor(15);
	gotoxy(7,7);
	printf("### M E N U ###");
	textcolor(10);
	gotoxy(4,11);  //10
	printf("[A] CADASTROS E MANUTENCOES");
	gotoxy(4,13);
	printf("[B] RELATORIOS");
	gotoxy(4,15);
	printf("[ESC] FINALIZAR PROGRAMA");
	gotoxy(4,17);
	printf("Opcao Desejada: ");
	gotoxy(20,17);
	return toupper(getche());
}

char Menu2(void)
{
	textcolor(15);
	gotoxy(7,7);
	printf("M E N U   C R U D");
	textcolor(10);
	gotoxy(4,9);
	printf("[A] CADASTRAR");
	gotoxy(4,11);
    printf("[B] CONSULTAR");
    gotoxy(4,13);
    printf("[C] ALTERAR");
    gotoxy(4,15);
    printf("[D] EXCLUIR");
    gotoxy(4,17);
    printf("[E] EXIBIR");
    gotoxy(4,19);
	printf("[TAB] VOLTAR");
	gotoxy(4,21);
	printf("Opcao Desejada: ");
	gotoxy(20,21);
	return toupper(getche());
}

char Menu3(void)
{
	textcolor(15);
	gotoxy(7,7);
	printf("M E N U    R E L A T O R I O S");
	textcolor(10);
	gotoxy(4,9);
	printf("[A] RELATORIO: AUTORES POR DETERMINADA LETRA");
	gotoxy(4,11);
	printf("[B] RELATORIO: LIVROS POR DETERMINADA PALAVRA");
	gotoxy(4,13);
	printf("[C] RELATORIO: EMPRESTIMO POR ID PESSOA");
	gotoxy(4,15);
	printf("[D] RELATORIO: DADOS LIVROS POR ID AUTOR");
	gotoxy(4,17);
	printf("[E] RELATORIO: GERAL EMPRESTIMOS");
	gotoxy(4,19);
	printf("[TAB] VOLTAR");
	gotoxy(4,21);
	printf("Opcao Desejada: ");
	gotoxy(20,21);
	return toupper(getche());
}

char MenuCadastro(void)
{
    textcolor(15);
	gotoxy(7,7);
	printf("OPCOES DE CADASTRO");
	textcolor(10);
	gotoxy(4,9);
	printf("[A] CADASTRAR LIVRO");
	gotoxy(4,11);
	printf("[B] CADASTRAR AUTOR");
	gotoxy(4,13);
	printf("[C] CADASTRAR PESSOAS");
	gotoxy(4,15);
	printf("[D] VINCULAR LIVRO E AUTOR");
	gotoxy(4,17);
	printf("[E] CADASTRAR EMPRESTIMO");
	gotoxy(4,19);
    printf("[ENTER] VOLTAR");
    gotoxy(4,21);
	printf("Opcao Desejada: ");
	gotoxy(20,21);
	return toupper(getche());
}

char MenuAlterar (void)
{
    textcolor(15);
	gotoxy(7,7);
	printf("OPCOES PARA ALTERAR");
	textcolor(10);
	gotoxy(4,10);
	printf("[A] ALTERAR LIVRO");
	gotoxy(4,12);
	printf("[B] ALTERAR AUTOR");
	gotoxy(4,14);
	printf("[C] ALTERAR PESSOA");
	gotoxy(4,16);
	printf("[D] ALTERAR EMPRESTIMO");
	gotoxy(4,18);
    printf("[ENTER] VOLTAR");
    gotoxy(4,20);
	printf("Opcao Desejada: ");
	gotoxy(20,20);
	return toupper(getche());
}

char MenuConsulta(void)
{
    textcolor(15);
	gotoxy(7,7);
	printf("OPCOES DE CONSULTA");
	textcolor(10);
	gotoxy(4,9);
	printf("[A] CONSULTAR LIVRO");
	gotoxy(4,11);
	printf("[B] CONSULTAR AUTOR");
	gotoxy(4,13);
	printf("[C] CONSULTAR PESSOA");
	gotoxy(4,15);
	printf("[D] CONSULTAR LIVRO-AUTOR COMPLETO");
	gotoxy(4,17);
	printf("[E] CONSULTAR EMPRESTIMO");
	gotoxy(4,19);
    printf("[ENTER] VOLTAR");
    gotoxy(4,21);
	printf("Opcao Desejada: ");
	gotoxy(20,21);
	return toupper(getche());
}

char MenuExcluir (void)
{
    textcolor(15);
	gotoxy(7,7);
	printf(" OPCOES DE EXCLUSAO ");
	textcolor(10);
	gotoxy(4,10);
	printf("[A] EXCLUIR LIVRO");
	gotoxy(4,12);
	printf("[B] EXCLUIR AUTOR");
	gotoxy(4,14);
	printf("[C] EXCLUIR PESSOA");
	gotoxy(4,16);
	printf("[D] EXCLUIR EMPRESTIMO");
	gotoxy(4,18);
    printf("[ENTER] VOLTAR");
    gotoxy(4,20);
	printf("Opcao Desejada: ");
	gotoxy(20,20);
	return toupper(getche());
}

char MenuExibir (void)
{
    textcolor(15);
	gotoxy(7,7);
	printf("OPCOES DE EXIBICAO");
	textcolor(10);
	gotoxy(4,9);
	printf("[A] EXIBIR LIVRO");
	gotoxy(4,11);
	printf("[B] EXIBIR AUTOR");
	gotoxy(4,13);
	printf("[C] EXIBIR PESSOA");
	gotoxy(4,15);
	printf("[D] EXIBIR VINCULO LIVROS X AUTORES");
	gotoxy(4,17);
	printf("[E] EXIBIR EMPRESTIMO");
	gotoxy(4,19);
    printf("[ENTER] VOLTAR");
    gotoxy(4,21);
	printf("Opcao Desejada: ");
	gotoxy(20,21);
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

int BuscaLivro(FILE *PtrLivro, int id)
{
    TpLivros R;
    rewind(PtrLivro);

    while (fread(&R, sizeof(TpLivros), 1, PtrLivro))
	{
        if (R.id_livro == id && R.status)
            return ftell(PtrLivro) - sizeof(TpLivros);
    }
    return -1;
}

int BuscaAutor(FILE *PtrAutor, int id)
{
	TpAutores R;
	rewind(PtrAutor);
	
	while(fread(&R,sizeof(TpAutores),1,PtrAutor))
	{
		if(id == R.id_autor && R.status)
			return ftell(PtrAutor)-sizeof(TpAutores);
	}
	return -1;
}

int BuscaPessoa(FILE *PtrPessoa, int id)
{
	TpPessoas R;
	rewind(PtrPessoa);
	
	while(fread(&R,sizeof(TpPessoas),1,PtrPessoa))
	{
		if(id == R.id_pessoa && R.status)
			return ftell(PtrPessoa)-sizeof(TpPessoas);
	}
	return -1;
}

int BuscaEmprestimo(FILE *PtrEmprestimo, int id)
{
	TpEmprestimos R;
	rewind(PtrEmprestimo);
	
	while(fread(&R,sizeof(TpEmprestimos),1,PtrEmprestimo))
	{
		if(id == R.id_emprestimo && R.status)
			return ftell(PtrEmprestimo)-sizeof(TpEmprestimos);
	}
	return -1;
}

void OrdenarAutoresNacionalidade(void)
{
    int a, b, QtdeReg;
    TpAutores RegA, RegB;
    FILE *PtrAutor = fopen("Autor.dat", "rb+");

    fseek(PtrAutor, 0, SEEK_END);
    QtdeReg = ftell(PtrAutor) / sizeof(TpAutores);
    rewind(PtrAutor);

    for (a = 0; a < QtdeReg - 1; a++)
    {
        for (b = a + 1; b < QtdeReg; b++)
        {
            
            fseek(PtrAutor, a * sizeof(TpAutores), SEEK_SET);
            fread(&RegA, sizeof(TpAutores), 1, PtrAutor);

           
            fseek(PtrAutor, b * sizeof(TpAutores), SEEK_SET);
            fread(&RegB, sizeof(TpAutores), 1, PtrAutor);

            
            if (strcmp(RegA.nacionalidade, RegB.nacionalidade) > 0)
            {
                fseek(PtrAutor, a * sizeof(TpAutores), SEEK_SET);
                fwrite(&RegB, sizeof(TpAutores), 1, PtrAutor);

                fseek(PtrAutor, b * sizeof(TpAutores), SEEK_SET);
                fwrite(&RegA, sizeof(TpAutores), 1, PtrAutor);
            }
        }
    }

    fclose(PtrAutor);
}

void OrdenarLivroAnoPublicacao(void)
{
    int a, b, QtdeReg;
    TpLivros RegA, RegB;
    FILE *PtrLivro = fopen("Livros.dat", "rb+");

    fseek(PtrLivro, 0, SEEK_END);
    QtdeReg = ftell(PtrLivro) / sizeof(TpLivros);

    for (a = 0; a < QtdeReg - 1; a++)
    {
        for (b = a + 1; b < QtdeReg; b++)
        {
            fseek(PtrLivro, a * sizeof(TpLivros), SEEK_SET);
            fread(&RegA, sizeof(TpLivros), 1, PtrLivro);

            fseek(PtrLivro, b * sizeof(TpLivros), SEEK_SET);
            fread(&RegB, sizeof(TpLivros), 1, PtrLivro);

            if (RegA.ano_publicacao > RegB.ano_publicacao)
            {
                fseek(PtrLivro, a * sizeof(TpLivros), SEEK_SET);
                fwrite(&RegB, sizeof(TpLivros), 1, PtrLivro);

                fseek(PtrLivro, b * sizeof(TpLivros), SEEK_SET);
                fwrite(&RegA, sizeof(TpLivros), 1, PtrLivro);
            }
        }
    }

    fclose(PtrLivro);
}

void GravarLivro(void)
{
    TpLivros registro;
    FILE *PtrLivro = fopen("Livros.dat", "ab+");
    
    int tecla = 0; // Variável para capturar a tecla pressionada
    
    do
    {
    	LimpaMensagem();
		LimpaExibe();
		gotoxy(62,6);
    	printf("## Cadastrar Livro ##");
    	LimpaMensagem();
		gotoxy(13,28);
        printf("Pressione ESC para sair ou qualquer outra tecla para continuar...");
        tecla = getch();

        if (tecla != 27)
        {
        	gotoxy(54,8);
            printf("ID Livro: ");
            gotoxy(68,8);
            scanf("%d", &registro.id_livro);

            if (registro.id_livro == 0)
            {
            	LimpaMensagem();
				gotoxy(13,28);
                printf("ID incorreto! Digite um ID diferente de 0.");
            }
            else
            {
                if (BuscaLivro(PtrLivro, registro.id_livro) == -1)
                {
                	gotoxy(54,9);
                    printf("Titulo: ");
                    fflush(stdin);
                    gotoxy(62,9);
                    gets(registro.titulo);

                    while (strcmp(registro.titulo, "\0") == 0) // Validação: título não pode ser vazio
                    {
                    	LimpaMensagem();
						gotoxy(13,28);
                        printf("Titulo invalido. Digite novamente: ");
                        fflush(stdin);
                        gotoxy(62,9);
                        gets(registro.titulo);
                    }
					gotoxy(54,10);
                    printf("Ano de Publicacao: ");
                    gotoxy(71,10);
                    scanf("%d", &registro.ano_publicacao);
                    while(registro.ano_publicacao == 0)
                    {
                    	LimpaMensagem();
						gotoxy(13,28);
						printf("Ano Invalido! Digite novamente.\n");
						gotoxy(54,10);
                    	printf("Ano de Publicacao: ");
                    	gotoxy(71,10);
                    	scanf("%d", &registro.ano_publicacao);
                    }

                    registro.status = 1;
                    fwrite(&registro, sizeof(TpLivros), 1, PtrLivro);
                    fclose(PtrLivro);
                    OrdenarLivroAnoPublicacao();
                    FILE *PtrLivro = fopen("Livros.dat", "ab+");
                    gotoxy(54,11);
                    printf("Dados cadastrados!");
                }
                else
                {
                	LimpaMensagem();
					gotoxy(13,28);
                    printf("ID Livro ja cadastrado!\n");
                }
            }
            getch();
        }
    }while (tecla != 27);
    
    fclose(PtrLivro);
    LimpaMensagem();
	gotoxy(13,28);
    printf("\nCadastro encerrado.\n");
}

void GravarAutor(void)
{
    TpAutores registro;
    FILE *PtrAutor = fopen("Autor.dat", "ab+");
    
    int tecla = 0;
    do
    {
	    LimpaMensagem();
		LimpaExibe();
	    gotoxy(71,6);
	    printf("## Cadastrar Autor ##");
		gotoxy(13,28);
        printf("Pressione ESC para sair ou qualquer outra tecla para continuar...");
        gotoxy(80,28);
        tecla = getch();
        LimpaMensagem();
        if (tecla != 27)
        {
        	gotoxy(54,8);
            printf("ID Autor: ");
            gotoxy(64,8);
            scanf("%d", &registro.id_autor);

            if (registro.id_autor == 0)
            {
            	LimpaMensagem();
				gotoxy(13,28);
                printf("ID incorreto! Digite um ID diferente de 0.");
            }
            else
            {
                if (BuscaAutor(PtrAutor, registro.id_autor) == -1)
                {
                	gotoxy(54,10);
					printf("Nome: ");
	                fflush(stdin);
	                gotoxy(60,10);
	                gets(registro.nome);
	                while(strcmp(registro.nome,"\0") == 0)
	                {
	                	gotoxy(54,10);
	                	printf("Nome: ");
		                fflush(stdin);
		                gotoxy(60,10);
		                gets(registro.nome);
	                }
	                gotoxy(54,11);
	                printf("Nacionalidade: ");
	                fflush(stdin);
	                gotoxy(69,11);
	                gets(registro.nacionalidade);
	                while(strcmp(registro.nacionalidade,"\0") == 0)
					{
						gotoxy(54,11);
						printf("Nacionalidade: ");
		                fflush(stdin);
		                gotoxy(69,11);
		                gets(registro.nacionalidade);
					} 
	                registro.status = 1;
	
	                fwrite(&registro, sizeof(TpAutores), 1, PtrAutor);
	                OrdenarAutoresNacionalidade();
	                gotoxy(54,13);
	                printf("Dados cadastrados!");
                }
                else
                {
                	gotoxy(54,14);
                    printf("ID Autor ja cadastrado!");
                }
            }
            getch();
        }
    } while (tecla != 27);
    
    fclose(PtrAutor);
    LimpaMensagem();
	gotoxy(13,28);
    printf("Cadastro encerrado.");
    
}

void GravarPessoa(void)
{
    TpPessoas registro;
    FILE *PtrPessoa = fopen("Pessoas.dat", "ab+");

    int tecla = 0; // Variável para capturar a tecla pressionada

    do
    {
    	LimpaMensagem();
		LimpaExibe();
		gotoxy(71,6);
    	printf("## Cadastrar Pessoa ##");
    	LimpaMensagem();
    	gotoxy(13,28);
        printf("Pressione ESC para sair ou qualquer outra tecla para continuar...");
        tecla = getch();

        if (tecla != 27)
        {
        	gotoxy(54,8);
            printf("ID Pessoa: ");
            gotoxy(65,8);
            scanf("%d", &registro.id_pessoa);

            if (registro.id_pessoa == 0)
            {
            	LimpaMensagem();
    			gotoxy(13,28);
    			printf("ID incorreto! Digite um ID diferente de 0.");
			}
            else
            {
                if (BuscaPessoa(PtrPessoa, registro.id_pessoa) == -1)
                {
                	gotoxy(54,9);
                    printf("Nome: ");
                    fflush(stdin);
                    gotoxy(60,9);
                    gets(registro.nome);
                    while(strcmp(registro.nome,"\0")== 0)
                    {
                    	LimpaMensagem();
    					gotoxy(13,28);
                    	printf("Nome invalido! Digite novamente: ");
	                    fflush(stdin);
	                    gotoxy(60,9);
	                    gets(registro.nome);
                    }
                    gotoxy(54,10);
                    printf("Telefone: ");
                    fflush(stdin);
                    gotoxy(63,10);
                    gets(registro.fone);
                    while(strcmp(registro.fone,"\0")== 0)
                    {
                    	LimpaMensagem();
    					gotoxy(13,28);
                    	printf("Telefone invalido! Digite novamente: ");
	                    fflush(stdin);
	                    gotoxy(63,10);
	                    gets(registro.fone);
                    }
                    gotoxy(54,11);
                    printf("Endereco: ");
                    fflush(stdin);
                    gotoxy(63,11);
                    gets(registro.endereco);
                    while(strcmp(registro.endereco,"\0")== 0)
                    {
                    	LimpaMensagem();
    					gotoxy(13,28);
                    	printf("Endereco invalido! Digite novamente: ");
	                    fflush(stdin);
	                    gotoxy(63,11);
	                    gets(registro.endereco);
                    }
                    
                    registro.status = 1;

                    fwrite(&registro, sizeof(TpPessoas), 1, PtrPessoa);
                    gotoxy(54,13);
                    printf("Dados cadastrados!");
                }
                else
                	LimpaMensagem();
    				gotoxy(13,28);
                    printf("\nID Pessoa ja cadastrado!\n");
            }
        }
    } while (tecla != 27);

    fclose(PtrPessoa);
    LimpaMensagem();
	gotoxy(13,28);
    printf("Cadastro encerrado.");
}

void GravarLivroAutor(void)
{
    TpLivroAutor registro;
    FILE *PtrLivroAutor = fopen("AutorLivro.dat", "ab+");
    FILE *PtrLivro = fopen("Livros.dat", "rb+");
    FILE *PtrAutor = fopen("Autor.dat", "rb+");
    LimpaMensagem();
	LimpaExibe();
    gotoxy(68,8);
    printf("## Vincular AUTOR - LIVRO ##");

    int teclaLivro = 0, teclaAutor = 0; // Variáveis para capturar teclas pressionadas
    int continuarLivro = 1, continuarAutor = 1; // Controle dos loops

    while (continuarLivro)
    {
    	LimpaMensagem();
		gotoxy(13,28);
        printf("Pressione ESC para sair ou qualquer outra tecla para selecionar um Livro...");
        gotoxy(80,28);
        teclaLivro = getch();

        if (teclaLivro == 27) // Verifica se o usuário pressionou ESC
        {
            continuarLivro = 0; // Encerra o loop de livros
        }
        else
        {
        	gotoxy(54,10);
            printf("ID Livro: ");
            gotoxy(68,10);
            scanf("%d", &registro.id_livro);

            if (registro.id_livro == 0)
            {
            	LimpaMensagem();
            	gotoxy(13,28);
                printf("ID incorreto! Digite um ID diferente de 0.");
            }
            else if (BuscaLivro(PtrLivro, registro.id_livro) != -1)
            {
                continuarAutor = 1; // Reinicia o controle para o loop de autores
                while (continuarAutor)
                {
                	LimpaMensagem();
                	gotoxy(13,28);
                    printf("Pressione ESC para sair ou qualquer outra tecla para selecionar um Autor...");
                    teclaAutor = getch();

                    if (teclaAutor == 27) // Verifica se o usuário pressionou ESC
                        continuarAutor = 0; // Encerra o loop de autores
                    else
                    {
                    	gotoxy(54,11);
                        printf("ID Autor: ");
                        gotoxy(68,11);
                        scanf("%d", &registro.id_autor);

                        if (registro.id_autor == 0)
                        {
                        	LimpaMensagem();
							gotoxy(13,28);
                            printf("ID incorreto! Digite um ID diferente de 0.");
                        }
                        else if (BuscaAutor(PtrAutor, registro.id_autor) != -1)
                        {
                            int jaExiste = 0; // Verifica se já existe um vínculo entre este livro e autor
                            TpLivroAutor tempRegistro; // Tipo temporário para verificação

                            rewind(PtrLivroAutor);
                            fread(&tempRegistro, sizeof(TpLivroAutor), 1, PtrLivroAutor);
                            while (!feof(PtrLivroAutor))
                            {
                                if (tempRegistro.id_livro == registro.id_livro && tempRegistro.id_autor == registro.id_autor)
                                    jaExiste = 1;

                                fread(&tempRegistro, sizeof(TpLivroAutor), 1, PtrLivroAutor);
                            }

                            if (jaExiste == 0)
                            {
                                registro.status = 1;
                                fwrite(&registro, sizeof(TpLivroAutor), 1, PtrLivroAutor);
                                gotoxy(54,13);
                                printf("Vinculo registrado com sucesso!");
                            }
                            else
                            {
                            	LimpaMensagem();
								gotoxy(13,28);
								printf("Vinculo entre Livro e Autor ja existe!");
							}
                                
                        }
                        else
                        {
                        	LimpaMensagem();
							gotoxy(13,28);
							printf("ID Autor nao esta cadastrado!");
						}
                            
                    }
                }
            }
            else
            {
            	LimpaMensagem();
				gotoxy(13,28);
				printf("ID Livro nao esta cadastrado!");
			}
                
        }
    }

	getch();
    fclose(PtrLivroAutor);
    fclose(PtrLivro);
    fclose(PtrAutor);
    LimpaMensagem();
	gotoxy(13,28);
    printf("Vinculacao encerrada.");
}

void GravarEmprestimo(void)
{
    TpEmprestimos registro;
    TpLivros livro;
    TpPessoas pessoa;
    FILE *PtrEmprestimo = fopen("Emprestimos.dat", "ab+");
    FILE *PtrLivro = fopen("Livros.dat", "rb+");
    FILE *PtrPessoa = fopen("Pessoas.dat", "rb+");
	LimpaMensagem();
	LimpaExibe();
	gotoxy(69,6);
    printf("## Cadastrar Emprestimo ##");

    int teclaPessoa = 0, teclaLivro = 0; // Variáveis para capturar teclas pressionadas
    int continuarPessoa = 1, continuarLivroLoop = 1; // Controle dos loops

    while (continuarPessoa)
    {
    	LimpaMensagem();
		gotoxy(13,28);
        printf("Pressione ESC para sair ou qualquer outra tecla para selecionar uma Pessoa...");
        gotoxy(80,28);
        teclaPessoa = getch();

        if(teclaPessoa == 27) // Verifica se o usuário pressionou ESC
            continuarPessoa = 0; // Encerra o loop de pessoa.
        else
        {
        	gotoxy(54,8);
            printf("ID Pessoa: ");
            gotoxy(65,8);
            scanf("%d", &registro.id_pessoa);

            if (registro.id_pessoa == 0)
            {
            	LimpaMensagem();
				gotoxy(13,28);
                printf("ID incorreto! Digite um ID diferente de 0.");
			}
            else if (BuscaPessoa(PtrPessoa, registro.id_pessoa) != -1)
            {
            	
                continuarLivroLoop = 1; // Reinicia o controle para o loop de livros
                while (continuarLivroLoop)
                {
                	LimpaMensagem();
					gotoxy(13,28);
                    printf("Pressione ESC para sair ou qualquer outra tecla para selecionar um Livro...");
                    teclaLivro = getch();

                    if (teclaLivro == 27) // Verifica se o usuário pressionou ESC
                        continuarLivroLoop = 0; // Encerra o loop de livros
                    else
                    {
                    	gotoxy(54,9);
                        printf("ID Livro: ");
                        gotoxy(64,9);
                        scanf("%d", &registro.id_livro);

                        if (registro.id_livro == 0)
                        {
                        	LimpaMensagem();
                        	gotoxy(13,28);
                            printf("ID incorreto! Digite um ID diferente de 0.");
						}
                        else if (BuscaLivro(PtrLivro, registro.id_livro) != -1)
                        {
                            fseek(PtrLivro, BuscaLivro(PtrLivro, registro.id_livro), SEEK_SET);
                            fread(&livro, sizeof(TpLivros), 1, PtrLivro);
							gotoxy(71,11);
                            printf("### Dados do Livro ###");
                            gotoxy(54,13);
                            printf("ID Livro: %d", livro.id_livro);
                            gotoxy(54,14);
                            printf("Titulo: %s", livro.titulo);
                            gotoxy(54,15);
                            printf("Ano de Publicacao: %d", livro.ano_publicacao);
                            LimpaMensagem();
                        	gotoxy(13,28);
                            printf("Deseja realmente realizar o emprestimo? (S/N): ");		
							gotoxy(47,28);
                            if (toupper(getche()) == 'S')
                            {
                                int dia1, mes1, ano1, dia2, mes2, ano2;
                                int dataValida = 0;

                                // Validando a data de emprestimo
                                while (!dataValida)
                                {
                                	gotoxy(54,16);
                                    printf("Digite a Data de Emprestimo (dd/mm/aaaa): ");
                                    gotoxy(96,16);
                                    scanf("%d/%d/%d", &dia1, &mes1, &ano1);

                                    // Verifica se a data de emprestimo é válida
                                    if (dia1 < 1 || dia1 > 31 || mes1 < 1 || mes1 > 12 || ano1 < 1900)
                                    {
                                    	LimpaMensagem();
                                    	gotoxy(13,28);
                                        printf("Data de Emprestimo invalida. Tente novamente.");
									}
                                    	
                                    else
                                        dataValida = 1;
                                }

                                dataValida = 0;
                                // Validando a data de devolucao
                                while (!dataValida)
                                {
                                	gotoxy(54,17);
                                    printf("Digite a Data de Devolucao (dd/mm/aaaa): ");
                                    gotoxy(91,17);
                                    scanf("%d/%d/%d", &dia2, &mes2, &ano2);

                                    // Verifica se a data de devolucao é válida
                                    if (dia2 < 1 || dia2 > 31 || mes2 < 1 || mes2 > 12 || ano2 < 1900)
                                    {
                                    	LimpaMensagem();
                                    	gotoxy(13,28);
                                        printf("Data de Devolucao invalida. Tente novamente.");
									}
                                    // Verifica se a data de devolucao é posterior à de emprestimo
                                    else if (ano2 < ano1 || (ano2 == ano1 && mes2 < mes1) || (ano2 == ano1 && mes2 == mes1 && dia2 < dia1))
                                    {
                                    	LimpaMensagem();
                                    	gotoxy(13,28);
                                        printf("A data de devolucao nao pode ser anterior ao emprestimo. Tente novamente.");
									}
                                    else
                                        dataValida = 1;
                                }

                                // FORMATA AS DATAS COMO STRINGS PARA O FORMATO ADEQUADO DA STRUCT
                                sprintf(registro.data_emprestimo, "%02d/%02d/%04d", dia1, mes1, ano1);
                                sprintf(registro.data_devolucao, "%02d/%02d/%04d", dia2, mes2, ano2);

                                do
                                {
                                	gotoxy(54,18);
                                    printf("Digite o ID do Emprestimo: ");
                                    gotoxy(79,18);
                                    scanf("%d", &registro.id_emprestimo);

                                    if (registro.id_emprestimo == 0)
                                    	LimpaMensagem();
                                    	gotoxy(13,28);
                                        printf("ID do Emprestimo invalido! Digite um ID diferente de 0.");
                                } while (registro.id_emprestimo == 0);

                                // Aqui é onde a busca de empréstimos existentes é feita antes de salvar um novo
                                if (BuscaEmprestimo(PtrEmprestimo, registro.id_emprestimo) == -1)
                                {
                                    registro.status = 1;
                                    fwrite(&registro, sizeof(TpEmprestimos), 1, PtrEmprestimo);
                                    gotoxy(54,20);
                                    printf("Emprestimo realizado com sucesso!");
                                }
                                else
                                {
                                	LimpaMensagem();
                                    gotoxy(13,28);
                                    printf("Erro: Este ID de emprestimo ja existe.");
								}
                            }
                            else
                            {
                            		LimpaMensagem();
                                gotoxy(13,28);;
                                printf("Emprestimo nao realizado!");
							}
                        }
                        else
                        {
                        	LimpaMensagem();
                           	gotoxy(13,28);
                            printf("Livro nao existe!\n");
						}
                        gotoxy(54,9);
                        printf("ID Livro: ");
                        gotoxy(64,9);
                        scanf("%d", &registro.id_livro);
                    }
                }
            }
            else
            {
            	LimpaMensagem();
				gotoxy(13,28);
				printf("Pessoa nao cadastrada!");
			}
            gotoxy(54,8);
            printf("\nID Pessoa: ");
            gotoxy(65,8);
            scanf("%d", &registro.id_pessoa);
        }
    }

    fclose(PtrEmprestimo);
    fclose(PtrLivro);
    fclose(PtrPessoa);
}

void ExibirLivro(void)
{
	TpLivros R;
	FILE *PtrLivro = fopen("Livros.dat","rb");
	clrscr();
	fread(&R,sizeof(TpLivros),1,PtrLivro);
	printf("\n### LISTA DE LIVROS ###\n");
	while(!feof(PtrLivro))
	{
		if(R.status)
		{
			printf("\nID Livro: %d",R.id_livro);
			printf("\nTitulo: %s",R.titulo);
			printf("\nAno de publicacao: %d",R.ano_publicacao);
			printf("\n\n");
		}
		fread(&R,sizeof(TpLivros),1,PtrLivro);
	}
	getch();
	fclose(PtrLivro);
}

void ExibirAutor (void)
{
	TpAutores R;
	FILE *PtrAutor = fopen("Autor.dat","rb");
	clrscr();
	fread(&R,sizeof(TpAutores),1,PtrAutor);
	printf("\n### LISTA DE AUTORES ###\n");
	while(!feof(PtrAutor))
	{
		if(R.status)
		{
			printf("\nID Autor: %d",R.id_autor);
			printf("\nNome: %s",R.nome);
			printf("\nNacionalidade: %s",R.nacionalidade);
			printf("\n\n");	
		}
		fread(&R,sizeof(TpAutores),1,PtrAutor);
	}
	getch();
	fclose(PtrAutor);
}

void ExibirPessoa (void)
{
	TpPessoas R;
	FILE *PtrPessoa = fopen("Pessoas.dat","rb");
	clrscr();
	fread(&R,sizeof(TpPessoas),1,PtrPessoa);
	printf("\n### LISTA DE PESSOAS ###\n");
	while(!feof(PtrPessoa))
	{
		if(R.status)
		{
			printf("\nID Pessoa: %d",R.id_pessoa);
			printf("\nNome: %s",R.nome);
			printf("\nTelefone: %s",R.fone);
			printf("\nEndereco: %s",R.endereco);
			printf("\n\n");
		}
		fread(&R,sizeof(TpPessoas),1,PtrPessoa);
	}
	getch();
	fclose(PtrPessoa);
}

void ExibirLivroAutor(void)
{
    TpLivroAutor R;
    TpLivros livro;
    TpAutores autor;
    
    FILE *PtrLivroAutor = fopen("AutorLivro.dat", "rb");
    FILE *PtrLivro = fopen("Livros.dat", "rb");
    FILE *PtrAutor = fopen("Autor.dat", "rb");
    
    clrscr();
    printf("\n### LISTA DE VINCULOS: ID-LIVRO X ID-AUTOR ###\n");

    // Lê cada vínculo de livro-autor
    while (fread(&R, sizeof(TpLivroAutor), 1, PtrLivroAutor))
    {
        if (R.status)
        {
            int posLivro = BuscaLivro(PtrLivro, R.id_livro);
            if (posLivro != -1)
            {
                fseek(PtrLivro, posLivro, SEEK_SET);
                fread(&livro, sizeof(TpLivros), 1, PtrLivro);
        	}
            
            int posAutor = BuscaAutor(PtrAutor, R.id_autor);
            if (posAutor != -1)
            {
                fseek(PtrAutor, posAutor, SEEK_SET);
                fread(&autor, sizeof(TpAutores), 1, PtrAutor);
            }

            if (posLivro != -1 && posAutor != -1)
            {
                printf("\nLivro: %s (ID: %d)\n", livro.titulo, livro.id_livro);
                printf("Autor: %s (ID: %d)\n", autor.nome, autor.id_autor);
                printf("--------------------------------------\n");
            }
        }
    }
    getch();
    fclose(PtrLivroAutor);
    fclose(PtrLivro);
    fclose(PtrAutor);
}

void ExibirEmprestimo(void)
{
    TpEmprestimos emprestimo;
    TpLivros livro;
    TpPessoas pessoa;
    
    FILE *PtrEmprestimo = fopen("Emprestimos.dat", "rb");
    FILE *PtrLivro = fopen("Livros.dat", "rb");
    FILE *PtrPessoa = fopen("Pessoas.dat", "rb");
    
    clrscr();
    fread(&emprestimo, sizeof(TpEmprestimos), 1, PtrEmprestimo);
    
    printf("\n### LISTA DE EMPRESTIMOS ATIVOS ###\n");
    
    while (!feof(PtrEmprestimo))
	{
        if (emprestimo.status == 1)
		{
            int posLivro = BuscaLivro(PtrLivro, emprestimo.id_livro);
            int posPessoa = BuscaPessoa(PtrPessoa, emprestimo.id_pessoa);
            
            if (posLivro != -1 && posPessoa != -1)
			{
                fseek(PtrLivro, posLivro, SEEK_SET);
                fread(&livro, sizeof(TpLivros), 1, PtrLivro);
                
                fseek(PtrPessoa, posPessoa, SEEK_SET);
                fread(&pessoa, sizeof(TpPessoas), 1, PtrPessoa);
                
                printf("\nEmprestimo ID: %d\n", emprestimo.id_emprestimo);
                printf("Livro: %s (ID: %d)\n", livro.titulo, livro.id_livro);
                printf("Pessoa: %s (ID: %d)\n", pessoa.nome, pessoa.id_pessoa);
                printf("Data de Emprestimo: %s\n", emprestimo.data_emprestimo);
                printf("Data de Devolucao: %s\n", emprestimo.data_devolucao);
                printf("--------------------------------------\n");
            }
        }
        fread(&emprestimo, sizeof(TpEmprestimos), 1, PtrEmprestimo);
    }

    getch();
    fclose(PtrEmprestimo);
    fclose(PtrLivro);
    fclose(PtrPessoa);
}

void ConsultarLivro(void)
{
    FILE *PtrLivro = fopen("Livros.dat", "rb");
    TpLivros R;
    int pos;
    char tecla;
    clrscr();
    printf("\n### CONSULTAR LIVRO PELO ID ###\n");
    do
    {
        printf("\nTecle ESC para sair, ou qualquer tecla para continuar...\n");
        tecla = getch();
        if(tecla != 27)
        {
            do
            {
                printf("\nID Livro a consultar: ");
                scanf("%d", &R.id_livro);
                if (R.id_livro == 0)
                    printf("\nID invalido! Digite um ID diferente de 0.\n");
            }while (R.id_livro == 0);

            pos = BuscaLivro(PtrLivro, R.id_livro);
            if (pos == -1)
                printf("\nLivro nao encontrado!\n");
            else
            {
                fseek(PtrLivro, pos, SEEK_SET);
                fread(&R, sizeof(TpLivros), 1, PtrLivro);
                printf("\nDados encontrados\n");
                printf("\nID LIVRO: %d", R.id_livro);
                printf("\nTITULO: %s", R.titulo);
                printf("\nANO PUBLICACAO: %d", R.ano_publicacao);
                printf("\n");
        	}
            getch();
        }
    } while (tecla != 27);
    printf("\nConsulta encerrada!\n");
    getch();
    fclose(PtrLivro);
}

void ConsultarAutor(void)
{
	FILE *PtrAutor = fopen("Autor.dat", "rb");
    TpAutores R;
    int pos;
    char tecla;
    
    do
    {
    	LimpaMensagem();
		LimpaExibe();
		gotoxy(68,6);
    	printf("### CONSULTAR AUTOR PELO ID ###");
    	LimpaMensagem();
    	gotoxy(13,28);
        printf("Tecle ESC para sair, ou qualquer tecla para continuar...");
        tecla = getch();
        if(tecla != 27)
        {
            do
            {
            	gotoxy(54,8);
                printf("ID Autor a consultar: ");
                gotoxy(75,8);
                scanf("%d", &R.id_autor);
                if (R.id_autor == 0)
                {
                	LimpaExibe();
                	gotoxy(13,28);
                	printf("ID invalido! Digite um ID diferente de 0.");
				}
                    
            }while (R.id_autor == 0);

            pos = BuscaAutor(PtrAutor, R.id_autor);
            if (pos == -1)
            {
            	LimpaExibe();
                gotoxy(13,28);
                printf("Autor nao encontrado!");
			}
                
            else
            {
                fseek(PtrAutor, pos, SEEK_SET);
                fread(&R, sizeof(TpAutores), 1, PtrAutor);
                gotoxy(54,10);
                printf("**Dados encontrados**");
                gotoxy(54,12);
                printf("ID AUTOR: %d", R.id_autor);
                gotoxy(54,13);
                printf("NOME: %s", R.nome);
                gotoxy(54,14);
                printf("NACIONALIDADE: %s", R.nacionalidade);
        	}
            LimpaMensagem();
	    	gotoxy(13,28);
	        printf("Tecle ESC para sair, ou qualquer tecla para continuar...");
        }
    } while (tecla != 27);
    gotoxy(54,16);
    printf("\nConsulta encerrada!\n");
    fclose(PtrAutor);
}

void ConsultarPessoa(void)
{
	FILE *PtrPessoa = fopen("Pessoas.dat", "rb");
    TpPessoas R;
    int pos;
    char tecla;
    do
    {
    	LimpaMensagem();
		LimpaExibe();
		gotoxy(68,6);
    	printf("### CONSULTAR PESSOA PELO ID ###");
    	LimpaMensagem();
    	gotoxy(13,28);
        printf("\nTecle ESC para sair, ou qualquer tecla para continuar...\n");
        tecla = getch();
        if(tecla != 27)
        {
            do
            {
            	gotoxy(54,8);
                printf("ID Pessoa a consultar: ");
                gotoxy(77,8);
                scanf("%d", &R.id_pessoa);
                if (R.id_pessoa == 0)
                    printf("\nID invalido! Digite um ID diferente de 0.\n");
            }while (R.id_pessoa == 0);

            pos = BuscaPessoa(PtrPessoa, R.id_pessoa);
            if (pos == -1)
                printf("\nID Pessoa nao encontrado!\n");
            else
            {
                fseek(PtrPessoa, pos, SEEK_SET);
                fread(&R, sizeof(TpPessoas), 1, PtrPessoa);
                printf("\nDados encontrados\n");
                printf("\nID PESSOA: %d", R.id_pessoa);
                printf("\nNOME: %s", R.nome);
                printf("\nTELEFONE: %s", R.fone);
                printf("\nENDERECO: %s", R.endereco);
                printf("\n");
        	}
            getch();
        }
    } while (tecla != 27);
    printf("\nConsulta encerrada!\n");
    getch();
    fclose(PtrPessoa);
}

void ConsultarLivroAutor(void)
{
	FILE *PtrLivroAutor = fopen("AutorLivro.dat","rb");
	FILE *PtrLivro = fopen("Livros.dat","rb");
	FILE *PtrAutor = fopen("Autor.dat","rb");
	TpLivroAutor R;
	TpLivros livro;
	TpAutores autor;
	int pos, op, id, continuar = 1;
	char tecla;
	printf("\n### CONSULTAR VINCULOS LIVRO X AUTOR ###\n");
	while(continuar)
	{
		clrscr();
		printf("\nEscolha uma opcao:\n");
        printf("1 - Consultar pelo ID do livro\n");
        printf("2 - Consultar pelo ID do autor\n");
        printf("Tecle ESC para sair.\n");
        tecla = getch();
        
        if(tecla == 27) //Sai ao teclar ESC
        	continuar = 0;
        else if(tecla == '1')
        {
        	clrscr();
        	printf("\nDigite o ID do Livro: ");
            scanf("%d", &id);
            pos = BuscaLivro(PtrLivro, id);
            if(pos == -1)
            	printf("\nLivro nao encontrao!\n");
            else
            {
            	fseek(PtrLivro,pos,SEEK_SET);
            	fread(&livro,sizeof(TpLivros),1,PtrLivro);
            	printf("\n## Livro encontrado ##\n");
                printf("\nID Livro: %d", livro.id_livro);
                printf("\nTitulo: %s", livro.titulo);
                printf("\nAno de Publicacao: %d\n", livro.ano_publicacao);
                
                // Buscar e exibir os autores vinculados ao livro
                rewind(PtrLivroAutor);
                printf("\n## Autores vinculados ao livro ##\n");
                while(fread(&R,sizeof(TpLivroAutor),1,PtrLivroAutor))
                {
                	if(R.id_livro == livro.id_livro && R.status)
                	{
                		pos = BuscaAutor(PtrAutor,R.id_autor);
                		if(pos != -1)
                		{
                			fseek(PtrAutor,pos,SEEK_SET);
                			fread(&autor,sizeof(TpAutores),1,PtrAutor);
                			printf("ID Autor: %d\n", autor.id_autor);
                			printf("Nome: %s\n", autor.nome);
                			printf("Nacionalidade: %s\n", autor.nacionalidade);
                			printf("\n");
                		}
                	}
                }
                getch();
            }
        }
        else if(tecla == '2')
        {
        	clrscr();
        	printf("\nDigite o ID do Autor: ");
            scanf("%d", &id);
            pos = BuscaAutor(PtrAutor, id);
            if (pos == -1)
            	printf("\nAutor nao encontrado!\n");
            else
            {
            	fseek(PtrAutor, pos, SEEK_SET);
                fread(&autor, sizeof(TpAutores), 1, PtrAutor);
                printf("\n### Autor encontrado ###\n");
                printf("\nID Autor: %d", autor.id_autor);
                printf("\nNome: %s", autor.nome);
                printf("\nNacionalidade: %s\n", autor.nacionalidade);
                
                // Buscar e exibir os livros vinculados ao autor
                rewind(PtrLivroAutor);
                printf("\n### Livros vinculados ao autor ###\n");
                
                while (fread(&R, sizeof(TpLivroAutor), 1, PtrLivroAutor))
                {
                    if (R.id_autor == autor.id_autor && R.status)
                    {
                        pos = BuscaLivro(PtrLivro, R.id_livro);
                        if (pos != -1)
                        {
                            fseek(PtrLivro, pos, SEEK_SET);
                            fread(&livro, sizeof(TpLivros), 1, PtrLivro);
                            printf("ID Livro: %d\n", livro.id_livro);
                            printf("Titulo: %s\n", livro.titulo);
                            printf("Ano de Publicacao: %d\n", livro.ano_publicacao);
                            printf("\n");
                        }
                    }
                }
                getch();
            }
        }
	}
	
	printf("\nConsulta encerrada!\n");
    getch();
    fclose(PtrLivroAutor);
    fclose(PtrLivro);
    fclose(PtrAutor);
}

void ConsultarEmprestimo(void)
{
    FILE *PtrEmprestimos = fopen("Emprestimos.dat", "rb");
    FILE *PtrLivro = fopen("Livros.dat", "rb");
    FILE *PtrPessoa = fopen("Pessoas.dat", "rb");
    TpEmprestimos R;
    TpLivros livro;
    TpPessoas pessoa;
    int pos, op, id, continuar = 1;
    char tecla;
    
    clrscr();  // Limpa a tela antes de exibir o menu inicial
    printf("\n### CONSULTAR EMPRESTIMOS ###\n");
    while (continuar)
    {
        clrscr();  // Limpa a tela antes de exibir o menu de opções
        printf("\nEscolha uma opcao:\n");
        printf("1 - Consultar pelo ID do emprestimo\n");
        printf("2 - Consultar pelo ID da pessoa\n");
        printf("Tecle ESC para sair.\n");
        tecla = getch();

        if (tecla == 27) // Sai ao teclar ESC
        {
            continuar = 0;
        }
        else if (tecla == '1')
        {
            clrscr();  // Limpa a tela antes de solicitar o ID do empréstimo
            printf("\nDigite o ID do Emprestimo: ");
            scanf("%d", &id);

            pos = BuscaEmprestimo(PtrEmprestimos, id);
            if (pos == -1)
                printf("\nEmprestimo nao encontrado!\n");
            else
            {
                fseek(PtrEmprestimos, pos, SEEK_SET);
                fread(&R, sizeof(TpEmprestimos), 1, PtrEmprestimos);

                printf("\n## Emprestimo encontrado ##\n");
                printf("\nID Emprestimo: %d", R.id_emprestimo);
                printf("\nData de Emprestimo: %s", R.data_emprestimo);
                printf("\nData de Devolucao: %s\n", R.data_devolucao);

                // Buscar e exibir o livro vinculado ao empréstimo
                pos = BuscaLivro(PtrLivro, R.id_livro);
                if (pos != -1)
                {
                    fseek(PtrLivro, pos, SEEK_SET);
                    fread(&livro, sizeof(TpLivros), 1, PtrLivro);
                    printf("\nLivro: %s (ID: %d)\n", livro.titulo, livro.id_livro);
                }

                // Buscar e exibir a pessoa vinculada ao empréstimo
                pos = BuscaPessoa(PtrPessoa, R.id_pessoa);
                if (pos != -1)
                {
                    fseek(PtrPessoa, pos, SEEK_SET);
                    fread(&pessoa, sizeof(TpPessoas), 1, PtrPessoa);
                    printf("\nPessoa: %s (ID: %d)\n", pessoa.nome, pessoa.id_pessoa);
                    printf("Telefone: %s\n", pessoa.fone);
                    printf("Endereco: %s\n", pessoa.endereco);
                }
                getch();
                clrscr();  // Limpa a tela após mostrar os detalhes do empréstimo
            }
        }
        else if (tecla == '2')
        {
            clrscr();  // Limpa a tela antes de solicitar o ID da pessoa
            printf("\nDigite o ID da Pessoa: ");
            scanf("%d", &id);

            pos = BuscaPessoa(PtrPessoa, id);
            if (pos == -1)
                printf("\nPessoa nao encontrada!\n");
            else
            {
                fseek(PtrPessoa, pos, SEEK_SET);
                fread(&pessoa, sizeof(TpPessoas), 1, PtrPessoa);

                printf("\n### Pessoa encontrada ###\n");
                printf("\nID Pessoa: %d", pessoa.id_pessoa);
                printf("\nNome: %s", pessoa.nome);
                printf("\nTelefone: %s", pessoa.fone);
                printf("\nEndereco: %s\n", pessoa.endereco);

                // Buscar e exibir os empréstimos vinculados à pessoa
                rewind(PtrEmprestimos);
                printf("\n### Emprestimos vinculados a pessoa ###\n");
                while (fread(&R, sizeof(TpEmprestimos), 1, PtrEmprestimos))
                {
                    if (R.id_pessoa == pessoa.id_pessoa && R.status)
                    {
                        pos = BuscaLivro(PtrLivro, R.id_livro);
                        if (pos != -1)
                        {
                            fseek(PtrLivro, pos, SEEK_SET);
                            fread(&livro, sizeof(TpLivros), 1, PtrLivro);
                            printf("\nID Emprestimo: %d", R.id_emprestimo);
                            printf("\nLivro: %s (ID: %d)\n", livro.titulo, livro.id_livro);
                            printf("Data de Emprestimo: %s\n", R.data_emprestimo);
                            printf("Data de Devolucaoo: %s\n", R.data_devolucao);
                            printf("\n");
                        }
                    }
                }
                getch();
                clrscr();  // Limpa a tela após mostrar os empréstimos da pessoa
            }
        }
    }

    printf("\nConsulta encerrada!\n");
    getch();
    fclose(PtrEmprestimos);
    fclose(PtrLivro);
    fclose(PtrPessoa);
}

void AlterarLivro(void)
{
	FILE *PtrLivro = fopen("Livros.dat","rb+");
	TpLivros R;
	int pos;
	LimpaMensagem();
	LimpaExibe();
	gotoxy(68,6);
	printf("## Alterar pelo ID LIVRO ##");
	gotoxy(54,8);
	printf("ID a alterar(0-SAIR): ");
	gotoxy(80,8);
	scanf("%d",&R.id_livro);
	while(R.id_livro !=0)
	{
		pos = BuscaLivro(PtrLivro,R.id_livro);
		if(pos == -1)
		{
			LimpaMensagem();
			gotoxy(13,28);
			printf("ID Livro nao encontrado!");
		}
			
		else
		{
			fseek(PtrLivro,pos,0);
			fread(&R,sizeof(TpLivros),1,PtrLivro);
			gotoxy(54,10);
			printf("### Dados Encontrados ###");
			gotoxy(54,12);
			printf("ID LIVRO: %d",R.id_livro);
			gotoxy(54,13);
			printf("TITULO: %s",R.titulo);
			gotoxy(54,14);
			printf("ANO DE PUBLICACAO: %d",R.ano_publicacao);
			gotoxy(54,16);
			printf("Deseja Alterar (S/N)? ");
			gotoxy(76,16);
			if (toupper(getche())=='S')
			{
				gotoxy(54,18);
				printf("Novo Titulo: ");
				fflush(stdin);
				gotoxy(67,18);
				gets(R.titulo);
				gotoxy(54,19);
				printf("Novo Ano de Publicacao.: ");
				gotoxy(78,16);
				scanf("%d",&R.ano_publicacao);
				
				fseek(PtrLivro,pos,0);
				fwrite(&R,sizeof(TpLivros),1,PtrLivro);
				OrdenarLivroAnoPublicacao();
				gotoxy(13,28);
				printf("Dados Atualizados com sucesso!");
				
				fseek(PtrLivro,pos,0);
				fread(&R,sizeof(TpLivros),1,PtrLivro);
				LimpaMensagem();
				LimpaExibe();
				gotoxy(68,6);
				printf("### Dados Atualizados ###");
				gotoxy(54,8);
				printf("ID LIVRO: %d",R.id_livro);
				gotoxy(54,9);
				printf("TITULO: %s",R.titulo);
				gotoxy(54,10);
				printf("ANO DE PUBLICACAO: %d",R.ano_publicacao);
			}
		}
		
		LimpaMensagem();
		LimpaExibe();
		gotoxy(68,6);
		printf("## Alterar pelo ID LIVRO ##");
		gotoxy(54,8);
		printf("ID a alterar(0-SAIR): ");
		gotoxy(80,8);
		scanf("%d",&R.id_livro);
	}
	fclose(PtrLivro);
}

void AlterarAutor(void)
{
	FILE *PtrAutor = fopen("Autor.dat","rb+");
	TpAutores R;
	int pos;
	LimpaMensagem();
	LimpaExibe();
	gotoxy(68,6);
	printf("## Alterar pelo ID AUTOR ##");
	gotoxy(54,8);
	printf("ID a alterar(0-SAIR): ");
	gotoxy(80,8);
	scanf("%d",&R.id_autor);
	while(R.id_autor !=0)
	{
		pos = BuscaAutor(PtrAutor,R.id_autor);
		if(pos == -1)
		{
			LimpaMensagem();
			gotoxy(13,28);
			printf("ID Autor nao encontrado!");
		}
			
			
		else
		{	
			fseek(PtrAutor,pos,0);
			fread(&R,sizeof(TpAutores),1,PtrAutor);
			gotoxy(54,10);
			printf("### Dados Encontrados ###");
			gotoxy(54,12);
			printf("ID AUTOR: %d",R.id_autor);
			gotoxy(54,13);
			printf("NOME: %s",R.nome);
			gotoxy(54,14);
			printf("NACIONALIDADE: %s",R.nacionalidade);
			gotoxy(54,15);
			printf("Deseja Alterar (S/N)?: ");
			gotoxy(81,15);
			if (toupper(getche())=='S')
			{
				gotoxy(54,17);
				printf("Novo Nome: ");
				fflush(stdin);
				gotoxy(65,17);
				gets(R.nome);
				gotoxy(54,18);
				printf("Nova Nacionalidade: ");
				fflush(stdin);
				gotoxy(74,18);
				gets(R.nacionalidade);
				
				fseek(PtrAutor,pos,0);
				fwrite(&R,sizeof(TpAutores),1,PtrAutor);
				OrdenarAutoresNacionalidade();
				gotoxy(54,19);
				printf("Dados Atualizados com sucesso!");
				
				fseek(PtrAutor,pos,0);
				fread(&R,sizeof(TpAutores),1,PtrAutor);
				gotoxy(54,20);
				printf("### Dados Atualizados ###");
				gotoxy(54,21);
				printf("ID AUTOR: %d",R.id_autor);
				gotoxy(54,22);
				printf("NOME: %s",R.nome);
				gotoxy(54,23);
				printf("NACIONALIDADE: %s",R.nacionalidade);
			}
		}
		LimpaExibe();	
		gotoxy(68,6);
		printf("## Alterar pelo ID AUTOR ##");
		gotoxy(54,8);
		printf("ID a alterar(0-SAIR): ");
		gotoxy(80,8);
		scanf("%d",&R.id_autor);
	}
	fclose(PtrAutor);
}

void AlterarPessoa(void)
{
	FILE *PtrPessoa = fopen("Pessoas.dat","rb+");
	TpPessoas R;
	int pos;
	LimpaMensagem();
	LimpaExibe();
	gotoxy(68,6);
	printf("## Alterar pelo ID PESSOA ##");
	gotoxy(54,8);
	printf("ID a alterar(0-SAIR): ");
	gotoxy(80,8);
	scanf("%d",&R.id_pessoa);
	while(R.id_pessoa !=0)
	{
		pos = BuscaPessoa(PtrPessoa,R.id_pessoa);
		if(pos == -1)
		{
			LimpaMensagem();
			gotoxy(13,28);
			printf("ID Pessoa nao encontrado!");
		}
			
		else
		{
			fseek(PtrPessoa,pos,0);
			fread(&R,sizeof(TpPessoas),1,PtrPessoa);
			gotoxy(54,10);
			printf("### Dados Encontrados ###");
			gotoxy(54,12);
			printf("ID PESSOA: %d",R.id_pessoa);
			gotoxy(54,13);
			printf("NOME: %s",R.nome);
			gotoxy(54,14);
			printf("TELEFONE: %s",R.fone);
			gotoxy(54,15);
			printf("ENERECO: %s",R.endereco);
			gotoxy(54,17);
			printf("Deseja Alterar (S/N)? ");
			gotoxy(76,17);
			if (toupper(getche())=='S')
			{
				gotoxy(54,19);
				printf("Novo Nome: ");
				fflush(stdin);
				gotoxy(65,19);
				gets(R.nome);
				gotoxy(54,20);
				printf("Novo Telefone: ");
				fflush(stdin);
				gotoxy(69,20);
				gets(R.fone);
				gotoxy(54,21);
				printf("Novo Endereco: ");
				fflush(stdin);
				gotoxy(69,21);
				gets(R.endereco);
				
				fseek(PtrPessoa,pos,0);
				fwrite(&R,sizeof(TpPessoas),1,PtrPessoa);
				LimpaMensagem();
				gotoxy(54,23);
				printf("Dados Atualizados com sucesso!");
				
				fseek(PtrPessoa,pos,0);
				fread(&R,sizeof(TpPessoas),1,PtrPessoa);
				LimpaMensagem();
				LimpaExibe();
				gotoxy(68,6);
				printf("### Dados Atualizados ###");
				gotoxy(54,8);
				printf("ID PESSOA: %d",R.id_pessoa);
				gotoxy(54,9);
				printf("NOME: %s",R.nome);
				gotoxy(54,10);
				printf("TELEFONE: %s",R.fone);
				gotoxy(54,11);
				printf("ENERECO: %s",R.endereco);
			}
		}
		LimpaMensagem();
		LimpaExibe();
		gotoxy(68,6);
		printf("## Alterar pelo ID PESSOA ##");
		gotoxy(54,8);
		printf("ID a alterar(0-SAIR): ");
		gotoxy(80,8);
		scanf("%d",&R.id_pessoa);
	}
	fclose(PtrPessoa);
}

void AlterarEmprestimo()
{
    FILE *PtrEmprestimo = fopen("Emprestimos.dat", "rb+");
    FILE *PtrLivro = fopen("Livros.dat", "rb");
    FILE *PtrPessoa = fopen("Pessoas.dat", "rb");
    TpEmprestimos R;
    TpLivros livro;
    TpPessoas pessoa;
    int pos;
    LimpaMensagem();
	LimpaExibe();
	gotoxy(68,6);
    printf("## Alterar Emprestimo pelo ID ##");
    gotoxy(54,8);
    printf("ID a alterar (0 para SAIR): ");
    gotoxy(82,8);
    scanf("%d", &R.id_emprestimo);

    while (R.id_emprestimo != 0)
    {
        pos = BuscaEmprestimo(PtrEmprestimo, R.id_emprestimo);
        if (pos == -1)
        {
        	LimpaMensagem();
        	gotoxy(13,28);
            printf("ID Emprestimo nao encontrado!");
        }
        else
        {
            int continuar = 1; // Controle para retornar ao início em caso de erro
            while (continuar)
            {
                fseek(PtrEmprestimo, pos, SEEK_SET);
                fread(&R, sizeof(TpEmprestimos), 1, PtrEmprestimo);

                // Buscar dados do livro vinculado
                int posLivro = BuscaLivro(PtrLivro, R.id_livro);
                if (posLivro != -1)
                {
                    fseek(PtrLivro, posLivro, SEEK_SET);
                    fread(&livro, sizeof(TpLivros), 1, PtrLivro);
                }

                // Buscar dados da pessoa vinculada
                int posPessoa = BuscaPessoa(PtrPessoa, R.id_pessoa);
                if (posPessoa != -1)
                {
                    fseek(PtrPessoa, posPessoa, SEEK_SET);
                    fread(&pessoa, sizeof(TpPessoas), 1, PtrPessoa);
                }

                // Exibir dados do emprestimo atual
                gotoxy(54,10);
                printf("### Detalhes do Emprestimo Atual ###");
                gotoxy(54,12);
                printf("ID Emprestimo: %d", R.id_emprestimo);
                gotoxy(54,13);
                printf("ID Livro: %d - Titulo: %s", livro.id_livro, livro.titulo);
                gotoxy(54,14);
                printf("ID Pessoa: %d - Nome: %s", pessoa.id_pessoa, pessoa.nome);
                gotoxy(54,15);
                printf("Data de Emprestimo: %s\n", R.data_emprestimo);
                gotoxy(54,16);
                printf("Data de Devolucao: %s\n", R.data_devolucao);

                // Perguntar se deseja alterar
                gotoxy(54,17);
                printf("Deseja Alterar (S/N)? ");
                gotoxy(80,17);
                if (toupper(getche()) == 'S')
                {
                    // Alterar ID do livro
                    int novoIdLivro;
                    gotoxy(54,19);
                    printf("Digite o novo ID do Livro (0 para manter): ");
                    gotoxy(97,19);
                    scanf("%d", &novoIdLivro);

                    if (novoIdLivro != 0)
                    {
                        int posNovoLivro = BuscaLivro(PtrLivro, novoIdLivro);
                        if (posNovoLivro == -1)
                        {
                        	LimpaMensagem();
                        	gotoxy(13,28);
                            printf("ID do Livro nao encontrado! Tente novamente.");
                            continue; // Retorna ao início do loop interno
                        }
                        else
                        {
                            R.id_livro = novoIdLivro;
                            fseek(PtrLivro, posNovoLivro, SEEK_SET);
                            fread(&livro, sizeof(TpLivros), 1, PtrLivro);
                        }
                    }

                    // Alterar datas de emprestimo e devolucao
                    int dia1, mes1, ano1, dia2, mes2, ano2;
                    int dataValida = 0;

                    while (!dataValida)
                    {
                    	gotoxy(54,20);
                        printf("Digite a Nova Data de Emprestimo (dd/mm/aaaa): ");
                        gotoxy(101,20);
                        scanf("%d/%d/%d", &dia1, &mes1, &ano1);

                        if (dia1 < 1 || dia1 > 31 || mes1 < 1 || mes1 > 12 || ano1 < 1900)
                        {
                        	LimpaMensagem();
                        	gotoxy(13,28);
                            printf("Data de Emprestimo invalida. Tente novamente.");
						}
                        else
                            dataValida = 1;
                    }

                    dataValida = 0;
                    while (!dataValida)
                    {
                    	gotoxy(54,21);
                        printf("Digite a Nova Data de Devolucao (dd/mm/aaaa): ");
                        gotoxy(103,21);
                        scanf("%d/%d/%d", &dia2, &mes2, &ano2);

                        if (dia2 < 1 || dia2 > 31 || mes2 < 1 || mes2 > 12 || ano2 < 1900)
                        {
                        	LimpaMensagem();
                        	gotoxy(13,28);
                        	printf("Data de Devolucao invalida. Tente novamente.");
						}
                            
                        else if (ano2 < ano1 || (ano2 == ano1 && mes2 < mes1) || (ano2 == ano1 && mes2 == mes1 && dia2 < dia1))
                        {
                        	LimpaMensagem();
                        	gotoxy(13,28);
                        	printf("A data de devolucao nao pode ser anterior ao emprestimo. Tente novamente.");
						}
                            
                        else
                            dataValida = 1;
                    }

                    sprintf(R.data_emprestimo, "%02d/%02d/%04d", dia1, mes1, ano1);
                    sprintf(R.data_devolucao, "%02d/%02d/%04d", dia2, mes2, ano2);

                    // Salvar alteracoes no arquivo de emprestimos
                    fseek(PtrEmprestimo, pos, SEEK_SET);
                    fwrite(&R, sizeof(TpEmprestimos), 1, PtrEmprestimo);

                    // Exibir dados atualizados
                    LimpaMensagem();
					LimpaExibe();
					gotoxy(68,6);
                    printf("### Emprestimo Atualizado com Sucesso ###");
                    gotoxy(54,8);
                    printf("ID Emprestimo: %d", R.id_emprestimo);
                    gotoxy(54,10);
                    printf("ID Livro: %d - Titulo: %s", livro.id_livro, livro.titulo);
                    gotoxy(54,11);
                    printf("ID Pessoa: %d - Nome: %s", pessoa.id_pessoa, pessoa.nome);
                    gotoxy(54,12);
                    printf("Data de Emprestimo: %s\n", R.data_emprestimo);
                    gotoxy(54,13);
                    printf("Data de Devolucao: %s\n", R.data_devolucao);

                    continuar = 0; // Sai do loop interno após a alteração bem-sucedida
                }
                else
                {
                    continuar = 0; // Sai do loop interno se o usuário não quiser alterar
                }
            }
        }

        gotoxy(68,6);
	    printf("## Alterar Emprestimo pelo ID ##");
	    gotoxy(54,8);
	    printf("ID a alterar (0 para SAIR): ");
	    gotoxy(82,8);
	    scanf("%d", &R.id_emprestimo);
    }

    fclose(PtrEmprestimo);
    fclose(PtrLivro);
    fclose(PtrPessoa);
	LimpaMensagem();
	gotoxy(13,28);
    printf("Alteracoes encerradas!");
}

void ExcluirLogicaLivros(void)
{
	FILE *PtrLivro = fopen("Livros.dat","rb+");
	TpLivros R;
	int pos;
	LimpaMensagem();
	LimpaExibe();
	gotoxy(68,6);
	printf("### EXCLUIR PELO ID LIVRO ###");
	gotoxy(54,8);
	printf("ID LIVRO a excluir (0-SAIR): ");
	gotoxy(83,8);
	scanf("%d",&R.id_livro);
	while(R.id_livro != 0)
	{
		pos = BuscaLivro(PtrLivro,R.id_livro);
		if(pos == -1)
		{
			LimpaMensagem();
			gotoxy(13,28);
			printf("ID Livro nao encontrado!");
		}
		else
		{
			fseek(PtrLivro,pos,0);
			fread(&R,sizeof(TpLivros),1,PtrLivro);
			gotoxy(54,10);
			printf("*** Dados Encontrados ***");
			gotoxy(54,12);
			printf("ID LIVRO: %d",R.id_livro);
			gotoxy(54,13);
			printf("TITULO: %s",R.titulo);
			gotoxy(54,14);
			printf("ANO DE PUBLICACAO: %d",R.ano_publicacao);
			gotoxy(54,16);
			printf("Confirma Exclusao (S/N)? ");
			gotoxy(79,16);
			if (toupper(getche())=='S')
			{
				R.status = 0;
				fseek(PtrLivro,pos,0);
				fwrite(&R,sizeof(TpLivros),1,PtrLivro);
				gotoxy(54,16);
				printf("Registro excluido!");
			}
		}
		
		LimpaMensagem();
		LimpaExibe();
		gotoxy(68,6);
		printf("### EXCLUIR PELO ID LIVRO ###");
		gotoxy(54,8);
		printf("ID LIVRO a excluir (0-SAIR): ");
		gotoxy(83,8);
		scanf("%d",&R.id_livro);
	}
	fclose(PtrLivro);
}

void ExcluirLogicaAutores(void)
{
	FILE *PtrAutor = fopen("Autor.dat","rb+");
	TpAutores R;
	int pos;
	LimpaMensagem();
	LimpaExibe();
	gotoxy(68,6);
	printf("### EXCLUIR PELO ID AUTOR ###");
	gotoxy(54,8);
	printf("ID AUTOR a excluir (0-SAIR): ");
	gotoxy(83,8);
	scanf("%d",&R.id_autor);
	while(R.id_autor != 0)
	{
		pos = BuscaAutor(PtrAutor,R.id_autor);
		if(pos == -1)
		{
			LimpaMensagem();
			gotoxy(13,28);
			printf("ID Autor nao encontrado!");
		}
			
		else
		{
			fseek(PtrAutor,pos,0);
			fread(&R,sizeof(TpAutores),1,PtrAutor);
			gotoxy(54,10);
			printf("*** Dados Encontrados ***");
			gotoxy(54,12);
			printf("\nID AUTOR: %d",R.id_autor);
			gotoxy(54,14);
			printf("NOME: %s",R.nome);
			gotoxy(54,15);
			printf("NACIONALIDADE: %d",R.nacionalidade);
			gotoxy(54,16);
			printf("Confirma Exclusao (S/N)? ");
			gotoxy(79,16);
			if (toupper(getche())=='S')
			{
				R.status = 0;
				fseek(PtrAutor,pos,0);
				fwrite(&R,sizeof(TpAutores),1,PtrAutor);
				gotoxy(54,18);
				printf("Registro excluido!");
			}
		}
		
		LimpaMensagem();
		LimpaExibe();
		gotoxy(68,6);
		printf("### EXCLUIR PELO ID AUTOR ###");
		gotoxy(54,8);
		printf("ID AUTOR a excluir (0-SAIR): ");
		gotoxy(83,8);
		scanf("%d",&R.id_autor);
	}
	fclose(PtrAutor);
}

void ExcluirLogicaPessoas(void)
{
	FILE *PtrPessoa = fopen("Pessoas.dat","rb+");
	TpPessoas R;
	int pos;
	LimpaMensagem();
	LimpaExibe();
	gotoxy(68,6);
	printf("## EXCLUIR PELO ID PESSOA ###");
	gotoxy(54,8);
	printf("ID PESSOA a excluir (0-SAIR): ");
	gotoxy(84,8);
	scanf("%d",&R.id_pessoa);
	while(R.id_pessoa != 0)
	{
		pos = BuscaPessoa(PtrPessoa,R.id_pessoa);
		if(pos == -1)
		{
			LimpaMensagem();
			gotoxy(13,28);
			printf("ID Pessoa nao encontrado!");
		}
			
		else
		{
			fseek(PtrPessoa,pos,0);
			fread(&R,sizeof(TpPessoas),1,PtrPessoa);
			gotoxy(54,10);
			printf("*** Dados Encontrados ***");
			gotoxy(54,12);
			printf("ID PESSOA: %d",R.id_pessoa);
			gotoxy(54,13);
			printf("NOME: %s",R.nome);
			gotoxy(54,14);
			printf("TELEFONE: %s",R.fone);
			gotoxy(54,15);
			printf("ENDERECO: %s",R.endereco);
			gotoxy(54,16);
			printf("Confirma Exclusao (S/N)? ");
			gotoxy(79,17);
			if (toupper(getche())=='S')
			{
				R.status = 0;
				fseek(PtrPessoa,pos,0);
				fwrite(&R,sizeof(TpPessoas),1,PtrPessoa);
				gotoxy(54,17);
				printf("Registro excluido!");
			}
		}
		
		LimpaMensagem();
		LimpaExibe();
		gotoxy(68,6);
		printf("## EXCLUIR PELO ID PESSOA ###");
		gotoxy(54,8);
		printf("ID PESSOA a excluir (0-SAIR): ");
		gotoxy(84,8);
		scanf("%d",&R.id_pessoa);
	}
	fclose(PtrPessoa);
}

void ExcluirLogicaEmprestimo(void)
{
	FILE *PtrEmprestimo = fopen("Emprestimos.dat","rb+");
	TpEmprestimos R;
	int pos;
	LimpaMensagem();
	LimpaExibe();
	gotoxy(68,6);
	printf("### EXCLUIR PELO ID EMPRESTIMO ###");
	gotoxy(54,8);
	printf("ID EMPRESTIMO a excluir (0-SAIR): ");
	gotoxy(88,8);
	scanf("%d",&R.id_emprestimo);
	while(R.id_emprestimo != 0)
	{
		pos = BuscaEmprestimo(PtrEmprestimo,R.id_emprestimo);
		if(pos == -1)
		{
			LimpaMensagem();
			gotoxy(13,28);
			printf("ID Emprestimo nao encontrado!");
		}		
			
		else
		{
			fseek(PtrEmprestimo,pos,0);
			fread(&R,sizeof(TpEmprestimos),1,PtrEmprestimo);
			gotoxy(54,10);
			printf("*** Dados Encontrados ***");
			gotoxy(54,12);
			printf("ID EMPRESTIMO: %d",R.id_emprestimo);
			gotoxy(54,13);
			printf("ID LIVRO: %d",R.id_livro);
			gotoxy(54,14);
			printf("ID PESSOA: %d",R.id_pessoa);
			gotoxy(54,15);
			printf("DATA EMPRESTIMO: %s",R.data_emprestimo);
			gotoxy(54,16);
			printf("DATA DEVOLUCAO: %s",R.data_devolucao);
			gotoxy(54,17);
			printf("Confirma Exclusao (S/N)? ");
			gotoxy(79,17);
			if (toupper(getche())=='S')
			{
				R.status = 0;
				fseek(PtrEmprestimo,pos,0);
				fwrite(&R,sizeof(TpEmprestimos),1,PtrEmprestimo);
				gotoxy(54,18);
				printf("Registro excluido!");
			}
		}
		
		LimpaMensagem();
		LimpaExibe();
		gotoxy(68,6);
		printf("### EXCLUIR PELO ID EMPRESTIMO ###");
		gotoxy(54,8);
		printf("ID EMPRESTIMO a excluir (0-SAIR): ");
		gotoxy(88,8);
		scanf("%d",&R.id_emprestimo);
	}
	fclose(PtrEmprestimo);
}

void ExclusaoFisicaTODOS(void) //EXCLUI FISICAMENTE TODAS AS EXCLUSOES LOGICA
{
	TpLivros livro;
	TpAutores autor;
	TpPessoas pessoa;
	TpEmprestimos emprestimo;
	
	
	FILE *PtrLivro = fopen("Livros.dat","rb");
	FILE *PtrAutor = fopen("Autor.dat","rb");
	FILE *PtrPessoa = fopen("Pessoas.dat","rb");
	FILE *PtrEmprestimo = fopen("Emprestimos.dat","rb");		
	
	
	FILE *PtrTemp = fopen("Temp.dat","wb");
	FILE *PtrTemp2 = fopen("Temp2.dat","wb");
	FILE *PtrTemp3 = fopen("Temp3.dat","wb");
	FILE *PtrTemp4 = fopen("Temp4.dat","wb");
	
	
	fread(&livro,sizeof(TpLivros),1,PtrLivro);
	fread(&autor,sizeof(TpAutores),1,PtrAutor);
	fread(&pessoa,sizeof(TpPessoas),1,PtrPessoa);
	fread(&emprestimo,sizeof(TpEmprestimos),1,PtrEmprestimo);
	// Processar cada arquivo individualmente
    while (fread(&livro, sizeof(TpLivros), 1, PtrLivro))
    {
        if (livro.status)
            fwrite(&livro, sizeof(TpLivros), 1, PtrTemp);
    }

    while (fread(&autor, sizeof(TpAutores), 1, PtrAutor))
    {
        if (autor.status)
            fwrite(&autor, sizeof(TpAutores), 1, PtrTemp2);
    }

    while (fread(&pessoa, sizeof(TpPessoas), 1, PtrPessoa))
    {
        if (pessoa.status)
            fwrite(&pessoa, sizeof(TpPessoas), 1, PtrTemp3);
    }

    while (fread(&emprestimo, sizeof(TpEmprestimos), 1, PtrEmprestimo))
    {
        if (emprestimo.status)
            fwrite(&emprestimo, sizeof(TpEmprestimos), 1, PtrTemp4);
    }

    // Fechar todos os arquivos abertos
    fclose(PtrLivro); fclose(PtrAutor); fclose(PtrPessoa); fclose(PtrEmprestimo);
    fclose(PtrTemp); fclose(PtrTemp2); fclose(PtrTemp3); fclose(PtrTemp4);

    remove("Livros.dat"); rename("Temp.dat", "Livros.dat");
    remove("Autor.dat"); rename("Temp2.dat", "Autor.dat");
    remove("Pessoas.dat"); rename("Temp3.dat", "Pessoas.dat");
    remove("Emprestimos.dat"); rename("Temp4.dat", "Emprestimos.dat");
}

void ConsultarAutorLetra(void)
{
    FILE *PtrAutor = fopen("Autor.dat", "rb");
    TpAutores R;
    char letra;
    int encontrou = 0;  // Variável para verificar se encontrou pelo menos um autor

    clrscr();
    printf("\n### CONSULTAR AUTORES PELO NOME INICIADO POR UMA LETRA ###\n");
    
    // Solicita ao usuário a letra inicial do nome do autor
    printf("\nDigite a letra inicial do nome do autor: ");
    letra = getche();  // Lê o caractere digitado
    letra = toupper(letra);  // Converte para maiúscula para evitar problemas com maiúsculas/minúsculas

    // Verifica se a letra é válida
    if (letra < 'A' || letra > 'Z') {
        clrscr();
        printf("\nLetra invalida! Por favor, digite uma letra de A a Z.\n");
        getch();
    } else {
        // Percorre o arquivo de autores
        rewind(PtrAutor);  // Reposiciona o ponteiro do arquivo no início
        while (fread(&R, sizeof(TpAutores), 1, PtrAutor)) {
            // Verifica se o autor está ativo e o nome começa com a letra fornecida
            if (R.status && toupper(R.nome[0]) == letra) {
                if (!encontrou)
				{
                    clrscr();
                    printf("\n### RELATORIO DE AUTORES ###\n\n");
                    encontrou = 1;  // Indica que encontrou pelo menos um autor
                }
                // Exibe as informações do autor
                printf("\nID Autor: %d", R.id_autor);
                printf("\nNome: %s", R.nome);
                printf("\nNacionalidade: %s", R.nacionalidade);
                printf("\n----------------------------\n");
            }
        }
        // Se não encontrou nenhum autor, exibe uma mensagem
        if (!encontrou) 
            printf("\nNenhum autor encontrado com a letra '%c'.\n", letra);
            
        getch();
    }
    fclose(PtrAutor);
}
// Função para comparar se a palavra está no título do livro
int ComparaPalavraNoTitulo(const char *titulo, const char *palavra) {
    int tamanhoTitulo = strlen(titulo);
    int tamanhoPalavra = strlen(palavra);

    // Percorre o título tentando encontrar a palavra em qualquer posição
    for (int i = 0; i <= tamanhoTitulo - tamanhoPalavra; i++) {
        // Compara cada substring do título com a palavra
        int j = 0;
        while (j < tamanhoPalavra && tolower(titulo[i + j]) == tolower(palavra[j])) {
            j++;
        }
        
        // Se a palavra inteira foi encontrada
        if (j == tamanhoPalavra) {
            return 1;  // Palavra encontrada no título
        }
    }
    return 0;  // Palavra não encontrada no título
}

void ConsultarLivroPalavra(void)
{
    FILE *PtrLivro = fopen("Livros.dat", "rb");
    FILE *PtrLivroAutor = fopen("AutorLivro.dat", "rb");
    FILE *PtrAutor = fopen("Autor.dat", "rb");
    TpLivros livro;
    TpLivroAutor vinculo;
    TpAutores autor;
    char palavra[50];
    int encontrou = 0;  // Variável de controle para indicar se encontrou algum livro

    clrscr();
    printf("\n### CONSULTAR LIVROS PELO TÍTULO (PALAVRA) ###\n");
    
    // Solicita ao usuário a palavra para pesquisar no título
    printf("\nDigite uma palavra para pesquisar no título dos livros: ");
    fflush(stdin);  // Limpa o buffer de entrada
    gets(palavra);  // Lê a palavra digitada

    // Converte a palavra para minúscula para evitar problemas com maiúsculas/minúsculas
    for (int i = 0; palavra[i]; i++) {
        palavra[i] = tolower(palavra[i]);
    }

    // Percorre o arquivo de livros
    rewind(PtrLivro);  // Reposiciona o ponteiro do arquivo no início
    while (fread(&livro, sizeof(TpLivros), 1, PtrLivro)) {
        // Verifica se o livro está ativo e se o título contém a palavra digitada
        if (livro.status && ComparaPalavraNoTitulo(livro.titulo, palavra)) {
            // Se for o primeiro livro encontrado, prepara o cabeçalho
            if (!encontrou) {
                clrscr();
                printf("\n### RELATÓRIO DE LIVROS ENCONTRADOS ###\n\n");
                encontrou = 1;  // Indica que encontrou pelo menos um livro
            }
            
            // Exibe as informações do livro
            printf("\nID Livro: %d", livro.id_livro);
            printf("\nTítulo: %s", livro.titulo);
            printf("\nAno de Publicação: %d", livro.ano_publicacao);
            printf("\n----------------------------\n");

            // Exibe os autores vinculados ao livro
            printf("\n### Autores Vinculados ###\n");
            rewind(PtrLivroAutor);  // Reposiciona o ponteiro do arquivo de vínculos no início
            while (fread(&vinculo, sizeof(TpLivroAutor), 1, PtrLivroAutor)) {
                if (vinculo.id_livro == livro.id_livro && vinculo.status) {
                    int posAutor = BuscaAutor(PtrAutor, vinculo.id_autor);
                    if (posAutor != -1) {
                        fseek(PtrAutor, posAutor, SEEK_SET);
                        fread(&autor, sizeof(TpAutores), 1, PtrAutor);
                        // Exibe as informações do autor
                        printf("\nID Autor: %d", autor.id_autor);
                        printf("\nNome: %s", autor.nome);
                        printf("\nNacionalidade: %s", autor.nacionalidade);
                        printf("\n----------------------------\n");
                    }
                }
            }
        }
    }

    // Se não encontrou nenhum livro, exibe uma mensagem
    if (!encontrou)
        printf("\nNenhum livro encontrado com a palavra '%s'.\n", palavra);
    
    getch();
    fclose(PtrLivro);
    fclose(PtrLivroAutor);
    fclose(PtrAutor);
}

int main (void)
{
	char opcao;
	CriaArquivos();
	PainelPrincipal();
	do
	{	
		LimpaMenu();
		opcao = Menu1();
		switch(opcao)
		{
			case 'A':
				do
				{
					LimpaMenu();
					opcao = Menu2();
					switch(opcao)
					{
						
						case 'A':
							
							do
							{
								LimpaMenu();
								opcao = MenuCadastro();
								switch(opcao)
								{
									case 'A':
										//PainelPrincipal();
										GravarLivro();
										break;
										
									case 'B':
										//PainelPrincipal();
										GravarAutor();
										break;
										
									case 'C':
										//PainelPrincipal();
										GravarPessoa();
										break;
										
									case 'D':
										//PainelPrincipal();
										GravarLivroAutor();
										break;
										
									case 'E':
										//PainelPrincipal();
										GravarEmprestimo();
										break;
								}
								
							}while(opcao != 13);
							
							break;
		
			            case 'B':
			            	
			            	do
							{
								LimpaMenu();
								opcao = MenuConsulta();
								switch(opcao)
								{
									case 'A':
										
										ConsultarLivro();
										break;
										
									case 'B':
										
										ConsultarAutor();
										break;
										
									case 'C':
										
										ConsultarPessoa();
										break;
									
									case 'D':
										
										ConsultarLivroAutor();
										break;
										
									case 'E':
										
										ConsultarEmprestimo();
										break;
								}
								
							}while(opcao != 13);
							
							break;
							
			            case 'C':
			            	
			            	do
							{
								LimpaMenu();
								opcao = MenuAlterar();
								switch(opcao)
								{
									case 'A':
										
										AlterarLivro();
										break;
										
									case 'B':
										
										AlterarAutor();
										break;
										
									case 'C':
										
										AlterarPessoa();
										break;
										
									case 'D':
										
										AlterarEmprestimo();
										break;
								}
								
							}while(opcao != 13);
							
							break;

			            case 'D':
			            	
			            	do
							{
								LimpaMenu();
								opcao = MenuExcluir();
								switch(opcao)
								{
									case 'A':
										
										ExcluirLogicaLivros();
										break;
										
									case 'B':
										
										ExcluirLogicaAutores();
										break;
										
									case 'C':
										
										ExcluirLogicaPessoas();
										break;
										
									case 'D':
										
										ExcluirLogicaEmprestimo();
										break;
								}
								
							}while(opcao != 13);
							
							break;
							
			            case 'E':
			            	
			            	do
							{
								LimpaMenu();
								opcao = MenuExibir();
								switch(opcao)
								{
									case 'A':
										
										ExibirLivro();
										break;
										
									case 'B':
										
										ExibirAutor();
										break;
										
									case 'C':
										
										ExibirPessoa();
										break;
									
									case 'D':
										
										ExibirLivroAutor();
										break;
										
									case 'E':
										
										ExibirEmprestimo();
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
					LimpaMenu();
					opcao = Menu3();
					switch(opcao)
					{
						case 'A':
							
							ConsultarAutorLetra();
							break;
							
						case 'B':
							
							ConsultarLivroPalavra();
							break;
							
						case 'C':
							
							ConsultarEmprestimo();
							break;
						
						case 'D':
							
							ConsultarLivroAutor();
							break;
						
						case 'E':
							
							ExibirEmprestimo();
							break;
					}
				}while(opcao != 9);
				
				break;
		}
	}while(opcao != 27);
	ExclusaoFisicaTODOS();
	return 0;
}
