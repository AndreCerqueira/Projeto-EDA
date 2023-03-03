#pragma once

/*****************************************************************//**
 * \file   MeioMobilidade.h
 * \brief  Funções de Meios de Mobilidade
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/


// Constants
#ifndef ID_SIZE
	#define ID_SIZE 20
#endif

#ifndef LOCALIZACAO_SIZE
	#define LOCALIZACAO_SIZE 20
#endif

#ifndef HARDDATA_FILE_NAME
	#define HARDDATA_FILE_NAME "MeiosMobilidade.txt"
#endif

#ifndef SAVE_FILE_NAME
	#define SAVE_FILE_NAME "MeiosMobilidade.dat"
#endif


// Enums
#ifndef TIPO_MEIO_MOBILIDADE
	typedef enum {
		Bicibleta,
		Trotinente,
		Scooter,
		Segway,
		SkateEletrico,
		Outro
	} TipoMeioMobilidade;

	#define TIPO_MEIO_MOBILIDADE 1
#endif


// Structs
#ifndef MEIO_MOBILIDADE

	typedef struct {
		TipoMeioMobilidade tipo;
		char id[ID_SIZE];
		float cargaBateria;
		float custoAluguer;
		char localizacao[LOCALIZACAO_SIZE];
		MeioMobilidade* proximo;
	} MeioMobilidade;
	
	#define MEIO_MOBILIDADE 1
#endif


// Funções