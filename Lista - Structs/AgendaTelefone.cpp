#include <stdio.h>
#include <string.h>
#include <stlib.h>
#include <conio.h>

#define TF

struct TpData
{
	int Dia, Mes, Ano;
};

struct TpPessoa
{
	struct TpData Data;
	char Nome[30], Email[50], Rua[70], Bairro[20], CEP[10], Cidade[25], Estado[3], Pais[20], Telefone[15], Observacao[100];
};


