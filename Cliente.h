/*****************************************************************//**
 * \file   Cliente.h
 * \brief  Declarações das funções relacionadas aos clientes
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
	* \brief Liberta a memória da lista ligada de clientes
	*
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool LibertarClientes(ClienteLista* primeiroCliente);


	/**
	* \brief Carrega os dados iniciais dos clientes de um ficheiro .txt para uma lista ligada e guarda no ficheiro .dat.
	*
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos clientes
	* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
	* \return O novo apontador para o primeiro elemento da lista ligada de clientes carregada
	* \author A. Cerqueira
	*/
	ClienteLista* CarregarClientesIniciais(ClienteLista* primeiroCliente, char* filePathInicial, char* saveFilePath);


	/**
	* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de clientes.
	*
	* \param filePath O caminho do ficheiro .txt com os dados dos clientes
	* \return O novo apontador para o primeiro elemento da lista ligada de clientes
	* \author A. Cerqueira
	*/
	ClienteLista* LerClientesIniciais(char* filePath);

	
	/**
	* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de clientes.
	*
	* \param filePath O caminho do ficheiro .dat com os dados dos clientes
	* \return O novo apontador para o primeiro elemento da lista ligada de clientes
	* \author A. Cerqueira
	*/
	ClienteLista* LerClientes(char* filePath);
	

	/**
	* \brief Guarda a lista ligada de clientes em um arquivo .dat.
	*
	* \param filePath O caminho para o arquivo .dat onde os clientes serão guardados.
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool GuardarClientes(char* filePath, ClienteLista* primeiroCliente);


	/**
	* \brief Adiciona um novo cliente ao inicio da lista ligada.
	*
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \param novoCliente O cliente que será adicionado à lista.
	* \return O novo apontador para o primeiro elemento da lista ligada de clientes
	* \author A. Cerqueira
	*/
	ClienteLista* AdicionarCliente(ClienteLista* primeiroCliente, Cliente novoCliente);

	
	/**
	* \brief Remover um cliente da lista ligada
	* 
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \param id O id do cliente que será removido
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool RemoverCliente(ClienteLista* primeiroCliente, int id);


	/**
	* \brief Alterar um cliente da lista ligada
	*
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \param clienteSelecionado O cliente que será alterado
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool EditarCliente(ClienteLista* primeiroCliente, Cliente clienteSelecionado);

	
	/**
	 * \brief Ordena a lista ligada de clientes por ID em ordem decrescente.
	 *
	 * \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	 * \return O novo apontador para o primeiro elemento da lista ligada de clientes ordenada
	 * \author A. Cerqueira
	 */
	ClienteLista* OrdenarClientesPorId(ClienteLista* primeiroCliente);


	/**
	* \brief Procura um cliente na lista ligada a partir do seu ID.
	*
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \param id O id do cliente que será procurado
	* \return O apontador para o cliente com o id selecionado
	* \author A. Cerqueira
	*/
	Cliente* ProcurarClientePorId(ClienteLista* primeiroCliente, int id);
	

	/**
	* \brief Procura o ultimo id de um cliente na lista ligada.
	*
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \return O proximo id a ser utilizado
	* \author A. Cerqueira
	*/
	int ProcurarProximoIdCliente(ClienteLista* primeiroCliente);

		
	/**
	* \brief Devolve se o cliente tem saldo suficiente para realizar uma operação.
	*
	* \param cliente O cliente que será verificado
	* \param O valor da operação
	* \return true se o cliente tem saldo suficiente, false caso contrário
	* \author A. Cerqueira
	*/
	bool ClienteTemSaldoSuficiente(Cliente cliente, float valor);

#endif


