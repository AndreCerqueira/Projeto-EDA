#pragma once

/*****************************************************************//**
 * \file   Cliente.h
 * \brief  Funções de Cliente
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/


// Constants
#ifndef NOME_SIZE
	#define NOME_SIZE 50
#endif

#ifndef NIF_SIZE
	#define NIF_SIZE 20
#endif

#ifndef MORADA_SIZE
	#define MORADA_SIZE 50
#endif


// Structs
#ifndef CLIENTE
	typedef struct {
		char nome[NOME_SIZE];
		char nif[NIF_SIZE];
		char morada[MORADA_SIZE];
		float saldo;
		Cliente* proximo;
	} Cliente;

	#define CLIENTE 1
#endif

	
// Funções
