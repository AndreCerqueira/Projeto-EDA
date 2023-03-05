/*****************************************************************//**
 * \file   Cliente.c
 * \brief  Funções de Cliente
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/


 // Includes
#include "Cliente.h"


void ResetarClientes(Cliente* ultimoCliente) {
	Cliente* cliente = ultimoCliente;

	while (cliente != NULL) {
		Cliente* clienteAnterior = cliente;
		cliente = cliente->proximo;
		free(clienteAnterior);
	}
}


void CarregarClientesIniciais(Cliente* ultimoCliente) {
	ResetarClientes(ultimoCliente);
	ultimoCliente = LerClientesIniciais();
	GuardarClientes(ultimoCliente);
}


Cliente* LerClientesIniciais() {
	FILE* fp;

	if (fopen_s(&fp, HARDDATA_FILE_NAME, "r") != 0) {
		printf("Erro ao abrir ficheiro\n");
		return NULL;
	}

	Cliente* ultimoCliente = NULL;
	char linha[MAX_SIZE];

	while (fgets(linha, MAX_SIZE, fp)) {
		Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));

		if (cliente == NULL) {
			printf("Erro ao alocar memoria\n");
			return NULL;
		}

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		cliente->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(cliente->nome, NOME_CLIENTE_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(cliente->nif, NIF_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(cliente->morada, MORADA_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		cliente->saldo = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		cliente->ativo = (bool)atoi(campo);

		cliente->proximo = ultimoCliente;
		ultimoCliente = cliente;
	}

	fclose(fp);

	return ultimoCliente;
}


/**
* \brief Ler dados de um ficheiro binario e guardar numa lista ligada
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
Cliente* LerClientes() {
    
    FILE* fp;
    
    if (fopen_s(&fp, SAVE_FILE_NAME, "rb") != 0) {
        printf("Erro ao abrir ficheiro\n");
        return NULL;
    }

	Cliente* ultimoCliente = NULL;
	char linha[MAX_SIZE];
        
	while (fgets(linha, MAX_SIZE, fp)) {
		Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));

		if (cliente == NULL) {
			printf("Erro ao alocar memoria\n");
			return NULL;
		}

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		cliente->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(cliente->nome, NOME_CLIENTE_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(cliente->nif, NIF_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(cliente->morada, MORADA_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		cliente->saldo = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		cliente->ativo = (bool)atoi(campo);

		cliente->proximo = ultimoCliente;
		ultimoCliente = cliente;
	}

	fclose(fp);

    return ultimoCliente;
}


/**
* \brief Carregar dados inicial de um ficheiro de texto e guardar numa lista ligada
*
* \param clientes Lista ligada com os clientes
* \return
* \author A. Cerqueira
*
*/
void GuardarClientes(Cliente* ultimoCliente) {
	FILE* fp;

	if (fopen_s(&fp, SAVE_FILE_NAME, "wb") != 0) {
		printf("Erro ao abrir ficheiro\n");
		return;
	}

	Cliente* cliente = ultimoCliente;

	while (cliente != NULL) {
		fprintf(fp, "%d;%s;%s;%s;%f;%d\n", cliente->id, cliente->nome, cliente->nif, cliente->morada, cliente->saldo, cliente->ativo);
		cliente = cliente->proximo;
	}

	fclose(fp);
}


/**
* \brief Adicionar um cliente à lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void AdicionarCliente(Cliente** ultimoCliente, char* nome, char* nif, char* morada, float saldo) {

	Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));
	
	if (cliente == NULL) {
		printf("Erro ao alocar memoria\n");
		return;
	}

	cliente->id = (*ultimoCliente == NULL) ? 1 : (*ultimoCliente)->id + 1;
	strcpy_s(cliente->nome, NOME_CLIENTE_LENGHT, nome);
	strcpy_s(cliente->nif, NIF_LENGHT, nif);
	strcpy_s(cliente->morada, MORADA_LENGHT, morada);
	cliente->saldo = saldo;
	cliente->ativo = true;

	cliente->proximo = *ultimoCliente;
	*ultimoCliente = cliente;
}


/**
* \brief Remover um cliente da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void RemoverCliente(Cliente* ultimoCliente, int id) {

	Cliente* cliente = ultimoCliente;

	while (cliente != NULL) {
		
		if (cliente->id == id) {
			cliente->ativo = false;
			return;
		}
		
		cliente = cliente->proximo;
	}
}


/**
* \brief Alterar um cliente da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void EditarCliente(Cliente* ultimoCliente, int id, char* nome, char* nif, char* morada, float saldo) {

	Cliente* cliente = ultimoCliente;

	while (cliente != NULL) {

		if (cliente->id == id) {
			strcpy_s(cliente->nome, NOME_CLIENTE_LENGHT, nome);
			strcpy_s(cliente->nif, NIF_LENGHT, nif);
			strcpy_s(cliente->morada, MORADA_LENGHT, morada);
			cliente->saldo = saldo;
			return;
		}

		cliente = cliente->proximo;
	}
	
}
