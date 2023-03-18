/*****************************************************************//**
 * \file   Gestor.c
 * \brief  Funções de Gestor
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

#include "Gestor.h"


/**
* \brief Liberta a memória da lista ligada de gestores.
*
* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool LibertarGestores(GestorLista* primeiroGestor) {
	GestorLista* gestorAtual = primeiroGestor;

	while (gestorAtual != NULL) {
		GestorLista* gestorAnterior = gestorAtual;
		gestorAtual = gestorAtual->proximo;
		free(gestorAnterior);
	}

	primeiroGestor = NULL;

	return true;
}


/**
* \brief Carrega os dados iniciais dos gestores de um ficheiro .txt para uma lista ligada e guarda no ficheiro .dat.
*
* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos gestores
* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
* \return O novo apontador para o primeiro elemento da lista ligada de gestores carregada
* \author A. Cerqueira
*/
GestorLista* CarregarGestoresIniciais(GestorLista* primeiroGestor, char* filePathInicial, char* saveFilePath) {
	LibertarGestores(primeiroGestor);
	primeiroGestor = LerGestoresIniciais(filePathInicial);
	GuardarGestores(saveFilePath, primeiroGestor);

	return primeiroGestor;
}


/**
* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de gestores.
*
* \param filePath O caminho do ficheiro .txt com os dados dos gestores
* \return O novo apontador para o primeiro elemento da lista ligada de gestores
* \author A. Cerqueira
*/
GestorLista* LerGestoresIniciais(char* filePath) {
	FILE* file;
	GestorLista* primeiroGestor = NULL;
	char linha[MAX_SIZE];

	file = fopen(filePath, "r");
	if (file == NULL)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		GestorLista* novoGestor = (GestorLista*)malloc(sizeof(GestorLista));

		if (novoGestor == NULL)
			return NULL;

		char* contexto = NULL;
		char* campo = strtok(linha, ";", &contexto);
		novoGestor->g.id = atoi(campo);

		campo = strtok(NULL, ";", &contexto);
		strcpy(novoGestor->g.nome, campo);

		campo = strtok(NULL, ";", &contexto);
		strcpy(novoGestor->g.email, campo);

		campo = strtok(NULL, ";", &contexto);
		strcpy(novoGestor->g.password, campo);

		campo = strtok(NULL, ";", &contexto);
		novoGestor->g.ativo = (bool)atoi(campo);

		novoGestor->proximo = primeiroGestor;
		primeiroGestor = novoGestor;
	}

	fclose(file);

	return primeiroGestor;
}


/**
* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de gestores.
*
* \param filePath O caminho do ficheiro .dat com os dados dos gestores
* \return O novo apontador para o primeiro elemento da lista ligada de gestores
* \author A. Cerqueira
*/
GestorLista* LerGestores(char* filePath) {
	FILE* file;
	GestorLista* primeiroGestor = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	Gestor gestor;
	size_t bytesLidos = fread(&gestor, sizeof(Gestor), 1, file);

	while (bytesLidos > 0) {
		GestorLista* novoGestor = (GestorLista*)malloc(sizeof(GestorLista));

		if (novoGestor == NULL)
			return NULL;

		novoGestor->g.id = gestor.id;
		strcpy(novoGestor->g.nome, gestor.nome);
		strcpy(novoGestor->g.email, gestor.email);
		strcpy(novoGestor->g.password, gestor.password);
		novoGestor->g.ativo = gestor.ativo;
		novoGestor->proximo = primeiroGestor;
		primeiroGestor = novoGestor;

		bytesLidos = fread(&gestor, sizeof(Gestor), 1, file);
	}

	fclose(file);

	primeiroGestor = OrdenarGestoresPorId(primeiroGestor);

	return primeiroGestor;
}


/**
* \brief Guarda a lista ligada de gestores em um arquivo .dat.
*
* \param filePath O caminho para o arquivo .dat onde os gestores serão guardados.
* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool GuardarGestores(char* filePath, GestorLista* primeiroGestor) {
	FILE* file;
	file = fopen(filePath, "wb");

	if (file == NULL)
		return false;

	GestorLista* gestorAtual = primeiroGestor;

	while (gestorAtual != NULL) {
		fwrite(&gestorAtual->g, sizeof(Gestor), 1, file);
		gestorAtual = gestorAtual->proximo;
	}

	fclose(file);

	return true;
}


/**
* \brief Adiciona um novo Gestor ao inicio da lista ligada.
*
* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
* \param novoGestor O Gestor que será adicionado à lista.
* \return O novo apontador para o primeiro elemento da lista ligada de gestores
* \author A. Cerqueira
*/
GestorLista* AdicionarGestor(GestorLista* primeiroGestor, Gestor novoGestor) {
	GestorLista* novoNode = (GestorLista*)malloc(sizeof(GestorLista));
	
	if (novoNode == NULL)
		return primeiroGestor;

	if (novoGestor.ativo == NULL)
		novoGestor.ativo = true;

	if (novoGestor.id == NULL)
		novoGestor.id = ProcurarProximoIdGestor(primeiroGestor);
	
	novoNode->proximo = (primeiroGestor != NULL) ? primeiroGestor : NULL;

	novoNode->g = novoGestor;
	primeiroGestor = novoNode;
	
	return primeiroGestor;
}


/**
* \brief Remover um Gestor da lista ligada
*
* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
* \param id O id do Gestor que será removido
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool RemoverGestor(GestorLista* primeiroGestor, int id) {

	GestorLista* gestorAtual = primeiroGestor;

	while (gestorAtual != NULL) {
		
		if (gestorAtual->g.id == id) {
			gestorAtual->g.ativo = false;
			return true;
		}

		gestorAtual = gestorAtual->proximo;
	}

	return false;
}


/**
* \brief Alterar um Gestor da lista ligada
*
* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
* \param gestorSelecionado O Gestor que será alterado
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool EditarGestor(GestorLista* primeiroGestor, Gestor gestorSelecionado) {
	GestorLista* gestorAtual = primeiroGestor;

	while (gestorAtual != NULL) {
		
		if (gestorAtual->g.id == gestorSelecionado.id) {
			strcpy(gestorAtual->g.nome, gestorSelecionado.nome);
			strcpy(gestorAtual->g.email, gestorSelecionado.email);
			strcpy(gestorAtual->g.password, gestorSelecionado.password);
			return true;
		}
		
		gestorAtual = gestorAtual->proximo;
	}

	return false;
}


/**
 * \brief Ordena a lista ligada de gestores por ID em ordem decrescente.
 *
 * \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
 * \return O novo apontador para o primeiro elemento da lista ligada de gestores ordenada
 * \author A. Cerqueira
 */
GestorLista* OrdenarGestoresPorId(GestorLista* primeiroGestor) {
	GestorLista* atual;
	GestorLista* proximo;
	Gestor temp;

	for (atual = primeiroGestor; atual != NULL; atual = atual->proximo) {
		for (proximo = atual->proximo; proximo != NULL; proximo = proximo->proximo) {
			
			if (atual->g.id < proximo->g.id) {
				temp = atual->g;
				atual->g = proximo->g;
				proximo->g = temp;
			}
			
		}
	}

	return primeiroGestor;
}


/**
* \brief Procura o ultimo id de um Gestor na lista ligada.
*
* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
* \return O proximo id a ser utilizado
* \author A. Cerqueira
*/
int ProcurarProximoIdGestor(GestorLista* primeiroGestor) {
	GestorLista* gestorAtual = primeiroGestor;
	int id = 0;

	while (gestorAtual != NULL) {

		if (gestorAtual->g.id > id)
			id = gestorAtual->g.id;

		gestorAtual = gestorAtual->proximo;
	}

	return id + 1;
}
