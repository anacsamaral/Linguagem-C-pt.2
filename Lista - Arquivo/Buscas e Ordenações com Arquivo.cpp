/*

|| -- || -- AVISO IMPORTANTE! -- || -- ||

Todas as funções de busca abaixo precisam que os arquivos sejam abertos como "rb" ou "rb+", e as ordenações EXCLUSIVAMENTE como "rb+".
Aberturas com "w" e "a" escrevem os arquivos APENAS no final, e por isso devem ser usadas somente em substituições de arquivos (para "w") e em cadastros (no caso de "a")

*/

// ### BUSCAS ###

// Busca exaustiva

int buscaExaustiva(FILE *Ptr, int id) {
	struct minhaStruct aux;
	rewind(Ptr); 													// Volta para o começo do arquivo
	fread(&aux, sizeof(minhaStruct), 1, Ptr);						// Lê o início
	while(!feof(Ptr) && !(id == aux.id && aux.status == 1)) {		// Enquanto (não for fim de arquivo) E não for verdade que (o registro atual (tem ID igual ao buscado) e (o registro é válido))
		fread(&aux, sizeof(minhaStruct), 1, Ptr);					// Continua lendo
	}
	if (id == aux.id && aux.status == 1) {							// Se o registro estiver com status válido e o ID for igual ao buscado
		return ftell(Ptr) - sizeof(minhaStruct);					// Retorne a posição onde a última leitura ocorreu (posição atual do ponteiro - tamanho da struct)
	}
	else return -1;													// Caso contrário, retorne -1 (Não encontrado)
}

// OBS: Sem versão com sentinela. Dá pra fazer, mas achei que gastaria tempo demais por ser arquivo binário.

// Busca sequencial indexada

int buscaSequencialIndexada(FILE *Ptr, int id) {
	struct minhaStruct aux;
	rewind(Ptr);
	fread(&aux, sizeof(minhaStruct), 1, Ptr);
	while(!feof(Ptr) && !(aux.id >= id && aux.status == 1)) {	// Quase a mesma coisa que a exaustiva, só muda as condições daqui... --> Enquanto (não for fim de arquivo) E não for verdade que ((o ID do registro atual É MAIOR OU IGUAL AO ID buscado) E (o registro é válido))
		fread(&aux, sizeof(minhaStruct), 1, Ptr);
	}
	if (id == aux.id && aux.status == 1) {
		return ftell(Ptr) - sizeof(minhaStruct);
	}
	else return -1;
}

// Busca binária

int buscaBinaria(FILE *Ptr, int id) {
	int inicio, meio, fim;
	struct minhaStruct aux;
	rewind(Ptr);													// Volta para o começo do arquivo
	inicio = ftell(Ptr) / sizeof(minhaStruct);						// Registra a posição LÓGICA inicial (normalmente não precisa do sizeof() por causa da rewind(), mas prefiro deixar mesmo assim)
	fseek(Ptr, 0, SEEK_END);										// Busca o final do arquivo
	fim = ftell(Ptr) / sizeof(minhaStruct);							// Registra a posição LÓGICA final (Aqui PRECISA do sizeof())
	do {
		meio = (inicio + fim) / 2;									// Registra a posição LÓGICA do meio do arquivo (OBS: SEMPRE REGISTRAR A *POSIÇÃO LÓGICA*; se buscar a posição em bits (sem dividir o início e o fim por sizeof()), pode ser que seja salva a posição do meio de um registro)
		fseek(Ptr, meio * sizeof(minhaStruct), SEEK_SET);			// Busca a posição onde o registro do meio se encontra
		fread(&aux, sizeof(minhaStruct), 1, Ptr);					// Lê o registro localizado no meio da área de busca
		if (!(aux.id == id && aux.status == 1)) {					// Se não for verdade que ((o ID do registro atual condiz com o buscado) E (o registro atual é válido))
			if (aux.id < id)										// Se o ponteiro de busca está localizado ANTES do ID buscado
				inicio = meio + 1;									// Redefine o INÍCIO da área de busca para o meio MAIS 1
			else fim = meio;										// Se o ponteiro está localizado DEPOIS do ID buscado, redefine o FIM da área de busca para o meio (sem somar 1)
		}
	} while (inicio < fim && !(aux.id == id && aux.status == 1));	// Repete o processo enquanto (a posição de início da busca for menor que a final) E (não for verdade que (o ID foi encontrado) E (o registro atual é válido))
	if (aux.id == id && aux.status == 1)							// Se (o ID foi encontrado) E (o registro atual é válido)
		return meio * sizeof(minhaStruct);							// Retorna a posição do meio VEZES o tamanho em bits da struct
	else return -1;													// Caso contrário, retorna -1 (não encontrado)
}

// ### ORDENAÇÕES ###

// Ordenação por inserção direta

void insercaoDireta(FILE *Ptr) {
	int tamanho;
	struct minhaStruct auxA, auxB;
	fseek(Ptr, 0, SEEK_END);												// Busca o final do arquivo
	tamanho = ftell(Ptr) / sizeof(minhaStruct);								// Define o tamanho lógico do arquivo
	if (tamanho > 1) {														// Verifica se é preciso realizar a ordenação (é preciso ter no mínimo DOIS registros)
		do {
			fseek(Ptr, (tamanho - 2) * sizeof(minhaStruct), SEEK_SET);		// Busca a penúltima posição antes do final do tamanho pré-estabelecido
			fread(&auxA, sizeof(minhaStruct), 1, Ptr);						// Copia para a variável auxiliar A o penúltimo registro
			fread(&auxB, sizeof(minhaStruct), 1, Ptr);						// Copia para a variável auxiliar B o último registro
			if (auxA.id > auxB.id) {										// Se (o ID da auxiliar A for maior que o da auxiliar B)
				fseek(Ptr, (tamanho - 2) * sizeof(minhaStruct), SEEK_SET);	// Volta para a penúltima posição antes do final do tamanho pré-estabelecido
				fread(&auxB, sizeof(minhaStruct), 1, Ptr);					// Passa os conteúdos da auxiliar B para a penúltima posição
				fread(&auxA, sizeof(minhaStruct), 1, Ptr);					// Passa os conteúdos da auxiliar A para a última posição
			}
			tamanho--;														// Reduz o tamanho lógico para ordenação em 1
		} while (tamanho > 1 && auxA.id > auxB.id);							// Repete o processo enquanto o tamanho lógico for maior que 1 E o registro inserido de forma direta não estiver em sua posição
	}
}

// Ordenação por permutação (NÃO CONFUNDIR COM A POR BOLHAS)

void ordenacaoPermutacao(FILE *Ptr) {
	int a, b, tamanho;
	struct minhaStruct auxA, auxB;
	fseek(Ptr, 0, SEEK_END);									// Busca o final do arquivo
	tamanho = ftell(Ptr) / sizeof(minhaStruct);					// Define o tamanho lógico do arquivo
	for (a = 0; a < tamanho - 1; a++) {							// Primeira repetição: começando de 0, irá percorrer até o penúltimo elemento do arquivo
		for (b = a + 1; b < tamanho; b++) {						// Segunda repetição: começando da posição "a" + 1, irá percorrer até o último elemento do arquivo
			fseek(Ptr, a * sizeof(minhaStruct), SEEK_SET);		// Busca a posição "a" do arquivo
			fread(&auxA, sizeof(minhaStruct), 1, Ptr);			// Salva o elemento da posição "a" do arquivo em uma variável auxiliar
			fseek(Ptr, b * sizeof(minhaStruct), SEEK_SET);		// Busca a posição "b" do arquivo
			fread(&auxB, sizeof(minhaStruct), 1, Ptr);			// Salva o elemento da posição "b" do arquivo em uma variável auxiliar
			if (auxA.id > auxB.id) {							// Se (o ID do elemento da posição "a" FOR MAIOR QUE o elemento da posição "b")
				fseek(Ptr, a * sizeof(minhaStruct), SEEK_SET);	// Busca a posição "a" do arquivo
				fwrite(&auxB, sizeof(minhaStruct), 1, Ptr);		// Sobrepõe os dados da posição "a" com os da posição "b"
				fseek(Ptr, b * sizeof(minhaStruct), Ptr);		// Busca a posição "b" do arquivo
				fwrite(&auxA, sizeof(minhaStruct), 1, Ptr);		// Sobrepõe os dados da posição "b" com os da posição "a"
			}
		}
	}
}

// Ordenação por bolhas

void ordenacaoBolhas(FILE *Ptr) {
	int tamanho, pos, encerrado = 0;
	struct minhaStruct auxA, auxB;
	fseek(Ptr, 0, SEEK_END);																	// Busca o final do arquivo
	for (tamanho = ftell(Ptr) / sizeof(minhaStruct); tamanho > 1 && !encerrado; tamanho--) {	// Após definir o tamanho lógico do arquivo, uma repetição se iniciará subtraindo 1 do tamanho enquanto (o tamanho FOR MAIOR QUE 1) E (a ordenação não estiver encerrada)
		encerrado = 1;																			// Pré-define a repetição como encerrada, para caso nenhuma troca ocorra
		for (pos = 0; pos < tamanho - 1; pos++) {												// A partir de 0, percorre o arquivo até o tamanho lógico atual - 1
			fseek(Ptr, pos * sizeof(minhaStruct), SEEK_SET);									// Busca a posição atual da repetição no arquivo
			fread(&auxA, sizeof(minhaStruct), 1, Ptr);											// Lê dois registros seguidos em auxiliares
			fread(&auxB, sizeof(minhaStruct), 1, Ptr);
			if (auxA.id > auxB.id) {															// Se (o ID do registro A FOR MAIOR QUE o do B)
				fseek(Ptr, pos * sizeof(minhaStruct), SEEK_SET);								// Volta para a posição atual da repetição
				fwrite(&auxB, sizeof(minhaStruct), 1, Ptr);										// Troca os registros das duas posições anteriormente lidas com as auxiliares
				fwrite(&auxA, sizeof(minhaStruct), 1, Ptr);
				encerrado = 0;																	// Determina que a ordenação ainda não foi encerrada
			}
		}
	}
}

// Ordenação por seleção direta

int buscarMaiorID(FILE *Ptr, int tamanho) { // Função ESSENCIAL para essa ordenação
	int maior_pos, maior, cont;
	struct minhaStruct aux;
	rewind(Ptr);											// Volta o arquivo para o início
	fread(&aux, sizeof(minhaStruct), 1, Ptr);				// Lê a primeira entrada e registra na variável auxiliar
	maior_pos = 0;											// Define a primeira posição como a com o maior ID registrado
	maior = aux.id;											// Define o ID da primeira posição como o maior
	for (cont = 1; cont < tamanho; cont++) {				// Começa uma repetição até o tamanho desejado A PARTIR DA SEGUNDA POSIÇÃO
		fseek(Ptr, cont * sizeof(minhaStruct), SEEK_SET);	// Busca o registro da posição atual
		fread(&aux, sizeof(minhaStruct), 1, Ptr);			// Insere o registro atual sobre a auxiliar
		if (maior < aux.id) {								// Se o maior ID salvo FOR MENOR QUE o ID da struct auxiliar
			maior = aux.id;									// Registra o novo maior ID
			maior_pos = cont;								// Registra a posição do novo maior ID
		}
	}
	return maior_pos;										// Retorna a maior posição
}

void selecaoDireta(FILE *Ptr) {
	int maior_pos, tamanho, encerrado = 0;
	struct minhaStruct auxA, auxB;
	fseek(Ptr, 0, SEEK_END);											// Busca o final do arquivo
	tamanho = ftell(Ptr) / sizeof(minhaStruct);							// Define o tamanho lógico do arquivo
	while (tamanho > 0 && !encerrado) {									// Enquanto (o tamanho lógico for maior que 0 E a repetição não estiver encerrada)
		maior_pos = buscarMaiorID(Ptr, tamanho);						// Procura se ainda há registros fora de posição
		if (maior_pos < tamanho - 1) {									// Se encontrar um registro fora de posição
			fseek(Ptr, maior_pos * sizeof(minhaStruct), SEEK_SET);		// Busca e salva o maior registro encontrado na área de busca em uma auxiliar
			fread(&auxA, sizeof(minhaStruct), 1, Ptr);
			fseek(Ptr, (tamanho - 1) * sizeof(minhaStruct), SEEK_SET);	// Busca e salva o último registro da área de busca em outra auxiliar
			fread(&auxB, sizeof(minhaStruct), 1, Ptr);
			fseek(Ptr, maior_pos * sizeof(minhaStruct), SEEK_SET);		// Busca o registro maior registro e o sobrepõe com o da última posição da área de busca
			fwrite(&auxB, sizeof(minhaStruct), 1, Ptr);
			fseek(Ptr, (tamanho - 1) * sizeof(minhaStruct), SEEK_SET);	// Busca a última posição da área de busca e o sobrepõe com o maior registro
			fwrite(&auxA, sizeof(minhaStruct), 1, Ptr);
			tamanho--;													// Decrementa 1 do tamanho lógico
		}
		else encerrado = 1;												// Se a maior posição encontrada for igual à última do tamanho lógico atual, o arquivo já está ordenado e o processo é finalizado
	}
}

