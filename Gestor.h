#pragma once

/*****************************************************************//**
 * \file   Gestor.h
 * \brief  Funções de Gestor
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/


// Constants
#ifndef NOME_SIZE
	#define NOME_SIZE 50
#endif

#ifndef EMAIL_SIZE
	#define EMAIL_SIZE 50
#endif

#ifndef PASSWORD_SIZE
	#define PASSWORD_SIZE 20
#endif


// Structs
#ifndef GESTOR

	typedef struct {
		char nome[NOME_SIZE];
		char email[EMAIL_SIZE];
		char password[PASSWORD_SIZE];
		Gestor* proximo;
	} Gestor;

	#define GESTOR 1
#endif

	
// Funções

