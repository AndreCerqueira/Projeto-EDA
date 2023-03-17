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

	#define CLIENTE_INITDATA_FILE_NAME "D:/IPCA/Projeto-EDA/data/simulacao/Clientes.txt"
	#define CLIENTE_SAVE_FILE_NAME "D:/IPCA/Projeto-EDA/data/save/Clientes.dat"

	// Structs
	typedef struct Cliente Cliente;
	typedef struct Cliente {
		int id;
		char nome[NOME_CLIENTE_LENGHT];
		char nif[NIF_LENGHT];
		char morada[MORADA_LENGHT];
		float saldo;
		bool ativo;
	};

	typedef struct ClienteLista ClienteLista;
	typedef struct ClienteLista {
		Cliente c;
		ClienteLista* proximo;
	};

	
	/**
	* \brief Resetar lista ligada de Clientes, reescreve o ficheiro .dat com a lista vazia
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool LibertarClientes(ClienteLista* primeiroCliente);


	/**
	* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	bool CarregarClientesIniciais(ClienteLista** primeiroCliente, char* filePathInicial, char* saveFilePath);


	/**
	* \brief Ler Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	ClienteLista* LerClientesIniciais(char* filePath);

	
	/**
	* \brief Ler dados de um ficheiro de .dat e guardar numa lista ligada
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	ClienteLista* LerClientes(char* filePath);
	

	/**
	* \brief Carregar dados inicial de um ficheiro de texto e guardar numa lista ligada
	*
	* \param clientes Lista ligada com os clientes
	* \return
	* \author A. Cerqueira
	*
	*/
	bool GuardarClientes(char* filePath, ClienteLista* primeiroCliente);


	/**
	* \brief Adicionar um cliente à lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool AdicionarCliente(ClienteLista** primeiroCliente, Cliente* novoCliente);

	
	/**
	* \brief Remover um cliente da lista ligada
	* 
	* \return
	* \author A. Cerqueira
	* 
	*/
	bool RemoverCliente(ClienteLista* primeiroCliente, int id);


	/**
	* \brief Alterar um cliente da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool EditarCliente(ClienteLista* primeiroCliente, Cliente* clienteSelecionado);

	
	/**
	 * \brief Ordenar clientes por id
	 *
	 * \param primeiroCliente
	 * \return
	 */
	bool OrdenarClientesPorId(ClienteLista** primeiroCliente);


	/**
	* \brief Devolve o cliente com o id selecionado
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	Cliente* ProcurarClientePorId(ClienteLista* primeiroCliente, int id);
	

	/**
	* \brief Devolve o proximo id disponivel para um Cliente
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	int ProcurarProximoIdCliente(ClienteLista* primeiroCliente);

		
	/**
	* \brief Devolve se o cliente tem saldo suficiente para realizar uma operação
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool ClienteTemSaldoSuficiente(Cliente cliente, float valor);

#endif


