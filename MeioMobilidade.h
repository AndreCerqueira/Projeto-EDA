/*****************************************************************//**
 * \file   MeioMobilidade.h
 * \brief  Fun��es de Meios de Mobilidade
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

	#define HARDDATA_FILE_NAME "C:/IPCA/Projeto-EDA/data/simulacao/MeiosMobilidade.txt"
	#define SAVE_FILE_NAME "C:/IPCA/Projeto-EDA/data/save/MeiosMobilidade.dat"

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


	/**
	* \brief Resetar lista ligada de Meios de Mobilidade, reescreve o ficheiro .dat com a lista vazia
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool ResetarMeiosMobilidade(MeioMobilidade* primeiroMeio);


	/**
	* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool CarregarMeiosMobilidadeIniciais(MeioMobilidade** ultimoMeio);

	
	/**
	* \brief Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	MeioMobilidade* LerMeiosMobilidadeIniciais();


	/**
	* \brief Ler dados de um ficheiro de .dat e retorna para guardar numa lista ligada
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	MeioMobilidade* LerMeiosMobilidade();


	/**
	* \brief Guardar dados de uma lista ligada num ficheiro .dat
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool GuardarMeiosMobilidade(MeioMobilidade* primeiroMeio);


	/**
	* \brief Adicionar um MeioMobilidade � lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool AdicionarMeioMobilidade(MeioMobilidade* primeiroMeio, MeioMobilidade* novoMeio);


	/**
	* \brief Remover um MeioMobilidade da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool RemoverMeioMobilidade(MeioMobilidade* primeiroMeio, int id);


	/**
	* \brief Alterar um MeioMobilidade da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool EditarMeioMobilidade(MeioMobilidade* primeiroMeio, MeioMobilidade* meioSelecionado);
	

	/**
	* \brief Converter um TipoMeioMobilidade para string
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	char* TipoMeioMobilidadeToString(TipoMeioMobilidade tipoMeioMobilidade);
	
	
#endif