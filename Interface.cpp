#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

void TabASCIICor(void)
{
	int i, corF = 0, corT = 15, coluna = 1, linha = 1;
	clrscr(); //system("cls");
	for(i = 0; i < 256; i++)
	{
		textcolor(corF);
		textbackground(corT);
		gotoxy(coluna,linha++);
		printf("%d-%c", i, i);
		if(linha > 23)
		{
			coluna += 7;
			corF++;
			corT--;
			linha = 1;
		}
	}
}

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
	Moldura(1,1,80,25,1,7);
	Moldura(2,2,79,4,2,6);
	textcolor(WHITE);
	gotoxy(28,3);
	printf("TITULO DO PROGRAMA");
	Moldura(2,5,28,21,3,5);
	Moldura(29,5,79,21,5,4);
	Moldura(2,22,79,24,6,3);
	textcolor(4);
	gotoxy(3,23);
	printf("Mensagem: ");
}

char Menu(void)
{
	textcolor(15);
	gotoxy(12,6);
	printf("M E N U ");
	textcolor(10);
	gotoxy(4,8);
	printf("[A] Alunos");
	gotoxy(4,10);
	printf("[B] Disciplinas");
	gotoxy(4,19);
	printf("[ESC] Finalizar");
}

int main (void)
{
	//TabASCIICor();
	PainelPrincipal();
	Menu();
	getch();
	printf("\n\n\n\n\n\n\n\n");
	return 0;
}
