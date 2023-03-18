/*****************************************************************//**
 * \file   Cliente.h
 * \brief  Declara��es das fun��es relacionadas aos clientes
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
	* \brief Liberta a mem�ria da lista ligada de clientes
	*
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \return true se a opera��o foi realizada com sucesso, false caso contr�rio
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
	* \brief L� os dados de um ficheiro .txt e retorna uma lista ligada de clientes.
	*
	* \param filePath O caminho do ficheiro .txt com os dados dos clientes
	* \return O novo apontador para o primeiro elemento da lista ligada de clientes
	* \author A. Cerqueira
	*/
	ClienteLista* LerClientesIniciais(char* filePath);

	
	/**
	* \brief L� os dados de um ficheiro .dat e retorna uma lista ligada de clientes.
	*
	* \param filePath O caminho do ficheiro .dat com os dados dos clientes
	* \return O novo apontador para o primeiro elemento da lista ligada de clientes
	* \author A. Cerqueira
	*/
	ClienteLista* LerClientes(char* filePath);
	

	/**
	* \brief Guarda a lista ligada de clientes em um arquivo .dat.
	*
	* \param filePath O caminho para o arquivo .dat onde os clientes ser�o guardados.
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \return true se a opera��o foi realizada com sucesso, false caso contr�rio
	* \author A. Cerqueira
	*/
	bool GuardarClientes(char* filePath, ClienteLista* primeiroCliente);


	/**
	* \brief Adiciona um novo cliente ao inicio da lista ligada.
	*
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \param novoCliente O cliente que ser� adicionado � lista.
	* \return O novo apontador para o primeiro elemento da lista ligada de clientes
	* \author A. Cerqueira
	*/
	ClienteLista* AdicionarCliente(ClienteLista* primeiroCliente, Cliente novoCliente);

	
	/**
	* \brief Remover um cliente da lista ligada
	* 
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \param id O id do cliente que ser� removido
	* \return true se a opera��o foi realizada com sucesso, false caso contr�rio
	* \author A. Cerqueira
	*/
	bool RemoverCliente(ClienteLista* primeiroCliente, int id);


	/**
	* \brief Alterar um cliente da lista ligada
	*
	* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
	* \param clienteSelecionado O cliente que ser� alterado
	* \return true se a opera��o foi realizada com sucesso, false caso contr�rio
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
	* \param id O id do cliente que ser� procurado
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
	* \brief Devolve se o cliente tem saldo suficiente para realizar uma opera��o.
	*
	* \param cliente O cliente que ser� verificado
	* \param O valor da opera��o
	* \return true se o cliente tem saldo suficiente, false caso contr�rio
	* \author A. Cerqueira
	*/
	bool ClienteTemSaldoSuficiente(Cliente cliente, float valor);

#endif


