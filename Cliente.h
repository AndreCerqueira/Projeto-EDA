/*****************************************************************//**
 * \file   Cliente.h
 * \brief  Funções de Cliente
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

#ifndef CLIENTE_H_
#define CLIENTE_H_

	#include "Utils.h"

	// Constants

	#define NOME_SIZE 50
	#define NIF_SIZE 20
	#define MORADA_SIZE 50

	#define HARDDATA_FILE_NAME "data/simulacao/Clientes.txt"
	#define SAVE_FILE_NAME "data\simulacao\Clientes.dat"


	// Structs
	typedef struct Cliente Cliente;
	typedef struct Cliente {
		int id;
		char nome[NOME_SIZE];
		char nif[NIF_SIZE];
		char morada[MORADA_SIZE];
		float saldo;
		bool ativo;
		Cliente* proximo;
	};

	
	
	// Funções



	// Funções de ficheiros

	// Ler dados de um ficheiro de texto e guardar numa lista ligada
	Cliente* LerDadosIniciais();

	// Carregar dados inicial de um ficheiro de texto e guardar numa lista ligada
	Cliente* GuardarDadosIniciais();

	// Ler dados de um ficheiro de .dat e guardar numa lista ligada
	Cliente* LerDados();

	// Guardar dados de uma lista ligada num ficheiro .dat
	void GuardarDados(Cliente* clientes);




#endif

