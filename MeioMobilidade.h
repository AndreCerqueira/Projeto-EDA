/*****************************************************************//**
 * \file   MeioMobilidade.h
 * \brief  Funções de Meios de Mobilidade
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/
#pragma once


#ifndef MEIO_MOBILIDADE_H_
#define MEIO_MOBILIDADE_H_

	// Includes
	#include "Utils.h"


	// Constants
	#define LOCALIZACAO_LENGHT 20

	#define HARDDATA_FILE_NAME "MeiosMobilidade.txt"
	#define SAVE_FILE_NAME "MeiosMobilidade.dat"


	// Enums
	typedef enum {
		Bicibleta,
		Trotinente,
		Scooter,
		Segway,
		SkateEletrico,
		Outro
	} TipoMeioMobilidade;


	// Structs
	typedef struct MeioMobilidade MeioMobilidade;
	typedef struct MeioMobilidade {
		char uid[UID_LENGHT];
		TipoMeioMobilidade tipo;
		float cargaBateria;
		float custoAluguer;
		char localizacao[LOCALIZACAO_LENGHT];
		bool ativo;
		MeioMobilidade* proximo;
	};


	// Funções
	
	
#endif