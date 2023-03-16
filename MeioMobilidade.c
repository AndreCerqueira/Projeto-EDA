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
bool ResetarMeiosMobilidade(MeioMobilidade* primeiroMeio) {
	MeioMobilidade* gestor = primeiroMeio;

	while (gestor != NULL) {
		MeioMobilidade* meioAnterior = gestor;
		gestor = gestor->proximo;
		free(meioAnterior);
	}

	primeiroMeio = NULL;
	
	return true;
}


/**
* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
*
* \return
* \author A. Cerqueira
*
*/
bool CarregarMeiosMobilidadeIniciais(MeioMobilidade** primeiroMeio, char* filePathInicial, char* saveFilePath) {
	ResetarMeiosMobilidade(*primeiroMeio);
	*primeiroMeio = LerMeiosMobilidadeIniciais(filePathInicial);
	GuardarMeiosMobilidade(saveFilePath , *primeiroMeio);

	return true;
}


/**
* \brief Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
*
* \return
* \author A. Cerqueira
*
*/
MeioMobilidade* LerMeiosMobilidadeIniciais(char* filePath) {
	FILE* file;
	MeioMobilidade* primeiroMeio = NULL;
	char linha[MAX_SIZE];
	
	if (fopen_s(&file, filePath, "r") != 0)
		return NULL;
	
	while (fgets(linha, MAX_SIZE, file)) {
		MeioMobilidade* novoMeio = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));

		if (novoMeio == NULL)
			return NULL;

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		novoMeio->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		novoMeio->tipo = (TipoMeioMobilidade)atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		novoMeio->cargaBateria = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		novoMeio->custoAluguer = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoMeio->localizacao, LOCALIZACAO_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		novoMeio->ativo = (bool)atoi(campo);

		novoMeio->proximo = NULL;

		if (primeiroMeio == NULL) {
			primeiroMeio = novoMeio;
		}
		else {
			MeioMobilidade* meioAtual = primeiroMeio;

			while (meioAtual->proximo != NULL) {
				meioAtual = meioAtual->proximo;
			}

			meioAtual->proximo = novoMeio;
		}
	}

	fclose(file);

	return primeiroMeio;
}


/**
* \brief Ler dados de um ficheiro binario e guardar numa lista ligada
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
MeioMobilidade* LerMeiosMobilidade(char* filePath) {
	FILE* file;
	MeioMobilidade* primeiroMeio = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	MeioMobilidade meio;
	size_t bytesLidos = fread(&meio, sizeof(MeioMobilidade), 1, file);

	while (bytesLidos > 0) {
		MeioMobilidade* novoMeio = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));

		if (novoMeio == NULL)
			return NULL;

		novoMeio->id = meio.id;
		novoMeio->tipo = meio.tipo;
		novoMeio->cargaBateria = meio.cargaBateria;
		novoMeio->custoAluguer = meio.custoAluguer;
		strcpy_s(novoMeio->localizacao, LOCALIZACAO_LENGHT, meio.localizacao);
		novoMeio->ativo = meio.ativo;
		novoMeio->proximo = NULL;

		if (primeiroMeio == NULL) {
			primeiroMeio = novoMeio;
		}
		else {
			MeioMobilidade* meioAtual = primeiroMeio;

			while (meioAtual->proximo != NULL) {
				meioAtual = meioAtual->proximo;
			}

			meioAtual->proximo = novoMeio;
		}
		
		bytesLidos = fread(&meio, sizeof(MeioMobilidade), 1, file);
	}
	
	fclose(file);

	return primeiroMeio;
}


/**
* \brief Carregar dados inicial de um ficheiro de texto e guardar numa lista ligada
*
* \param clientes Lista ligada com os clientes
* \return
* \author A. Cerqueira
*
*/
bool GuardarMeiosMobilidade(char* filePath, MeioMobilidade* primeiroMeio) {
	FILE* file;
	file = fopen(filePath, "wb");

	if (file == NULL)
		return false;
	
	MeioMobilidade* meioAtual = primeiroMeio;

	while (meioAtual != NULL) {
		fwrite(meioAtual, sizeof(MeioMobilidade), 1, file);
		meioAtual = meioAtual->proximo;
	}

	fclose(file);

	return true;
}


/**
* \brief Adicionar um MeioMobilidade à lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool AdicionarMeioMobilidade(MeioMobilidade* primeiroMeio, MeioMobilidade* novoMeio) {

	if (novoMeio == NULL)
		return false;

	if (primeiroMeio == NULL) {
		primeiroMeio = novoMeio;
		return true;
	}

	MeioMobilidade* meioAtual = primeiroMeio;

	while (meioAtual->proximo != NULL) {
		meioAtual = meioAtual->proximo;
	}

	novoMeio->id = meioAtual->id + 1;
	novoMeio->ativo = true;
	novoMeio->proximo = NULL;
	meioAtual->proximo = novoMeio;

	return true;
}


/**
* \brief Remover um MeioMobilidade da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool RemoverMeioMobilidade(MeioMobilidade* primeiroMeio, int id) {

	MeioMobilidade* meio = primeiroMeio;

	while (meio->proximo != NULL) {

		if (meio->id == id) {
			meio->ativo = false;
			return;
		}

		meio = meio->proximo;
	}
	
	return true;
}


/**
* \brief Alterar um MeioMobilidade da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool EditarMeioMobilidade(MeioMobilidade* primeiroMeio, MeioMobilidade* meioSelecionado) {

	MeioMobilidade* meio = primeiroMeio;

	while (meio->proximo != NULL) {

		if (meio->id == meioSelecionado->id) {
			meio->tipo = meioSelecionado->tipo;
			meio->cargaBateria = meioSelecionado->cargaBateria;
			meio->custoAluguer = meioSelecionado->custoAluguer;
			strcpy_s(meio->localizacao, LOCALIZACAO_LENGHT, meioSelecionado->localizacao);
			return;
		}

		meio = meio->proximo;
	}

	return true;
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