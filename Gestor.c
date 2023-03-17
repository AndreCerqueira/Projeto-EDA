/*****************************************************************//**
 * \file   Gestor.c
 * \brief  Funções de Gestor
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

#include "Gestor.h"


/**
* \brief Resetar lista ligada de Gestores, reescreve o ficheiro .dat com a lista vazia
*
* \return
* \author A. Cerqueira
*
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
* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
bool CarregarGestoresIniciais(GestorLista** primeiroGestor, char* filePathInicial, char* saveFilePath) {
	LibertarGestores(*primeiroGestor);
	*primeiroGestor = LerGestoresIniciais(filePathInicial);
	GuardarGestores(saveFilePath, *primeiroGestor);

	return true;
}


/**
* \brief Ler Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
*
* \return
* \author A. Cerqueira
*
*/

GestorLista* LerGestoresIniciais(char* filePath) {
	FILE* file;
	GestorLista* primeiroGestor = NULL;
	char linha[MAX_SIZE];

	if (fopen_s(&file, filePath, "r") != 0)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		GestorLista* novoGestor = (GestorLista*)malloc(sizeof(GestorLista));

		if (novoGestor == NULL)
			return NULL;

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		novoGestor->g.id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoGestor->g.nome, NOME_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoGestor->g.email, EMAIL_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoGestor->g.password, PASSWORD_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		novoGestor->g.ativo = (bool)atoi(campo);

		novoGestor->proximo = primeiroGestor;
		primeiroGestor = novoGestor;
	}

	fclose(file);

	return primeiroGestor;
}


 /**
 * \brief Ler dados de um ficheiro binario e guardar numa lista ligada
 *
 * \return Lista ligada com os dados lidos
 * \author A. Cerqueira
 *
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
		strcpy_s(novoGestor->g.nome, NOME_LENGHT, gestor.nome);
		strcpy_s(novoGestor->g.email, EMAIL_LENGHT, gestor.email);
		strcpy_s(novoGestor->g.password, PASSWORD_LENGHT, gestor.password);
		novoGestor->g.ativo = gestor.ativo;
		novoGestor->proximo = primeiroGestor;
		primeiroGestor = novoGestor;

		bytesLidos = fread(&gestor, sizeof(Gestor), 1, file);
	}

	fclose(file);

	OrdenarGestoresPorId(&primeiroGestor);
	
	return primeiroGestor;
}


/**
 * \brief Guardar dados de uma lista ligada num ficheiro de texto
 *
 * \param lista Lista ligada com os dados a guardar
 * \return 0 se tudo correu bem, 1 caso contrário
 * \author A. Cerqueira
 *
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
* \brief Adicionar um Gestor à lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool AdicionarGestor(GestorLista** primeiroGestor, Gestor* novoGestor) {
	if (novoGestor == NULL)
		return false;

	GestorLista* novoNode = (GestorLista*)malloc(sizeof(GestorLista));
	if (novoNode == NULL)
		return false;

	novoGestor->ativo = true;
	novoGestor->id = ProcurarProximoIdGestor(*primeiroGestor);
	novoNode->proximo = (*primeiroGestor != NULL) ? *primeiroGestor : NULL;

	novoNode->g = *novoGestor;
	*primeiroGestor = novoNode;
	
	return true;
}


/**
* \brief Remover um Gestor da lista ligada
*
* \return
* \author A. Cerqueira
*
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
* \return
* \author A. Cerqueira
*
*/
bool EditarGestor(GestorLista* primeiroGestor, Gestor* gestorSelecionado) {
	GestorLista* gestorAtual = primeiroGestor;

	while (gestorAtual != NULL) {
		
		if (gestorAtual->g.id == gestorSelecionado->id) {
			strcpy_s(gestorAtual->g.nome, NOME_LENGHT, gestorSelecionado->nome);
			strcpy_s(gestorAtual->g.email, EMAIL_LENGHT, gestorSelecionado->email);
			strcpy_s(gestorAtual->g.password, PASSWORD_LENGHT, gestorSelecionado->password);
			return true;
		}
		
		gestorAtual = gestorAtual->proximo;
	}

	return false;
}


/**
 * \brief Ordenar gestores por id
 *
 * \param primeiroCliente
 * \return
 */
bool OrdenarGestoresPorId(GestorLista** primeiroGestor) {
	GestorLista* atual;
	GestorLista* proximo;
	Gestor temp;

	for (atual = *primeiroGestor; atual != NULL; atual = atual->proximo) {
		for (proximo = atual->proximo; proximo != NULL; proximo = proximo->proximo) {
			
			if (atual->g.id < proximo->g.id) {
				temp = atual->g;
				atual->g = proximo->g;
				proximo->g = temp;
			}
			
		}
	}

	return true;
}


/**
* \brief Devolve o proximo id disponivel para um Gestor
*
* \return
* \author A. Cerqueira
*
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
