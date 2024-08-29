#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

#define FILAS 20
#define POLTRONAS 15

int main(void)
{
	int Lugar[FILAS][POLTRONAS]={0}, Fila, Polt, ContOcup, ContLivres;
	char op;
	
	do
	{
		system("cls");    //clrscr();
		printf("\n### M E N U  TEATRO ###\n");
		printf("\n[A] Inicializar Reservas\n");
		printf("[B] Efetuar Reservas\n");
		printf("[C] Qtde Poltronas Livres/Ocupadas\n");
		printf("[D] Mapa de Reservas\n");
		printf("[E] Consultar Reservas\n");
		printf("[ESC] Finalizar\n");
		printf("\nOpcao desejada:");
		
		op = toupper(getche());
		switch(op)    
		{
			case 'A': printf("\nInicializar Reservas:\n");
					  Lugar[FILAS][POLTRONAS]={0};
					  getch();
					  break;
			
			case 'B': printf("\nEfetuar Reservas:\n");
					  printf("Qual a Fila? - [-1 para Sair]:\n");
					  scanf("%d",&Fila);
					  while (Fila>=0)
					  {  
						  printf("Qual a Poltrona? \n");
						  scanf("%d",&Polt);
						  if (Polt>=0)
						  {
						  	Lugar[Fila][Polt]=1;
						  	printf("\nLugar [%d][%d] Reservado!\n",Fila,Polt);
						  	getch();
						  }
						  else
						  	  {
						  	  	printf("\nA Poltrona deve ser POSITIVA!\n");
						  	  	getch();
						  	  }
						  	  
						  printf("\nQual a Fila? - [-1 para Sair]:\n");
					      scanf("%d",&Fila);
					  }
					  
	 			      break;
			
			case 'C': printf("\nQtde Poltronas Livres/Ocupadas:\n");
					  ContOcup=0;
					  ContLivres=0;
					  for(Fila=0; Fila<FILAS; Fila++)
					  	for(Polt=0; Polt<POLTRONAS; Polt++)
					  		if (Lugar[Fila][Polt]==0)
					  			ContLivres++;
					  		else
					  			ContOcup++;
					  	
					  printf("\nTotal de Livres: %d\n",ContLivres);
					  printf("\nTotal de Ocupadas: %d\n",ContOcup);
					  getch();
					  break;
			
			case 'D': printf("\nMapa de Reservas:\n");
						for(Fila=0; Fila<FILAS; Fila++)
						{
					  	  for(Polt=0; Polt<POLTRONAS; Polt++)
					  	   	   printf("[%d]", Lugar[Fila][Polt]);
					  	  printf("\n");
						}
					  getch();
					  break;
					   
			case 'E': printf("\nConsultar Reservas:\n");
					  printf("Fila desejada: ");
					  scanf("%d", &Fila);
					  printf("Poltrona desejada: ");
					  scanf("%d", &Polt);
					  if (Fila >=0 && Fila < FILAS && Polt >= 0 && Polt < POLTRONAS) {
					  	if (Lugar[Fila][Polt] == 0)
					  		printf("Lugar da posicao [%d][%d] disponivel\n", Fila, Polt);
					  	else printf("Lugar da posicao [%d][%d] ocupado\n", Fila, Polt);
					  }
					  else printf("Lugar inexistente\n");
					  printf("Pressione qualquer tecla para prosseguir\n");
					  getch();
					  break;
		}
		
	}while (op != 27);  //ESC
	
	return 0;
}
