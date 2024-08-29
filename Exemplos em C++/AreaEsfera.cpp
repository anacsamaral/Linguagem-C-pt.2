#include <stdio.h>
#define PI 3.14159

float area(int r); // prototipo da funcao

int main(void)
{
    int raio;
    float area_esfera;
    printf("Digite o raio da esfera: ");
    scanf("%d", &raio);       // por referencia (&)
    area_esfera = area(raio); // chamada a funcao
    printf("A area da esfera eh %.5f", area_esfera);
}

float area(int r) // definicao da funcao
{
    return (4 * PI * r * r); // retorna float
}