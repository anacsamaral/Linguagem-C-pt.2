#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>
#include <conio.h>

#define DO 261
#define RE 293
#define MI 329
#define FA 349
#define SOL 392
#define LA 440
#define SI 493

int LeNumero(void) {
    int num;
    printf("\nDigite um valor: ");
    scanf("%d", &num);
    return num;
}

int ConverteBinario(int num) {
    int Binario = 0, mult = 1, resto;

    while (num > 0) {
        resto = num % 2;
        Binario += resto * mult;
        mult *= 10;
        num /= 2;
    }

    return Binario;
}

int ConverteDecimal(int Binario) {
    int Decimal = 0, expo = 0;

    while (Binario > 0) {
        Decimal += (Binario % 10) * pow(2, expo);
        Binario /= 10;
        expo++;
    }

    return Decimal;
}

int Fatorial(int numero) {
    if (numero < 0) {
        return -1;
    }

    int mult = 1;
    while (numero > 0) {
        mult *= numero;
        numero--;
    }

    return mult;
}

void LeHoras(int *a, int *b, int *c, int *d, int *e, int *f) {
    printf("Digite a hora inicial (hh mm ss):\n");
    scanf("%d %d %d", a, b, c);
    printf("Digite a hora final (hh mm ss):\n");
    scanf("%d %d %d", d, e, f);
}

int ConverteSegundos(int horaI, int minI, int segI, int horaF, int minF, int segF) {
    int SomaSegundosI = horaI * 3600 + minI * 60 + segI;
    int SomaSegundosF = horaF * 3600 + minF * 60 + segF;
    return SomaSegundosF - SomaSegundosI;
}

void Perfeito(int Num) {
    int SomaDiv = 0;

    for (int Divisor = 1; Divisor <= Num / 2; Divisor++) {
        if (Num % Divisor == 0) {
            SomaDiv += Divisor;
        }
    }

    if (Num == SomaDiv) {
        printf("\nNumero PERFEITO!\n");
    } else {
        printf("\nNumero NAO PERFEITO!\n");
    }
}

void Parametros(int *ColunaI, int *LinhaI, int *ColunaF, int *LinhaF) {
    printf("Digite a coluna inicial: ");
    scanf("%d", ColunaI);

    printf("Digite a linha inicial: ");
    scanf("%d", LinhaI);

    printf("Digite a coluna final: ");
    scanf("%d", ColunaF);

    printf("Digite a linha final: ");
    scanf("%d", LinhaF);
}

int Dimensao(int ColunaI, int LinhaI, int ColunaF, int LinhaF, int *Largura, int *Altura) {
    *Largura = ColunaF - ColunaI + 1;
    *Altura = LinhaF - LinhaI + 1;

    if (*Largura < 2 || *Altura < 2) {
        printf("Dimensões inválidas para uma moldura.\n");
        return 1;
    }
    return 0;
}

void Moldura(int ColunaI, int LinhaI, int ColunaF, int LinhaF, int Largura, int Altura) {
    for (int i = 0; i < ColunaI; i++) printf(" ");
    printf("+");
    for (int i = 0; i < Largura - 2; i++) printf("-");
    printf("+\n");

    for (int i = LinhaI + 1; i < LinhaF; i++) {
        for (int j = 0; j < ColunaI; j++) printf(" ");
        printf("|");
        for (int j = 0; j < Largura - 2; j++) printf(" ");
        printf("|\n");
    }

    for (int i = 0; i < ColunaI; i++) printf(" ");
    printf("+");
    for (int i = 0; i < Largura - 2; i++) printf("-");
    printf("+\n");
}

void ExibeResultado(int valor) {
    printf("\nResultado: %d\n", valor);
}

void ExibeDiferenca(int Diferenca) {
    printf("A diferenca em segundos da hora final para a inicial eh de %d segundos.\n", Diferenca);
}

char Menu(void) {
    system("cls");
    printf("### M E N U ###\n");
    printf("[A] Conversao Decimal > Binario\n");
    printf("[B] Conversao Binario > Decimal\n");
    printf("[C] Diferenca de Horas\n");
    printf("[D] Calcular Fatorial\n");
    printf("[E] Numero Perfeito\n");
    printf("[F] Piano\n");
    printf("[G] Moldura\n");
    printf("[ESC] Sair\n");
    printf("Opcao Desejada: ");
    fflush(stdin);
    return toupper(getch());
}

void Piano(void) {
	
    char ch;
    printf("Pressione teclas para tocar notas do piano. Pressione ESC para sair.\n");

    while (1) {
    	
        ch = getche();

        if (ch == 27) {
            break;
        }

        switch (ch) {
            case 'A': case 'a': Beep(DO, 500); break;
            case 'S': case 's': Beep(RE, 500); break;
            case 'D': case 'd': Beep(MI, 500); break;
            case 'F': case 'f': Beep(FA, 500); break;
            case 'G': case 'g': Beep(SOL, 500); break;
            case 'H': case 'h': Beep(LA, 500); break;
            case 'J': case 'j': Beep(SI, 500); break;
            default: printf("Tecla invalida! Use A, S, D, F, G, H, J para notas.\n"); break;
        }
    }
    printf("Programa encerrado.\n");
}

void Executar(void) {
    int hi, mi, si, hf, mf, sf, diferenca;
    int num, ColunaI, LinhaI, ColunaF, LinhaF, Largura, Altura;

    char op;
    do {
        op = Menu();

        if (op == 27) {
            printf("\nPrograma encerrado pelo usuário.\n");
            break; // Sai do loop ao pressionar ESC
        }

        switch (op) {
            case 'A':
                printf("\n### Conversao de Decimal para Binario ###\n");
                ExibeResultado(ConverteBinario(LeNumero()));
                getch();
                break;

            case 'B':
                printf("\n### Conversao de Binario para Decimal ###\n");
                ExibeResultado(ConverteDecimal(LeNumero()));
                getch();
                break;

            case 'C':
                LeHoras(&hi, &mi, &si, &hf, &mf, &sf);
                diferenca = ConverteSegundos(hi, mi, si, hf, mf, sf);
                ExibeDiferenca(diferenca);
                getch();
                break;

            case 'D':
                printf("\n### Calculo de Fatorial ###\n");
                num = LeNumero();
                ExibeResultado(Fatorial(num));
                getch();
                break;

            case 'E':
                printf("\n### Numero Perfeito ###\n");
                Perfeito(LeNumero());
                getch();
                break;

            case 'F':
                Piano();
                getch();
                break;

            case 'G':
                Parametros(&ColunaI, &LinhaI, &ColunaF, &LinhaF);
                if (Dimensao(ColunaI, LinhaI, ColunaF, LinhaF, &Largura, &Altura) == 0) {
                    Moldura(ColunaI, LinhaI, ColunaF, LinhaF, Largura, Altura);
                }
                getch();
                break;
            
            default:
                break;
        }
    } while (op != 27);
}

int main(void) {
    Executar();
    return 0;
}