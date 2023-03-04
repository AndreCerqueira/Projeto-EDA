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
* \brief Ler dados de um ficheiro de texto e guardar numa lista ligada
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
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
* \brief Carregar dados inicial de um ficheiro de texto e guardar numa lista ligada
*
* \param clientes Lista ligada com os clientes
* \return
* \author A. Cerqueira
*
*/
void GuardarClientes(Cliente* ultimoCliente) {

	// open the file for writing
	FILE* fp = fopen(HARDDATA_FILE_NAME, "w");
	if (fp == NULL)
	{
		printf("Error opening the file %s", HARDDATA_FILE_NAME);
		return -1;
	}
	// write to the text file
	for (int i = 0; i < 10; i++)
		fprintf(fp, "This is the line #%d\n", i + 1);

	// close the file
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

	cliente->id = (*ultimoCliente)->id + 1;
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


/**
* \brief Listar todos os clientes
*
* \return
* \author A. Cerqueira
*
*/
void ListarClientes(Cliente* cliente) {

	// Variaveis
	int i;

	// Mostrar os dados da clinica
	system("cls");
	puts("+---------------------------------------------------------------------------------+");
	puts("|                                   Lista de Clientes                             |");
	puts("+---------------------------------------------------------------------------------+");
	puts("|  ID  |          Nome          |      Nif     |       Morada       |    Saldo    |");
	puts("+---------------------------------------------------------------------------------+");

	while (cliente != NULL) {
		if (cliente->ativo == 1)
		{
			printf("| %-4d | %-22s | %-12s | %-18s | %-11.2f |\n", cliente->id, cliente->nome, cliente->nif, cliente->morada, cliente->saldo);
		}

		cliente = cliente->proximo;
	}

	puts("+---------------------------------------------------------------------------------+");

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
}