/*****************************************************************//**
 * \file   MeioMobilidade.c
 * \brief  Funções de Meios de mobilidade
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

#include "MeioMobilidade.h"


/**
* \brief Resetar lista ligada de Meios de Mobilidade, reescreve o ficheiro .dat com a lista vazia
*
* \return
* \author A. Cerqueira
*
*/
void ResetarMeiosMobilidade(MeioMobilidade* ultimoMeio) {
	MeioMobilidade* gestor = ultimoMeio;

	while (gestor != NULL) {
		MeioMobilidade* meioAnterior = gestor;
		gestor = gestor->proximo;
		free(meioAnterior);
	}
}


/**
* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
*
* \return
* \author A. Cerqueira
*
*/
void CarregarMeiosMobilidadeIniciais(MeioMobilidade* ultimoMeio) {
	ResetarMeiosMobilidade(ultimoMeio);
	ultimoMeio = LerMeiosMobilidadeIniciais();
	GuardarMeiosMobilidade(ultimoMeio);
}


/**
* \brief Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
*
* \return
* \author A. Cerqueira
*
*/
MeioMobilidade* LerMeiosMobilidadeIniciais() {
	FILE* fp;

	if (fopen_s(&fp, HARDDATA_FILE_NAME, "r") != 0) {
		printf("Erro ao abrir ficheiro\n");
		return NULL;
	}

	MeioMobilidade* ultimoMeioMobilidade = NULL;
	char linha[MAX_SIZE];

	while (fgets(linha, MAX_SIZE, fp)) {
		MeioMobilidade* meioMobilidade = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));

		if (meioMobilidade == NULL) {
			printf("Erro ao alocar memoria\n");
			return NULL;
		}

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		meioMobilidade->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		meioMobilidade->tipo = (TipoMeioMobilidade)atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		meioMobilidade->cargaBateria = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		meioMobilidade->custoAluguer = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(meioMobilidade->localizacao, LOCALIZACAO_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		meioMobilidade->ativo = (bool)atoi(campo);

		meioMobilidade->proximo = ultimoMeioMobilidade;
		ultimoMeioMobilidade = meioMobilidade;
	}

	fclose(fp);

	return ultimoMeioMobilidade;
}


/**
* \brief Ler dados de um ficheiro binario e guardar numa lista ligada
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
MeioMobilidade* LerMeiosMobilidade() {

	FILE* fp;

	if (fopen_s(&fp, SAVE_FILE_NAME, "rb") != 0) {
		printf("Erro ao abrir ficheiro\n");
		return NULL;
	}

	MeioMobilidade* ultimoMeioMobilidade = NULL;
	char linha[MAX_SIZE];
	
	while (fgets(linha, MAX_SIZE, fp)) {
		MeioMobilidade* meioMobilidade = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));

		if (meioMobilidade == NULL) {
			printf("Erro ao alocar memoria\n");
			return NULL;
		}

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		meioMobilidade->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		meioMobilidade->tipo = (TipoMeioMobilidade)atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		meioMobilidade->cargaBateria = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		meioMobilidade->custoAluguer = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(meioMobilidade->localizacao, LOCALIZACAO_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		meioMobilidade->ativo = (bool)atoi(campo);

		meioMobilidade->proximo = ultimoMeioMobilidade;
		ultimoMeioMobilidade = meioMobilidade;
	}
	
	fclose(fp);

	return ultimoMeioMobilidade;
}


/**
* \brief Carregar dados inicial de um ficheiro de texto e guardar numa lista ligada
*
* \param clientes Lista ligada com os clientes
* \return
* \author A. Cerqueira
*
*/
void GuardarMeiosMobilidade(MeioMobilidade* ultimoMeioMobilidade) {
	FILE* fp;
	MeioMobilidade* meio = ultimoMeioMobilidade;

	if (fopen_s(&fp, SAVE_FILE_NAME, "wb") != 0) {
		printf("Erro ao abrir ficheiro\n");
		return;
	}

	if (ultimoMeioMobilidade == NULL) {
		printf("Lista vazia\n");
		return;
	}

	while (meio->proximo != NULL) {

		fprintf(fp, "%d;%d;%.2f;%.2f;%s;%d;\n", meio->id, meio->tipo, meio->cargaBateria, meio->custoAluguer, meio->localizacao, meio->ativo);

		meio = meio->proximo;
	}

	fclose(fp);
}


/**
* \brief Adicionar um MeioMobilidade à lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void AdicionarMeioMobilidade(MeioMobilidade** ultimoMeioMobilidade, TipoMeioMobilidade tipo, float cargaBateria, float custoAluguer, char* localizacao) {
	
	MeioMobilidade* novoMeioMobilidade = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));

	if (novoMeioMobilidade == NULL) {
		printf("Erro ao alocar memoria\n");
		return;
	}

	novoMeioMobilidade->id = (*ultimoMeioMobilidade)->id + 1;
	novoMeioMobilidade->tipo = tipo;
	novoMeioMobilidade->cargaBateria = cargaBateria;
	novoMeioMobilidade->custoAluguer = custoAluguer;
	strcpy_s(novoMeioMobilidade->localizacao, LOCALIZACAO_LENGHT, localizacao);
	novoMeioMobilidade->ativo = true;
	novoMeioMobilidade->proximo = NULL;

	novoMeioMobilidade->proximo = *ultimoMeioMobilidade;
	*ultimoMeioMobilidade = novoMeioMobilidade;
}


/**
* \brief Remover um MeioMobilidade da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void RemoverMeioMobilidade(MeioMobilidade* ultimoMeioMobilidade, int id) {

	MeioMobilidade* meio = ultimoMeioMobilidade;

	while (meio->proximo != NULL) {

		if (meio->id == id) {
			meio->ativo = false;
			return;
		}

		meio = meio->proximo;
	}
}


/**
* \brief Alterar um MeioMobilidade da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void EditarMeioMobilidade(MeioMobilidade* ultimoMeioMobilidade, int id, TipoMeioMobilidade tipo, float cargaBateria, float custoAluguer, char* localizacao) {

	MeioMobilidade* meio = ultimoMeioMobilidade;

	while (meio->proximo != NULL) {

		if (meio->id == id) {
			meio->tipo = tipo;
			meio->cargaBateria = cargaBateria;
			meio->custoAluguer = custoAluguer;
			strcpy_s(meio->localizacao, LOCALIZACAO_LENGHT, localizacao);
			return;
		}

		meio = meio->proximo;
	}
}


/**
* \brief Converter um TipoMeioMobilidade para string
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
char* TipoMeioMobilidadeToString(TipoMeioMobilidade tipoMeioMobilidade) {

	switch (tipoMeioMobilidade) {
		case Bicibleta:
			return "Bicibleta";
		case Trotinente:
			return "Trotinente";
		case Scooter:
			return "Scooter";
		case SkateEletrico:
			return "SkateEletrico";
		case Outro:
			return "Outro";
		default:
			return "Desconhecido";
	}
}