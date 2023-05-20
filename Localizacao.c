/*****************************************************************//**
 * \file   Localizacao.c
 * \brief  Funções relacionadas ás localizações
 *
 * \author A. Cerqueira
 * \date   May 2023
 *********************************************************************/

 // Includes
#include "Localizacao.h"


/**
* \brief Liberta a memória da lista ligada de postos
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool LibertarPostos(PostoVertice* primeiroPosto) {
	PostoVertice* postoAtual = primeiroPosto;

	while (postoAtual != NULL) {
		PostoVertice* postoAnterior = postoAtual;
		postoAtual = postoAtual->proximo;
		LibertarPostosAdjacentes(postoAnterior->p.primeiraAdjacencia);
		free(postoAnterior);
	}

	primeiroPosto = NULL;

	return true;
}


/**
* \brief Liberta a memória da lista ligada de postos adjacentes
*
* \param primeiroPostoAdjacente O apontador para o primeiro elemento da lista ligada de postos adjacentes
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool LibertarPostosAdjacentes(PostoAdjacente* primeiroPostoAdjacente) {
	PostoAdjacente* postoAdjacenteAtual = primeiroPostoAdjacente;

	while (postoAdjacenteAtual != NULL) {
		PostoAdjacente* postoAdjacenteAnterior = postoAdjacenteAtual;
		postoAdjacenteAtual = postoAdjacenteAtual->proximo;
		free(postoAdjacenteAnterior);
	}

	primeiroPostoAdjacente = NULL;

	return true;
}


/**
* \brief Carrega os dados iniciais dos postos de um ficheiro .txt para uma lista ligada e guarda no ficheiro .dat.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos postos
* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
* \return O novo apontador para o primeiro elemento da lista ligada de postos carregada
* \author A. Cerqueira
*/
PostoVertice* CarregarPostosIniciais(PostoVertice* primeiroPosto, char* filePathInicial, char* saveFilePath) {
	LibertarPostos(primeiroPosto);
	primeiroPosto = LerPostosIniciais(filePathInicial);
	GuardarPostos(saveFilePath, primeiroPosto);

	return primeiroPosto;
}


/**
* \brief Carrega os dados iniciais dos postos adjacentes de um ficheiro .txt para uma lista ligada.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos postos adjacentes
* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes carregada
* \author A. Cerqueira
*/
PostoVertice* CarregarPostosAdjacentesIniciais(PostoVertice* primeiroPosto, char* filePathInicial, char* saveFilePath) {
	PostoVertice* atual;

	ApagarPostosAdjacentesFicheiro(saveFilePath);
	for (atual = primeiroPosto; atual != NULL; atual = atual->proximo) {
		LibertarPostosAdjacentes(atual->p.primeiraAdjacencia);
	}

	primeiroPosto = LerPostosAdjacentesIniciais(primeiroPosto, filePathInicial);

	for (atual = primeiroPosto; atual != NULL; atual = atual->proximo) {
		GuardarPostosAdjacentes(saveFilePath, atual->p.primeiraAdjacencia);
	}

	return primeiroPosto;
}


/**
* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de postos.
*
* \param filePath O caminho do ficheiro .txt com os dados dos postos
* \return O novo apontador para o primeiro elemento da lista ligada de postos
* \author A. Cerqueira
*/
PostoVertice* LerPostosIniciais(char* filePath) {
	FILE* file;
	PostoVertice* primeiroPosto = NULL;
	char linha[MAX_SIZE];

	file = fopen(filePath, "r");
	if (file == NULL)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		Posto posto;
		PostoFicheiro novoPostoFicheiro;

		int numLidos = sscanf(linha, "%d;%[^;];%[^;]",
			&novoPostoFicheiro.id,
			novoPostoFicheiro.nome,
			novoPostoFicheiro.geocode
		);

		if (numLidos != 3)
			continue;

		posto.f = novoPostoFicheiro;
		posto.primeiraAdjacencia = NULL;
		primeiroPosto = AdicionarPosto(primeiroPosto, posto);
	}

	fclose(file);

	return primeiroPosto;
}


/**
* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de postos adjacentes.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param filePath O caminho do ficheiro .txt com os dados dos postos adjacentes
* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes
* \author A. Cerqueira
*/
PostoVertice* LerPostosAdjacentesIniciais(PostoVertice* primeiroPosto, char* filePath) {
	FILE* file;
	char linha[MAX_SIZE];

	file = fopen(filePath, "r");
	if (file == NULL)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		PostoAdjacente adj;
		AdjacenciaFicheiro adjFicheiro;

		int numLidos = sscanf(linha, "%d;%d;%f",
			&adjFicheiro.origemId,
			&adjFicheiro.destinoId,
			&adjFicheiro.distancia
		);

		PostoVertice* origem = ProcurarPostoVerticePorId(primeiroPosto, adjFicheiro.origemId);

		adj.origem = &origem->p;
		adj.destino = ProcurarPostoPorId(primeiroPosto, adjFicheiro.destinoId);
		adj.f = adjFicheiro;

		origem = AdicionarPostoAdjacente(origem, &adj);
	}

	fclose(file);

	return primeiroPosto;
}


/**
* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de postos.
*
* \param filePath O caminho do ficheiro .dat com os dados dos postos
* \return O novo apontador para o primeiro elemento da lista ligada de postos
* \author A. Cerqueira
*/
PostoVertice* LerPostos(char* filePath) {
	FILE* file;
	PostoFicheiro* postoFicheiro;
	Posto* posto;
	PostoVertice* primeiroPosto = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	postoFicheiro = (PostoFicheiro*)malloc(sizeof(PostoFicheiro));
	posto = (Posto*)malloc(sizeof(Posto));

	while (postoFicheiro != NULL && fread(postoFicheiro, sizeof(PostoFicheiro), 1, file)) {

		posto->f = *postoFicheiro;
		posto->primeiraAdjacencia = NULL;

		primeiroPosto = AdicionarPosto(primeiroPosto, *posto);
		
		posto = (Posto*)malloc(sizeof(Posto));
		postoFicheiro = (PostoFicheiro*)malloc(sizeof(PostoFicheiro));
	}

	fclose(file);

	primeiroPosto = OrdenarPostosPorId(primeiroPosto);

	return primeiroPosto;
}


/**
* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de postos adjacentes.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param posto O apontador para o posto atual
* \param filePath O caminho do ficheiro .dat com os dados dos posto adjacentes.
* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes
* \author A. Cerqueira
*/
PostoVertice* LerPostosAdjacentes(PostoVertice* primeiroPosto, char* filePath) {
	FILE* file;
	AdjacenciaFicheiro* adjFicheiro;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	adjFicheiro = (AdjacenciaFicheiro*)malloc(sizeof(AdjacenciaFicheiro));

	while (adjFicheiro != NULL && fread(adjFicheiro, sizeof(AdjacenciaFicheiro), 1, file)) {
		PostoAdjacente adj;
		PostoVertice* origem = ProcurarPostoVerticePorId(primeiroPosto, adjFicheiro->origemId);

		adj.origem = &origem->p;
		adj.destino = ProcurarPostoPorId(primeiroPosto, adjFicheiro->destinoId);
		adj.f = *adjFicheiro;

		origem = AdicionarPostoAdjacente(origem, &adj);
		adjFicheiro = (AdjacenciaFicheiro*)malloc(sizeof(AdjacenciaFicheiro));
	}

	fclose(file);

	return primeiroPosto;
}


/**
* \brief Guarda a lista ligada de postos em um arquivo .dat.
*
* \param filePath O caminho para o arquivo .dat onde os postos serão guardados.
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool GuardarPostos(char* filePath, PostoVertice* primeiroPosto) {
	FILE* file;
	file = fopen(filePath, "wb");

	if (file == NULL)
		return false;

	PostoVertice* postoAtual = primeiroPosto;

	while (postoAtual != NULL) {
		fwrite(&postoAtual->p.f, sizeof(PostoFicheiro), 1, file);
		postoAtual = postoAtual->proximo;
	}

	fclose(file);

	return true;
}


/**
* \brief Guarda a lista ligada de postos adjacentes em um arquivo .dat.
*
* \param filePath O caminho para o arquivo .dat onde os postos adjacentes serão guardados.
* \param primeiroPostoAdjacente O apontador para o primeiro elemento da lista ligada de postos adjacentes
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool GuardarPostosAdjacentes(char* filePath, PostoAdjacente* primeiroPostoAdjacente) {
	FILE* file;
	file = fopen(filePath, "ab");

	if (file == NULL || primeiroPostoAdjacente == NULL)
		return false;

	PostoAdjacente* postoAdjacenteAtual = primeiroPostoAdjacente;

	while (postoAdjacenteAtual != NULL) {
		fwrite(&postoAdjacenteAtual->f, sizeof(AdjacenciaFicheiro), 1, file);
		postoAdjacenteAtual = postoAdjacenteAtual->proximo;
	}

	fclose(file);

	return true;
}


/**
* \brief Apaga o arquivo .dat com os dados dos postos.
* 
* \param filePath O caminho para o arquivo .dat onde os postos serão guardados.
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool ApagarPostosAdjacentesFicheiro(char* filePath) {
	return (remove(filePath) == 0);
}


/**
* \brief Adiciona um novo Posto ao inicio da lista ligada.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param novoPosto O Posto que será adicionado à lista.
* \return O novo apontador para o primeiro elemento da lista ligada de postos
* \author A. Cerqueira
*/
PostoVertice* AdicionarPosto(PostoVertice* primeiroPosto, Posto novoPosto) {
	PostoVertice* novoNode = (PostoVertice*)malloc(sizeof(PostoVertice));

	if (novoNode == NULL)
		return primeiroPosto;

	if (novoPosto.f.id == NULL)
		novoPosto.f.id = ProcurarProximoIdPosto(primeiroPosto);

	novoNode->proximo = (primeiroPosto != NULL) ? primeiroPosto : NULL;

	novoNode->p = novoPosto;
	primeiroPosto = novoNode;

	return primeiroPosto;
}


/**
* \brief Adiciona um novo Posto adjacente ao inicio da lista ligada.
*
* \param posto O apontador para o posto atual
* \param postoAdjacente O Posto adjacente que será adicionado à lista.
* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes
* \author A. Cerqueira
*/
PostoVertice* AdicionarPostoAdjacente(PostoVertice* posto, PostoAdjacente* postoAdjacente) {
	PostoAdjacente* novoNode = (PostoAdjacente*)malloc(sizeof(PostoAdjacente));

	if (novoNode == NULL)
		return posto;

	novoNode->f = postoAdjacente->f;
	novoNode->origem = postoAdjacente->origem;
	novoNode->destino = postoAdjacente->destino;
	novoNode->proximo = (posto->p.primeiraAdjacencia != NULL) ? posto->p.primeiraAdjacencia : NULL;

	posto->p.primeiraAdjacencia = novoNode;

	return posto;
}


/**
* \brief Ordena a lista ligada de postos por ID em ordem decrescente.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \return O novo apontador para o primeiro elemento da lista ligada de postos ordenada
* \author A. Cerqueira
*/
PostoVertice* OrdenarPostosPorId(PostoVertice* primeiroPosto) {
	PostoVertice* atual;
	PostoVertice* proximo;
	Posto temp;

	for (atual = primeiroPosto; atual != NULL; atual = atual->proximo) {
		for (proximo = atual->proximo; proximo != NULL; proximo = proximo->proximo) {

			if (atual->p.f.id < proximo->p.f.id) {
				temp = atual->p;
				atual->p = proximo->p;
				proximo->p = temp;
			}

		}
	}

	return primeiroPosto;
}


/**
* \brief Procura um posto na lista ligada a partir do seu ID.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param id O id do posto que será procurado
* \return O apontador para o posto com o id selecionado
* \author A. Cerqueira
*/
Posto* ProcurarPostoPorId(PostoVertice* primeiroPosto, int id) {
	PostoVertice* postoAtual = primeiroPosto;

	while (postoAtual != NULL) {
		if (postoAtual->p.f.id == id)
			return &postoAtual->p;
		postoAtual = postoAtual->proximo;
	}

	return NULL;
}


/**
* \brief Procura um posto vertice na lista ligada a partir do seu ID.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param id O id do posto que será procurado
* \return O apontador para o vertice do posto com o id selecionado
* \author A. Cerqueira
*/
PostoVertice* ProcurarPostoVerticePorId(PostoVertice* primeiroPosto, int id) {
	PostoVertice* postoAtual = primeiroPosto;

	while (postoAtual != NULL) {
		if (postoAtual->p.f.id == id)
			return postoAtual;
		postoAtual = postoAtual->proximo;
	}

	return NULL;
}


/**
* \brief Procura o ultimo id de um posto na lista ligada.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \return O proximo id a ser utilizado
* \author A. Cerqueira
*/
int ProcurarProximoIdPosto(PostoVertice* primeiroPosto) {
	PostoVertice* postoAtual = primeiroPosto;
	int id = 0;

	while (postoAtual != NULL) {

		if (postoAtual->p.f.id > id)
			id = postoAtual->p.f.id;

		postoAtual = postoAtual->proximo;
	}

	return id + 1;
}


/**
* \brief Procura o id de um posto na lista ligada a partir do seu geocodigo.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param geocodigo O geocodigo do posto que será procurado
* \return O id do posto com o geocodigo selecionado
* \author A. Cerqueira
*/
int ProcurarIdPostoDeGeocodigo(PostoVertice* primeiroPosto, char* geocodigo) {
	PostoVertice* postoAtual = primeiroPosto;

	while (postoAtual != NULL) {
		if (strcmp(postoAtual->p.f.geocode, geocodigo) == 0)
			return postoAtual->p.f.id;
		postoAtual = postoAtual->proximo;
	}

	return -1;
}


/**
* \brief Conta o numero de postos na lista ligada.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \return O numero de postos na lista ligada
* \author A. Cerqueira
*/
int ContarPostos(PostoVertice* primeiroPosto) {
	PostoVertice* postoAtual = primeiroPosto;
	int total = 0;

	while (postoAtual != NULL) {
		total++;
		postoAtual = postoAtual->proximo;
	}

	return total;
}


/**
* \brief Conta a distancia entre os postos na lista ligada.
*
* \param percurso O apontador para o primeiro elemento da lista ligada de postos do percurso
* \return O numero de postos na lista ligada
* \author A. Cerqueira
*/
float ContarDistanciaEmPercurso(Percurso* percurso) {
	Percurso* postoAtual = percurso;
	float distancia = 0;

	while (postoAtual != NULL) {
		distancia += postoAtual->distancia;
		postoAtual = postoAtual->proximo;
	}

	return distancia;
}


/**
* \brief Procura o percurso mais rapido entre dois postos, utilizando o algoritmo de Dijkstra.
*
* \param origem O apontador para o vertice do posto de origem
* \param destino O apontador para o vertice do posto de destino
* \return O apontador para o vertice do posto de inicio do percurso mais rapido
* \author A. Cerqueira
*/
Percurso* ProcurarPercursoMaisRapido(PostoVertice* origem, PostoVertice* destino, PostoVertice* primeiroPosto) {
	VerticeDijkstra* dijkstraVertices = InicializarDijkstraVertices(primeiroPosto);
	VerticeDijkstra* atual = EncontrarVerticeDijkstraPorId(dijkstraVertices, origem->p.f.id);
	atual->distancia = 0;

	while (atual != NULL) {
		PostoAdjacente* adj = atual->vertice->p.primeiraAdjacencia;
		
		while (adj != NULL) {
			VerticeDijkstra* adjDijkstra = EncontrarVerticeDijkstraPorId(dijkstraVertices, adj->f.destinoId);
			float novaDistancia = atual->distancia + adj->f.distancia;
			
			if (novaDistancia < adjDijkstra->distancia) {
				adjDijkstra->distancia = novaDistancia;
				adjDijkstra->antecessor = atual;
			}
			
			adj = adj->proximo;
		}
		
		atual->visitado = true;
		atual = EncontrarProximoVertice(dijkstraVertices);
	}

	// Agora, construímos o Percurso do destino de volta à origem
	VerticeDijkstra* dijkstraDestino = EncontrarVerticeDijkstraPorId(dijkstraVertices, destino->p.f.id);
	Percurso* percursoMaisRapido = ConstruirPercurso(dijkstraDestino);
	
	// Limpar a memoria
	LibertarDijkstraVertices(dijkstraVertices);
	
	return percursoMaisRapido;
}


/**
 * \brief Constroi um percurso a partir de um vertice de destino do algoritmo de Dijkstra.
 * 
 * \param dijkstraDestino O apontador para o vertice de destino do algoritmo de Dijkstra
 * \return O apontador para o primeiro elemento da lista ligada de postos do percurso
 */
Percurso* ConstruirPercurso(VerticeDijkstra* dijkstraDestino) {
	Percurso* percursoMaisRapido = NULL;
	VerticeDijkstra* dijkstraAtual = dijkstraDestino;
	
	while (dijkstraAtual->antecessor != NULL) {
		
		Percurso* novo = malloc(sizeof(Percurso));
		if (novo == NULL)
			return;
		
		novo->vertice = dijkstraAtual->vertice;
		novo->proximo = percursoMaisRapido;
		novo->distancia = dijkstraAtual->distancia - dijkstraAtual->antecessor->distancia;
		percursoMaisRapido = novo;
		dijkstraAtual = dijkstraAtual->antecessor;
	}

	// Adicionar a origem no percurso
	Percurso* novo = malloc(sizeof(Percurso));
	if (novo == NULL)
		return;

	novo->vertice = dijkstraAtual->vertice;
	novo->proximo = percursoMaisRapido;
	novo->distancia = 0;  
	percursoMaisRapido = novo;

	return percursoMaisRapido;
}


/**
* \brief Inicializa o algoritmo de Dijkstra para um conjunto de vertices.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \return O apontador para o primeiro elemento da lista ligada de vertices do algoritmo de Dijkstra
*/
VerticeDijkstra* InicializarDijkstraVertices(PostoVertice* primeiroPosto) {
	PostoVertice* postoAtual = primeiroPosto;
	VerticeDijkstra* dijkstraVertices = NULL;
	VerticeDijkstra* ultimo = NULL;

	while (postoAtual != NULL) {
		
		VerticeDijkstra* novo = malloc(sizeof(VerticeDijkstra));
		if (novo == NULL)
			return;

		novo->vertice = postoAtual;
		novo->distancia = INFINITO;
		novo->antecessor = NULL;
		novo->visitado = false;
		novo->proximo = NULL;

		if (dijkstraVertices == NULL) {
			dijkstraVertices = novo;
		}
		else {
			ultimo->proximo = novo;
		}
		ultimo = novo;

		postoAtual = postoAtual->proximo;
	}
	
	return dijkstraVertices;
}


/**
 * \brief Encontra o proximo vertice a ser visitado no algoritmo de Dijkstra.
 * 
 * \param dijkstraVertices O array com todos os vertices
 * \return O apontador para o vertice a ser visitado
 */
VerticeDijkstra* EncontrarProximoVertice(VerticeDijkstra* dijkstraVertices) {
	VerticeDijkstra* proximo = NULL;
	
	while (dijkstraVertices != NULL) {
		if (!dijkstraVertices->visitado && (proximo == NULL || dijkstraVertices->distancia < proximo->distancia)) {
			proximo = dijkstraVertices;
		}
		dijkstraVertices = dijkstraVertices->proximo;
	}
	
	return proximo;
}


/**
 * \brief Encontra um vertice na lista ligada de vertices do algoritmo de Dijkstra.
 * 
 * \param dijkstraVertices A lista ligada de vertices do algoritmo de Dijkstra
 * \param id O id do vertice a encontrar
 * \return O apontador para o vertice encontrado
 */
VerticeDijkstra* EncontrarVerticeDijkstraPorId(VerticeDijkstra* dijkstraVertices, int id) {
	while (dijkstraVertices != NULL && dijkstraVertices->vertice->p.f.id != id) {
		dijkstraVertices = dijkstraVertices->proximo;
	}
	return dijkstraVertices;
}


/**
 * \brief Liberta a memoria alocada para a lista ligada de vertices do algoritmo de Dijkstra.
 *
 * \param dijkstraVertices O apontador para o primeiro elemento da lista ligada de vertices do algoritmo de Dijkstra
 */
bool LibertarDijkstraVertices(VerticeDijkstra* dijkstraVertices) {
	VerticeDijkstra* dijkstraAtual = dijkstraVertices;
	
	while (dijkstraAtual != NULL) {
		VerticeDijkstra* dijkstraProximo = dijkstraAtual->proximo;
		free(dijkstraAtual);
		dijkstraAtual = dijkstraProximo;
	}

	return true;
}