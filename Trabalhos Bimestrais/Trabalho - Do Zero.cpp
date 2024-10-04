#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>
#include <windows.h>

#define TF 100

struct TpAlunos
{
	char RA[13], Nome[40];
};

struct TpDisc
{
	int CodDisc;
	char Disciplina[40];
};

struct TpNotas
{
	char RA[13];
	int CodDisc, Nota;
};

void Moldura(int CI,int LI, int CF, int LF, int CorT,int CorF)
{
	int i;
	textcolor(CorT);
	textbackground(CorF);
	gotoxy(CI, LI); printf("%c", 201);
	gotoxy(CF, LI); printf("%c", 187);
	gotoxy(CI, LF); printf("%c", 200);
	gotoxy(CF, LF); printf("%c", 188);
	
	for(i = CI + 1; i < CF; i++)
	{
		gotoxy(i, LI); printf("%c", 205);
		gotoxy(i, LF); printf("%c", 205);
	}
	for(i = LI + 1; i < LF; i++)
	{
		gotoxy(CI, i); printf("%c", 186);
		gotoxy(CF, i); printf("%c", 186);
	}
	textcolor(7);
	textbackground(0);
}

void PainelPrincipal(void)
{
	Moldura(1,1,166,25,1,7); //branco
	Moldura(2,2,165,4,2,6); //titulo
	textcolor(15);
	gotoxy(67,3);
	printf("Cadastro de Alunos, Notas e Disciplinas");
	Moldura(40,5,165,24,3,14); //tela principal
	Moldura(2,5,39,24,8,13); //menu
	Moldura(3,22,38,24,6,3); //mensagem
	textcolor(15);
}

char Menu(void)
{
	textcolor(15);
	gotoxy(17,6);
	printf("M E N U ");
	textcolor(15);
	gotoxy(4,8);
	printf("[A] Cadastrar");
	gotoxy(4,10);
	printf("[B] Exibir");
	gotoxy(4,12);
	printf("[C] Consultar por Nome");
	gotoxy(4,14);
	printf("[D] Ordenar por Nome");
	gotoxy(4,16);
	printf("[E] Excluir por RA");
	gotoxy(4,18);
	printf("[F] Alterar por Nome");
	gotoxy(4,20);
	printf("[ESC] Finalizar");
	gotoxy(4,23);
	printf("Opcao Desejada: ");
	
	return toupper(getch());
}

void Limpar(void)
{
	int col, lin;
	textbackground(0);
	
	for(col = 20, lin = 6; col < 75; col++, lin++)
	{
		gotoxy(col, lin);
		printf("%c", 32);
	}
}

void CadAuto(TpAlunos TabAl[TF], TpDisc TabDi[TF], TpNotas TabNo[TF], int &TLA, int &TLA2, int &TLA3)
{
	 TLA = 0;TLA2 = 0; TLA3 = 0;
	
	//===================ALUNOS========================
	
	strcpy(TabAl[TLA].RA,"12.04.1987-5");
	strcpy(TabAl[TLA++].Nome,"Alberto");
	strcpy(TabAl[TLA].RA,"03.11.2000-2");
	strcpy(TabAl[TLA++].Nome,"Carlos");
	strcpy(TabAl[TLA].RA,"25.06.2015-8");
	strcpy(TabAl[TLA++].Nome,"Jarros");
	strcpy(TabAl[TLA].RA,"08.09.1992-1");
	strcpy(TabAl[TLA++].Nome,"Sabetico");
	strcpy(TabAl[TLA].RA,"17.02.2023-4");
	strcpy(TabAl[TLA++].Nome,"Yuri");
	
	//===============DISCIPLINAS=======================
	
	TabDi[TLA2].CodDisc = 100;
	strcpy(TabDi[TLA2++].Disciplina,"ATP I");
	TabDi[TLA2++].CodDisc = 111;
	strcpy(TabDi[TLA2++].Disciplina,"ATP II");
	TabDi[TLA2].CodDisc = 133;
	strcpy(TabDi[TLA2++].Disciplina,"Estrutura dados");
	TabDi[TLA2].CodDisc = 160;
	strcpy(TabDi[TLA2++].Disciplina,"Dados");
	TabDi[TLA2].CodDisc = 200;
	strcpy(TabDi[TLA2].Disciplina,"Engenharia de dados");
	
//=================ALUNOS/DISCIPLINAS=================
	
	strcpy(TabNo[TLA3].RA,"12.04.1987-5");
	TabNo[TLA3].CodDisc = 210;
	TabNo[TLA3++].Nota = 8;
	strcpy(TabNo[TLA3].RA,"03.11.2000-2");
	TabNo[TLA3].CodDisc = 133;
	TabNo[TLA3++].Nota = 2;
	strcpy(TabNo[TLA3].RA,"25.06.2015-8");
	TabNo[TLA3].CodDisc = 111;
	TabNo[TLA3++].Nota = 6;
	strcpy(TabNo[TLA3].RA,"08.09.1992-1");
	TabNo[TLA3].CodDisc = 210;
	TabNo[TLA3++].Nota = 4;
	strcpy(TabNo[TLA3].RA,"17.02.2023-4");
	TabNo[TLA3].CodDisc = 160;
	TabNo[TLA3].Nota = 9;
}

void Executar(void)
{
	PainelPrincipal();
	TpAlunos TabAl[TF];
	TpDisc TabDi[TF];
	TpNotas TabNo[TF];
	int tl = 0, TLA, TLA2, TLA3;
	char Opcao;
	do
	{
		Opcao = Menu();
		switch(Opcao)
		{	
			case'A':CadAuto(TabAl, TabDi, TabNo, TLA, TLA2, TLA3);
					getch();
					break;
					
			case'B':gotoxy(45,7);
					printf("teste kkkkkkk");
					getch();
					gotoxy(45,9);
					printf("teste kkkkkkk");
					break;
		}
	}while(Opcao!=27);
}

int main(void)
{
	Executar();
	getch();
	printf("\n\n\n\n\n\n\n\n");
	return 0;
}
