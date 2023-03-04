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

	#define HARDDATA_FILE_NAME "D:/IPCA/Projeto-EDA/data/simulacao/MeiosMobilidade.txt"
	#define SAVE_FILE_NAME "D:/IPCA/Projeto-EDA/data/simulacao/MeiosMobilidade.dat"

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
	* \brief Ler dados de um ficheiro de texto e guardar numa lista ligada
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	MeioMobilidade* LerMeiosMobilidadeIniciais();


	/**
	* \brief Ler dados de um ficheiro de .dat e guardar numa lista ligada
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
	void GuardarMeiosMobilidade(MeioMobilidade* ultimoMeioMobilidade);


	/**
	* \brief Adicionar um MeioMobilidade à lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void AdicionarMeioMobilidade(MeioMobilidade** ultimoMeioMobilidade, TipoMeioMobilidade tipo, float cargaBateria, float custoAluguer, char* localizacao);


	/**
	* \brief Remover um MeioMobilidade da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void RemoverMeioMobilidade(MeioMobilidade* ultimoMeioMobilidade, int id);


	/**
	* \brief Alterar um MeioMobilidade da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void EditarMeioMobilidade(MeioMobilidade* ultimoMeioMobilidade, int id, TipoMeioMobilidade tipo, float cargaBateria, float custoAluguer, char* localizacao);


	/**
	* \brief Listar todos os MeiosMobilidade
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void ListarMeiosMobilidade(MeioMobilidade* ultimoMeioMobilidade);
	

	/**
	* \brief Converter um TipoMeioMobilidade para string
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	char* TipoMeioMobilidadeToString(TipoMeioMobilidade tipoMeioMobilidade);
	
	
#endif