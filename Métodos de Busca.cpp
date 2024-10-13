int BuscaExaustiva(int V[TF], int TL, int Chave)
{
	int i = 0;
	
	while(i < TL && Chave != V[i]) // i < TL existe pois há a possibilidade de não achar o elemento;
		i++;
	
	if( i < TL)
		return i;
	else
		return -1;
}

//Busca é diferente de varredura;

int BuscaSentinela(int V[TF], int TL, int Chave)
{
	int i = 0;
	
	V[TL] = Chave;
	while(Chave != V[i]) // i < TL existe pois há a possibilidade de não achar o elemento;
		i++;
	
	if( i < TL)
		return i;
	else
		return -1;
}

/*A Busca Sentinela, pega o valor do elemento a ser procurado, insere na
última posição do vetor e faz a comparação até encontrar a real ou a sentinela*/

//66,6% do tempo ganho em relação a Busca Exaustiva;
//A sentinela gasta 1/3 do tempo que a exaustiva gasta;

/*Para usar a sentinela, tem que garantir que sempre terá uma posição 
vazia no vetor, para poder inserir o elemento, garantindo isso no cadastro. 
Em vez de TF, ser TF + 1 ou - 1*/

//Busca Sequencial Indexada e Inserção Indexada (Estrutura ordenada)

/*Com base na ordenação, encontra o lugar, se maior que o elemento procurado, 
reordena e insere de forma ordenada*/

//Vantagem = diminui a quantidade de perguntas, menos processos e mais otimização do algoritmo

int BuscaSeqIndex(int V[TF], int TL, int Chave)
{
	int i = 0;
	
	while(i < TL && Chave > V[i]) // se descrescente, Chave < V[i]
		i++;
	
	if( i < TL && Chave == V[i]) // saiu porque achou? ou alguem maior do que procura?
		return i;
	else
		return -1;
}

//BUSCA BINÁRIA
//Ela fatia o vetor em metades até encontrar o elemento;
//Ou seja, diminui a quantidade de buscas que são feitas;
//Olhe sempre o meio;
//Metade, metade da metade, metade da metade da metade, etc;
//algo que guarde o inicio do vetor e o fim em TL - 1;
//algo que guarde o meio, fim / 2 ou Tl / 2;
//Tl = 7; Meio = Tl / 2;
//se o elemento for maior que o meio, o inicio = meio + 1;
//novo meio = (inicio + fim) / 2 -> para qualquer ocasião;
// quando elemento menor -> fim = meio - 1; quando for maior -> inicio = m + 1;
//A última situação é quando F == I == M, precisa vali;
//Quando I -> F vai para F -> I, significa que tem que parar o algoritmo;
//A posição que tem que devolver é a do meio;
//enquanto inicio > fim; se o fim maior, significa que algo está errado;

int BuscaBinaria(int V[TF], int TL, int Chave)
{
	int inicio = 0, fim = TL - 1, meio;
	meio = TL / 2
	
	while(inicio < fim && Chave != V[meio])
	{
		if(Chave > V[meio])
			inicio = meio + 1;
		
		else
			fim = meio - 1; //fim = meio tambem da certo;
		
		meio = (inicio + fim) / 2;
	}
	
	if(Chave == V[i]) // saiu porque achou?
		return meio;
	else
		return -1; //posição inexistente no vetor;
}
