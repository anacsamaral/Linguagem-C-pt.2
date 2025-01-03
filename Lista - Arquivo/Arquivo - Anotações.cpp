// persistência dos dados = gravar ele em algum lugar e levar para onde quiser
/* 
	caractere: fgetc(), fputc(); - para arquivo texto (caracter puro, nao tem marcação)
	string: fgets(), fputs(); - para arquivo texto (caracter puro, nao tem marcação)
	formatada: fscanf(), fprint() - para arquivo texto (caracter puro, nao tem marcação)
	- arquivo de texto serve para mostrar os dados
	
	registros - para arquivo binário (armazena os dados)
			  - se não tiver o programa que criou o arquivo, não dá para acessar ele;
			  - arquivo robusto
	
	- quando precisa ler ou gravar coisas no arquivo, são funções diferentes
	para arq texto e binário;
	
	- são diferentes as formas de manipular o arquivo
	- para criar, apagar, renomear, onde está, são os mesmos comandos para os 2 tipos
	
	- precisamos criar uma seção para que consiga usar esse arquivo
	- colocar extensão: dados.dat ou dados.txt
	- para mandar os dados para o arquivo, tem que ter uma variável
	do tipo FIlE, que terá um ponteiro, ou seja, guarda o endereço de um arquivo.
		- Ela não é o arquivo, só guarda o endereço de onde o arquivo está;
		- É uma variável hexadecimal.;
		- É pego o ponteiro e associa com o arquivo de fora;
		- O programa precisa ter alguém que vincula o arquivo que está lá fora;
		- É como se houvesse um buffer intermediando entre o programa e o arquivo
		ele descarrega os dados. É o momento em que abre uma seção.
		As vezes é necessário forçar o descarregamento
		- Ponteiro - Nome Físico
		- Toda vez que usar o aquivo, vai abrir uma seção;
		- Se não fechar a sessão, podem ficar dados no buffer e eles se perderem;
		- O que enche o buffer vai pro arquivo, o que não enche não vai
		- O arquivo pode acabar sendo corrompido e não terá como usá-lo mais.
		- Onde você abre, você fecha;
		- Objetivo = integridade dos dados, mesmo que perca tempo;
	
	- Abrir o arquivo = fopen(); 
	- Vai estar associado a uma variável FILE *Ptr
	- Usou o nome, atualiza no arquivo;
	- FILE *Ptr = fopen("Dados.dat", "" -> tipo de abertura);
	- Banco de dados = mandar gravar e recuperar; Grava e lê;
	- Algo físico, pega da memória e manda pro lugar ou pega do lugar e manda pra memória
	- A linguagem C tem 12 tipos de abertura de arquivo:
		- 6 para arquivo texto;
		- 6 para arquivo binário;
	- O arquivo só vai ser criado/manipulado, só depois do comando fopen(), aí
	pode ser utilizado
	- é recomendado estar no mesmo diretório do programa
	- quando o usuário for digitar o caminho, ela só irá digitar uma barra
	- quando for fixo, são duas barras;
	- se criar um arquivo ja existente, ele zera o arquivo;
	- quando abre um arquivo, uma seção, o ponteiro está em algum lugar;
	- EOF - end of file = indica onde o arquivo está, um endereço nulo
	em C, que significa que o arquivo acabou;
	- a marca de final de arquivo está onde acabou de criar o arquivo, toda vez que 
	é gravado, grava a partir dessa marca; não deixa observar o que já foi gravado;
	se abrir um arquivo com wb, não consegue ver se o dado é repetido ou não
	porque com WB o ponteiro sempre está no fim do arquivo;
	- quando abrimos com RB, o ponteiro do arquivo é colocado no início
	podendo andar no arquivo, mas não consegue gravar (buscas);
	- só dá para abortar o arquivo se abrir o arquivo e não tiver nada
	- AB grava no final; se o arquivo nao existe, ele cria, se ja existe
	mantem os dados e posiciona o ponteiro no final
	- os plus fazem a mesma coisa, mas nao deixa gravar, deixa gravar em qualquer lugar
	e atualizar o que ja tem (RB+), se colocar o ponteiro no fim, ele grava. mas 
	na teoria nao
	- se arq existe, zera, senao, ele cria (WB+)
	- AB+ para buscas;
	
	fclose() - como um "salvar"
	
 */
