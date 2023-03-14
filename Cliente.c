/*****************************************************************//**
 * \file   Cliente.c
 * \brief  Funções de Cliente
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/


 // Includes
#include "Cliente.h"


/**
* \brief Resetar lista ligada de Clientes, reescreve o ficheiro .dat com a lista vazia
*
* \return
* \author A. Cerqueira
*
*/
bool ResetarClientes(Cliente* primeiroCliente) {
	Cliente* cliente = primeiroCliente;

	while (cliente != NULL) {
		Cliente* clienteAnterior = cliente;
		cliente = cliente->proximo;
		free(clienteAnterior);
	}

	primeiroCliente = NULL;
	
	return true;
}


/**
* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
bool CarregarClientesIniciais(Cliente** primeiroCliente) {
	ResetarClientes(*primeiroCliente);
	*primeiroCliente = LerClientesIniciais();
	GuardarClientes(*primeiroCliente);

	return true;
}


/**
* \brief Ler Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
*
* \return
* \author A. Cerqueira
*
*/
Cliente* LerClientesIniciais() {
	FILE* file;
	Cliente* primeiroCliente = NULL;
	char linha[MAX_SIZE];

	if (fopen_s(&file, HARDDATA_FILE_NAME, "r") != 0)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

		if (novoCliente == NULL)
			return NULL;

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		novoCliente->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoCliente->nome, NOME_CLIENTE_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoCliente->nif, NIF_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoCliente->morada, MORADA_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		novoCliente->saldo = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		novoCliente->ativo = (bool)atoi(campo);

		novoCliente->proximo = NULL;

		if (primeiroCliente == NULL) {
			primeiroCliente = novoCliente;
		}
		else {
			Cliente* clienteAtual = primeiroCliente;

			while (clienteAtual->proximo != NULL) {
				clienteAtual = clienteAtual->proximo;
			}

			clienteAtual->proximo = novoCliente;
		}
	}

	fclose(file);

	return primeiroCliente;
}


/**
* \brief Ler dados de um ficheiro binario e guardar numa lista ligada
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
Cliente* LerClientes() {
	FILE* file;
	Cliente* primeiroCliente = NULL;

	file = fopen(SAVE_FILE_NAME, "rb");

	if (file == NULL)
		return NULL;

	Cliente cliente;
	size_t bytesLidos = fread(&cliente, sizeof(Cliente), 1, file);

	while (bytesLidos > 0) {
		Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

		if (novoCliente == NULL)
			return NULL;
	
		novoCliente->id = cliente.id;
		strcpy(novoCliente->nome, cliente.nome);
		strcpy(novoCliente->nif, cliente.nif);
		strcpy(novoCliente->morada, cliente.morada);
		novoCliente->saldo = cliente.saldo;
		novoCliente->ativo = cliente.ativo;
		novoCliente->proximo = NULL;

		if (primeiroCliente == NULL) {
			primeiroCliente = novoCliente;
		}
		else {
			Cliente* clienteAtual = primeiroCliente;

			while (clienteAtual->proximo != NULL) {
				clienteAtual = clienteAtual->proximo;
			}

			clienteAtual->proximo = novoCliente;
		}
		
		bytesLidos = fread(&cliente, sizeof(Cliente), 1, file);
	}

	fclose(file);
	return primeiroCliente;
}


/**
* \brief Guardar dados de lista ligada em um ficheiro binario
*
* \param clientes Lista ligada com os clientes
* \return
* \author A. Cerqueira
*
*/
bool GuardarClientes(Cliente* primeiroCliente) {
	FILE* file;
	file = fopen(SAVE_FILE_NAME, "wb");

	if (file == NULL)
		return false;

	Cliente* clienteAtual = primeiroCliente;

	while (clienteAtual != NULL) {
		fwrite(clienteAtual, sizeof(Cliente), 1, file);
		clienteAtual = clienteAtual->proximo;
	}

	fclose(file);
	
	return true;
}


/**
* \brief Adicionar um cliente à lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool AdicionarCliente(Cliente* primeiroCliente, Cliente* novoCliente) {
	
	if (novoCliente == NULL)
		return false;

	if (primeiroCliente == NULL) {
		primeiroCliente = novoCliente;
		return true;
	}
	
	Cliente* clienteAtual = primeiroCliente;
	
	while (clienteAtual->proximo != NULL) {
		clienteAtual = clienteAtual->proximo;
	}
	
	novoCliente->id = clienteAtual->id + 1;
	novoCliente->ativo = true;
	novoCliente->proximo = NULL;
	clienteAtual->proximo = novoCliente;
	
	return true;
}



/**
* \brief Remover um cliente da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool RemoverCliente(Cliente* primeiroCliente, int id) {

	Cliente* cliente = primeiroCliente;

	while (cliente != NULL) {
		
		if (cliente->id == id) {
			cliente->ativo = false;
			return;
		}
		
		cliente = cliente->proximo;
	}

	return true;
}


/**
* \brief Alterar um cliente da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool EditarCliente(Cliente* primeiroCliente, Cliente* clienteSelecionado) {

	Cliente* cliente = primeiroCliente;

	while (cliente != NULL) {

		if (cliente->id == clienteSelecionado->id) {
			strcpy_s(cliente->nome, NOME_CLIENTE_LENGHT, clienteSelecionado->nome);
			strcpy_s(cliente->nif, NIF_LENGHT, clienteSelecionado->nif);
			strcpy_s(cliente->morada, MORADA_LENGHT, clienteSelecionado->morada);
			cliente->saldo = clienteSelecionado->saldo;
			return;
		}

		cliente = cliente->proximo;
	}
	
	return true;
}
