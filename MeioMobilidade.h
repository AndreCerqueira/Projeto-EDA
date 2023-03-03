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
	typedef struct {
		TipoMeioMobilidade tipo;
		char uid[UID_LENGHT];
		float cargaBateria;
		float custoAluguer;
		char localizacao[LOCALIZACAO_LENGHT];
		MeioMobilidade* proximo;
	} MeioMobilidade;


	// Funções
	
	
#endif