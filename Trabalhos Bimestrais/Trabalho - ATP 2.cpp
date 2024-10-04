#include <stdio.h>
#include <ctype.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//#include "meuconio.h"
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

//cadastro automatico
void CadAuto(TpAlunos TabAl[TF], TpDisc TabDi[TF], TpNotas TabNo[TF], int &TLA, int &TLA2, int &TLA3)
{
	 TLA = 0;TLA2 = 0; TLA3 = 0;
	
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
	
	//===================================
	
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
	
//===================================================
	
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

//exibir tabelas
void exibe(TpAlunos TabAl[TF], TpDisc TabDi[TF], TpNotas TabNo[TF], int &TLA)
{
	int i;
	if(TLA =! 0)
	for(i=0;i<TLA;i++)
	{	
		gotoxy(39,i*2+7);
		printf("RA:%s",TabAl[i].RA);	
		gotoxy(39,i*2+8);
		printf("Nome:%s",TabAl[i].Nome);
		
		gotoxy(60,i*2+7);
		printf("Codigo da materia:%d",TabDi[i].CodDisc);	
		gotoxy(60,i*2+8);
		printf("Disciplina:%s",TabDi[i].Disciplina);
		
		gotoxy(90,i*3+7);
		printf("RA:%s",TabNo[i].RA);	
		gotoxy(90,i*3+8);
		printf("Disciplina:%d",TabNo[i].CodDisc);
		gotoxy(90,i*3+9);
		printf("Nota:%d",TabNo[i].Nota);
	}
	else
	printf("Não possui dadso salvous");
	getch();
}


//Entrada com animacao para inicio
void moldura(int CI, int LI, int CF, int LF, int CorT, int CorF, int temp)
{
	int i,j;
	
	textcolor(CorT);
	textbackground(CorF);
	gotoxy(CI, LI); printf("%c", 201);
	gotoxy(CF, LI); printf("%c", 187);
	gotoxy(CI, LF); printf("%c", 200);
	gotoxy(CF, LF); printf("%c", 188);
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI);printf("%c", 205);
		Sleep(temp);
		gotoxy(i,LF); printf("%c", 205);
	}
	for(j=LI+1; j<LF; j++){
		gotoxy(CI,j);printf("%c", 186);
		Sleep(temp);
		gotoxy(CF,j); printf("%c", 186);	
	}
}

//Padronizacao das fontes
void cor(){
	textcolor(WHITE);
	textbackground(16);
}

//Menu, print dos itens para selecionar
char menu(void)
{
	gotoxy(5,7);
	printf("[A]Cadastrar");
	gotoxy(5,8);
	printf("[B]Exibir");
	gotoxy(5,9);
	printf("[C]Consultar por nome");
	gotoxy(5,10);
	printf("[D]Teste");
	gotoxy(5,11);
	printf("[E]Exibir tabelas");
	gotoxy(5,12);
	printf("[F]Tabelas pronta");
	gotoxy(5,13);
	printf("[ESC]Sair");
	gotoxy(5,14);
	printf("Opcao desejada");
	gotoxy(5,16);
	return toupper(getche());
}

//Montagem principal aumentar ultima cvariavel pra 10
void PainelPrincipal(void)
{
	system("cls");
	moldura(1,1,120,25,1,7,0);
	moldura(2,2,119,4,2,6,0);
	moldura(2,5,30,24,8,13,0);
	moldura(31,5,119,24,3,14,0);
	gotoxy(28,3);
	cor();
	printf("TITULO do programa");
}

//montagem secundaria
void PainelPrincipal2(void)
{
	system("cls");
	moldura(1,1,120,25,1,7,0);
	moldura(2,2,119,4,2,6,0);
	moldura(2,5,30,24,8,13,0);
	moldura(31,5,119,24,3,14,0);
	gotoxy(50,3);
	cor();
	printf("Notas do Psor");

}

void executarMenu(void)
{
	TpAlunos TabAl[TF];
	TpDisc TabDi[TF];
	TpNotas TabNo[TF];
	
	int Tlag=0,Tlag2=0,Tlag3=0; 
	char opcao;
	do
	{
		PainelPrincipal2();
		opcao=menu();
		switch(opcao)
		{	
			case'A':
					break;
			case'B':;
					break;
			case'C':;
					break;
			case'D':gotoxy(40,10);
					printf("teste afirmativo"); 
					getch();
					break;
			case'E':exibe(TabAl, TabDi, TabNo, Tlag);
					break;
			case'F':CadAuto(TabAl, TabDi, TabNo, Tlag, Tlag2, Tlag3);
					break;	
		}
	}while(opcao!=27);
}

int main()
{	
	PainelPrincipal();
	executarMenu();
	
	getch();
	return 0;
}
