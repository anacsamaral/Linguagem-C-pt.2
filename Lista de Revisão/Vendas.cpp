#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#define TFP 5
#define TFC 30
#define TFV 50

int main(void)
{
	char Produto[TFP][20], Cliente[TFC][25], op, AuxProd[20], AuxCli[25];
	float Preco[TFP];
	int Estoque[TFP], Venda[TFV][3], TLP=0, TLC=0, TLV=0, i, j, pos, AuxEst, quant;
	
	do
	{
		system("cls");
		printf("\n# # #  MENU VENDAS  # # #\n");
		printf("[A] Cadastrar Clientes\n");
		printf("[B] Exibir Clientes\n");
		printf("[C] Excluir Clientes\n");
		printf("[D] Ordenar Clientes (Crescente)\n");
		printf("[E] Cadastrar Produtos\n");
		printf("[F] Exibir Produtos\n");
		printf("[G] Consultar Produtos\n");
		printf("[H] Excluir Produtos\n");
		printf("[I] Ordenar Produtos pela Qtde em Estoque (Decrescente)\n");
		printf("[J] Alterar Estoque de Produtos\n");
		printf("[K] Realizar Vendas\n");
		printf("[L] Exibir Vendas\n");
		printf("[ESC] Finalizar\n");
		op = toupper(getche());
		switch(op)
		{
			case 'A': 
					  printf("\n### Cadastro de Clientes ###\n");
					  if (TLC==TFC)
					  {
					  	printf("\nVetor de Clientes esta cheio!\n");
					  	getch();
					  }
					  else
					  	  {
					  	  	  printf("Nome do Cliente[%d]: ",TLC);
							  fflush(stdin);
							  gets(AuxCli);
							  //while (TLC<TFC && strlen(AuxCli)>0)
							  //while (TLC<TFC && AuxCli[0]!='\0')
							  //while (TLC<TFC && strcmp(AuxCli,"")!=0)
							  while (TLC<TFC && strcmp(AuxCli,"\0")!=0)
							  {
							  	//Validar a exist�ncia do Cliente - Busca Exaustiva
								pos=0;
							  	while (pos<TLC && strcmp(AuxCli,Cliente[pos])!=0)
							  			pos++;
							  	
							  	if(pos<TLC)  //Achou
							  	{
								  printf("\nCliente ja esta Cadastrado!!\n");
								  getch();
							  	}
							  	else
							  		{
							  			strcpy(Cliente[TLC],AuxCli);
							  			TLC++;
								  	}
							  																  	
							  	if (TLC<TFC)
							  	{
								  printf("\nNome do Cliente[%d]: ",TLC);
							      fflush(stdin);
							      gets(AuxCli);
							  	}
							  	else
							  		{
							  			printf("\nVetor de Clientes esta cheio!\n");
							  			getch();
							  		}
								
							  }
					  	  }		  
					  break;
			
			case 'B': printf("\n### Relatorio de Clientes ###\n");
					  if (TLC == 0)
					  	printf("\nNao ha Clientes!\n");	  
					  else
					  	for(i=0; i<TLC; i++)
					  		printf("\nCliente[%d]: %s",i,Cliente[i]);
					  
					  getch();
					  break;
			
			case 'C': printf("\n### Exclusao de Clientes ###\n");
					  if (TLC==0)
					  {
					  	printf("\nNao ha Clientes!\n");
					  	getch();
					  }
					  else
					  	  {
					  		printf("\nCliente a Excluir: ");
					  		fflush(stdin);
					  		gets(AuxCli);
					  		while (TLC>0 && strcmp(AuxCli,"\0")!=0)
					  		{                       
					  			pos=0;
					  			while (pos<TLC && stricmp(AuxCli,Cliente[pos])!=0)
					  				pos++;
					  				
					  			if (pos<TLC)  //Achou
					  			{
					  				printf("\n### Nome do Cliente ###\n");
					  				printf(">>> %s\n",Cliente[pos]);
					  				printf("\nConfirma Exclusao (S/N)? ");
					  				if (toupper(getch()) == 'S')
					  				{
					  					for(; pos<TLC-1; pos++) // a inicialização está vazia pois ja temos o valor incial de pos
					  						strcpy(Cliente[pos],Cliente[pos+1]);
					  					
					  					TLC--;
					  					printf("\nCliente [%s] foi Excluido!\n",AuxCli);
					  					getch();
					  				}
					  			}
					  			else
								{
									printf("\nCliente nao Cadastrado!\n");
									getch();
								}
					  			
								printf("\nCliente a Excluir: ");
					  			fflush(stdin);
					  			gets(AuxCli);
					  		}
					  	  }
					  break;
			
			case 'D': for(i=0; i<TLC-1; i++)
						for(j=i+1; j<TLC; j++)
							if(strcmp(Cliente[i],Cliente[j])>0)
							{
								strcpy(AuxCli,Cliente[i]);
								strcpy(Cliente[i],Cliente[j]);
								strcpy(Cliente[j],AuxCli);
							}
							
					  printf("\n###Clientes Ordenados com Sucesso!!###\n");
					  getch();
					  break;
					  
			case 'E':  system("cls");
					   printf("\n### Cadastrar Produtos: ###\n");
					   if (TLP==TFP)
					   {
					   	  printf("\nVetor de Produtos Cheio!\n");
					      getch();
					   }
					   else
					   		{
					   		   printf("Descricao do Produto [%d]: ",TLP);
							   fflush(stdin);
							   gets(AuxProd);
							   //while (TLP<TFP && AuxProd[0]!='\0')
							   //while (TLP<TFP && strlen(AuxProd)>0)
							   //while (TLP<TFP && strcmp(AuxProd,"")!=0)
							   while (TLP<TFP && strcmp(AuxProd,"\0")!=0)
							   {
								  //Busca para validar a existência do Produto
								  pos=0;
								  while (pos<TLP && stricmp(AuxProd,Produto[pos])!=0)
								  			pos++;
								  
								  if(pos==TLP) //Não achou...
								  {
									  strcpy(Produto[TLP],AuxProd);
									  printf("Preco [%d]: ",TLP);
									  scanf("%f",&Preco[TLP]);
									  printf("Qtde Estoque [%d]: ",TLP);
									  scanf("%d",&Estoque[TLP]);
									  TLP++;
								  }
								  else
								  	{
								  		printf("\nProduto ja Cadastrado!\n");
								  		getch();
								  	}
								  
								  
								  if (TLP<TFP)
								  {
								  	printf("\nDescricao do Produto [%d]: ",TLP);
							        fflush(stdin);
							        gets(AuxProd);
								  }
								  else
								  	  {
								  	  	printf("\nVetor de Produtos Cheio!\n");
								  	  	getch();
								  	  }
							   }
					   		}
					   
					   break;
					   
			case 'F':  printf("\nRelatorio de Produtos:\n");
					   if (TLP==0)
					      printf("\nNao ha Produtos!\n");
					   else
				   		  for(i=0; i<TLP; i++)
				   		  {
				   		  	printf("\nProduto[%d]:\n",i);
							printf("Descricao: %s\n",Produto[i]);
				   		  	printf("Preco: R$ %.2f\n",Preco[i]);
				   		  	printf("Estoque: %d\n",Estoque[i]);
				   		  }
					   
					   getch();
					   break;
					   
			case 'G':  printf("\nConsultar Produtos:\n");
					   if (TLP==0)
					   {
					   	  printf("\nNao ha Produtos!\n");
					   	  getch();
					   }
					   else	
					   	  {
					   	  	 printf("\nProduto a Consultar: ");
					   	  	 fflush(stdin);
					   	  	 gets(AuxProd);
					   	  	 while (strcmp(AuxProd,"\0")!=0) //Enquanto AuxProd é válido
					   	  	 {
					   	  	 	pos=0;
					   	  	 	while(pos<TLP && stricmp(AuxProd,Produto[pos])!=0) //stricmp 
					   	  	 			pos++;
					   	  	 	
					   	  	 	if(pos<TLP)  //Achou
					   	  	 	{
					   	  	 		printf("\n### Detalhes do Produto ###\n");
					   	  	 		printf("Produto: %s",Produto[pos]);
					   	  	 		printf("\nPreco: R$ %.2f",Preco[pos]);
					   	  	 		printf("\nEstoque: %d\n",Estoque[pos]);
					   	  	 	}
					   	  	 	else
					   	  	 		printf("\nProduto nao Cadastrado!\n");
					   	  	 	
								getch();
								printf("\nProduto a Consultar: ");
					   	  	 	fflush(stdin);
					   	  	 	gets(AuxProd);
					   	  	 }
					   	  }
					   
					   break;
			
			case 'H':  printf("\nExcluir Produtos:\n");
					   if (TLP==0)
					   {
					   	  printf("\nNao ha Produtos!\n");
					   	  getch();
					   }
					   else	
					   	  {
					   	  	 printf("\nProduto a Excluir: ");
					   	  	 fflush(stdin);
					   	  	 gets(AuxProd);
					   	  	 while (TLP>0 && strcmp(AuxProd,"\0")!=0)
					   	  	 {
					   	  	 	pos=0;
					   	  	 	while(pos<TLP && stricmp(AuxProd,Produto[pos])!=0)
					   	  	 			pos++;
					   	  	 	
					   	  	 	if(pos<TLP)  //Achou
					   	  	 	{
					   	  	 		printf("\n### Detalhes do Produto ###\n");
					   	  	 		printf("Produto: %s",Produto[pos]);
					   	  	 		printf("\nPreco: R$ %.2f",Preco[pos]);
					   	  	 		printf("\nEstoque: %d\n",Estoque[pos]);
					   	  	 		printf("\nConfirma Exclusao (S/N)? ");
					   	  	 		if (toupper(getche())=='S')
					   	  	 		{
					   	  	 			for(; pos<TLP-1; pos++)
					   	  	 			{
					   	  	 				strcpy(Produto[pos],Produto[pos+1]);
					   	  	 				Estoque[pos] = Estoque[pos+1];
					   	  	 				Preco[pos] = Preco[pos+1];	
					   	  	 			}
					   	  	 			TLP--;
					   	  	 			printf("\nProduto [%s] Excluido!\n", AuxProd);
					   	  	 		}
					   	  	 	}
					   	  	 	else
					   	  	 		printf("\nProduto nao Cadastrado!\n");
					   	  	 	
								getch();
								printf("\nProduto a Excluir: ");
					   	  	 	fflush(stdin);
					   	  	 	gets(AuxProd);
					   	  	 }
					   	  }
					   
					   break;

			case 'I':  printf("\nOrdenacao de Produtos por Estoque:\n");
					   if (TLP==0)
					   {
							printf("\nNao ha Produtos!\n");
							getch();
					   }
					   else
					   {
							for(i=0; i<TLP-1; i++)
								for(j=i+1; j<TLP; j++)
									if(Estoque[i] > Estoque[j])
									{
										AuxEst = Estoque[i];
										Estoque[i] = Estoque[j];
										Estoque[j] = AuxEst;
									}
								
							printf("\nProdutos Ordenados com Sucesso!!\n");
							getch();
					   }
					   break;

			case 'J':  printf("\nExcluir Produtos:\n");
					   if (TLP==0)
					   {
					   	  printf("\nNao ha Produtos!\n");
					   	  getch();
					   }
					   else
					   {
							printf("\nProduto a Excluir:");
							fflush(stdin);
							gets(AuxProd);
							
							while (TLP > 0 && strcmp(AuxProd,"\0")!=0)
							{
								pos = 0;
								while (pos < TLP && stricmp(AuxProd,Produto[pos])!=0) 
									pos++;

								if (pos < TLP)
								{
									printf("\n### Nome do Produto ###\n");
									printf(">>> %s\n", Produto[pos]);
									printf("Confirma Exclusao (S/N)?");
									if(toupper(getch()) == 'S')
									{
										for(pos = pos; pos < TLP-1; pos++)
											strcpy(Produto[pos],Produto[pos+1]);

										TLP--;
										printf("\nProduto [%s] foi Excluido!\n", AuxProd);
					  					getch();
									}
								}
								else
								{
									printf("Produto nao Cadastrado!!\n");
									getch();
								}
								printf("\nProduto a Excluir: ");
					  			fflush(stdin);
					  			gets(AuxProd);
							}
					   }
					   break;
					   
			case 'K':  printf("\nRealizar Vendas:\n");
						if (TFC == 0)
						{
							printf("Nao ha Clientes para realizar vendas!\n");
							getch();
						}
						else
						{
							printf("\nNome do Cliente: ");
					  		fflush(stdin);
					  		gets(AuxCli);
					  		while (TLC>0 && strcmp(AuxCli,"\0")!=0)
					  		{                       
					  			pos=0;
					  			while (pos<TLC && stricmp(AuxCli,Cliente[pos])!=0)
					  				pos++;
					  				
					  			if (pos<TLC)  //Achou
					  			{
									Venda[TLV][0] = pos;
					  				printf("\nNome do produto:\n");
									fflush(stdin);
					  				gets(AuxProd);
									while (TLP > 0 && strcmp(AuxProd,"\0")!=0)
									{
										pos = 0;
										while (pos < TLP && stricmp(AuxProd, Produto[pos])!=0)
										{
											pos++;
										}

										if (pos < TLP)
										{
											Venda[TLV][1] = pos;
											printf("Quantidade:\n");
											scanf("%d", &quant);
											if (quant > Estoque[pos])
												printf("Essa quantidade não está disponível, pois só tem apenas %d unidades em estoque\n", Estoque[pos]);
											else
											{
												Venda[TLV][3] = quant;
												Estoque[pos] -= quant;
												TLV++;
												printf("Cliente: %s | Produto: %s | Quantidade: %d [vendido]\n", Cliente[pos], Produto[pos], Estoque[pos]);
											}
										}
										else
										{
											printf("Produto nao encontrado!\n");
											getch();
										}
									}
								}
								else
								{
									printf("Cliente nao Cadastrado!!!\n");

								}
							}
						}
					   getch();
					   break;
			
			case 'L':  printf("\nExibir Vendas:\n");
					   if (TLV==0)
					   {
					   	  printf("\nNao ha Vendas!\n");
					   	  getch();
					   }
					   else
					   {
							printf("Cliente\t Produto\t Quantidade\t\n");
							for (i = 0; i < TLV; i++)
								printf("%d\t %d\t %d\t\n", Venda[i][1], Venda[i][2], Venda[i][3]);
							
					   }
					   getch();
					   break;
		}				
	}while (op!=27);
	return 0;
}