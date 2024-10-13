#include <stdio.h>

// Função para receber os parâmetros da moldura
void Parametros(int &ColunaI, int &LinhaI, int &ColunaF, int &LinhaF)
{
    printf("Digite a coluna inicial: ");
    scanf("%d", &ColunaI);
    
    printf("Digite a linha inicial: ");
    scanf("%d", &LinhaI);
    
    printf("Digite a coluna final: ");
    scanf("%d", &ColunaF);
    
    printf("Digite a linha final: ");
    scanf("%d", &LinhaF);
}

// Função para calcular as dimensões da moldura
int Dimensao(int ColunaI, int LinhaI, int ColunaF, int LinhaF, int &Largura, int &Altura)
{
    Largura = ColunaF - ColunaI + 1;
    Altura = LinhaF - LinhaI + 1;

    if (Largura < 2 || Altura < 2)
	{
        printf("Dimensoes invalidas para uma moldura.\n");
        return 1;
    }
    return 0;
}

// Função para desenhar a moldura na tela
void Moldura(int ColunaI, int LinhaI, int ColunaF, int LinhaF, int Largura, int Altura)
{
    // Desenha a linha superior
    for (int i = 0; i < ColunaI; i++) printf(" ");
    printf("+");
    for (int i = 0; i < Largura - 2; i++) printf("-");
    printf("+\n");

    // Desenha as linhas intermediárias
    for (int i = LinhaI + 1; i < LinhaF; i++)
	{
        for (int j = 0; j < ColunaI; j++) printf(" ");
        printf("|");
        for (int j = 0; j < Largura - 2; j++) printf(" ");
        printf("|\n");
    }

    // Desenha a linha inferior
    for (int i = 0; i < ColunaI; i++) printf(" ");
    printf("+");
    for (int i = 0; i < Largura - 2; i++) printf("-");
    printf("+\n");
}

int main(void)
{
    int ColunaI, LinhaI, ColunaF, LinhaF, Largura, Altura;

    Parametros(ColunaI, LinhaI, ColunaF, LinhaF);
    
    if (Dimensao(ColunaI, LinhaI, ColunaF, LinhaF, Largura, Altura) == 0)
        Moldura(ColunaI, LinhaI, ColunaF, LinhaF, Largura, Altura);

    return 0;
}
