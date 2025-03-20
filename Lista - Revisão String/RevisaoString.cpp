#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define TF 100

char Menu()
{
    char op;
    system("cls");

    printf("Digite o numero da opcao desejada ou X para sair.\n");
    printf("==================================================\n");

    printf("\n1 - Exercicio 1\n");
    printf("2 - Exercicio 2\n");
    printf("3 - Exercicio 3\n");
    printf("4 - Exercicio 4\n");
    printf("5 - Exercicio 5\n");
    printf("6 - Exercicio 6\n");
    printf("7 - Exercicio 7\n");
    printf("8 - Exercicio 8\n");
    printf("9 - Exercicio 9\n");
    printf("10 - Exercicio 10\n");

    fflush(stdin);
    op = toupper(getche());
    return op;
}

int main(void)
{
    char op;
    op = Menu();

    switch (op)
    {
        case '1':
            printf("\n========[Exercicio 1]========\n");
            break;

        case '2':
            printf("\n========[Exercicio 2]========\n");
            break;

        case '3':
            printf("\n========[Exercicio 3]========\n");
            break;

        case '4':
            printf("\n========[Exercicio 4]========\n");
            break;

        case '5':
            printf("\n========[Exercicio 5]========\n");
            break;

        case '6':
            printf("\n========[Exercicio 6]========\n");
            break;

        case '7':
            printf("\n========[Exercicio 7]========\n");
            break;

        case '8':
            printf("\n========[Exercicio 8]========\n");
            break;

        case '9':
            printf("\n========[Exercicio 9]========\n");
            break;

        case '10':
            printf("\n========[Exercicio 10]========\n");
            break;
            
        case 'X': case 'x':
            printf("\n========[Fim do Programa]========\n");
            break;
        
        default:
            printf("\nOpcao Invalida\n");
            break;
    }
}