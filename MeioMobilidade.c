/*****************************************************************//**
 * \file   MeioMobilidade.c
 * \brief  Funções de Meios de mobilidade
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

#include "MeioMobilidade.h"


/**
* \brief Ler dados de um ficheiro de texto e guardar numa lista ligada
*
* \return Lista ligada com os dados lidos
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
* \brief Carregar dados inicial de um ficheiro de texto e guardar numa lista ligada
*
* \param clientes Lista ligada com os clientes
* \return
* \author A. Cerqueira
*
*/
void GuardarMeiosMobilidade(MeioMobilidade* ultimoMeioMobilidade) {
	
}


/**
* \brief Adicionar um MeioMobilidade à lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void AdicionarMeioMobilidade(MeioMobilidade** ultimoMeioMobilidade, TipoMeioMobilidade tipo, float cargaBateria, float custoAluguer, char* localizacao) {

}


/**
* \brief Remover um MeioMobilidade da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void RemoverMeioMobilidade(MeioMobilidade* ultimoMeioMobilidade, int id) {
}


/**
* \brief Alterar um MeioMobilidade da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void EditarMeioMobilidade(MeioMobilidade* ultimoMeioMobilidade, int id, TipoMeioMobilidade tipo, float cargaBateria, float custoAluguer, char* localizacao){
}


/**
* \brief Listar todos os clientes
*
* \return
* \author A. Cerqueira
*
*/
void ListarMeiosMobilidade(MeioMobilidade* ultimoMeioMobilidade) {

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
		return "Tipo de meio de mobilidade desconhecido";
	}
}