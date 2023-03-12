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
void ResetarClientes(Cliente* ultimoCliente) {
	Cliente* cliente = ultimoCliente;

	while (cliente != NULL) {
		Cliente* clienteAnterior = cliente;
		cliente = cliente->proximo;
		free(clienteAnterior);
	}

	ultimoCliente = NULL;
}


/**
* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
void CarregarClientesIniciais(Cliente* ultimoCliente) {
	ResetarClientes(ultimoCliente);
	ultimoCliente = LerClientesIniciais();
	GuardarClientes(ultimoCliente);
}


/**
* \brief Ler Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
*
* \return
* \author A. Cerqueira
*
*/
Cliente* LerClientesIniciais() {
	FILE* fp;
	Cliente* ultimoCliente = NULL;
	char linha[MAX_SIZE];

	if (fopen_s(&fp, HARDDATA_FILE_NAME, "r") != 0) {
		printf("Erro ao abrir ficheiro\n");
		return NULL;
	}

	while (fgets(linha, MAX_SIZE, fp)) {
		Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

		if (novoCliente == NULL) {
			printf("Erro ao alocar memoria\n");
			return NULL;
		}

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

		if (ultimoCliente == NULL) {
			ultimoCliente = novoCliente;
		}
		else {
			Cliente* clienteAtual = ultimoCliente;

			while (clienteAtual->proximo != NULL) {
				clienteAtual = clienteAtual->proximo;
			}

			clienteAtual->proximo = novoCliente;
		}
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
	FILE* arquivo;
	Cliente* ultimoCliente = NULL;

	arquivo = fopen(SAVE_FILE_NAME, "rb");

	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo\n");
		return NULL;
	}

	Cliente cliente;
	size_t bytesLidos = fread(&cliente, sizeof(Cliente), 1, arquivo);

	while (bytesLidos > 0) {
		Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

		if (novoCliente == NULL) {
			printf("Erro ao alocar memoria\n");
			return NULL;
		}
	
		novoCliente->id = cliente.id;
		strcpy(novoCliente->nome, cliente.nome);
		strcpy(novoCliente->nif, cliente.nif);
		strcpy(novoCliente->morada, cliente.morada);
		novoCliente->saldo = cliente.saldo;
		novoCliente->ativo = cliente.ativo;
		novoCliente->proximo = NULL;

		if (ultimoCliente == NULL) {
			ultimoCliente = novoCliente;
		}
		else {
			Cliente* clienteAtual = ultimoCliente;

			while (clienteAtual->proximo != NULL) {
				clienteAtual = clienteAtual->proximo;
			}

			clienteAtual->proximo = novoCliente;
		}
		
		bytesLidos = fread(&cliente, sizeof(Cliente), 1, arquivo);
	}

	fclose(arquivo);
	return ultimoCliente;
}


/**
* \brief Guardar dados de lista ligada em um ficheiro binario
*
* \param clientes Lista ligada com os clientes
* \return
* \author A. Cerqueira
*
*/
void GuardarClientes(Cliente* ultimoCliente) {
	FILE* arquivo;
	arquivo = fopen(SAVE_FILE_NAME, "wb");

	if (arquivo == NULL) {
		printf("Erro ao criar o arquivo\n");
		return;
	}

	Cliente* clienteAtual = ultimoCliente;

	while (clienteAtual != NULL) {
		fwrite(clienteAtual, sizeof(Cliente), 1, arquivo);
		clienteAtual = clienteAtual->proximo;
	}

	fclose(arquivo);
}


/**
* \brief Adicionar um cliente à lista ligada
*
* \return
* \author A. Cerqueira
*
*/
void AdicionarCliente(Cliente* ultimoCliente, char* nome, char* nif, char* morada, float saldo) {

	Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));
	
	if (novoCliente == NULL) {
		printf("Erro ao alocar memoria\n");
		return;
	}

	novoCliente->id = GetNovoClienteId(ultimoCliente);
	strcpy_s(novoCliente->nome, NOME_CLIENTE_LENGHT, nome);
	strcpy_s(novoCliente->nif, NIF_LENGHT, nif);
	strcpy_s(novoCliente->morada, MORADA_LENGHT, morada);
	novoCliente->saldo = saldo;
	novoCliente->ativo = true;
	novoCliente->proximo = NULL;

	if (ultimoCliente == NULL) {
		ultimoCliente = novoCliente;
	}
	else {
		Cliente* clienteAtual = ultimoCliente;

		while (clienteAtual->proximo != NULL) {
			clienteAtual = clienteAtual->proximo;
		}

		clienteAtual->proximo = novoCliente;
	}
}


/**
* \brief Verifica o id de todos os clientes e retorna o proximo
*
* \return
* \author A. Cerqueira
*
*/
int GetNovoClienteId(Cliente* ultimoCliente) {
	Cliente* clienteAtual = ultimoCliente;
	int id = 0;

	while (clienteAtual != NULL) {
		if (clienteAtual->id > id) {
			id = clienteAtual->id;
		}

		clienteAtual = clienteAtual->proximo;
	}

	return id + 1;
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
