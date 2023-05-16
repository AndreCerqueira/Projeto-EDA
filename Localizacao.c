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
PostoVertice* CarregarPostosIniciais(PostoVertice* primeiroPosto, char* postosFilePathInicial, char* postosSaveFilePath, char* postosAdjFilePathInicial, char* postosAdjSaveFilePath) {
	LibertarPostos(primeiroPosto);
	primeiroPosto = LerPostosIniciais(postosFilePathInicial);
	primeiroPosto = CarregarPostosAdjacentesIniciais(primeiroPosto, postosAdjFilePathInicial, postosAdjSaveFilePath);
	GuardarPostos(postosSaveFilePath, primeiroPosto);

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

	for (atual = primeiroPosto; atual != NULL; atual = atual->proximo) {
		LibertarPostosAdjacentes(atual->p.primeiraAdjacencia);
		atual->p.primeiraAdjacencia = LerPostosAdjacentesIniciais(primeiroPosto, atual, filePathInicial);
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
* \param filePath O caminho do ficheiro .txt com os dados dos postos adjacentes
* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes
* \author A. Cerqueira
*/
PostoAdjacente* LerPostosAdjacentesIniciais(PostoVertice* primeiroPosto, PostoVertice* posto, char* filePath) {
	FILE* file;
	PostoAdjacente* primeiroPostoAdjacente = NULL;
	char linha[MAX_SIZE];

	file = fopen(filePath, "r");
	if (file == NULL)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		AdjacenciaFicheiro adjFicheiro;

		int numLidos = sscanf(linha, "%d;%d;%f",
			&adjFicheiro.origemId,
			&adjFicheiro.destinoId,
			&adjFicheiro.distancia
		);

		if (numLidos != 3 || posto->p.f.id != adjFicheiro.origemId)
			continue;

		primeiroPostoAdjacente = AdicionarPostoAdjacente(primeiroPosto, primeiroPostoAdjacente, adjFicheiro);
	}

	fclose(file);

	return primeiroPostoAdjacente;
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
	Posto* posto;
	PostoVertice* primeiroPosto = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	posto = (Posto*)malloc(sizeof(Posto));

	while (posto != NULL && fread(posto, sizeof(Posto), 1, file)) {
		primeiroPosto = AdicionarPosto(primeiroPosto, *posto);
		posto = (Posto*)malloc(sizeof(Posto));
	}

	fclose(file);

	primeiroPosto = OrdenarPostosPorId(primeiroPosto);

	return primeiroPosto;
}


/**
* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de postos adjacentes.
*
* \param filePath O caminho do ficheiro .dat com os dados dos posto adjacentes.
* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes
* \author A. Cerqueira
*/
PostoAdjacente* LerPostosAdjacentes(PostoVertice* primeiroPosto, char* filePath) {
	FILE* file;
	AdjacenciaFicheiro* adjFicheiro;
	PostoAdjacente* primeiroPostoAdjacente = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	adjFicheiro = (AdjacenciaFicheiro*)malloc(sizeof(AdjacenciaFicheiro));

	while (adjFicheiro != NULL && fread(adjFicheiro, sizeof(AdjacenciaFicheiro), 1, file)) {
		primeiroPostoAdjacente = AdicionarPostoAdjacente(primeiroPosto, primeiroPostoAdjacente, *adjFicheiro);
		adjFicheiro = (AdjacenciaFicheiro*)malloc(sizeof(AdjacenciaFicheiro));
	}

	fclose(file);

	return primeiroPostoAdjacente;
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
		fwrite(&postoAtual->p, sizeof(Posto), 1, file);
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
	file = fopen(filePath, "wb");

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
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param primeiroPostoAdjacente O apontador para o primeiro elemento da lista ligada de postos adjacentes
* \param novaAdjacencia A adjacência que será adicionada à lista.
* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes
* \author A. Cerqueira
*/
PostoAdjacente* AdicionarPostoAdjacente(PostoVertice* primeiroPosto, PostoAdjacente* primeiroPostoAdjacente, AdjacenciaFicheiro novoAdjFicheiro) {
	PostoAdjacente* novoNode = (PostoAdjacente*)malloc(sizeof(PostoAdjacente));

	if (novoNode == NULL)
		return primeiroPostoAdjacente;

	novoNode->f = novoAdjFicheiro;
	novoNode->origem = ProcurarPostoPorId(primeiroPosto, novoAdjFicheiro.origemId);
	novoNode->destino = ProcurarPostoPorId(primeiroPosto, novoAdjFicheiro.destinoId);
	novoNode->proximo = (primeiroPostoAdjacente != NULL) ? primeiroPostoAdjacente : NULL;

	primeiroPostoAdjacente = novoNode;

	return primeiroPostoAdjacente;
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