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
void ResetarGestores(Gestor* ultimoGestor) {
	Gestor* gestor = ultimoGestor;

	while (gestor != NULL) {
		Gestor* gestorAnterior = gestor;
		gestor = gestor->proximo;
		free(gestorAnterior);
	}
}


/**
* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
void CarregarGestoresIniciais(Gestor* ultimoGestor) {
	ResetarGestores(ultimoGestor);
	ultimoGestor = LerGestoresIniciais();
	GuardarGestores(ultimoGestor);
}


/**
* \brief Ler Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
*
* \return
* \author A. Cerqueira
*
*/
Gestor* LerGestoresIniciais() {
	FILE* fp;

	if (fopen_s(&fp, HARDDATA_FILE_NAME, "r") != 0) {
		printf("Erro ao abrir ficheiro\n");
		return NULL;
	}

	Gestor* ultimoGestor = NULL;
	char linha[MAX_SIZE];

	while (fgets(linha, MAX_SIZE, fp)) {
		Gestor* gestor = (Gestor*)malloc(sizeof(Gestor));

		if (gestor == NULL) {
			printf("Erro ao alocar memoria\n");
			return NULL;
		}

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		gestor->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(gestor->nome, NOME_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(gestor->email, EMAIL_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(gestor->password, PASSWORD_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		gestor->ativo = (bool)atoi(campo);

		gestor->proximo = ultimoGestor;
		ultimoGestor = gestor;
	}

	fclose(fp);

	return ultimoGestor;
}


 /**
 * \brief Ler dados de um ficheiro binario e guardar numa lista ligada
 *
 * \return Lista ligada com os dados lidos
 * \author A. Cerqueira
 *
 */
Gestor* LerGestores() {
	
	FILE* fp;

	if (fopen_s(&fp, SAVE_FILE_NAME, "rb") != 0) {
		printf("Erro ao abrir ficheiro\n");
		return NULL;
	}

	Gestor* ultimoGestor = NULL;
	char linha[MAX_SIZE];
	
	while (fgets(linha, MAX_SIZE, fp)) {
		Gestor* gestor = (Gestor*)malloc(sizeof(Gestor));

		if (gestor == NULL) {
			printf("Erro ao alocar memoria\n");
			return NULL;
		}

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		gestor->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(gestor->nome, NOME_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(gestor->email, EMAIL_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(gestor->password, PASSWORD_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		gestor->ativo = (bool)atoi(campo);

		gestor->proximo = ultimoGestor;
		ultimoGestor = gestor;
	}

	fclose(fp);

	return ultimoGestor;
}


/**
 * \brief Guardar dados de uma lista ligada num ficheiro de texto
 *
 * \param lista Lista ligada com os dados a guardar
 * \return 0 se tudo correu bem, 1 caso contrário
 * \author A. Cerqueira
 *
 */
void GuardarGestores(Gestor* ultimoGestor) {
	FILE* fp;
	Gestor* gestor = ultimoGestor;

	if (fopen_s(&fp, SAVE_FILE_NAME, "wb") != 0) {
		printf("Erro ao abrir ficheiro\n");
		return 1;
	}

	if (ultimoGestor == NULL) {
		printf("Lista vazia\n");
		return;
	}

	while (gestor != NULL) {
		fprintf(fp, "%d;%s;%s;%s;%d;\n", gestor->id, gestor->nome, gestor->email, gestor->password, gestor->ativo);
		gestor = gestor->proximo;
	}

	fclose(fp);

	return 0;
}


/**
* \brief Adicionar um Gestor à lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void AdicionarGestor(Gestor** ultimoGestor, char* nome, char* email, char* password) {

	Gestor* gestor = (Gestor*)malloc(sizeof(Gestor));

	if (gestor == NULL) {
		printf("Erro ao alocar memoria\n");
		return;
	}

	gestor->id = (*ultimoGestor)->id + 1;
	strcpy_s(gestor->nome, NOME_LENGHT, nome);
	strcpy_s(gestor->email, EMAIL_LENGHT, email);
	strcpy_s(gestor->password, PASSWORD_LENGHT, password);
	gestor->ativo = true;
	gestor->proximo = NULL;

	gestor->proximo = *ultimoGestor;
	*ultimoGestor = gestor;
}


/**
* \brief Remover um Gestor da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void RemoverGestor(Gestor* ultimoGestor, int id) {

	Gestor* gestor = ultimoGestor;

	while (gestor->proximo != NULL) {
		
		if (gestor->id == id) {
			gestor->ativo = false;
			return;
		}

		gestor = gestor->proximo;
	}
}


/**
* \brief Alterar um Gestor da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void EditarGestor(Gestor* ultimoGestor, int id, char* nome, char* email, char* password) {

	Gestor* gestor = ultimoGestor;

	while (gestor != NULL) {
		if (gestor->id == id) {
			strcpy_s(gestor->nome, NOME_LENGHT, nome);
			strcpy_s(gestor->email, EMAIL_LENGHT, email);
			strcpy_s(gestor->password, PASSWORD_LENGHT, password);
			return;
		}
		gestor = gestor->proximo;
	}
}
