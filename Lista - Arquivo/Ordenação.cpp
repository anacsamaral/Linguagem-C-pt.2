#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//
void OrdenarAlunos(void)
{
	int a, b, QtdeReg;
	TpAluno RegAux, RegA, RegB;
	FILE *PtrAlu = fopen("Alunos.dat", "rb+");
	if(PtrAlu == NULL)
		printf("\nErro de Abertura\n");
	else
	{
		fseek(PtrAlu, 0, 2)
		QtdeReg = ftell(PtrAlu)/sizeof(TpAluno);
		for(a=0; a<QtdeReg-1; a++) //a++ --> a += sizeof(TpAluno); b < QtdeReg - sizeof
			for(b = a+1; b<QtdeReg; b++) 
			/*b<feof(PtrAlu) = numero menor que verdadeiro ou falso????? nao da p usar assim
			O TL representa a quantidade de registros
			ftell retorna quantos bytes o ponteiro andou para estar onde esta atualmente
			*/
			{
				fseek(PtrAlu,a*sizeof(TpAluno), 0);//fseek não funciona sozinho
				fread(&RegA,sizeof(TpAluno), 1, PtrAlu);
				
				fseek(PtrAlu,b*sizeof(TpAluno), 0);
				fread(&RegB,sizeof(TpAluno),1,PtrAlun);
				
				if(strcmp(RegA.RA,RegB.RA)>0)
				//T[a*sizeof(TpAluno)].Campo > T[b*sizeof(TpAluno)].Campo
				{
					fseek(PtrAlu,a*sizeof(TpAluno), 0);
					fwrite(&RegB,sizeof(TpAluno),1,PtrAlun);
					
					fseek(PtrAlu,b*sizeof(TpAluno), 0);
					fwrite(&RegA,sizeof(TpAluno),1,PtrAlun);
				}
			}
				
		fclose(PtrAlu);
		printf("\nArquivo Ordenado\n");
	}
	getch();
	
}
