// EXERCICIOS DA LISTA "MODULARIZACAO DE VETORES"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define TF 100

// EXERC�CIO [1]: VETOR FREQUENCIA
void LeVetor(int V[TF], int &TL)
{
	int aux;
	system("cls");
	printf("### Inserir no Vetor ###\n");
	printf("Numero: ");
	scanf("%d", &aux);
	
	while(TL < TF && aux > 0)
	{
		V[TL++] = aux;
		
		if(TL == TF)
		{
			printf("Vetor Cheio!\n");
            getch();
		}
		else
        {
            printf("Numero: ");
            scanf("%d", &aux);
        }
	}
}

void ExibeVetor(int V[TF], int TL)
{
	int i;
	system("cls");
	printf("### Conteudo do Vetor ###\n");
	
	if(TL == 0)
	{
		printf("Vetor Vazio\n");
	}
	else
	{
		for(i = 0; i < TL; i++)
			printf("\nVetor [%d]: %d", i, V[i]);
	}
	printf("\n");
}

void ExibeVetorSub(int V[TF * 2], int TL)
{
	int i;
	system("cls");
	printf("### Conteudo do Vetor ###\n");
	
	if(TL == 0)
	{
		printf("Vetor Vazio\n");
	}
	else
	{
		for(i = 0; i < TL; i++)
			printf("\nVetor [%d]: %d", i, V[i]);
	}
	printf("\n");
}

void Frequencia(int	V[TF], int TL, int &MaisAparece, int &QtdeVezes)
{
	int i, j, cont = 0;
	
	QtdeVezes = 0;
	
	for(i = 0; i < TL - 1; i++)
	{
		cont = 0;
		for(j = i; j < TL; j++)
		{
			if(V[i] == V[j])
				cont++;
				
			if(cont > QtdeVezes)
			{
				QtdeVezes = cont;
				MaisAparece = V[i];
			}
				
		}
	}
	
}

//EXERC�CIO [2]: VETOR SOMA
int Soma(int V[TF], int TL)
{
	int i, Soma = 0;
	
	if(TL == 0)
	{
		printf("Nao ha elementos no vetor para somar!!!\n");
		getch();
	}
	else
		for(i = 0; i < TL; i++)
			Soma += V[i];
			
	return Soma;
}

//EXERCICIO [3]: VETOR CONTIDO
int Contido(int V[TF], int TL, int Valor)
{
	int i = 0;
	
	while (i < TL && Valor != V[i])
		i++;
		
	if (i < TL)
		return 1;
	else
		return 0;
}

int ContidoSub(int V[TF * 2], int TL, int Valor)
{
	int i = 0;
	
	while (i < TL && Valor != V[i])
		i++;
		
	if (i < TL)
		return 1;
	else
		return 0;
}

//EXERCICIO [4]: VETOR BINARIO
int LeNumero(void)
{
    int Decimal;
    system("cls");
    printf("### Decimal para Binario ###\n");
    printf("Digite um valor decimal: ");
    scanf("%d", &Decimal);

    return Decimal;
}

int ConverteBinario(int Decimal)
{
    int Binario = 0, mult = 1, resto;

    while (Decimal > 0)
    {
        resto = Decimal % 2;      
        Binario += resto * mult;      
        mult = mult * 10;
        Decimal = Decimal / 2;          
    }

    return Binario;
}

void ExibeResultado(int valor)
{
    printf("\nResultado: %d\n", valor);
    getch();
}


// EXERCICIO [5-A]
void Subtracao(int VSub[TF * 2], int &TLSub, int VA[TF], int TLA, int VB[TF], int TLB)
{
	printf("\n### Subtracao dos Vetores A e B ###\n");
	getch();
	int i;
	
	TLSub = 0;
	
	for(i = 0; i < TLA; i++)
		if(!Contido(VB, TLB, VA[i])) // Se verdade que o Elemento de VA n�o est� contido em VB
			if(!ContidoSub(VSub, TLSub, VA[i])) // Se verdade que o Elemento de VA n�o est� contido em VSub
				VSub[TLSub++] = VA[i];
}

void Interseccao(int VSub[TF * 2], int &TLSub, int VA[TF], int TLA, int VB[TF], int TLB)
{
	printf("\n### Subtracao dos Vetores A e B ###\n");
	getch();
	int i;
	
	TLSub = 0;
	
	for(i = 0; i < TLA; i++)
		if(Contido(VB, TLB, VA[i])) // Se verdade que o Elemento de VA n�o est� contido em VB
			if(!ContidoSub(VSub, TLSub, VA[i])) // Se verdade que o Elemento de VA n�o est� contido em VSub
				VSub[TLSub++] = VA[i];
}

void Merge(int VSub[TF * 2], int &TLSub, int VA[TF], int TLA, int VB[TF], int TLB)
{
	printf("\n### Merge Sort dos Vetores A e B ###\n");
	getch();
	int i = 0, j = 0, k = 0;
	
	TLSub = 0;
	
	while(i < TLA && j < TLB)
		if(VA[i] <= VB[j])
			VSub[k++] = VA[i++];
		else
			VSub[k++] = VB[j++];
			
	while(i < TLA)
		VSub[k++] = VA[i++];
		
	while(j < TLB)
		VSub[k++] = VB[j++];
		
	TLSub = k;
}

void Uniao(int VSub[TF * 2], int &TLSub, int VA[TF], int TLA, int VB[TF], int TLB)
{
	printf("\n### Uniao dos Vetores A e B ###\n");
	getch();
	int i, j;
	
	TLSub = 0;
	
	for(i = 0, j = 0; i < TLA && j < TLB; i++, j++)
	{
		if(!Contido(VSub, TLSub, VA[i]))
			VSub[TLSub++] = VA[i];
		if(!Contido(VSub, TLSub, VB[j]))
			VSub[TLSub++] = VB[j];
	}
}

void ParImpar(int V[TF], int TL) 
{
    int i = 0, j = TL - 1, temp;
    
    while (i < j) 
	{
        while (i < TL && V[i] % 2 == 0)
            i++;
        
        while (j >= 0 && V[j] % 2 != 0)
            j--;
        
        if (i < j) 
		{
            temp = V[i];
            V[i] = V[j];
            V[j] = temp;
        }
    }
}

// EXERCICIO [5-B]

int main(void)
{
	int VF[TF], VS[TF], VC[TF], VA[TF], VB[TF], VSub[TF * 2]; // vetores
	int TLF = 0, TLS = 0, TLC = 0, TLA = 0, TLB = 0, TLSub = 0; // tamanho l�gico
	int MaisAparece, QtdeVezes, SomaVetor, ContidoVetor, Valor; // variaveis
	
	//EXERCICIO [1]: VETOR FREQUENCIA
	
	LeVetor(VF, TLF);
	ExibeVetor(VF, TLF);
	Frequencia(VF, TLF, MaisAparece, QtdeVezes);
	
	if(QtdeVezes == 1)
		printf("\nNenhum elemento se repete.\n");
	else
	{
		printf("\nElemento que mais aparece: %d", MaisAparece);
		printf("\nQtde de Vezes: %d\n", QtdeVezes);
	}
	
	getch();
	
	//EXERCICIO [2]: VETOR SOMA
	
	LeVetor(VS, TLS);
	ExibeVetor(VS, TLS);
	SomaVetor = Soma(VS, TLS);
	
	printf("\nA soma dos elementos resulta em: %d\n", SomaVetor);
	getch();
	
	//EXERCICIO [3]: VETOR CONTIDO
	
	LeVetor(VC, TLC);
	ExibeVetor(VC, TLC);
	
	printf("\nDigite o valor: ");
	scanf("%d", &Valor);
	
	ContidoVetor = Contido(VC, TLC, Valor);
	
	if(ContidoVetor == 1)
		printf("\nValor contido no vetor.\n");
	else
		printf("\nValor nao contido no vetor.\n");
	
	getch();
	
	//EXERCICIO [4]: VETOR BINARIO
	
	ExibeResultado(ConverteBinario(LeNumero()));
	getch();
	
	//EXERCICIO [5-A]: SUBTRACAO
	
	system("cls");
	printf("### Inserir Elementos no Vetor A [ENTER] ###\n"); getch();
	LeVetor(VA, TLA);
	ExibeVetor(VA, TLA); getch();
	
	system("cls");
	printf("### Inserir Elementos no Vetor B [ENTER] ###\n"); getch();
	LeVetor(VB, TLB);
	ExibeVetor(VB, TLB); getch();
	
	Subtracao(VSub, TLSub, VA, TLA, VB, TLB);
	
	printf("\nResultado da Subtracao: \n"); getch();
	ExibeVetorSub(VSub, TLSub); getch();
	
	//EXERCICIO [5-B]: INTERSECCAO
	
	system("cls");
	printf("### Inserir Elementos no Vetor A [ENTER] ###\n"); getch();
	LeVetor(VA, TLA);
	ExibeVetor(VA, TLA); getch();
	
	system("cls");
	printf("### Inserir Elementos no Vetor B [ENTER] ###\n"); getch();
	LeVetor(VB, TLB);
	ExibeVetor(VB, TLB); getch();
	
	Interseccao(VSub, TLSub, VA, TLA, VB, TLB);
	
	printf("\nResultado da Interseccao: \n"); getch();
	ExibeVetorSub(VSub, TLSub); getch();
	
	//EXERCICIO [5-C]: MERGE SORT
	
	system("cls");
	printf("### Inserir Elementos no Vetor A [ENTER] ###\n"); getch();
	LeVetor(VA, TLA);
	ExibeVetor(VA, TLA); getch();
	
	system("cls");
	printf("### Inserir Elementos no Vetor B [ENTER] ###\n"); getch();
	LeVetor(VB, TLB);
	ExibeVetor(VB, TLB); getch();
	
	Merge(VSub, TLSub, VA, TLA, VB, TLB);
	
	printf("\nResultado da Merge: \n"); getch();
	ExibeVetorSub(VSub, TLSub); getch();
	
	// EXERCICIO [6]: VETOR UNIAO
	
	system("cls");
	printf("### Inserir Elementos no Vetor A [ENTER] ###\n"); getch();
	LeVetor(VA, TLA);
	ExibeVetor(VA, TLA); getch();
	
	system("cls");
	printf("### Inserir Elementos no Vetor B [ENTER] ###\n"); getch();
	LeVetor(VB, TLB);
	ExibeVetor(VB, TLB); getch();
	
	Uniao(VSub, TLSub, VA, TLA, VB, TLB);
	
	printf("\nResultado da Uniao: \n"); getch();
	ExibeVetorSub(VSub, TLSub); getch();

	// EXERCICIO [7]: VETOR PAR E IMPAR
	
	system("cls");
	LeVetor(VA, TLA);
	ExibeVetor(VA, TLA); getch();
	
	ParImpar(VA, TLA);
	
	printf("\nResultado da Separacao: \n"); getch();
	ExibeVetor(VA, TLA); getch();
	
	return 0;
}
