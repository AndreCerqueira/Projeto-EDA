#pragma once

/*****************************************************************//**
 * \file   MeioMobilidade.h
 * \brief  Funções de Meios de Mobilidade
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/


// Constants
#ifndef TIPO_SIZE
	#define TIPO_SIZE 20
#endif

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


// Structs
#ifndef MEIO_MOBILIDADE

	typedef struct {
		char tipo[TIPO_SIZE];
		char id[ID_SIZE];
		float cargaBateria;
		float custoAluguer;
		char localizacao[LOCALIZACAO_SIZE];
		MeioMobilidade* proximo;
	} MeioMobilidade;
	
	#define MEIO_MOBILIDADE 1
#endif


// Funções

