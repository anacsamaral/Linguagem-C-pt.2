#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define TF 20

struct TpAgenda
{
    char Nome[30], Endereco[40], Fone[15];
    //Agenda; --> seria a variável (global) sendo declarada logo depois da Struct (não recomendado)
};

void CadAgenda(TpAgenda TabAgenda[TF], int &TL)
{   
    char AuxNome[30];

    system("cls");
    printf("\nCadastro de Pessoas\n");
    printf("Nome: ");
    fflush(stdin);
    gets(AuxNome);
    while (TL < TL && strcmp(AuxNome,"\0") != 0)
    {
        strcpy(TabAgenda[TL].Nome, AuxNome);
        printf("Endereco: ");
        fflush(stdin);
        gets(TabAgenda[TL].Endereco);
        printf("Telefone: ");
        fflush(stdin);
        gets(TabAgenda[TL].Fone);
        TL++;
        printf("\n Digite outro Nome para Cadastrar:");
        fflush(stdin);
        gets(AuxNome);
    }
    
    void ExibeAgenda(TpAgenda TabAgenda[TF], int TL)
    {
        int i;
        system("cls");
        printf("\n ## Conteudo de Agenda ##\n");
        if (TL == 0)
            printf("\n Nao ha Dados!!!\n");
        else
        {
            printf("---------------------------\n");
            printf("Nome\t\t Endereco\t\t Telefone\n");
            printf("---------------------------\n");
            for (i = 0; i < TL; i++)
                printf("%s\t\t %s\t\t %s\n", TabAgenda[i].Nome, TabAgenda[i].Endereco, TabAgenda[i].Fone);
        }
        getch();
    }

    char Menu(void)
    {
        system("cls");
        printf("\n### M E N U  A G E N D A");
        printf("\n[A] Cadastrar")
        printf("\n[B] Exibir")
        printf("\n[C] Consultar por Nome")
        printf("\n[D] Ordenar por Nome")
        printf("\n[E] Excluir pelo Telefone")
        printf("\n[F] ")
        printf("\n[ESC]")
    }
}
