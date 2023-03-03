/*****************************************************************//**
 * \file   Gestor.h
 * \brief  Funções de Gestor
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/
#pragma once

#ifndef GESTOR_H_
#define GESTOR_H_


	// Constants
	#define NOME_LENGHT 50
	#define EMAIL_LENGHT 50
	#define PASSWORD_LENGHT 20


	// Structs
	typedef struct Gestor Gestor;
	struct Gestor {
		char uid[UID_LENGHT];
		char nome[NOME_LENGHT];
		char email[EMAIL_LENGHT];
		char password[PASSWORD_LENGHT];
		bool ativo;
		Gestor* proximo;
	};

	/*typedef struct {
		char nome[NOME_LENGHT];
		char email[EMAIL_LENGHT];
		char password[PASSWORD_LENGHT];
		Gestor* proximo;
	} Gestor;*/

	
	// Funções

#endif

	
