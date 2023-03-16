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

	// Includes
	#include "Utils.h"

	// Constants
	#define NOME_CLIENTE_LENGHT 50
	#define NIF_LENGHT 20
	#define MORADA_LENGHT 50

	#define CLIENTE_INITDATA_FILE_NAME "C:/IPCA/Projeto-EDA/data/simulacao/Clientes.txt"
	#define CLIENTE_SAVE_FILE_NAME "C:/IPCA/Projeto-EDA/data/save/Clientes.dat"

	// Structs
	typedef struct Cliente Cliente;
	typedef struct Cliente {
		int id;
		char nome[NOME_CLIENTE_LENGHT];
		char nif[NIF_LENGHT];
		char morada[MORADA_LENGHT];
		float saldo;
		bool ativo;
		Cliente* proximo;
	};

	
	/**
	* \brief Resetar lista ligada de Clientes, reescreve o ficheiro .dat com a lista vazia
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool ResetarClientes(Cliente* primeiroCliente);


	/**
	* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	bool CarregarClientesIniciais(Cliente** primeiroCliente, char* filePathInicial, char* saveFilePath);


	/**
	* \brief Ler Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	Cliente* LerClientesIniciais(char* filePath);

	
	/**
	* \brief Ler dados de um ficheiro de .dat e guardar numa lista ligada
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	Cliente* LerClientes(char* filePath);
	

	/**
	* \brief Carregar dados inicial de um ficheiro de texto e guardar numa lista ligada
	*
	* \param clientes Lista ligada com os clientes
	* \return
	* \author A. Cerqueira
	*
	*/
	bool GuardarClientes(char* filePath, Cliente* primeiroCliente);


	/**
	* \brief Adicionar um cliente à lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool AdicionarCliente(Cliente* primeiroCliente, Cliente* novoCliente);

	
	/**
	* \brief Remover um cliente da lista ligada
	* 
	* \return
	* \author A. Cerqueira
	* 
	*/
	bool RemoverCliente(Cliente* primeiroCliente, int id);


	/**
	* \brief Alterar um cliente da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool EditarCliente(Cliente* primeiroCliente, Cliente* clienteSelecionado);
	
	
#endif


