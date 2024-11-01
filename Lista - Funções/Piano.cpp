#include <stdio.h>
#include <conio2.h>
#include <windows.h>

// Frequência das notas
#define DO 261
#define RE 293
#define MI 329
#define FA 349
#define SOL 392
#define LA 440
#define SI 493

int main() 
{
    char ch;
    printf("Press keys to play piano notes. Press ESC to exit.\n");

    while(1) 
	{
        ch = getch(); // Get character without pressing Enter
        
        if (ch == 27) { // ESC key to exit
            break;
        }

        switch(ch) {
            case 'A':
            case 'a':
                Beep(DO, 500); // 500ms for DO
                break;
            case 'S':
            case 's':
                Beep(RE, 500); // 500ms for RE
                break;
            case 'D':
            case 'd':
                Beep(MI, 500); // 500ms for MI
                break;
            case 'F':
            case 'f':
                Beep(FA, 500); // 500ms for FA
                break;
            case 'G':
            case 'g':
                Beep(SOL, 500); // 500ms for SOL
                break;
            case 'H':
            case 'h':
                Beep(LA, 500); // 500ms for LA
                break;
            case 'J':
            case 'j':
                Beep(SI, 500); // 500ms for SI
                break;
            default:
                printf("Invalid key! Use A, S, D, F, G, H, J for notes.\n");
                break;
        }
    }
    
    printf("Program exited.\n");
    return 0;
}

