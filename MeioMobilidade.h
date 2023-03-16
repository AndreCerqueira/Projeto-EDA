/*****************************************************************//**
 * \file   MeioMobilidade.h
 * \brief  Funções de Meios de Mobilidade
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

#ifndef MEIO_MOBILIDADE_H_
#define MEIO_MOBILIDADE_H_

	// Includes
	#include "Utils.h"

	// Constants
	#define LOCALIZACAO_LENGHT 20

	#define MEIO_INITDATA_FILE_NAME "C:/IPCA/Projeto-EDA/data/simulacao/MeiosMobilidade.txt"
	#define MEIO_SAVE_FILE_NAME "C:/IPCA/Projeto-EDA/data/save/MeiosMobilidade.dat"

	// Enums
	typedef enum {
		Bicibleta,
		Trotinente,
		Scooter,
		SkateEletrico,
		Outro
	} TipoMeioMobilidade;

	// Structs
	typedef struct MeioMobilidade MeioMobilidade;
	typedef struct MeioMobilidade {
		int id;
		TipoMeioMobilidade tipo;
		float cargaBateria;
		float custoAluguer;
		char localizacao[LOCALIZACAO_LENGHT];
		bool ativo;
		MeioMobilidade* proximo;
	};

	typedef struct MeioMobilidadeLista MeioMobilidadeLista;
	typedef struct MeioMobilidadeLista {
		MeioMobilidade m;
		MeioMobilidadeLista* proximo;
	};

	/**
	* \brief Resetar lista ligada de Meios de Mobilidade, reescreve o ficheiro .dat com a lista vazia
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool ResetarMeiosMobilidade(MeioMobilidadeLista* primeiroMeio);


	/**
	* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool CarregarMeiosMobilidadeIniciais(MeioMobilidadeLista** primeiroMeio, char* filePathInicial, char* saveFilePath);

	
	/**
	* \brief Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	MeioMobilidadeLista* LerMeiosMobilidadeIniciais(char* filePath);


	/**
	* \brief Ler dados de um ficheiro de .dat e retorna para guardar numa lista ligada
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	MeioMobilidadeLista* LerMeiosMobilidade(char* filePath);


	/**
	* \brief Guardar dados de uma lista ligada num ficheiro .dat
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool GuardarMeiosMobilidade(char* filePath, MeioMobilidadeLista* primeiroMeio);


	/**
	* \brief Adicionar um MeioMobilidade à lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool AdicionarMeioMobilidade(MeioMobilidadeLista** primeiroMeio, MeioMobilidade* novoMeio);


	/**
	* \brief Remover um MeioMobilidade da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool RemoverMeioMobilidade(MeioMobilidadeLista* primeiroMeio, int id);


	/**
	* \brief Alterar um MeioMobilidade da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool EditarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, MeioMobilidade* meioSelecionado);
	

	/**
	* \brief Converter um TipoMeioMobilidade para string
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	char* TipoMeioMobilidadeToString(TipoMeioMobilidade tipoMeioMobilidade);
	

	/**
	 * \brief Ordenar meios de mobilidade por id
	 *
	 * \param primeiroMeio
	 * \return
	 */
	bool OrdenarMeiosMobilidadePorId(MeioMobilidadeLista** primeiroMeio);


	/**
	 * \brief Ordenar meios de mobilidade por ordem decrescente de autonomia
	 *
	 * \param primeiroMeio
	 * \return
	 */
	bool OrdenarMeiosMobilidadePorAutonomia(MeioMobilidadeLista** primeiroMeio);

	
	/**
	 * \brief Procurar meios de mobilidade em localização
	 *
	 * \param primeiroMeio
	 * \return
	 */
	MeioMobilidadeLista* ProcurarMeiosMobilidadePorLocalizacao(MeioMobilidadeLista* primeiroMeio, char* localizacao);
	
#endif