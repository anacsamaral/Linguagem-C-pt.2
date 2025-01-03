#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>

// ### Tamanhos físicos ###

// Livro
#define TFTitulo 101

// Autor
#define TFNomeAutor 101
#define TFNacionalidade 31

// Pessoa
#define TFNomePessoa 101
#define TFTelefonePessoa 31
#define TFEnderecoPessoa 101

// ### Structs ###

struct livro {
	int id_livro, ano_publicacao, status;
	char titulo[TFTitulo];
};

struct autor {
	int id_autor;
	char nome[TFNomeAutor], nacionalidade[TFNacionalidade], status;
};

struct data {
	int dia, mes, ano;
};

struct emprestimo {
	int id_emprestimo, id_livro, id_pessoa, status;
	struct data data_emprestimo, data_devolucao;
};

struct pessoa {
	int id_pessoa, status;
	char nome[TFNomePessoa], telefone[TFTelefonePessoa], endereco[TFEnderecoPessoa];
};

struct livAut {
	int id_livro, id_autor, status;
};

// ### Funções gerais ###

void meuScanfInt(int &num) {
	fflush(stdin);
	scanf("%d", &num);
}

void meuScanfFloat(float &num) {
	fflush(stdin);
	scanf("%f", &num);
}

void limpar(char string[]) { // Limpa espaços desnecessários de uma string
	int pos, posAux = 0, podeRegistrar = 0;
	char stringAux[101];
	for (pos = 0; pos < strlen(string); pos++) {
		if (string[pos] != ' ' || podeRegistrar == 1) {
			stringAux[posAux] = string[pos];
			posAux++;
			if (string[pos + 1] == ' ') {
				podeRegistrar = 1;
			}
		}
		if (string[pos] == ' ' && podeRegistrar == 1) {
			podeRegistrar = 0;
		}
	}
	if (stringAux[posAux] == ' ')
		posAux--;
	stringAux[posAux] = '\0';
	strcpy(string, stringAux);
}

void meuGets(char string[]) {
	fflush(stdin);
	gets(string);
	limpar(string);
}

void desenharMoldura(void) {
	int posX = 1, posY = 1;
	textcolor(CYAN);
	gotoxy(posX, 1);
	printf("%c", 201);
	gotoxy(posX, 25);
	printf("%c", 200);
	for (posX = 2; posX < 80; posX++) {
		gotoxy(posX, 1);
		printf("%c", 205);
		gotoxy(posX, 25);
		printf("%c", 205);
	}
	gotoxy(posX, 1);
	printf("%c", 187);
	gotoxy(posX, 25);
	printf("%c", 188);
	for (posY = 2; posY < 25; posY++) {
		gotoxy(1, posY);
		printf("%c", 186);
		gotoxy(80, posY);
		printf("%c", 186);
	}
	gotoxy(1, 5);
	printf("%c", 204);
	gotoxy(1, 23);
	printf("%c", 204);
	for (posX = 2; posX < 80; posX++) {
		gotoxy(posX, 5);
		printf("%c", 205);
		gotoxy(posX, 23);
		printf("%c", 205);
	}
	gotoxy(80, 5);
	printf("%c", 185);
	gotoxy(80, 23);
	printf("%c", 185);
	textcolor(WHITE);
}

void tituloDoPrograma(void) {
	char titulo[75];
	int tamanhoTitulo, posX;
	strcpy(titulo, "##### Sistema de gerenciamento de biblioteca #####");
	tamanhoTitulo = strlen(titulo);
	posX = 41 - tamanhoTitulo / 2; // Obtém a posição para centralizar o título
	gotoxy(posX, 3);
	printf("%s", titulo);
}

void desenharJanela(void) {
	desenharMoldura();
	tituloDoPrograma();
}

void primeiraLinha(int &posX, int &posY) {
	posX = 3;
	posY = 7;
	gotoxy(posX, posY);
}

void pularLinha(int &posX, int &posY) {
	posX = 3;
	posY++;
	gotoxy(posX, posY);
}

void limparLinha(int posY) {
	for (int posX = 2; posX < 80; posX++) {
		gotoxy(posX, posY);
		printf("%c", 32);
	}
	gotoxy(3, posY);
}

void limparTela(int &posX, int &posY) {
	for (posY = 6; posY < 23; posY++)
		for (posX = 2; posX < 80; posX++) {
			gotoxy(posX, posY);
			printf("%c", 32);
		}
}

void posMsg(int cor) {
	gotoxy(2, 24);
	for (int posX = 2; posX < 80; posX++)
		printf("%c", 32);
	gotoxy(3, 24);
	textcolor(cor);
}

void erroAbertura(void) {
	posMsg(LIGHTRED);
	printf("Erro de abertura");
	textcolor(WHITE);
	getch();
}

// ### Funções de busca (Separadas para aumentar o alcance) ###

int buscarLivro(FILE *PtrLivro, int id_livro) {
	struct livro livroAux;
	rewind(PtrLivro);
	fread(&livroAux, sizeof(livro), 1, PtrLivro);
	while(!feof(PtrLivro) && !(id_livro == livroAux.id_livro && livroAux.status == 1)) {
		fread(&livroAux, sizeof(livro), 1, PtrLivro);
	}
	if (id_livro == livroAux.id_livro && livroAux.status == 1) {
		return ftell(PtrLivro) - sizeof(livro);
	}
	else return -1;
}

int buscaBinariaLivro(FILE *PtrLivro, int id_livro) {
	int inicio, meio, fim;
	struct livro livroAux;
	rewind(PtrLivro);
	inicio = ftell(PtrLivro) / sizeof(livro);
	fseek(PtrLivro, 0, SEEK_END);
	fim = ftell(PtrLivro) / sizeof(livro);
	
//	meio = fim / 2;
//	fseek(PtrLivro, meio * sizeof(livro), SEEK_SET);
//	fread(&livroAux, sizeof(PtrLivro), 1, PtrLivro);
//	while (inicio < fim && !(livroAux.id_livro == id_livro && livroAux.status == 1)) {
//		if (livroAux.id_livro < id_livro)
//			inicio = meio + 1;
//		else fim = meio;
//		meio = (inicio + fim) / 2;
//		fseek(PtrLivro, meio * sizeof(livro), SEEK_SET);
//		fread(&livroAux, sizeof(livro), 1, PtrLivro);
//	}
	
	do {
		meio = (inicio + fim) / 2;
		fseek(PtrLivro, meio * sizeof(livro), SEEK_SET);
		fread(&livroAux, sizeof(livro), 1, PtrLivro);
		if (!(livroAux.id_livro == id_livro && livroAux.status == 1)) {
			if (livroAux.id_livro < id_livro)
				inicio = meio + 1;
			else fim = meio;
		}
	} while (inicio < fim && !(livroAux.id_livro == id_livro && livroAux.status == 1));
	
	if (livroAux.id_livro == id_livro && livroAux.status == 1)
		return meio * sizeof(livro);
	else return -1;
}

int buscarAutor(FILE *PtrAutor, int id_autor) {
	struct autor autorAux;
	rewind(PtrAutor);
	fread(&autorAux, sizeof(autor), 1, PtrAutor);
	while(!feof(PtrAutor) && !(id_autor == autorAux.id_autor && autorAux.status == 1)) {
		fread(&autorAux, sizeof(autor), 1, PtrAutor);
	}
	if (id_autor == autorAux.id_autor && autorAux.status == 1) {
		return ftell(PtrAutor) - sizeof(autor);
	}
	else return -1;
}

int buscarPessoa(FILE *PtrPessoa, int id_pessoa) {
	struct pessoa pessoaAux;
	rewind(PtrPessoa);
	fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
	while (!feof(PtrPessoa) && !(pessoaAux.id_pessoa == id_pessoa && pessoaAux.status == 1))
		fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
	if (id_pessoa == pessoaAux.id_pessoa && pessoaAux.status == 1)
		return ftell(PtrPessoa) - sizeof(pessoa);
	else return -1;
}

int buscarEmprestimo(FILE *PtrEmprestimo, int id_emprestimo) {
	struct emprestimo emprestimoAux;
	rewind(PtrEmprestimo);
	fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
	while (!feof(PtrEmprestimo) && !(emprestimoAux.id_emprestimo == id_emprestimo && emprestimoAux.status == 1))
		fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
	if (emprestimoAux.id_emprestimo == id_emprestimo && emprestimoAux.status == 1)
		return ftell(PtrEmprestimo) - sizeof(emprestimo);
	else return -1;
}

int buscarLivAut(FILE *PtrLivAut, int id_livro, int id_autor) {
	struct livAut livAutAux;
	rewind(PtrLivAut);
	fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	while (!feof(PtrLivAut) && !(livAutAux.id_livro == id_livro && livAutAux.id_autor == id_autor && livAutAux.status == 1))
		fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	if (livAutAux.id_livro == id_livro && livAutAux.id_autor == id_autor && livAutAux.status == 1)
		return ftell(PtrLivAut) - sizeof(livAut);
	else return -1;
}

int buscarLivroEmprestimo(FILE *PtrEmprestimo, int id_livro) { // Buscar livro em emprestimos
	struct emprestimo emprestimoAux;
	rewind(PtrEmprestimo);
	fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
	while (!feof(PtrEmprestimo) && !(emprestimoAux.id_livro == id_livro && emprestimoAux.status == 1))
		fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
	if (emprestimoAux.id_livro == id_livro && emprestimoAux.status == 1)
		return ftell(PtrEmprestimo) - sizeof(emprestimo);
	else return -1;
}

int buscarPessoaEmprestimo(FILE *PtrEmprestimo, int id_pessoa) { // Buscar pessoa em emprestimos
	struct emprestimo emprestimoAux;
	rewind(PtrEmprestimo);
	fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
	while (!feof(PtrEmprestimo) && !(emprestimoAux.id_pessoa == id_pessoa && emprestimoAux.status == 1))
		fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
	if (emprestimoAux.id_pessoa == id_pessoa && emprestimoAux.status == 1)
		return ftell(PtrEmprestimo) - sizeof(emprestimo);
	else return -1;
}

int buscarLivroLivAut(FILE *PtrLivAut, int id_livro) { // Buscar livro em livro-autor
	struct livAut livAutAux;
	rewind(PtrLivAut);
	fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	while (!feof(PtrLivAut) && !(livAutAux.id_livro == id_livro && livAutAux.status == 1))
		fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	if (livAutAux.id_livro == id_livro && livAutAux.status == 1)
		return ftell(PtrLivAut) - sizeof(livAut);
	else return -1;
}

int buscarLivroLivAutPos(FILE *PtrLivAut, int id_livro, int pos) { // Buscar livro em livro-autor A PARTIR DE UMA POSIÇÃO
	struct livAut livAutAux;
	fseek(PtrLivAut, pos, SEEK_SET);
	fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	while (!feof(PtrLivAut) && !(livAutAux.id_livro == id_livro && livAutAux.status == 1))
		fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	if (livAutAux.id_livro == id_livro && livAutAux.status == 1)
		return ftell(PtrLivAut) - sizeof(livAut);
	else return -1;
}

int buscarAutorLivAut(FILE *PtrLivAut, int id_autor) { // Buscar autor em livro-autor
	struct livAut livAutAux;
	rewind(PtrLivAut);
	fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	while (!feof(PtrLivAut) && !(livAutAux.id_autor == id_autor && livAutAux.status == 1))
		fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	if (livAutAux.id_autor == id_autor && livAutAux.status == 1)
		return ftell(PtrLivAut) - sizeof(livAut);
	else return -1;
}

int buscarAutorLivAutPos(FILE *PtrLivAut, int id_autor, int pos) { // Buscar autor em livro-autor A PARTIR DE UMA POSIÇÃO
	struct livAut livAutAux;
	fseek(PtrLivAut, pos, SEEK_SET);
	fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	while (!feof(PtrLivAut) && !(livAutAux.id_autor == id_autor && livAutAux.status == 1))
		fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	if (livAutAux.id_autor == id_autor && livAutAux.status == 1)
		return ftell(PtrLivAut) - sizeof(livAut);
	else return -1;
}

int buscarPalavraTitulo(char titulo[TFTitulo], char palavra[TFTitulo]) { // Buscar uma palavra em um titulo (separação por espaços)
	int pos, posAux = 0, achou = 0, tamanhoTitulo;
	char palavraAux[TFTitulo];
	tamanhoTitulo = strlen(titulo);
	for (pos = 0; pos <= tamanhoTitulo && !achou; pos++) {
		if (titulo[pos] != ' ' && titulo[pos] != '\0') {
			palavraAux[posAux] = titulo[pos];
			posAux++;
		}
		else {
			palavraAux[posAux] = '\0';
			if (stricmp(palavra, palavraAux) == 0) {
				achou = 1;
			}
			else {
				posAux = 0;
			}
		}
	}
	return achou;
}

// ### Gerador de dados para testes ###

void gerarLivros(void) {
	FILE *PtrLivro = fopen("livros.dat", "wb");
	struct livro livroAux;
	livroAux.status = 1;
	
	livroAux.id_livro = 10;
	strcpy(livroAux.titulo, "Livro Dez");
	livroAux.ano_publicacao = 2010;
	fwrite(&livroAux, sizeof(livro), 1, PtrLivro);
	
	livroAux.id_livro = 24;
	strcpy(livroAux.titulo, "Fevereiro");
	livroAux.ano_publicacao = 2006;
	fwrite(&livroAux, sizeof(livro), 1, PtrLivro);
	
	livroAux.id_livro = 30;
	strcpy(livroAux.titulo, "Dom Casmurro");
	livroAux.ano_publicacao = 1899;
	fwrite(&livroAux, sizeof(livro), 1, PtrLivro);
	
	livroAux.id_livro = 40;
	strcpy(livroAux.titulo, "Harry Potter e a Pedra Filosofal");
	livroAux.ano_publicacao = 2000;
	fwrite(&livroAux, sizeof(livro), 1, PtrLivro);
	
	livroAux.id_livro = 50;
	strcpy(livroAux.titulo, "Daniel Esta Com Sono");
	livroAux.ano_publicacao = 2024;
	fwrite(&livroAux, sizeof(livro), 1, PtrLivro);
	
	fclose(PtrLivro);
}

void gerarAutores(void) {
	FILE *PtrAutor = fopen("autores.dat", "wb");
	struct autor autorAux;
	autorAux.status = 1;
	
	autorAux.id_autor = 1;
	strcpy(autorAux.nome, "D. S. Batista");
	strcpy(autorAux.nacionalidade, "Brasileiro");
	fwrite(&autorAux, sizeof(autor), 1, PtrAutor);
	
	autorAux.id_autor = 10;
	strcpy(autorAux.nome, "Autor Dez");
	strcpy(autorAux.nacionalidade, "Dezeniese");
	fwrite(&autorAux, sizeof(autor), 1, PtrAutor);
	
	autorAux.id_autor = 20;
	strcpy(autorAux.nome, "J. K. Rowling");
	strcpy(autorAux.nacionalidade, "Britanica");
	fwrite(&autorAux, sizeof(autor), 1, PtrAutor);
	
	autorAux.id_autor = 30;
	strcpy(autorAux.nome, "Machado de Assis");
	strcpy(autorAux.nacionalidade, "Brasileiro");
	fwrite(&autorAux, sizeof(autor), 1, PtrAutor);
	
	fclose(PtrAutor);
}

void gerarEmprestimos(void) {
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "wb");
	struct emprestimo emprestimoAux;
	emprestimoAux.status = 1;
	
	emprestimoAux.id_emprestimo = 5;
	emprestimoAux.id_livro = 50;
	emprestimoAux.id_pessoa = 6;
	emprestimoAux.data_emprestimo.dia = 6;
	emprestimoAux.data_emprestimo.mes = 5;
	emprestimoAux.data_emprestimo.ano = 2017;
	emprestimoAux.data_devolucao.dia = 13;
	emprestimoAux.data_devolucao.mes = 5;
	emprestimoAux.data_devolucao.ano = 2017;
	fwrite(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
	
	emprestimoAux.id_emprestimo = 10;
	emprestimoAux.id_livro = 10;
	emprestimoAux.id_pessoa = 10;
	emprestimoAux.data_emprestimo.dia = 10;
	emprestimoAux.data_emprestimo.mes = 10;
	emprestimoAux.data_emprestimo.ano = 1010;
	emprestimoAux.data_devolucao.dia = 10;
	emprestimoAux.data_devolucao.mes = 10;
	emprestimoAux.data_devolucao.ano = 2010;
	fwrite(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
	
	fclose(PtrEmprestimo);
}

void gerarPessoas(void) {
	FILE *PtrPessoa = fopen("pessoas.dat", "wb");
	struct pessoa pessoaAux;
	pessoaAux.status = 1;
	
	pessoaAux.id_pessoa = 6;
	strcpy(pessoaAux.nome, "Juliana Salles Batista");
	strcpy(pessoaAux.telefone, "5518123456789");
	strcpy(pessoaAux.endereco, "Rua das Jujubas, 5");
	fwrite(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
	
	pessoaAux.id_pessoa = 10;
	strcpy(pessoaAux.nome, "Pessoa Dez");
	strcpy(pessoaAux.telefone, "5510101010101");
	strcpy(pessoaAux.endereco, "Rua Dez, 10");
	fwrite(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
	
	pessoaAux.id_pessoa = 25;
	strcpy(pessoaAux.nome, "Alguem");
	strcpy(pessoaAux.telefone, "5518987654321");
	strcpy(pessoaAux.endereco, "Avenida Presidente Fulano");
	fwrite(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
	
	fclose(PtrPessoa);
}

void gerarLivAut(void) {
	FILE *PtrLivAut = fopen("livaut.dat", "wb");
	struct livAut livAutAux;
	livAutAux.status = 1;
	
	livAutAux.id_livro = 10;
	livAutAux.id_autor = 10;
	fwrite(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	
	livAutAux.id_livro = 24;
	livAutAux.id_autor = 1;
	fwrite(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	
	livAutAux.id_livro = 30;
	livAutAux.id_autor = 30;
	fwrite(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	
	livAutAux.id_livro = 40;
	livAutAux.id_autor = 20;
	fwrite(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	
	livAutAux.id_livro = 50;
	livAutAux.id_autor = 1;
	fwrite(&livAutAux, sizeof(livAut), 1, PtrLivAut);
	
	fclose(PtrLivAut);
}

void gerarDados(int &posX, int &posY) {
	limparTela(posX, posY);
	posMsg(WHITE);
	printf("Para sair, aperte quaisquer *OUTRAS* teclas");
	primeiraLinha(posX, posY);
	textcolor(YELLOW);
	printf("/!\\ AVISO IMPORTANTE /!\\");
	textcolor(WHITE);
	pularLinha(posX, posY);
	pularLinha(posX, posY);
	printf("Ao gerar novos dados, os ja existentes serao sobreescritos.");
	textcolor(LIGHTRED);
	pularLinha(posX, posY);
	pularLinha(posX, posY);
	printf("NAO SERA POSSIVEL REVERTER ISSO");
	pularLinha(posX, posY);
	pularLinha(posX, posY);
	textcolor(WHITE);
	printf("Pressione as teclas [O] e [K] (nessa sequencia) para confirmar");
	if (toupper(getch()) == 'O') {
		if (toupper(getch()) == 'K') {
			gerarLivros();
			gerarAutores();
			gerarEmprestimos();
			gerarPessoas();
			gerarLivAut();
			posMsg(LIGHTGREEN);
			printf("Dados gerados");
			getch();
		}
	}
}

// ### Livros ###

void ordenarLivros(void) { // Ordenação por ID
	int a, b, qntd;
	struct livro auxA, auxB;
	FILE *PtrLivro = fopen("livros.dat", "rb+");
	if (PtrLivro != NULL) {
		fseek(PtrLivro, 0, SEEK_END);
		qntd = ftell(PtrLivro) / sizeof(livro);
		for (a = 0; a < qntd - 1; a++) {
			for (b = a + 1; b < qntd; b++) {
				fseek(PtrLivro, sizeof(livro) * a, SEEK_SET);
				fread(&auxA, sizeof(livro), 1, PtrLivro);
				fseek(PtrLivro, sizeof(livro) * b, SEEK_SET);
				fread(&auxB, sizeof(livro), 1, PtrLivro);
				if (auxA.id_livro > auxB.id_livro) {
					fseek(PtrLivro, sizeof(livro) * a, SEEK_SET);
					fwrite(&auxB, sizeof(livro), 1, PtrLivro);
					fseek(PtrLivro, sizeof(livro) * b, SEEK_SET);
					fwrite(&auxA, sizeof(livro), 1, PtrLivro);
				}
			}
		}
		fclose(PtrLivro);
	}
}

void insercaoDiretaLivros(FILE *PtrLivro) {
	int pos;
	struct livro auxA, auxB;
	fseek(PtrLivro, 0, SEEK_END);
	pos = ftell(PtrLivro) / sizeof(livro);
	if (pos >= 2) {
		do {
			fseek(PtrLivro, (pos - 2) * sizeof(livro), SEEK_SET);
			fread(&auxA, sizeof(livro), 1, PtrLivro);
			fread(&auxB, sizeof(livro), 1, PtrLivro);
			if (auxA.id_livro > auxB.id_livro) {
				fseek(PtrLivro, (pos - 2) * sizeof(livro), SEEK_SET);
				fwrite(&auxB, sizeof(livro), 1, PtrLivro);
				fwrite(&auxA, sizeof(livro), 1, PtrLivro);
			}
			pos--;
		} while (pos >= 2 && auxA.id_livro > auxB.id_livro);
	}
}

void cadastrarLivro(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct livro livroAux;
	FILE *PtrLivro = fopen("livros.dat", "rb+");
	do {
		limparTela(posX, posY);
		posMsg(WHITE);
		printf("Digite um valor menor ou igual a 0 para sair");
		primeiraLinha(posX, posY);
		do {
			printf("ID do livro: ");
			meuScanfInt(livroAux.id_livro);
			if (livroAux.id_livro <= 0) {
				encerrado = 1;
			}
			else  {
				buscador = buscarLivro(PtrLivro, livroAux.id_livro);
				if (buscador >= 0) {
					posMsg(LIGHTRED);
					printf("ID ja existente.");
					textcolor(WHITE);
					limparLinha(posY);
				}
			}
		} while(buscador >= 0 && !encerrado);
		if (!encerrado) {
			posMsg(WHITE);
			printf("Pressione [ENTER] com uma entrada vazia para sair.");
			pularLinha(posX, posY);
			printf("Titulo do livro: ");
			meuGets(livroAux.titulo);
			if (stricmp(livroAux.titulo, "\0") == 0) {
				encerrado = 1;
			}
			else {
				posMsg(WHITE);
				printf("Digite um valor menor ou igual a 0 para sair");
				pularLinha(posX, posY);
				printf("Ano de publicacao do livro: ");
				meuScanfInt(livroAux.ano_publicacao);
				if (livroAux.ano_publicacao <= 0) {
					encerrado = 1;
				}
				else {
					livroAux.status = 1;
					fseek(PtrLivro, 0, SEEK_END);
					fwrite(&livroAux, sizeof(livro), 1, PtrLivro);
					insercaoDiretaLivros(PtrLivro);
					posMsg(LIGHTGREEN);
					printf("Cadastro concluido");
					getch();
				}
			}
		}
	} while (!encerrado);
	fclose(PtrLivro);
}

void excluirLivroEmprestimo(int id_livro) { // Excluir livro em emprestimos
	int buscador;
	struct emprestimo emprestimoAux;
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb+");
	if (PtrEmprestimo != NULL) {
		do {
			buscador = buscarLivroEmprestimo(PtrEmprestimo, id_livro);
			if (buscador >= 0) {
				fseek(PtrEmprestimo, buscador, SEEK_SET);
				fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
				emprestimoAux.status = 0;
				fseek(PtrEmprestimo, buscador, SEEK_SET);
				fwrite(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
			}
		} while (buscador >= 0);
		fclose(PtrEmprestimo);
	}
}

void excluirLivroLivAut(int id_livro) { // Excluir livro em livro-autor
	int buscador;
	struct livAut livAutAux;
	FILE *PtrLivAut = fopen("livaut.dat", "rb+");
	if (PtrLivAut != NULL) {
		do {
			buscador = buscarLivroLivAut(PtrLivAut, id_livro);
			if (buscador >= 0) {
				fseek(PtrLivAut, buscador, SEEK_SET);
				fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
				livAutAux.status = 0;
				fseek(PtrLivAut, buscador, SEEK_SET);
				fwrite(&livAutAux, sizeof(livAut), 1, PtrLivAut);
			}
		} while (buscador >= 0);
		fclose(PtrLivAut);
	}
}

void excluirLivro(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct livro livroAux;
	FILE *PtrLivro = fopen("livros.dat", "rb+");
	if (PtrLivro == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do livro: ");
				meuScanfInt(livroAux.id_livro);
				if (livroAux.id_livro <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarLivro(PtrLivro, livroAux.id_livro);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrLivro, buscador, SEEK_SET);
				fread(&livroAux, sizeof(livro), 1, PtrLivro);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados do livro:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID: %d", livroAux.id_livro);
				pularLinha(posX, posY);
				printf("Titulo: %s", livroAux.titulo);
				pularLinha(posX, posY);
				printf("Ano de publicacao: %d", livroAux.ano_publicacao);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Deseja mesmo excluir? (Pressione [S] para confirmar)");
				if (toupper(getch()) == 'S') {
					livroAux.status = 0;
					fseek(PtrLivro, buscador, SEEK_SET);
					fwrite(&livroAux, sizeof(livro), 1, PtrLivro);
					excluirLivroEmprestimo(livroAux.id_livro);
					excluirLivroLivAut(livroAux.id_livro);
					posMsg(LIGHTGREEN);
					printf("Exclusao concluida");
					getch();
				}
			}
		} while (!encerrado);
		fclose(PtrLivro);
	}
}

void alterarLivro(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct livro livroAux, alteracoes;
	FILE *PtrLivro = fopen("livros.dat", "rb+");
	if (PtrLivro == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do livro: ");
				meuScanfInt(livroAux.id_livro);
				if (livroAux.id_livro <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarLivro(PtrLivro, livroAux.id_livro);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrLivro, buscador, SEEK_SET);
				fread(&livroAux, sizeof(livro), 1, PtrLivro);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados do livro:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID: %d", livroAux.id_livro);
				pularLinha(posX, posY);
				printf("Titulo: %s", livroAux.titulo);
				pularLinha(posX, posY);
				printf("Ano de publicacao: %d", livroAux.ano_publicacao);
				pularLinha(posX, posY);
				posMsg(WHITE);
				printf("Pressione [ENTER] com uma entrada vazia para manter.");
				pularLinha(posX, posY);
				alteracoes = livroAux;
				printf("Novo titulo: ");
				meuGets(alteracoes.titulo);
				posMsg(WHITE);
				printf("Digite um valor menor ou igual a 0 para manter.");
				pularLinha(posX, posY);
				printf("Novo ano de publicacao: ");
				meuScanfInt(alteracoes.ano_publicacao);
				pularLinha(posX, posY);
				if (stricmp(alteracoes.titulo, "\0") == 0) {
					strcpy(alteracoes.titulo, livroAux.titulo);
				}
				if (alteracoes.ano_publicacao <= 0) {
					alteracoes.ano_publicacao = livroAux.ano_publicacao;
				}
				fseek(PtrLivro, buscador, SEEK_SET);
				fwrite(&alteracoes, sizeof(livro), 1, PtrLivro);
				posMsg(LIGHTGREEN);
				printf("Alteracao concluida");
				getch();
			}
		} while (!encerrado);
		fclose(PtrLivro);
		ordenarLivros();
	}
}

void consultarLivro(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct livro livroAux;
	FILE *PtrLivro = fopen("livros.dat", "rb");
	if (PtrLivro == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do livro: ");
				meuScanfInt(livroAux.id_livro);
				if (livroAux.id_livro <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscaBinariaLivro(PtrLivro, livroAux.id_livro);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrLivro, buscador, SEEK_SET);
				fread(&livroAux, sizeof(livro), 1, PtrLivro);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados do livro:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID: %d", livroAux.id_livro);
				pularLinha(posX, posY);
				printf("Titulo: %s", livroAux.titulo);
				pularLinha(posX, posY);
				printf("Ano de publicacao: %d", livroAux.ano_publicacao);
				posMsg(LIGHTGREEN);
				printf("Livro encontrado.");
				getch();
			}
		} while (!encerrado);
		fclose(PtrLivro);
	}
}

void deletarLivros(void) { // Exclusão física
	FILE *PtrLivro = fopen("livros.dat", "rb");
	if (PtrLivro != NULL) {
		struct livro livroAux;
		FILE *PtrTemp = fopen("livros_temp.dat", "wb");
		fread(&livroAux, sizeof(livro), 1, PtrLivro);
		while (!feof(PtrLivro)) {
			if (livroAux.status == 1)
				fwrite(&livroAux, sizeof(livro), 1, PtrTemp);
			fread(&livroAux, sizeof(livro), 1, PtrLivro);
		}
		fclose(PtrLivro);
		fclose(PtrTemp);
		remove("livros.dat");
		rename("livros_temp.dat", "livros.dat");
	}
}

// ### Autores ###

void ordenarAutores(void) { // Ordenação por ID
	int a, b, qntd;
	struct autor auxA, auxB;
	FILE *PtrAutor = fopen("autores.dat", "rb+");
	if (PtrAutor != NULL) {
		fseek(PtrAutor, 0, SEEK_END);
		qntd = ftell(PtrAutor) / sizeof(autor);
		for (a = 0; a < qntd - 1; a++) {
			for (b = a + 1; b < qntd; b++) {
				fseek(PtrAutor, sizeof(autor) * a, SEEK_SET);
				fread(&auxA, sizeof(autor), 1, PtrAutor);
				fseek(PtrAutor, sizeof(autor) * b, SEEK_SET);
				fread(&auxB, sizeof(autor), 1, PtrAutor);
				if (auxA.id_autor > auxB.id_autor) {
					fseek(PtrAutor, sizeof(autor) * a, SEEK_SET);
					fwrite(&auxB, sizeof(autor), 1, PtrAutor);
					fseek(PtrAutor, sizeof(autor) * b, SEEK_SET);
					fwrite(&auxA, sizeof(autor), 1, PtrAutor);
				}
			}
		}
		fclose(PtrAutor);
	}
}

void insercaoDiretaAutores(FILE *PtrAutor) {
	int pos;
	struct autor auxA, auxB;
	fseek(PtrAutor, 0, SEEK_END);
	pos = ftell(PtrAutor);
	if (pos >= sizeof(autor) * 2) {
		do {
			fseek(PtrAutor, pos - sizeof(autor) * 2, SEEK_SET);
			fread(&auxA, sizeof(autor), 1, PtrAutor);
			fread(&auxB, sizeof(autor), 1, PtrAutor);
			if (auxA.id_autor > auxB.id_autor) {
				fseek(PtrAutor, pos - sizeof(autor) * 2, SEEK_SET);
				fwrite(&auxB, sizeof(autor), 1, PtrAutor);
				fwrite(&auxA, sizeof(autor), 1, PtrAutor);
			}
			pos -= sizeof(autor);
		} while (pos >= sizeof(autor) * 2 && auxA.id_autor > auxB.id_autor);
	}
}

void cadastrarAutor(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct autor autorAux;
	FILE *PtrAutor = fopen("autores.dat", "rb+");
	do {
		limparTela(posX, posY);
		posMsg(WHITE);
		printf("Digite um valor menor ou igual a 0 para sair");
		primeiraLinha(posX, posY);
		do {
			printf("ID do autor: ");
			meuScanfInt(autorAux.id_autor);
			if (autorAux.id_autor <= 0) {
				encerrado = 1;
			}
			else {
				buscador = buscarAutor(PtrAutor, autorAux.id_autor);
				if (buscador >= 0) {
					posMsg(LIGHTRED);
					printf("ID ja existente.");
					textcolor(WHITE);
					limparLinha(posY);
				}	
			} 
		} while(buscador >= 0 && !encerrado);
		if (!encerrado) {
			posMsg(WHITE);
			printf("Pressione [ENTER] com uma entrada vazia para sair.");
			pularLinha(posX, posY);
			printf("Nome do autor: ");
			meuGets(autorAux.nome);
			if (stricmp(autorAux.nome, "\0") == 0) {
				encerrado = 1;
			}
			else {
				pularLinha(posX, posY);
				printf("Nacionalidade do autor: ");
				meuGets(autorAux.nacionalidade);
				if (stricmp(autorAux.nacionalidade, "\0") == 0) {
					encerrado = 1;
				}
				else {
					autorAux.status = 1;
					fseek(PtrAutor, 0, SEEK_END);
					fwrite(&autorAux, sizeof(autor), 1, PtrAutor);
					insercaoDiretaAutores(PtrAutor);
					posMsg(LIGHTGREEN);
					printf("Cadastro concluido");
					getch();
				}
			}
		}
	} while (!encerrado);
	fclose(PtrAutor);
}

void excluirAutorLivAut(int id_autor) { // Excluir autor em livro-autor
	int buscador;
	struct livAut livAutAux;
	FILE *PtrLivAut = fopen("livaut.dat", "rb+");
	if (PtrLivAut != NULL) {
		do {
			buscador = buscarAutorLivAut(PtrLivAut, id_autor);
			if (buscador >= 0) {
				fseek(PtrLivAut, buscador, SEEK_SET);
				fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
				livAutAux.status = 0;
				fseek(PtrLivAut, buscador, SEEK_SET);
				fwrite(&livAutAux, sizeof(livAut), 1, PtrLivAut);
			}
		} while (buscador >= 0);
		fclose(PtrLivAut);
	}
}

void excluirAutor(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct autor autorAux;
	FILE *PtrAutor = fopen("autores.dat", "rb+");
	if (PtrAutor == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do autor: ");
				meuScanfInt(autorAux.id_autor);
				if (autorAux.id_autor <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarAutor(PtrAutor, autorAux.id_autor);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado.");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrAutor, buscador, SEEK_SET);
				fread(&autorAux, sizeof(autor), 1, PtrAutor);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados do autor:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID: %d", autorAux.id_autor);
				pularLinha(posX, posY);
				printf("Nome: %s", autorAux.nome);
				pularLinha(posX, posY);
				printf("Nacionalidade: %s", autorAux.nacionalidade);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Deseja mesmo excluir esse autor? (Pressione [S] para confirmar)");
				if (toupper(getch()) == 'S') {
					autorAux.status = 0;
					fseek(PtrAutor, buscador, SEEK_SET);
					fwrite(&autorAux, sizeof(autor), 1, PtrAutor);
					excluirAutorLivAut(autorAux.id_autor);
					posMsg(LIGHTGREEN);
					printf("Exclusao completa");
					getch();
				}
			}
		} while (!encerrado);
	}
}

void alterarAutor(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct autor autorAux, alteracoes;
	FILE *PtrAutor = fopen("autores.dat", "rb+");
	if (PtrAutor == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do autor: ");
				meuScanfInt(autorAux.id_autor);
				if (autorAux.id_autor <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarAutor(PtrAutor, autorAux.id_autor);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrAutor, buscador, SEEK_SET);
				fread(&autorAux, sizeof(autor), 1, PtrAutor);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados do autor:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID: %d", autorAux.id_autor);
				pularLinha(posX, posY);
				printf("Nome: %s", autorAux.nome);
				pularLinha(posX, posY);
				printf("Nacionalidade: %s", autorAux.nacionalidade);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				posMsg(WHITE);
				printf("Pressione [ENTER] com uma entrada vazia para manter.");
				pularLinha(posX, posY);
				alteracoes = autorAux;
				printf("Novo nome: ");
				meuGets(alteracoes.nome);
				pularLinha(posX, posY);
				printf("Nova nacionalidade: ");
				meuGets(alteracoes.nacionalidade);
				pularLinha(posX, posY);
				if (stricmp(alteracoes.nome, "\0") == 0) {
					strcpy(alteracoes.nome, autorAux.nome);
				}
				if (stricmp(alteracoes.nacionalidade, "\0") == 0) {
					strcpy(alteracoes.nacionalidade, autorAux.nacionalidade);
				}
				fseek(PtrAutor, buscador, SEEK_SET);
				fwrite(&alteracoes, sizeof(autor), 1, PtrAutor);
				posMsg(LIGHTGREEN);
				printf("Alteracao concluida");
				getch();
			}
		} while (!encerrado);
		fclose(PtrAutor);
		ordenarAutores();
	}
}

void consultarAutor(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct autor autorAux;
	FILE *PtrAutor = fopen("autores.dat", "rb+");
	if (PtrAutor == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do autor: ");
				meuScanfInt(autorAux.id_autor);
				if (autorAux.id_autor <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarAutor(PtrAutor, autorAux.id_autor);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrAutor, buscador, SEEK_SET);
				fread(&autorAux, sizeof(autor), 1, PtrAutor);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados do autor:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID: %d", autorAux.id_autor);
				pularLinha(posX, posY);
				printf("Nome: %s", autorAux.nome);
				pularLinha(posX, posY);
				printf("Nacionalidade: %s", autorAux.nacionalidade);
				posMsg(LIGHTGREEN);
				printf("Autor encontrado.");
				getch();
			}
		} while (!encerrado);
		fclose(PtrAutor);
	}
}

void deletarAutores(void) { // Exclusão física
	FILE *PtrAutor = fopen("autores.dat", "rb");
	if (PtrAutor != NULL) {
		struct autor autorAux;
		FILE *PtrTemp = fopen("autores_temp.dat", "wb");
		fread(&autorAux, sizeof(autor), 1, PtrAutor);
		while (!feof(PtrAutor)) {
			if (autorAux.status == 1)
				fwrite(&autorAux, sizeof(autor), 1, PtrTemp);
			fread(&autorAux, sizeof(autor), 1, PtrAutor);
		}
		fclose(PtrAutor);
		fclose(PtrTemp);
		remove("autores.dat");
		rename("autores_temp.dat", "autores.dat");
	}
}

// ### Pessoas ###

void ordenarPessoas(void) {
	int a, b, qntd;
	struct pessoa auxA, auxB;
	FILE *PtrPessoa = fopen("pessoas.dat", "rb+");
	if (PtrPessoa != NULL) {
		fseek(PtrPessoa, 0, SEEK_END);
		qntd = ftell(PtrPessoa) / sizeof(pessoa);
		for (a = 0; a < qntd - 1; a++) {
			for (b = a + 1; b < qntd; b++) {
				fseek(PtrPessoa, sizeof(pessoa) * a, SEEK_SET);
				fread(&auxA, sizeof(pessoa), 1, PtrPessoa);
				fseek(PtrPessoa, sizeof(pessoa) * b, SEEK_SET);
				fread(&auxB, sizeof(pessoa), 1, PtrPessoa);
				if (auxA.id_pessoa > auxB.id_pessoa) {
					fseek(PtrPessoa, sizeof(pessoa) * a, SEEK_SET);
					fwrite(&auxB, sizeof(pessoa), 1, PtrPessoa);
					fseek(PtrPessoa, sizeof(pessoa) * b, SEEK_SET);
					fwrite(&auxA, sizeof(pessoa), 1, PtrPessoa);
				}
			}
		}
		fclose(PtrPessoa);
	}
}

void insercaoDiretaPessoas(FILE *PtrPessoa) {
	int pos;
	struct pessoa auxA, auxB;
	fseek(PtrPessoa, 0, SEEK_END);
	pos = ftell(PtrPessoa);
	if (pos >= sizeof(pessoa) * 2) {
		do {
			fseek(PtrPessoa, pos - sizeof(pessoa) * 2, SEEK_SET);
			fread(&auxA, sizeof(pessoa), 1, PtrPessoa);
			fread(&auxB, sizeof(pessoa), 1, PtrPessoa);
			if (auxA.id_pessoa > auxB.id_pessoa) {
				fseek(PtrPessoa, pos - sizeof(pessoa) * 2, SEEK_SET);
				fwrite(&auxB, sizeof(pessoa), 1, PtrPessoa);
				fwrite(&auxA, sizeof(pessoa), 1, PtrPessoa);
			}
			pos -= sizeof(pessoa);
		} while (pos >= sizeof(pessoa) * 2 && auxA.id_pessoa > auxB.id_pessoa);
	}
}

void formataTelefone (char telefone[]) {
	int pos, posAux = 0, TLTelefone = strlen(telefone);
	char telefoneAux[TFTelefonePessoa];
	for (pos = 0; pos < TLTelefone; pos++) {
		if (telefone[pos] >= '0' && telefone[pos] <= '9') {
			telefoneAux[posAux] = telefone[pos];
			posAux++;
		}
	}
	telefoneAux[posAux] = '\0';
	strcpy(telefone, telefoneAux);
}

void cadastrarPessoa(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct pessoa pessoaAux;
	FILE *PtrPessoa = fopen("pessoas.dat", "rb+");
	do {
		limparTela(posX, posY);
		posMsg(WHITE);
		printf("Digite um valor menor ou igual a 0 para sair");
		primeiraLinha(posX, posY);
		do {
			printf("ID da pessoa: ");
			meuScanfInt(pessoaAux.id_pessoa);
			if (pessoaAux.id_pessoa <= 0) {
				encerrado = 1;
			}
			else {
				buscador = buscarPessoa(PtrPessoa, pessoaAux.id_pessoa);
				if (buscador >= 0) {
					posMsg(LIGHTRED);
					printf("ID ja existente.");
					textcolor(WHITE);
					limparLinha(posY);
				}	
			} 
		} while(buscador >= 0 && !encerrado);
		if (!encerrado) {
			posMsg(WHITE);
			printf("Pressione [ENTER] com uma entrada vazia para sair.");
			pularLinha(posX, posY);
			printf("Nome da pessoa: ");
			meuGets(pessoaAux.nome);
			if (stricmp(pessoaAux.nome, "\0") == 0) {
				encerrado = 1;
			}
			else {
				pularLinha(posX, posY);
				printf("Telefone: ");
				meuGets(pessoaAux.telefone);
				if (stricmp(pessoaAux.telefone, "\0") == 0) {
					encerrado = 1;
				}
				else {
					formataTelefone(pessoaAux.telefone);
					pularLinha(posX, posY);
					printf("Endereco: ");
					meuGets(pessoaAux.endereco);
					if (stricmp(pessoaAux.endereco, "\0") == 0) {
						encerrado = 1;
					}
					else {
						pessoaAux.status = 1;
						fseek(PtrPessoa, 0, SEEK_END);
						fwrite(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
						insercaoDiretaPessoas(PtrPessoa);
						posMsg(LIGHTGREEN);
						printf("Cadastro concluido");
						getch();
					}
				}
			}
		}
	} while (!encerrado);
	fclose(PtrPessoa);
}

void excluirPessoaEmprestimo(int id_pessoa) { // Excluir livro em emprestimos
	int buscador;
	struct emprestimo emprestimoAux;
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb+");
	if (PtrEmprestimo != NULL) {
		do {
			buscador = buscarPessoaEmprestimo(PtrEmprestimo, id_pessoa);
			if (buscador >= 0) {
				fseek(PtrEmprestimo, buscador, SEEK_SET);
				fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
				emprestimoAux.status = 0;
				fseek(PtrEmprestimo, buscador, SEEK_SET);
				fwrite(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
			}
		} while (buscador >= 0);
		fclose(PtrEmprestimo);
	}
}

void excluirPessoa(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct pessoa pessoaAux;
	FILE *PtrPessoa = fopen("pessoas.dat", "rb+");
	if (PtrPessoa == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID da pessoa: ");
				meuScanfInt(pessoaAux.id_pessoa);
				if (pessoaAux.id_pessoa <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarPessoa(PtrPessoa, pessoaAux.id_pessoa);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado.");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrPessoa, buscador, SEEK_SET);
				fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados da pessoa:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID: %d", pessoaAux.id_pessoa);
				pularLinha(posX, posY);
				printf("Nome: %s", pessoaAux.nome);
				pularLinha(posX, posY);
				printf("Telefone: %s", pessoaAux.telefone);
				pularLinha(posX, posY);
				printf("Endereco: %s", pessoaAux.endereco);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Deseja mesmo excluir essa pessoa? (Pressione [S] para confirmar)");
				if (toupper(getch()) == 'S') {
					pessoaAux.status = 0;
					fseek(PtrPessoa, buscador, SEEK_SET);
					fwrite(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
					excluirPessoaEmprestimo(pessoaAux.id_pessoa);
					posMsg(LIGHTGREEN);
					printf("Exclusao concluida");
					getch();
				}
			}
		} while (!encerrado);
		fclose(PtrPessoa);
	}
}

void alterarPessoa(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct pessoa pessoaAux, alteracoes;
	FILE *PtrPessoa = fopen("pessoas.dat", "rb+");
	if (PtrPessoa == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID da pessoa: ");
				meuScanfInt(pessoaAux.id_pessoa);
				if (pessoaAux.id_pessoa <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarPessoa(PtrPessoa, pessoaAux.id_pessoa);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado.");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrPessoa, buscador, SEEK_SET);
				fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados da pessoa:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID: %d", pessoaAux.id_pessoa);
				pularLinha(posX, posY);
				printf("Nome: %s", pessoaAux.nome);
				pularLinha(posX, posY);
				printf("Telefone: %s", pessoaAux.telefone);
				pularLinha(posX, posY);
				printf("Endereco: %s", pessoaAux.endereco);
				pularLinha(posX, posY);
				alteracoes = pessoaAux;
				posMsg(WHITE);
				printf("Pressione [ENTER] com uma entrada vazia para manter.");
				pularLinha(posX, posY);
				printf("Novo nome: ");
				meuGets(alteracoes.nome);
				pularLinha(posX, posY);
				printf("Novo telefone: ");
				meuGets(alteracoes.telefone);
				formataTelefone(alteracoes.telefone);
				pularLinha(posX, posY);
				printf("Novo endereco: ");
				meuGets(alteracoes.endereco);
				if (stricmp(alteracoes.nome, "\0") == 0) {
					strcpy(alteracoes.nome, pessoaAux.nome);
				}
				if (stricmp(alteracoes.telefone, "\0") == 0) {
					strcpy(alteracoes.telefone, pessoaAux.telefone);
				}
				if (stricmp(alteracoes.endereco, "\0") == 0) {
					strcpy(alteracoes.endereco, pessoaAux.endereco);
				}
				fseek(PtrPessoa, buscador, SEEK_SET);
				fwrite(&alteracoes, sizeof(pessoa), 1, PtrPessoa);
				posMsg(LIGHTGREEN);
				printf("Alteracao concluida");
				getch();
			}
		} while (!encerrado);
		fclose(PtrPessoa);
		ordenarPessoas();
	}
}

void consultarPessoa(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct pessoa pessoaAux;
	FILE *PtrPessoa = fopen("pessoas.dat", "rb+");
	if (PtrPessoa == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID da pessoa: ");
				meuScanfInt(pessoaAux.id_pessoa);
				if (pessoaAux.id_pessoa <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarPessoa(PtrPessoa, pessoaAux.id_pessoa);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado.");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrPessoa, buscador, SEEK_SET);
				fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados da pessoa:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID: %d", pessoaAux.id_pessoa);
				pularLinha(posX, posY);
				printf("Nome: %s", pessoaAux.nome);
				pularLinha(posX, posY);
				printf("Telefone: %s", pessoaAux.telefone);
				pularLinha(posX, posY);
				printf("Endereco: %s", pessoaAux.endereco);
				posMsg(LIGHTGREEN);
				printf("Pessoa encontrada");
				getch();
			}
		} while (!encerrado);
		fclose(PtrPessoa);
	}
}

void deletarPessoas(void) { // Exclusão física
	FILE *PtrPessoa = fopen("pessoas.dat", "rb");
	if (PtrPessoa != NULL) {
		struct pessoa pessoaAux;
		FILE *PtrTemp = fopen("pessoas_temp.dat", "wb");
		fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
		while (!feof(PtrPessoa)) {
			if (pessoaAux.status == 1)
				fwrite(&pessoaAux, sizeof(pessoa), 1, PtrTemp);
			fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
		}
		fclose(PtrPessoa);
		fclose(PtrTemp);
		remove("pessoas.dat");
		rename("pessoas_temp.dat", "pessoas.dat");
	}
}

// ### Empréstimos ###

void ordenarEmprestimos(void) {
	int a, b, qntd;
	struct emprestimo auxA, auxB;
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb+");
	if (PtrEmprestimo != NULL) {
		fseek(PtrEmprestimo, 0, SEEK_END);
		qntd = ftell(PtrEmprestimo) / sizeof(emprestimo);
		for (a = 0; a < qntd - 1; a++) {
			for (b = a + 1; b < qntd; b++) {
				fseek(PtrEmprestimo, sizeof(emprestimo) * a, SEEK_SET);
				fread(&auxA, sizeof(emprestimo), 1, PtrEmprestimo);
				fseek(PtrEmprestimo, sizeof(emprestimo) * b, SEEK_SET);
				fread(&auxB, sizeof(emprestimo), 1, PtrEmprestimo);
				if (auxA.id_emprestimo > auxB.id_emprestimo) {
					fseek(PtrEmprestimo, sizeof(emprestimo) * a, SEEK_SET);
					fwrite(&auxB, sizeof(emprestimo), 1, PtrEmprestimo);
					fseek(PtrEmprestimo, sizeof(emprestimo) * b, SEEK_SET);
					fwrite(&auxA, sizeof(emprestimo), 1, PtrEmprestimo);
				}
			}
		}
		fclose(PtrEmprestimo);
	}
}

void insercaoDiretaEmprestimos(FILE *PtrEmprestimo) {
	int pos;
	struct emprestimo auxA, auxB;
	fseek(PtrEmprestimo, 0, SEEK_END);
	pos = ftell(PtrEmprestimo);
	if (pos >= sizeof(emprestimo) * 2) {
		do {
			fseek(PtrEmprestimo, pos - sizeof(emprestimo) * 2, SEEK_SET);
			fread(&auxA, sizeof(emprestimo), 1, PtrEmprestimo);
			fread(&auxB, sizeof(emprestimo), 1, PtrEmprestimo);
			if (auxA.id_emprestimo > auxB.id_emprestimo) {
				fseek(PtrEmprestimo, pos - sizeof(emprestimo) * 2, SEEK_SET);
				fwrite(&auxB, sizeof(emprestimo), 1, PtrEmprestimo);
				fwrite(&auxA, sizeof(emprestimo), 1, PtrEmprestimo);
			}
			pos -= sizeof(emprestimo);
		} while (pos >= sizeof(emprestimo) * 2 && auxA.id_emprestimo > auxB.id_emprestimo);
	}
}

int validaDia(int dia, int mes, int ano) {
	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) { // Se for um mês de 31 dias
		if (dia < 1 || dia > 31)
			return 0;
		else return 1;
	}
	else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { // Se for um mês de 30 dias
		if (dia < 1 || dia > 30)
			return 0;
		else return 1;
	}
	else if (mes == 2) { // Se for fevereiro
		if (ano % 4 == 0) { // Ano bissexto
			if (dia < 1 || dia > 29)
				return 0;
			else return 1;
		}
		else { // Ano não bissexto
			if (dia < 1 || dia > 28)
				return 0;
			else return 1;
		}
	}
}

int validaMes(int mes) {
	if (mes < 1 || mes > 12)
		return 0;
	else return 1;
}

int validaAno(int ano) {
	// Para este trabalho, não será considerada a possibilidade de empréstimo em anos antes de Cristo
	if (ano < 1)
		return 0;
	else return 1;
}

int validaData(struct data dataAux) {
	int valida = 0;
	if (validaAno(dataAux.ano)) {
		if (validaMes(dataAux.mes)) {
			if (validaDia(dataAux.dia, dataAux.mes, dataAux.ano)) {
				valida = 1;
			}
		}
	}
	return valida;
}

int comparaDatas(struct data dataInicial, struct data dataFinal) {
	if (dataInicial.ano < dataFinal.ano) {
		return 1;
	}
	else if (dataInicial.ano == dataFinal.ano) {
		if (dataInicial.mes < dataFinal.mes) {
			return 1;
		}
		else if (dataInicial.mes == dataFinal.mes) {
			if (dataInicial.dia <= dataFinal.dia)
				return 1;
			else return 0;
		}
		else return 0;
	}
	else return 0;
}

int verificarLivro(FILE *PtrEmprestimo, int id_livro) { // Verifica se já existem registros de emprestimo de um determinado livro por ID
	struct emprestimo emprestimoAux;
	rewind(PtrEmprestimo);
	fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
	while (!feof(PtrEmprestimo) && !(emprestimoAux.id_livro == id_livro && emprestimoAux.status == 1))
		fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
	if (emprestimoAux.id_livro == id_livro && emprestimoAux.status == 1)
		return ftell(PtrEmprestimo) - sizeof(emprestimo);
	else return -1;
}

void cadastraEmprestimo(int &posX, int &posY) {
	int encerrado = 0, buscador, buscadorLivro, buscadorPessoa, datasValidas = 0;
	struct emprestimo emprestimoAux;
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb+");
	FILE *PtrLivro = fopen("livros.dat", "rb");
	FILE *PtrPessoa = fopen("pessoas.dat", "rb");
	if (PtrLivro == NULL || PtrPessoa == NULL) {
		erroAbertura();
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
		if (PtrPessoa != NULL) {
			fclose(PtrPessoa);
		}
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do emprestimo: ");
				meuScanfInt(emprestimoAux.id_emprestimo);
				if (emprestimoAux.id_emprestimo <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarEmprestimo(PtrEmprestimo, emprestimoAux.id_emprestimo);
					if (buscador >= 0) {
						posMsg(LIGHTRED);
						printf("ID ja existente.");
						textcolor(WHITE);
						limparLinha(posY);
					}	
				} 
			} while(buscador >= 0 && !encerrado);
			if (!encerrado) {
				posMsg(WHITE);
				printf("Digite um valor menor ou igual a 0 para sair");
				pularLinha(posX, posY);
				do {
					printf("ID do livro: ");
					meuScanfInt(emprestimoAux.id_livro);
					if (emprestimoAux.id_livro <= 0) {
						encerrado = 1;
					}
					else {
						buscadorLivro = buscarLivro(PtrLivro, emprestimoAux.id_livro);
						if (buscadorLivro < 0) {
							posMsg(LIGHTRED);
							printf("ID nao encontrado");
							textcolor(WHITE);
							limparLinha(posY);
						}
						else {
							buscadorLivro = verificarLivro(PtrEmprestimo, emprestimoAux.id_livro);
							if (buscadorLivro >= 0) {
								posMsg(LIGHTRED);
								printf("Livro ja emprestado");
								textcolor(WHITE);
								limparLinha(posY);
								buscadorLivro = -1; // O livro foi encontrado, mas ele não está disponível, então o buscador precisa ser negado
							}
							else buscadorLivro = 1; // O livro foi encontrado e está disponível
						}
					}
				} while (!encerrado && buscadorLivro < 0);
				if (!encerrado) {
					posMsg(WHITE);
					printf("Digite um valor menor ou igual a 0 para sair");
					pularLinha(posX, posY);
					do {
						printf("ID da pessoa: ");
						meuScanfInt(emprestimoAux.id_pessoa);
						if (emprestimoAux.id_pessoa <= 0) {
							encerrado = 1;
						}
						else {
							buscadorPessoa = buscarPessoa(PtrPessoa, emprestimoAux.id_pessoa);
							if (buscadorPessoa < 0) {
								posMsg(LIGHTRED);
								printf("ID nao encontrado");
								textcolor(WHITE);
								limparLinha(posY);
							}
						}
					} while (!encerrado && buscadorPessoa < 0);
					if (!encerrado) {
						posMsg(WHITE);
						printf("Digite um valor menor ou igual a 0 para sair");
						do {
							limparTela(posX, posY);
							primeiraLinha(posX, posY);
							printf("Dia do emprestimo: ");
							meuScanfInt(emprestimoAux.data_emprestimo.dia);
							pularLinha(posX, posY);
							printf("Mes do emprestimo: ");
							meuScanfInt(emprestimoAux.data_emprestimo.mes);
							pularLinha(posX, posY);
							printf("Ano do emprestimo: ");
							meuScanfInt(emprestimoAux.data_emprestimo.ano);
							if (validaData(emprestimoAux.data_emprestimo)) {
								pularLinha(posX, posY);
								printf("Dia da devolucao: ");
								meuScanfInt(emprestimoAux.data_devolucao.dia);
								pularLinha(posX, posY);
								printf("Mes da devolucao: ");
								meuScanfInt(emprestimoAux.data_devolucao.mes);
								pularLinha(posX, posY);
								printf("Ano da devolucao: ");
								meuScanfInt(emprestimoAux.data_devolucao.ano);
								if (validaData(emprestimoAux.data_devolucao)) {
									if (comparaDatas(emprestimoAux.data_emprestimo, emprestimoAux.data_devolucao))
										datasValidas = 1;
									else {
										posMsg(LIGHTRED);
										printf("Datas invalidas");
										textcolor(WHITE);
									}
								}
								else {
									posMsg(LIGHTRED);
									printf("Data invalida");
									textcolor(WHITE);
								}
							}
							else {
								posMsg(LIGHTRED);
								printf("Data invalida");
								textcolor(WHITE);
							}
						} while (!encerrado && !datasValidas);
						if (datasValidas) {
							emprestimoAux.status = 1;
							fseek(PtrEmprestimo, 0, SEEK_END);
							fwrite(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
							insercaoDiretaEmprestimos(PtrEmprestimo);
							posMsg(LIGHTGREEN);
							printf("Cadastro concluido");
							getch();
						}
					}
				}
			}
		} while (!encerrado);
		fclose(PtrLivro);
		fclose(PtrPessoa);
	}
	fclose(PtrEmprestimo);
}

void excluirEmprestimo(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct emprestimo emprestimoAux;
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb+");
	if (PtrEmprestimo == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do emprestimo: ");
				meuScanfInt(emprestimoAux.id_emprestimo);
				if (emprestimoAux.id_emprestimo <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarEmprestimo(PtrEmprestimo, emprestimoAux.id_emprestimo);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrEmprestimo, buscador, SEEK_SET);
				fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados do emprestimo:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID do emprestimo: %d", emprestimoAux.id_emprestimo);
				pularLinha(posX, posY);
				printf("ID do livro: %d", emprestimoAux.id_livro);
				pularLinha(posX, posY);
				printf("ID da pessoa: %d", emprestimoAux.id_pessoa);
				pularLinha(posX, posY);
				printf("Data do emprestimo: %d/%d/%d", emprestimoAux.data_emprestimo.dia, emprestimoAux.data_emprestimo.mes, emprestimoAux.data_emprestimo.ano);
				pularLinha(posX, posY);
				printf("Data do devolucao: %d/%d/%d", emprestimoAux.data_devolucao.dia, emprestimoAux.data_devolucao.mes, emprestimoAux.data_devolucao.ano);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Deseja mesmo excluir esse emprestimo? (Pressione [S] para confirmar)");
				if (toupper(getch()) == 'S') {
					emprestimoAux.status = 0;
					fseek(PtrEmprestimo, buscador, SEEK_SET);
					fwrite(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
					posMsg(LIGHTGREEN);
					printf("Exclusao concluida");
					getch();
				}
			}
		} while (!encerrado);
		fclose(PtrEmprestimo);
	}
}

void alterarEmprestimo(int &posX, int &posY) {
	int encerrado = 0, buscador, buscadorLivro, buscadorPessoa, datasValidas = 0;
	struct emprestimo emprestimoAux, alteracoes;
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb+");
	FILE *PtrLivro = fopen("livros.dat", "rb");
	FILE *PtrPessoa = fopen("pessoas.dat", "rb");
	if (PtrLivro == NULL || PtrPessoa == NULL || PtrEmprestimo == NULL) {
		erroAbertura();
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
		if (PtrPessoa != NULL) {
			fclose(PtrPessoa);
		}
		if (PtrEmprestimo != NULL) {
			fclose(PtrEmprestimo);
		}
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do emprestimo: ");
				meuScanfInt(emprestimoAux.id_emprestimo);
				if (emprestimoAux.id_emprestimo <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarEmprestimo(PtrEmprestimo, emprestimoAux.id_emprestimo);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrEmprestimo, buscador, SEEK_SET);
				fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados do emprestimo:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID do emprestimo: %d", emprestimoAux.id_emprestimo);
				pularLinha(posX, posY);
				printf("ID do livro: %d", emprestimoAux.id_livro);
				pularLinha(posX, posY);
				printf("ID da pessoa: %d", emprestimoAux.id_pessoa);
				pularLinha(posX, posY);
				printf("Data do emprestimo: %d/%d/%d", emprestimoAux.data_emprestimo.dia, emprestimoAux.data_emprestimo.mes, emprestimoAux.data_emprestimo.ano);
				pularLinha(posX, posY);
				printf("Data do devolucao: %d/%d/%d", emprestimoAux.data_devolucao.dia, emprestimoAux.data_devolucao.mes, emprestimoAux.data_devolucao.ano);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Deseja mesmo alterar esse emprestimo? (Pressione [S] para confirmar)"); // Foi preciso fazer essa divisão para as novas informações caberem na tela
				if (toupper(getch()) == 'S') {
					alteracoes = emprestimoAux;
					limparTela(posX, posY);
					posMsg(WHITE);
					printf("Digite um valor menor ou igual a 0 para manter");
					primeiraLinha(posX, posY);
					do {
						printf("ID do livro: ");
						meuScanfInt(alteracoes.id_livro);
						if (alteracoes.id_livro > 0) {
							buscadorLivro = buscarLivro(PtrLivro, alteracoes.id_livro);
							if (buscadorLivro < 0) {
								posMsg(LIGHTRED);
								printf("ID nao encontrado");
								textcolor(WHITE);
								limparLinha(posY);
							}
							else {
								buscadorLivro = verificarLivro(PtrEmprestimo, alteracoes.id_livro);
								if (buscadorLivro >= 0) {
									posMsg(LIGHTRED);
									printf("Livro ja emprestado");
									textcolor(WHITE);
									limparLinha(posY);
									buscadorLivro = -1; // O livro foi encontrado, mas ele não está disponível, então o buscador precisa ser negado
								}
								else buscadorLivro = 1; // O livro foi encontrado e está disponível
							}
						}
					} while (alteracoes.id_livro > 0 && buscadorLivro < 0);
					if (alteracoes.id_livro <= 0) {
						alteracoes.id_livro = emprestimoAux.id_livro;
					}
					posMsg(WHITE);
					printf("Digite um valor menor ou igual a 0 para sair");
					pularLinha(posX, posY);
					do {
						printf("ID da pessoa: ");
						meuScanfInt(alteracoes.id_pessoa);
						if (alteracoes.id_pessoa > 0)  {
							buscadorPessoa = buscarPessoa(PtrPessoa, alteracoes.id_pessoa);
							if (buscadorPessoa < 0) {
								posMsg(LIGHTRED);
								printf("ID nao encontrado");
								textcolor(WHITE);
								limparLinha(posY);
							}
						}
					} while (alteracoes.id_pessoa > 0 && buscadorPessoa < 0);
					if (alteracoes.id_pessoa <= 0) {
						alteracoes.id_pessoa = emprestimoAux.id_pessoa;
					}
					posMsg(WHITE);
					printf("Digite as novas datas");
					do {
						limparTela(posX, posY);
						primeiraLinha(posX, posY);
						printf("Dia do emprestimo: ");
						meuScanfInt(alteracoes.data_emprestimo.dia);
						pularLinha(posX, posY);
						printf("Mes do emprestimo: ");
						meuScanfInt(alteracoes.data_emprestimo.mes);
						pularLinha(posX, posY);
						printf("Ano do emprestimo: ");
						meuScanfInt(alteracoes.data_emprestimo.ano);
						if (validaData(alteracoes.data_emprestimo)) {
							pularLinha(posX, posY);
							printf("Dia da devolucao: ");
							meuScanfInt(alteracoes.data_devolucao.dia);
							pularLinha(posX, posY);
							printf("Mes da devolucao: ");
							meuScanfInt(alteracoes.data_devolucao.mes);
							pularLinha(posX, posY);
							printf("Ano da devolucao: ");
							meuScanfInt(alteracoes.data_devolucao.ano);
							if (validaData(alteracoes.data_devolucao)) {
								if (comparaDatas(alteracoes.data_emprestimo, alteracoes.data_devolucao))
									datasValidas = 1;
								else {
									posMsg(LIGHTRED);
									printf("Datas invalidas");
									textcolor(WHITE);
								}
							}
							else {
								posMsg(LIGHTRED);
								printf("Data invalida");
								textcolor(WHITE);
							}
						}
						else {
							posMsg(LIGHTRED);
							printf("Data invalida");
							textcolor(WHITE);
						}
					} while (!datasValidas);
					if (datasValidas) {
						alteracoes.status = 1;
						fseek(PtrEmprestimo, buscador, SEEK_SET);
						fwrite(&alteracoes, sizeof(emprestimo), 1, PtrEmprestimo);
						posMsg(LIGHTGREEN);
						printf("Alteracao concluida");
						getch();
					}
				}
			}
		} while (!encerrado);
		fclose(PtrEmprestimo);
		ordenarEmprestimos();
	}
}

void consultarEmprestimo(int &posX, int &posY) {
	int encerrado = 0, buscador;
	struct emprestimo emprestimoAux;
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb+");
	if (PtrEmprestimo == NULL) {
		erroAbertura();
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um valor menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do emprestimo: ");
				meuScanfInt(emprestimoAux.id_emprestimo);
				if (emprestimoAux.id_emprestimo <= 0) {
					encerrado = 1;
				}
				else {
					buscador = buscarEmprestimo(PtrEmprestimo, emprestimoAux.id_emprestimo);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscador < 0);
			if (!encerrado) {
				fseek(PtrEmprestimo, buscador, SEEK_SET);
				fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("Dados do emprestimo:");
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID do emprestimo: %d", emprestimoAux.id_emprestimo);
				pularLinha(posX, posY);
				printf("ID do livro: %d", emprestimoAux.id_livro);
				pularLinha(posX, posY);
				printf("ID da pessoa: %d", emprestimoAux.id_pessoa);
				pularLinha(posX, posY);
				printf("Data do emprestimo: %d/%d/%d", emprestimoAux.data_emprestimo.dia, emprestimoAux.data_emprestimo.mes, emprestimoAux.data_emprestimo.ano);
				pularLinha(posX, posY);
				printf("Data do devolucao: %d/%d/%d", emprestimoAux.data_devolucao.dia, emprestimoAux.data_devolucao.mes, emprestimoAux.data_devolucao.ano);
				posMsg(LIGHTGREEN);
				printf("Emprestimo encontrado");
				getch();
			}
		} while (!encerrado);
		fclose(PtrEmprestimo);
	}
}

void deletarEmprestimos(void) { // Exclusão física
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb");
	if (PtrEmprestimo != NULL) {
		struct emprestimo emprestimoAux;
		FILE *PtrTemp = fopen("emprestimos_temp.dat", "wb");
		fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
		while (!feof(PtrEmprestimo)) {
			if (emprestimoAux.status == 1)
				fwrite(&emprestimoAux, sizeof(emprestimo), 1, PtrTemp);
			fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
		}
		fclose(PtrEmprestimo);
		fclose(PtrTemp);
		remove("emprestimos.dat");
		rename("emprestimos_temp.dat", "emprestimos.dat");
	}
}

// ### Relacionamento livro-autor

void cadastrarLivAut(int &posX, int &posY) {
	int encerrado = 0, buscador, buscadorLivro, buscadorAutor;
	struct livAut livAutAux;
	FILE *PtrLivAut = fopen("livaut.dat", "ab+");
	FILE *PtrLivro = fopen("livros.dat", "rb");
	FILE *PtrAutor = fopen("autores.dat", "rb");
	if (PtrLivro == NULL || PtrAutor == NULL) {
		erroAbertura();
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
		if (PtrAutor != NULL) {
			fclose(PtrAutor);
		}
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um numero menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do livro: ");
				meuScanfInt(livAutAux.id_livro);
				if (livAutAux.id_livro <= 0) {
					encerrado = 1;
				}
				else {
					buscadorLivro = buscarLivro(PtrLivro, livAutAux.id_livro);
					if (buscadorLivro < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscadorLivro < 0);
			if (!encerrado) {
				posMsg(WHITE);
				printf("Digite um numero menor ou igual a 0 para sair");
				pularLinha(posX, posY);
				do {
					printf("ID do autor: ");
					meuScanfInt(livAutAux.id_autor);
					if (livAutAux.id_autor <= 0) {
						encerrado = 1;
					}
					else {
						buscadorAutor = buscarAutor(PtrAutor, livAutAux.id_autor);
						if (buscadorAutor < 0) {
							posMsg(LIGHTRED);
							printf("ID nao encontrado");
							textcolor(WHITE);
							limparLinha(posY);
						}
					}
				} while (!encerrado && buscadorAutor < 0);
				if (!encerrado) {
					buscador = buscarLivAut(PtrLivAut, livAutAux.id_livro, livAutAux.id_autor);
					if (buscador < 0) {
						livAutAux.status = 1;
						fwrite(&livAutAux, sizeof(livAut), 1, PtrLivAut);
						posMsg(LIGHTGREEN);
						printf("Cadastro concluido");
						getch();
					}
					else {
						posMsg(LIGHTRED);
						printf("Relacao ja existente");
						textcolor(WHITE);
						limparLinha(posY);
						getch();
					}
				}
			}
		} while (!encerrado);
		fclose(PtrLivro);
		fclose(PtrAutor);
	}
	fclose(PtrLivAut);
}

void excluirLivAut(int &posX, int &posY) {
	int encerrado = 0, buscador, buscadorLivro, buscadorAutor;
	struct livAut livAutAux;
	FILE *PtrLivAut = fopen("livaut.dat", "rb+");
	FILE *PtrLivro = fopen("livros.dat", "rb");
	FILE *PtrAutor = fopen("autores.dat", "rb");
	if (PtrLivro == NULL || PtrAutor == NULL || PtrLivAut == NULL) {
		erroAbertura();
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
		if (PtrAutor != NULL) {
			fclose(PtrAutor);
		}
		if (PtrLivAut != NULL) {
			fclose(PtrLivAut);
		}
	}
	else {
		do {
			limparTela(posX, posY);
			posMsg(WHITE);
			printf("Digite um numero menor ou igual a 0 para sair");
			primeiraLinha(posX, posY);
			do {
				printf("ID do livro: ");
				meuScanfInt(livAutAux.id_livro);
				if (livAutAux.id_livro <= 0) {
					encerrado = 1;
				}
				else {
					buscadorLivro = buscarLivro(PtrLivro, livAutAux.id_livro);
					if (buscadorLivro < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscadorLivro < 0);
			if (!encerrado) {
				posMsg(WHITE);
				printf("Digite um numero menor ou igual a 0 para sair");
				pularLinha(posX, posY);
				do {
					printf("ID do autor: ");
					meuScanfInt(livAutAux.id_autor);
					if (livAutAux.id_autor <= 0) {
						encerrado = 1;
					}
					else {
						buscadorAutor = buscarAutor(PtrAutor, livAutAux.id_autor);
						if (buscadorAutor < 0) {
							posMsg(LIGHTRED);
							printf("ID nao encontrado");
							textcolor(WHITE);
							limparLinha(posY);
						}
					}
				} while (!encerrado && buscadorAutor < 0);
				if (!encerrado) {
					buscador = buscarLivAut(PtrLivAut, livAutAux.id_livro, livAutAux.id_autor);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("Relacao inexistente");
						textcolor(WHITE);
						limparLinha(posY);
						getch();
					}
					else {
						pularLinha(posX, posY);
						printf("Deseja mesmo excluir essa relacao (Pressione [S] para confirmar)");
						if (toupper(getch()) == 'S') {
							fseek(PtrLivAut, buscador, SEEK_SET);
							fread(&livAutAux, sizeof(livAutAux), 1, PtrLivAut);
							livAutAux.status = 0;
							fseek(PtrLivAut, buscador, SEEK_SET);
							fwrite(&livAutAux, sizeof(livAutAux), 1, PtrLivAut);
							posMsg(LIGHTGREEN);
							printf("Exclusao concluida");
							getch();
						}
					}
				}
			}
		} while (!encerrado);
		fclose(PtrLivro);
		fclose(PtrAutor);
		fclose(PtrLivAut);
	}
}

// Alterações de relacionamento livro-autor não serão feitas, visto que ambos os campos disponíveis são chaves primárias

void consultarLivAut(int &posX, int &posY) { // Como ambos os campos da struct "livAut" são usados como chave primária, essa função apenas verifica a existência da relação entre eles
	int encerrado = 0, buscador, buscadorLivro, buscadorAutor;
	struct livAut livAutAux;
	FILE *PtrLivAut = fopen("livaut.dat", "rb+");
	FILE *PtrLivro = fopen("livros.dat", "rb");
	FILE *PtrAutor = fopen("autores.dat", "rb");
	if (PtrLivro == NULL || PtrAutor == NULL || PtrLivAut == NULL) {
		posMsg(LIGHTRED);
		erroAbertura();
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
		if (PtrAutor != NULL) {
			fclose(PtrAutor);
		}
		if (PtrLivAut != NULL) {
			fclose(PtrLivAut);
		}
	}
	else {
		posMsg(WHITE);
		printf("Digite um numero menor ou igual a 0 para sair");
		do {
			limparTela(posX, posY);
			textcolor(WHITE);
			primeiraLinha(posX, posY);
			do {
				printf("ID do livro: ");
				meuScanfInt(livAutAux.id_livro);
				if (livAutAux.id_livro <= 0) {
					encerrado = 1;
				}
				else {
					buscadorLivro = buscarLivro(PtrLivro, livAutAux.id_livro);
					if (buscadorLivro < 0) {
						posMsg(LIGHTRED);
						printf("ID nao encontrado");
						textcolor(WHITE);
						limparLinha(posY);
					}
				}
			} while (!encerrado && buscadorLivro < 0);
			if (!encerrado) {
				posMsg(WHITE);
				printf("Digite um numero menor ou igual a 0 para sair");
				pularLinha(posX, posY);
				do {
					printf("ID do autor: ");
					meuScanfInt(livAutAux.id_autor);
					if (livAutAux.id_autor <= 0) {
						encerrado = 1;
					}
					else {
						buscadorAutor = buscarAutor(PtrAutor, livAutAux.id_autor);
						if (buscadorAutor < 0) {
							posMsg(LIGHTRED);
							printf("ID nao encontrado");
							textcolor(WHITE);
							limparLinha(posY);
						}
					}
				} while (!encerrado && buscadorAutor < 0);
				if (!encerrado) {
					buscador = buscarLivAut(PtrLivAut, livAutAux.id_livro, livAutAux.id_autor);
					if (buscador < 0) {
						posMsg(LIGHTRED);
						printf("Relacao inexistente");
						textcolor(WHITE);
						limparLinha(posY);
					}
					else {
						posMsg(LIGHTGREEN);
						printf("A relacao informada existe");
					}
				}
			}
		} while (!encerrado);
		fclose(PtrLivro);
		fclose(PtrAutor);
		fclose(PtrLivAut);
	}
}

void deletarLivAut(void) { // Exclusão física
	FILE *PtrLivAut = fopen("livaut.dat", "rb");
	if (PtrLivAut != NULL) {
		struct livAut livAutAux;
		FILE *PtrTemp = fopen("livaut_temp.dat", "wb");
		fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
		while (!feof(PtrLivAut)) {
			if (livAutAux.status == 1)
				fwrite(&livAutAux, sizeof(livAut), 1, PtrTemp);
			fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
		}
		fclose(PtrLivAut);
		fclose(PtrTemp);
		remove("livaut.dat");
		rename("livaut_temp.dat", "livaut.dat");
	}
}

// ### Relatorios ###

void pausarRelatorio(int &posX, int &posY) {
	getch();
	limparTela(posX, posY);
	primeiraLinha(posX, posY);
}

void ordenarLivrosAnoPublicacao(FILE *PtrLivro) {
	int a, b, qntd;
	struct livro auxA, auxB;
	fseek(PtrLivro, 0, SEEK_END);
	qntd = ftell(PtrLivro) / sizeof(livro);
	for (a = 0; a < qntd - 1; a++) {
		for (b = a + 1; b < qntd; b++) {
			fseek(PtrLivro, sizeof(livro) * a, SEEK_SET);
			fread(&auxA, sizeof(livro), 1, PtrLivro);
			fseek(PtrLivro, sizeof(livro) * b, SEEK_SET);
			fread(&auxB, sizeof(livro), 1, PtrLivro);
			if (auxA.ano_publicacao > auxB.ano_publicacao) {
				fseek(PtrLivro, sizeof(livro) * a, SEEK_SET);
				fwrite(&auxB, sizeof(livro), 1, PtrLivro);
				fseek(PtrLivro, sizeof(livro) * b, SEEK_SET);
				fwrite(&auxA, sizeof(livro), 1, PtrLivro);
			}
		}
	}
}

void ordenarAutoresNacionalidade(FILE *PtrAutor) {
	int a, b, qntd;
	struct autor auxA, auxB;
	fseek(PtrAutor, 0, SEEK_END);
	qntd = ftell(PtrAutor) / sizeof(autor);
	for (a = 0; a < qntd - 1; a++) {
		for (b = a + 1; b < qntd; b++) {
			fseek(PtrAutor, sizeof(autor) * a, SEEK_SET);
			fread(&auxA, sizeof(autor), 1, PtrAutor);
			fseek(PtrAutor, sizeof(autor) * b, SEEK_SET);
			fread(&auxB, sizeof(autor), 1, PtrAutor);
			if (stricmp(auxA.nacionalidade, auxB.nacionalidade) > 0) {
				fseek(PtrAutor, sizeof(autor) * a, SEEK_SET);
				fwrite(&auxB, sizeof(autor), 1, PtrAutor);
				fseek(PtrAutor, sizeof(autor) * b, SEEK_SET);
				fwrite(&auxA, sizeof(autor), 1, PtrAutor);
			}
		}
	}
}

void relatorioA(int &posX, int &posY) {
	int encerrado = 0, buscadorLivro, buscadorAutor, buscadorLivAut, contador;
	struct livro livroAux;
	struct autor autorAux;
	struct livAut livAutAux;
	FILE *PtrLivro = fopen("livros.dat", "rb");
	FILE *PtrAutor = fopen("autores.dat", "rb");
	FILE *PtrLivAut = fopen("livaut.dat", "rb");
	if (PtrLivro == NULL || PtrAutor == NULL || PtrLivAut == NULL) {
		erroAbertura();
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
		if (PtrAutor != NULL) {
			fclose(PtrAutor);
		}
		if (PtrLivAut != NULL) {
			fclose(PtrLivAut);
		}
	}
	else {
		posMsg(WHITE);
		printf("Pressione [X] para sair");
		fread(&livroAux, sizeof(livro), 1, PtrLivro);
		while (!feof(PtrLivro) && !encerrado) {
			contador = 1;
			limparTela(posX, posY);
			primeiraLinha(posX, posY);
			if (livroAux.status == 1) {
				printf("ID do livro: %d", livroAux.id_livro);
				pularLinha(posX, posY);
				printf("Titulo: %s", livroAux.titulo);
				pularLinha(posX, posY);
				printf("Ano de publicacao: %d", livroAux.ano_publicacao);
				pularLinha(posX, posY);
				buscadorLivAut = buscarLivroLivAut(PtrLivAut, livroAux.id_livro);
				while (buscadorLivAut >= 0) {
					fseek(PtrLivAut, buscadorLivAut, SEEK_SET);
					fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
					buscadorAutor = buscarAutor(PtrAutor, livAutAux.id_autor);
					fseek(PtrAutor, buscadorAutor, SEEK_SET);
					fread(&autorAux, sizeof(autor), 1, PtrAutor);
					pularLinha(posX, posY);
					if (posY > 22) {
						pausarRelatorio(posX, posY);
					}
					printf("Autor %d: %s", contador++, autorAux.nome);
					buscadorLivAut = buscarLivroLivAutPos(PtrLivAut, livroAux.id_livro, buscadorLivAut + sizeof(livAut));
				}
				if (toupper(getch()) == 'X')
					encerrado = 1;
				else fread(&livroAux, sizeof(livro), 1, PtrLivro);
			}
			else fread(&livroAux, sizeof(livro), 1, PtrLivro);
		}
		fclose(PtrLivro);
		fclose(PtrAutor);
		fclose(PtrLivAut);
	}
}

void relatorioB(int &posX, int &posY) {
	int encerrado = 0, buscadorLivro, buscadorAutor, buscadorLivAut, contador;
	struct livro livroAux;
	struct autor autorAux;
	struct livAut livAutAux;
	FILE *PtrLivro = fopen("livros.dat", "rb");
	FILE *PtrAutor = fopen("autores.dat", "rb");
	FILE *PtrLivAut = fopen("livaut.dat", "rb");
	if (PtrLivro == NULL || PtrAutor == NULL || PtrLivAut == NULL) {
		erroAbertura();
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
		if (PtrAutor != NULL) {
			fclose(PtrAutor);
		}
		if (PtrLivAut != NULL) {
			fclose(PtrLivAut);
		}
	}
	else {
		posMsg(WHITE);
		printf("Pressione [X] para sair");
		fread(&autorAux, sizeof(autor), 1, PtrAutor);
		while (!feof(PtrAutor) && !encerrado) {
			contador = 1;
			limparTela(posX, posY);
			primeiraLinha(posX, posY);
			if (autorAux.status == 1) {
				printf("ID do autor: %d", autorAux.id_autor);
				pularLinha(posX, posY);
				printf("Nome: %s", autorAux.nome);
				pularLinha(posX, posY);
				printf("Nacionalidade: %s", autorAux.nacionalidade);
				pularLinha(posX, posY);
				buscadorLivAut = buscarAutorLivAut(PtrLivAut, autorAux.id_autor);
				while (buscadorLivAut >= 0) {
					fseek(PtrLivAut, buscadorLivAut, SEEK_SET);
					fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
					buscadorLivro = buscarLivro(PtrLivro, livAutAux.id_livro);
					fseek(PtrLivro, buscadorLivro, SEEK_SET);
					fread(&livroAux, sizeof(livro), 1, PtrLivro);
					pularLinha(posX, posY);
					if (posY > 22) {
						pausarRelatorio(posX, posY);
					}
					printf("Livro %d: %s", contador++, livroAux.titulo);
					buscadorLivAut = buscarAutorLivAutPos(PtrLivAut, autorAux.id_autor, buscadorLivAut + sizeof(livAut));
				}
				if (toupper(getch()) == 'X')
					encerrado = 1;
				else fread(&autorAux, sizeof(autor), 1, PtrAutor);
			}
			else fread(&autorAux, sizeof(autor), 1, PtrAutor);
		}
		fclose(PtrLivro);
		fclose(PtrAutor);
		fclose(PtrLivAut);
	}
}

void relatorioC(int &posX, int &posY) {
	int encerrado = 0, buscadorEmprestimo, buscadorLivro, buscadorPessoa;
	struct emprestimo emprestimoAux;
	struct livro livroAux;
	struct pessoa pessoaAux;
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb");
	FILE *PtrLivro = fopen("livros.dat", "rb");
	FILE *PtrPessoa = fopen("pessoas.dat", "rb");
	if (PtrEmprestimo == NULL || PtrLivro == NULL || PtrPessoa == NULL) {
		erroAbertura();
		if (PtrEmprestimo != NULL) {
			fclose(PtrEmprestimo);
		}
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
		if (PtrPessoa != NULL) {
			fclose(PtrPessoa);
		}
	}
	else {
		posMsg(WHITE);
		printf("Pressione [X] para sair");
		fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
		while (!feof(PtrEmprestimo) && !encerrado) {
			limparTela(posX, posY);
			primeiraLinha(posX, posY);
			if (emprestimoAux.status == 1) {
				printf("ID do emprestimo: %d", emprestimoAux.id_emprestimo);
				pularLinha(posX, posY);
				printf("Data do emprestimo: %d/%d/%d", emprestimoAux.data_emprestimo.dia, emprestimoAux.data_emprestimo.mes, emprestimoAux.data_emprestimo.ano);
				pularLinha(posX, posY);
				printf("Data da devolucao: %d/%d/%d", emprestimoAux.data_devolucao.dia, emprestimoAux.data_devolucao.mes, emprestimoAux.data_devolucao.ano);
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID do livro: %d", emprestimoAux.id_livro);
				buscadorLivro = buscarLivro(PtrLivro, emprestimoAux.id_livro);
				if (buscadorLivro >= 0) {
					pularLinha(posX, posY);
					fseek(PtrLivro, buscadorLivro, SEEK_SET);
					fread(&livroAux, sizeof(livro), 1, PtrLivro);
					printf("Titulo: %s", livroAux.titulo);
					pularLinha(posX, posY);
					printf("Ano de publicacao: %d", livroAux.ano_publicacao);
				}
				pularLinha(posX, posY);
				pularLinha(posX, posY);
				printf("ID da pessoa: %d", emprestimoAux.id_pessoa);
				buscadorPessoa = buscarPessoa(PtrPessoa, emprestimoAux.id_pessoa);
				if (buscadorPessoa >= 0) {
					pularLinha(posX, posY);
					fseek(PtrPessoa, buscadorPessoa, SEEK_SET);
					fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
					printf("Nome: %s", pessoaAux.nome);
					pularLinha(posX, posY);
					printf("Telefone: %s", pessoaAux.telefone);
					pularLinha(posX, posY);
					printf("Endereco: %s", pessoaAux.endereco);
				}
				if (toupper(getch()) == 'X') {
					encerrado = 1;
				}
				else fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
			}
			else fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
		}
		fclose(PtrEmprestimo);
		fclose(PtrLivro);
		fclose(PtrPessoa);
	}
}

void relatorioD(int &posX, int &posY) {
	int encerrado = 0;
	struct pessoa pessoaAux;
	FILE *PtrPessoa = fopen("pessoas.dat", "rb");
	if (PtrPessoa == NULL) {
		erroAbertura();
	}
	else {
		posMsg(WHITE);
		printf("Pressione [X] para sair");
		fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
		while (!encerrado && !feof(PtrPessoa)) {
			if (pessoaAux.status == 1) {
				limparTela(posX, posY);
				primeiraLinha(posX, posY);
				printf("ID da pessoa: %d", pessoaAux.id_pessoa);
				pularLinha(posX, posY);
				printf("Nome: %s", pessoaAux.nome);
				pularLinha(posX, posY);
				printf("Telefone: %s", pessoaAux.telefone);
				pularLinha(posX, posY);
				printf("Endereco: %s", pessoaAux.endereco);
				if (toupper(getch()) == 'X') {
					encerrado = 1;
				}
				else fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
			}
			else fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
		}
		fclose(PtrPessoa);
	}
}

void relatorioE(int &posX, int &posY) {
	int encerrado = 0, contador = 1, buscadorLivro, buscadorAutor;
	struct livAut livAutAux;
	struct livro livroAux;
	struct autor autorAux;
	FILE *PtrLivAut = fopen("livaut.dat", "rb");
	FILE *PtrLivro = fopen("livros.dat", "rb");
	FILE *PtrAutor = fopen("autores.dat", "rb");
	if (PtrLivAut == NULL || PtrLivro == NULL || PtrAutor == NULL) {
		erroAbertura();
		if (PtrLivAut != NULL) {
			fclose(PtrLivAut);
		}
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
		if (PtrAutor != NULL) {
			fclose(PtrAutor);
		}
	}
	else {
		posMsg(WHITE);
		printf("Pressione [X] para sair");
		fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
		while (!feof(PtrLivAut) && !encerrado) {
			limparTela(posX, posY);
			primeiraLinha(posX, posY);
			printf("Relacionamento %d", contador);
			pularLinha(posX, posY);
			if (livAutAux.status == 1) {
				buscadorLivro = buscarLivro(PtrLivro, livAutAux.id_livro);
				if (buscadorLivro >= 0) {
					fseek(PtrLivro, buscadorLivro, SEEK_SET);
					fread(&livroAux, sizeof(livro), 1, PtrLivro);
					pularLinha(posX, posY);
					printf("ID do livro: %d", livroAux.id_livro);
					pularLinha(posX, posY);
					printf("Titulo: %s", livroAux.titulo);
					pularLinha(posX, posY);
					printf("Ano de publicacao: %d", livroAux.ano_publicacao);
					pularLinha(posX, posY);
				}
				buscadorAutor = buscarAutor(PtrAutor, livAutAux.id_autor);
				if (buscadorAutor >= 0) {
					fseek(PtrAutor, buscadorAutor, SEEK_SET);
					fread(&autorAux, sizeof(autor), 1, PtrAutor);
					pularLinha(posX, posY);
					printf("ID do autor: %d", autorAux.id_autor);
					pularLinha(posX, posY);
					printf("Nome: %s", autorAux.nome);
					pularLinha(posX, posY);
					printf("Nacionalidade: %s", autorAux.nacionalidade);
				}
				if (toupper(getch()) == 'X') {
					encerrado = 1;
				}
				else {
					fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
					contador++;
				}
			}
			else fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
		}
		fclose(PtrLivAut);
		fclose(PtrLivro);
		fclose(PtrAutor);
	}
}

void relatorioF(int &posX, int &posY) {
	int encontrado = 0;
	char inicial;
	struct autor autorAux;
	FILE *PtrAutor = fopen("autores.dat", "rb");
	if (PtrAutor == NULL) {
		erroAbertura();
	}
	else {
		ordenarAutoresNacionalidade(PtrAutor);
		posMsg(WHITE);
		printf("Pressione a tecla com a inicial a ser buscada");
		rewind(PtrAutor);
		limparTela(posX, posY);
		primeiraLinha(posX, posY);
		printf("Inicial a ser buscada: ");
		inicial = toupper(getch());
		printf("%c", inicial);
		pularLinha(posX, posY);
		pularLinha(posX, posY);
		fread(&autorAux, sizeof(autor), 1, PtrAutor);
		while(!feof(PtrAutor)) {
			if (autorAux.status == 1 && autorAux.nome[0] == inicial) {
				encontrado = 1;
				printf("ID do autor: %d", autorAux.id_autor);
				pularLinha(posX, posY);
				printf("Nome: %s", autorAux.nome);
				pularLinha(posX, posY);
				printf("Nacionalidade: %s", autorAux.nacionalidade);
				pularLinha(posX, posY);
				if (posY > 20) {
					pausarRelatorio(posX, posY);
				}
			}
			fread(&autorAux, sizeof(autor), 1, PtrAutor);
		}
		if (!encontrado) {
			posMsg(LIGHTRED);
			printf("Nenhum autor foi encontrado");
			textcolor(WHITE);
		}
		getch();
		fclose(PtrAutor);
		ordenarAutores();
	}
}

void relatorioG(int &posX, int &posY) {
	int encontrado = 0;
	char palavra[TFTitulo];
	struct livro livroAux;
	FILE *PtrLivro = fopen("livros.dat", "rb");
	if (PtrLivro == NULL) {
		erroAbertura();
	}
	else {
		ordenarLivrosAnoPublicacao(PtrLivro);
		rewind(PtrLivro);
		limparTela(posX, posY);
		posMsg(WHITE);
		printf("Pressione [ENTER] com uma entrada vazia para sair");
		primeiraLinha(posX, posY);
		textcolor(YELLOW);
		printf("OBS: Se houver espacos, somente a primeira parte sera buscada");
		textcolor(WHITE);
		pularLinha(posX, posY);
		printf("Palavra a ser buscada: ");
		meuGets(palavra);
		pularLinha(posX, posY);
		pularLinha(posX, posY);
		if (stricmp(palavra, "\0") != 0) {
			fread(&livroAux, sizeof(livro), 1, PtrLivro);
			while (!feof(PtrLivro)) {
				if (livroAux.status == 1) {
					if (buscarPalavraTitulo(livroAux.titulo, palavra)) {
						encontrado = 1;
						printf("ID do livro: %d", livroAux.id_livro);
						pularLinha(posX, posY);
						printf("Titulo: %s", livroAux.titulo);
						pularLinha(posX, posY);
						printf("Ano de publicacao: %d", livroAux.ano_publicacao);
						if (posY > 20) {
							pausarRelatorio(posX, posY);
						}
					}
				}
				fread(&livroAux, sizeof(livro), 1, PtrLivro);
			}
			if (!encontrado) {
				posMsg(LIGHTRED);
				printf("Nenhum livro encontrado");
				textcolor(WHITE);
			}
			else {
				posMsg(LIGHTGREEN);
				printf("Livro(s) encontrado(s)");
				textcolor(WHITE);
			}
			getch();
		}
		fclose(PtrLivro);
		ordenarLivros();
	}
}

void relatorioH(int &posX, int &posY) {
	int encerrado = 0, buscadorEmprestimo, buscadorPessoa, buscadorLivro, id_pessoa;
	struct emprestimo emprestimoAux;
	struct pessoa pessoaAux;
	struct livro livroAux;
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb");
	FILE *PtrPessoa = fopen("pessoas.dat", "rb");
	FILE *PtrLivro = fopen("livros.dat", "rb");
	if (PtrEmprestimo == NULL || PtrPessoa == NULL || PtrLivro == NULL) {
		erroAbertura();
		if (PtrEmprestimo != NULL) {
			fclose(PtrEmprestimo);
		}
		if (PtrPessoa != NULL) {
			fclose(PtrPessoa);
		}
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
	}
	else {
		posMsg(WHITE);
		printf("Digite um valor menor ou igual a 0 para sair");
		limparTela(posX, posY);
		primeiraLinha(posX, posY);
		printf("ID da pessoa: ");
		meuScanfInt(id_pessoa);
		buscadorPessoa = buscarPessoa(PtrPessoa, id_pessoa);
		if (buscadorPessoa < 0) {
			posMsg(LIGHTRED);
			printf("Pessoa nao encontrada");
			textcolor(WHITE);
			getch();
		}
		else {
			posMsg(WHITE);
			printf("Pressione [X] para sair");
			pularLinha(posX, posY);
			fseek(PtrPessoa, buscadorPessoa, SEEK_SET);
			fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
			fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
			pularLinha(posX, posY);
			while(!feof(PtrEmprestimo) && !encerrado) {
				if (emprestimoAux.status == 1 && emprestimoAux.id_pessoa == id_pessoa) {
					printf("ID do emprestimo: %d", emprestimoAux.id_emprestimo);
					pularLinha(posX, posY);
					printf("Data do emprestimo: %d/%d/%d", emprestimoAux.data_emprestimo.dia, emprestimoAux.data_emprestimo.mes, emprestimoAux.data_emprestimo.ano);
					pularLinha(posX, posY);
					printf("Data da devolucao: %d/%d/%d", emprestimoAux.data_devolucao.dia, emprestimoAux.data_devolucao.mes, emprestimoAux.data_devolucao.ano);
					pularLinha(posX, posY);
					pularLinha(posX, posY);
					buscadorLivro = buscarLivro(PtrLivro, emprestimoAux.id_livro);
					if (buscadorLivro >= 0) {
						fseek(PtrLivro, buscadorLivro, SEEK_SET);
						fread(&livroAux, sizeof(livro), 1, PtrLivro);
						printf("ID do livro: %d", emprestimoAux.id_livro);
						pularLinha(posX, posY);
						printf("Titulo: %s", livroAux.titulo);
						pularLinha(posX, posY);
						printf("Ano de publicacao: %d", livroAux.ano_publicacao);
						pularLinha(posX, posY);
					}
					if (toupper(getch()) == 'X') {
						encerrado = 1;
					}
					else {
						limparTela(posX, posY);
						primeiraLinha(posX, posY);
						fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
					}
				}
				else fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
			}
		}
		fclose(PtrEmprestimo);
		fclose(PtrPessoa);
		fclose(PtrLivro);
	}
}

void relatorioI(int &posX, int &posY) {
	int encerrado = 0, encontrado = 0, id_autor, buscadorAutor, buscadorLivro;
	struct livro livroAux;
	struct autor autorAux;
	struct livAut livAutAux;
	FILE *PtrAutor = fopen("autores.dat", "rb");
	FILE *PtrLivro = fopen("livros.dat", "rb");
	FILE *PtrLivAut = fopen("livaut.dat", "rb");
	if (PtrAutor == NULL || PtrLivro == NULL || PtrLivAut == NULL) {
		erroAbertura();
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
		if (PtrAutor != NULL) {
			fclose(PtrAutor);
		}
		if (PtrLivAut != NULL) {
			fclose(PtrLivAut);
		}
	}
	else {
		posMsg(WHITE);
		printf("Digite um valor menor ou igual a 0 para sair");
		limparTela(posX, posY);
		primeiraLinha(posX, posY);
		do {
			printf("ID do autor: ");
			meuScanfInt(id_autor);
			if (id_autor < 0) {
				encerrado = 1;
			}
			else {
				buscadorAutor = buscarAutor(PtrAutor, id_autor);
				if (buscadorAutor < 0) {
					posMsg(LIGHTRED);
					printf("ID nao encontrado");
					textcolor(WHITE);
					limparLinha(posY);
				}
			}
		} while (!encerrado && buscadorAutor < 0);
		if (!encerrado) {
			posMsg(WHITE);
			printf("Pressione [X] para sair");
			pularLinha(posX, posY);
			pularLinha(posX, posY);
			fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
			while (!feof(PtrLivAut) && !encerrado) {
				if (livAutAux.status == 1 && livAutAux.id_autor == id_autor) {
					encontrado = 1;
					printf("ID do livro: %d", livAutAux.id_livro);
					buscadorLivro = buscarLivro(PtrLivro, livAutAux.id_livro);
					if (buscadorLivro >= 0) {
						fseek(PtrLivro, buscadorLivro, SEEK_SET);
						fread(&livroAux, sizeof(livro), 1, PtrLivro);
						pularLinha(posX, posY);
						printf("Titulo: %s", livroAux.titulo);
						pularLinha(posX, posY);
						printf("Ano de publicacao: %d", livroAux.ano_publicacao);
					}
					if (toupper(getch()) == 'X') {
						encerrado = 1;
					}
					else {
						fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
						limparTela(posX, posY);
						primeiraLinha(posX, posY);
					}
				}
				else fread(&livAutAux, sizeof(livAut), 1, PtrLivAut);
			}
			if (!encontrado) {
				posMsg(LIGHTRED);
				printf("Nenhum livro encontrado");
				getch();
			}
			textcolor(WHITE);
		}
		fclose(PtrLivro);
		fclose(PtrAutor);
		fclose(PtrLivAut);
	}
}

void relatorioJ(int &posX, int &posY) {
	int encerrado = 0, encontrado = 0, buscadorLivro;
	struct emprestimo emprestimoAux;
	struct pessoa pessoaAux;
	struct livro livroAux;
	FILE *PtrEmprestimo = fopen("emprestimos.dat", "rb");
	FILE *PtrPessoa = fopen("pessoas.dat", "rb");
	FILE *PtrLivro = fopen("livros.dat", "rb");
	if (PtrPessoa == NULL || PtrEmprestimo == NULL || PtrLivro == NULL) {
		erroAbertura();
		if (PtrPessoa != NULL) {
			fclose(PtrPessoa);
		}
		if (PtrEmprestimo != NULL) {
			fclose(PtrEmprestimo);
		}
		if (PtrLivro != NULL) {
			fclose(PtrLivro);
		}
	}
	else {
		posMsg(WHITE);
		printf("Pressione [X] para sair");
		fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
		while (!feof(PtrPessoa) && !encerrado) {
			if (pessoaAux.status == 1) {
				rewind(PtrEmprestimo);
				fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
				while (!feof(PtrEmprestimo) && !encerrado) {
					if (emprestimoAux.status == 1 && emprestimoAux.id_pessoa == pessoaAux.id_pessoa) {
						encontrado = 1;
						limparTela(posX, posY);
						primeiraLinha(posX, posY);
						printf("ID da pessoa: %d", pessoaAux.id_pessoa);
						pularLinha(posX, posY);
						printf("Nome: %s", pessoaAux.nome);
						pularLinha(posX, posY);
						pularLinha(posX, posY);
						printf("ID do emprestimo: %d", emprestimoAux.id_emprestimo);
						pularLinha(posX, posY);
						printf("Data do emprestimo: %d/%d/%d", emprestimoAux.data_emprestimo.dia, emprestimoAux.data_emprestimo.mes, emprestimoAux.data_emprestimo.ano);
						pularLinha(posX, posY);
						printf("Data da devolucao: %d/%d/%d", emprestimoAux.data_devolucao.dia, emprestimoAux.data_devolucao.mes, emprestimoAux.data_devolucao.ano);
						buscadorLivro = buscarLivro(PtrLivro, emprestimoAux.id_livro);
						fseek(PtrLivro, buscadorLivro, SEEK_SET);
						fread(&livroAux, sizeof(livro), 1, PtrLivro);
						pularLinha(posX, posY);
						pularLinha(posX, posY);
						printf("ID do livro: %d", emprestimoAux.id_livro);
						pularLinha(posX, posY);
						printf("Titulo: %s", livroAux.titulo);
						if (toupper(getch()) == 'X') {
							encerrado = 1;
						}
						else fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
					}
					else fread(&emprestimoAux, sizeof(emprestimo), 1, PtrEmprestimo);
				}
				if (!encerrado)
					fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
			}
			else fread(&pessoaAux, sizeof(pessoa), 1, PtrPessoa);
		}
		fclose(PtrLivro);
		fclose(PtrPessoa);
		fclose(PtrEmprestimo);
	}
}

// ### Sair do programa ###

char sair(int &posX, int &posY) {
	char selecao;
	primeiraLinha(posX, posY);
	printf("Deseja mesmo sair? ([S] para confirmar)");
	selecao = toupper(getch());
	if (selecao == 'S') {
		posMsg(YELLOW);
		printf("Encerrando...");
		deletarLivros();
		deletarAutores();
		deletarEmprestimos();
		deletarPessoas();
		deletarLivAut();
		textcolor(LIGHTCYAN);
		primeiraLinha(posX, posY);
		printf("Programa produzido por Daniel Salles Batista (;D)");
		pularLinha(posX, posY);
		printf("R.A.: 26.24.1096-6");
		posMsg(LIGHTRED);
		printf("Programa encerrado.");
		gotoxy(1, 26);
		return 27;
	}
	else {
		return 0;
	}
}

// ### Menus ###

char menuCadastros(int &posX, int &posY) {
	char selecao;
	printf("[A] Cadastrar livro");
	pularLinha(posX, posY);
	printf("[B] Cadastrar autor");
	pularLinha(posX, posY);
	printf("[C] Cadastrar emprestimo");
	pularLinha(posX, posY);
	printf("[D] Cadastrar pessoa");
	pularLinha(posX, posY);
	printf("[E] Associar livro a um autor");
	pularLinha(posX, posY);
	printf("[ESC] Sair");
	pularLinha(posX, posY);
	do {
		selecao = toupper(getch());
	} while ((selecao < 'A' || selecao > 'E') && selecao != 27);
	return selecao;
}

char menuExclusoes(int &posX, int &posY) {
	char selecao;
	printf("[A] Excluir livro");
	pularLinha(posX, posY);
	printf("[B] Excluir autor");
	pularLinha(posX, posY);
	printf("[C] Excluir emprestimo");
	pularLinha(posX, posY);
	printf("[D] Excluir pessoa");
	pularLinha(posX, posY);
	printf("[E] Desassociar livro de um autor");
	pularLinha(posX, posY);
	printf("[ESC] Sair");
	pularLinha(posX, posY);
	do {
		selecao = toupper(getch());
	} while ((selecao < 'A' || selecao > 'E') && selecao != 27);
	return selecao;
}

char menuAlteracoes(int &posX, int &posY) {
	char selecao;
	printf("[A] Alterar livro");
	pularLinha(posX, posY);
	printf("[B] Alterar autor");
	pularLinha(posX, posY);
	printf("[C] Alterar emprestimo");
	pularLinha(posX, posY);
	printf("[D] Alterar pessoa");
	pularLinha(posX, posY);
	// Alterações de relacionamento livro-autor não serão feitas, visto que ambos os campos disponíveis são chaves primárias
	printf("[ESC] Sair");
	pularLinha(posX, posY);
	do {
		selecao = toupper(getch());
	} while ((selecao < 'A' || selecao > 'E') && selecao != 27);
	return selecao;
}

char menuConsultas(int &posX, int &posY) {
	char selecao;
	printf("[A] Consultar livro");
	pularLinha(posX, posY);
	printf("[B] Consultar autor");
	pularLinha(posX, posY);
	printf("[C] Consultar emprestimo");
	pularLinha(posX, posY);
	printf("[D] Consultar pessoa");
	pularLinha(posX, posY);
	printf("[E] Verificar associacao livro-autor");
	pularLinha(posX, posY);
	printf("[ESC] Sair");
	pularLinha(posX, posY);
	do {
		selecao = toupper(getch());
	} while ((selecao < 'A' || selecao > 'E') && selecao != 27);
	return selecao;
}

char menuRelatorios(int &posX, int &posY) {
	char selecao;
	printf("[A] Exibir todos os livros (com detalhes)");
	pularLinha(posX, posY);
	printf("[B] Exibir todos os autores (com detalhes)");
	pularLinha(posX, posY);
	printf("[C] Exibir todos os emprestimos (com detalhes)");
	pularLinha(posX, posY);
	printf("[D] Exibir todas as pessoas (com detalhes)");
	pularLinha(posX, posY);
	printf("[E] Exibir todas as associacoes livro-autor (com detalhes)");
	pularLinha(posX, posY);
	printf("[F] Buscar autores pela inicial do primeiro nome (ordem de nacionalidade)");
	pularLinha(posX, posY);
	printf("[G] Buscar livros por palavra (ordem de publicacao)");
	pularLinha(posX, posY);
	printf("[H] Exibir emprestimos de uma pessoa");
	pularLinha(posX, posY);
	printf("[I] Exibir dados de livros de um autor");
	pularLinha(posX, posY);
	printf("[J] Exibir todos os emprestimos separados por pessoa");
	pularLinha(posX, posY);
	printf("[ESC] Sair");
	pularLinha(posX, posY);
	do {
		selecao = toupper(getch());
	} while ((selecao < 'A' || selecao > 'J') && selecao != 27);
	return selecao;
}

char menuPrincipal(int &posX, int &posY) {
	char selecao;
	printf("[A] Gerar dados para testes");
	pularLinha(posX, posY);
	printf("[B] Cadastros");
	pularLinha(posX, posY);
	printf("[C] Exclusoes");
	pularLinha(posX, posY);
	printf("[D] Alteracoes");
	pularLinha(posX, posY);
	printf("[E] Consultas");
	pularLinha(posX, posY);
	printf("[F] Relatorios");
	pularLinha(posX, posY);
	printf("[ESC] Sair");
	pularLinha(posX, posY);
	do {
		selecao = toupper(getch());
	} while ((selecao < 'A' || selecao > 'F') && selecao != 27);
	return selecao;
}

// ### Execução do programa ###

void executar(void) {
	int posX = 1, posY = 1;
	char selecaoMenu, selecaoAux;
	desenharJanela();
	do {
		limparTela(posX, posY);
		posMsg(WHITE);
		printf("Selecione uma das opcoes acima");
		primeiraLinha(posX, posY);
		selecaoMenu = menuPrincipal(posX, posY);
		limparTela(posX, posY);
		primeiraLinha(posX, posY);
		switch(selecaoMenu) {
			case 'A':
				gerarDados(posX, posY);
				break;
			case 'B':
				selecaoAux = menuCadastros(posX, posY);
				switch(selecaoAux) {
					case 'A':
						cadastrarLivro(posX, posY);
						break;
					case 'B':
						cadastrarAutor(posX, posY);
						break;
					case 'C':
						cadastraEmprestimo(posX, posY);
						break;
					case 'D':
						cadastrarPessoa(posX, posY);
						break;
					case 'E':
						cadastrarLivAut(posX, posY);
						break;
				}
				break;
			case 'C':
				selecaoAux = menuExclusoes(posX, posY);
				switch(selecaoAux) {
					case 'A':
						excluirLivro(posX, posY);
						break;
					case 'B':
						excluirAutor(posX, posY);
						break;
					case 'C':
						excluirEmprestimo(posX, posY);
						break;
					case 'D':
						excluirPessoa(posX, posY);
						break;
					case 'E':
						excluirLivAut(posX, posY);
						break;
				}
				break;
			case 'D':
				selecaoAux = menuAlteracoes(posX, posY);
				switch(selecaoAux) {
					case 'A':
						alterarLivro(posX, posY);
						break;
					case 'B':
						alterarAutor(posX, posY);
						break;
					case 'C':
						alterarEmprestimo(posX, posY);
						break;
					case 'D':
						alterarPessoa(posX, posY);
						break;
				}
				break;
			case 'E':
				selecaoAux = menuConsultas(posX, posY);
				switch(selecaoAux) {
					case 'A':
						consultarLivro(posX, posY);
						break;
					case 'B':
						consultarAutor(posX, posY);
						break;
					case 'C':
						consultarEmprestimo(posX, posY);
						break;
					case 'D':
						consultarPessoa(posX, posY);
						break;
					case 'E':
						consultarLivAut(posX, posY);
						break;
				}
				break;
			case 'F':
				selecaoAux = menuRelatorios(posX, posY);
				switch(selecaoAux) {
					case 'A':
						relatorioA(posX, posY);
						break;
					case 'B':
						relatorioB(posX, posY);
						break;
					case 'C':
						relatorioC(posX, posY);
						break;
					case 'D':
						relatorioD(posX, posY);
						break;
					case 'E':
						relatorioE(posX, posY);
						break;
					case 'F':
						relatorioF(posX, posY);
						break;
					case 'G':
						relatorioG(posX, posY);
						break;
					case 'H':
						relatorioH(posX, posY);
						break;
					case 'I':
						relatorioI(posX, posY);
						break;
					case 'J':
						relatorioJ(posX, posY);
						break;
				}
				break;
			case 27:
				selecaoMenu = sair(posX, posY);
				break;
		}
	} while (selecaoMenu != 27);
}

int main() {
	executar();
	return 0;
}



