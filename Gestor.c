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
bool ResetarGestores(Gestor* primeiroGestor) {
	Gestor* gestor = primeiroGestor;

	while (gestor != NULL) {
		Gestor* gestorAnterior = gestor;
		gestor = gestor->proximo;
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
bool CarregarGestoresIniciais(Gestor** primeiroGestor, char* filePathInicial, char* saveFilePath) {
	ResetarGestores(*primeiroGestor);
	*primeiroGestor = LerGestoresIniciais(filePathInicial);
	GuardarGestores(saveFilePath , *primeiroGestor);
	
	return true;
}


/**
* \brief Ler Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
*
* \return
* \author A. Cerqueira
*
*/
Gestor* LerGestoresIniciais(char* filePath) {
	FILE* file;
	Gestor* primeiroGestor = NULL;
	char linha[MAX_SIZE];

	if (fopen_s(&file, filePath, "r") != 0)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));

		if (novoGestor == NULL)
			return NULL;

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		novoGestor->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoGestor->nome, NOME_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoGestor->email, EMAIL_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoGestor->password, PASSWORD_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		novoGestor->ativo = (bool)atoi(campo);

		novoGestor->proximo = NULL;

		if (primeiroGestor == NULL) {
			primeiroGestor = novoGestor;
		}
		else {
			Gestor* gestorAtual = primeiroGestor;

			while (gestorAtual->proximo != NULL) {
				gestorAtual = gestorAtual->proximo;
			}

			gestorAtual->proximo = novoGestor;
		}
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
Gestor* LerGestores(char* filePath) {
	FILE* file;
	Gestor* primeiroGestor = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	Gestor* gestor = NULL;
	size_t bytesLidos = fread(&gestor, sizeof(Gestor), 1, file);
	
	while (bytesLidos > 0) {
		Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));
		
		if (novoGestor == NULL)
			return NULL;

		novoGestor->id = gestor->id;
		strcpy_s(novoGestor->nome, NOME_LENGHT, gestor->nome);
		strcpy_s(novoGestor->email, EMAIL_LENGHT, gestor->email);
		strcpy_s(novoGestor->password, PASSWORD_LENGHT, gestor->password);
		novoGestor->ativo = gestor->ativo;
		novoGestor->proximo = NULL;

		if (primeiroGestor == NULL) {
			primeiroGestor = novoGestor;
		}
		else {
			Gestor* gestorAtual = primeiroGestor;

			while (gestorAtual->proximo != NULL) {
				gestorAtual = gestorAtual->proximo;
			}

			gestorAtual->proximo = novoGestor;
		}
		
		bytesLidos = fread(&gestor, sizeof(Gestor), 1, file);
	}

	fclose(file);
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
bool GuardarGestores(char* filePath, Gestor* primeiroGestor) {
	FILE* file;
	file = fopen(filePath, "wb");

	if (file == NULL)
		return false;

	Gestor* gestorAtual = primeiroGestor;

	while (gestorAtual != NULL) {
		// fwrite(gestorAtual, sizeof(Gestor), 1, file);
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
bool AdicionarGestor(Gestor* primeiroGestor, Gestor* novoGestor) {

	if (novoGestor == NULL)
		return false;

	if (primeiroGestor == NULL) {
		primeiroGestor = novoGestor;
		return true;
	}

	Gestor* gestorAtual = primeiroGestor;

	while (gestorAtual->proximo != NULL) {
		gestorAtual = gestorAtual->proximo;
	}

	novoGestor->id = gestorAtual->id + 1;
	novoGestor->ativo = true;
	novoGestor->proximo = NULL;
	gestorAtual->proximo = novoGestor;

	return true;
}


/**
* \brief Remover um Gestor da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool RemoverGestor(Gestor* primeiroGestor, int id) {

	Gestor* gestor = primeiroGestor;

	while (gestor->proximo != NULL) {
		
		if (gestor->id == id) {
			gestor->ativo = false;
			return;
		}

		gestor = gestor->proximo;
	}

	return true;
}


/**
* \brief Alterar um Gestor da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool EditarGestor(Gestor* primeiroGestor, Gestor* gestorSelecionado) {

	Gestor* gestor = primeiroGestor;

	while (gestor != NULL) {
		
		if (gestor->id == gestorSelecionado->id) {
			strcpy_s(gestor->nome, NOME_LENGHT, gestorSelecionado->nome);
			strcpy_s(gestor->email, EMAIL_LENGHT, gestorSelecionado->email);
			strcpy_s(gestor->password, PASSWORD_LENGHT, gestorSelecionado->password);
			return;
		}
		
		gestor = gestor->proximo;
	}

	return true;
}
