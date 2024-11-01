#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define DO 261
#define RE 293
#define MI 329
#define FA 349
#define SOL 392
#define LA 440
#define SI 493

char Menu(void)
{
    system("cls");
    printf("### M E N U ###");
    printf("\n[A] Conversao Decimal > Binario");
    printf("\n[B] Conversao Binario > Decimal");
    printf("\n[C] Diferenca de Horas");
    printf("\n[C] Calcular Fatorial");
    printf("\n[D] Moldura de Pontos");
    printf("\n[E] Numero Perfeito");
    printf("\n[F] Piano");
    printf("\n[ESC] Sair");
    printf("\nOpcao Desejada: ");

    return toupper(getche());
}

void Executar(void)
{
    char op;
    op = Menu();
    do
    {
        switch (op)
        {
        case 'A':
            /* code */
            break;
        case 'B':
            /* code */
            break;
        case 'C':
            /* code */
            break;
        case 'D':
            /* code */
            break;
        case 'E':
            /* code */
            break;
        case 'F':
            /* code */
            break;
        
        default:
            
            break;
        }
    } while (op != 27);
    
}

int main(void)
{
    Menu();
    return 0;
}