/*****************************************************************//**
 * \file   Cliente.h
 * \brief  Fun��es de Cliente
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

	#define HARDDATA_FILE_NAME "D:/IPCA/Projeto-EDA/data/simulacao/Clientes.txt"
	#define SAVE_FILE_NAME "D:/IPCA/Projeto-EDA/data/simulacao/Clientes.dat"

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
	* \brief Ler dados de um ficheiro de texto e guardar numa lista ligada
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	Cliente* LerClientesIniciais();


	/**
	* \brief Ler dados de um ficheiro de .dat e guardar numa lista ligada
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	Cliente* LerClientes();
	

	/**
	* \brief Carregar dados inicial de um ficheiro de texto e guardar numa lista ligada
	*
	* \param clientes Lista ligada com os clientes
	* \return
	* \author A. Cerqueira
	*
	*/
	void GuardarClientesIniciais(Cliente* ultimoCliente);


	/**
	* \brief Adicionar um cliente � lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void AdicionarCliente(Cliente** ultimoCliente, char* nome, char* nif, char* morada, float saldo);

	
	/**
	* \brief Remover um cliente da lista ligada
	* 
	* \return
	* \author A. Cerqueira
	* 
	*/
	void RemoverCliente(Cliente* ultimoCliente, int id);


	/**
	* \brief Alterar um cliente da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void EditarCliente(Cliente* ultimoCliente, int id, char* nome, char* nif, char* morada, float saldo);


	/**
	* \brief Listar todos os clientes
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void ListarClientes(Cliente* ultimoCliente);
	
	
#endif


