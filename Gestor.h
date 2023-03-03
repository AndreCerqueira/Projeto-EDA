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
	#define NOME_SIZE 50
	#define EMAIL_SIZE 50
	#define PASSWORD_SIZE 20


	// Structs
	typedef struct Gestor Gestor;
	struct Gestor {
		char nome[NOME_SIZE];
		char email[EMAIL_SIZE];
		char password[PASSWORD_SIZE];
		Gestor* proximo;
	};

	/*typedef struct {
		char nome[NOME_SIZE];
		char email[EMAIL_SIZE];
		char password[PASSWORD_SIZE];
		Gestor* proximo;
	} Gestor;*/

	
	// Funções

#endif

	
