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
bool LibertarClientes(ClienteLista* primeiroCliente) {
	ClienteLista* clienteAtual = primeiroCliente;

	while (clienteAtual != NULL) {
		ClienteLista* clienteAnterior = clienteAtual;
		clienteAtual = clienteAtual->proximo;
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
ClienteLista* CarregarClientesIniciais(ClienteLista* primeiroCliente, char* filePathInicial, char* saveFilePath) {
	LibertarClientes(primeiroCliente);
	primeiroCliente = LerClientesIniciais(filePathInicial);
	GuardarClientes(saveFilePath, primeiroCliente);

	return primeiroCliente;
}


/**
* \brief Ler Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
*
* \return
* \author A. Cerqueira
*
*/
ClienteLista* LerClientesIniciais(char* filePath) {
	FILE* file;
	ClienteLista* primeiroCliente = NULL;
	char linha[MAX_SIZE];

	if (fopen_s(&file, filePath, "r") != 0)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		ClienteLista* novoCliente = (ClienteLista*)malloc(sizeof(ClienteLista));

		if (novoCliente == NULL)
			return NULL;

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		novoCliente->c.id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoCliente->c.nome, NOME_CLIENTE_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoCliente->c.nif, NIF_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novoCliente->c.morada, MORADA_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		novoCliente->c.saldo = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		novoCliente->c.ativo = (bool)atoi(campo);

		novoCliente->proximo = primeiroCliente;
		primeiroCliente = novoCliente;
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
ClienteLista* LerClientes(char* filePath) {
	FILE* file;
	ClienteLista* primeiroCliente = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	Cliente cliente;
	size_t bytesLidos = fread(&cliente, sizeof(Cliente), 1, file);

	while (bytesLidos > 0) {
		ClienteLista* novoCliente = (ClienteLista*)malloc(sizeof(ClienteLista));

		if (novoCliente == NULL)
			return NULL;

		novoCliente->c.id = cliente.id;
		strcpy(novoCliente->c.nome, cliente.nome);
		strcpy(novoCliente->c.nif, cliente.nif);
		strcpy(novoCliente->c.morada, cliente.morada);
		novoCliente->c.saldo = cliente.saldo;
		novoCliente->c.ativo = cliente.ativo;
		novoCliente->proximo = primeiroCliente;
		primeiroCliente = novoCliente;

		bytesLidos = fread(&cliente, sizeof(Cliente), 1, file);
	}

	fclose(file);

	primeiroCliente = OrdenarClientesPorId(primeiroCliente);

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
bool GuardarClientes(char* filePath, ClienteLista* primeiroCliente) {
	FILE* file;
	file = fopen(filePath, "wb");

	if (file == NULL)
		return false;

	ClienteLista* clienteAtual = primeiroCliente;

	while (clienteAtual != NULL) {
		fwrite(&clienteAtual->c, sizeof(Cliente), 1, file);
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
ClienteLista* AdicionarCliente(ClienteLista* primeiroCliente, Cliente novoCliente) {
	ClienteLista* novoNode = (ClienteLista*)malloc(sizeof(ClienteLista));
	
	if (novoNode == NULL)
		return primeiroCliente;

	novoCliente.ativo = true;
	novoCliente.id = ProcurarProximoIdCliente(primeiroCliente);
	novoNode->proximo = (primeiroCliente != NULL) ? primeiroCliente : NULL;
	
	novoNode->c = novoCliente;
	primeiroCliente = novoNode;
	
	return primeiroCliente;
}


/**
* \brief Remover um cliente da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool RemoverCliente(ClienteLista* primeiroCliente, int id) {

	ClienteLista* clienteAtual = primeiroCliente;

	while (clienteAtual != NULL) {

		if (clienteAtual->c.id == id) {
			clienteAtual->c.ativo = false;
			return true;
		}

		clienteAtual = clienteAtual->proximo;
	}

	return false;
}


/**
* \brief Alterar um cliente da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool EditarCliente(ClienteLista* primeiroCliente, Cliente clienteSelecionado) {

	ClienteLista* clienteAtual = primeiroCliente;

	while (clienteAtual != NULL) {

		if (clienteAtual->c.id == clienteSelecionado.id) {
			strcpy_s(clienteAtual->c.nome, NOME_CLIENTE_LENGHT, clienteSelecionado.nome);
			strcpy_s(clienteAtual->c.nif, NIF_LENGHT, clienteSelecionado.nif);
			strcpy_s(clienteAtual->c.morada, MORADA_LENGHT, clienteSelecionado.morada);
			clienteAtual->c.saldo = clienteSelecionado.saldo;
			return true;
		}

		clienteAtual = clienteAtual->proximo;
	}

	return false;
}


/**
 * \brief Ordenar clientes por id
 * 
 * \param primeiroCliente
 * \return 
 */
ClienteLista* OrdenarClientesPorId(ClienteLista* primeiroCliente) {
	ClienteLista* atual;
	ClienteLista* proximo;
	Cliente temp;

	for (atual = primeiroCliente; atual != NULL; atual = atual->proximo) {
		for (proximo = atual->proximo; proximo != NULL; proximo = proximo->proximo) {
			
			if (atual->c.id < proximo->c.id) {
				temp = atual->c;
				atual->c = proximo->c;
				proximo->c = temp;
			}
			
		}
	}

	return primeiroCliente;
}


/**
* \brief Devolve o cliente com o id selecionado
*
* \return
* \author A. Cerqueira
*
*/
Cliente* ProcurarClientePorId(ClienteLista* primeiroCliente, int id) {
	ClienteLista* clienteAtual = primeiroCliente;

	while (clienteAtual != NULL) {

		if (clienteAtual->c.id == id)
			return &(clienteAtual->c);

		clienteAtual = clienteAtual->proximo;
	}

	return NULL;
}


/**
* \brief Devolve o proximo id disponivel para um Cliente
*
* \return
* \author A. Cerqueira
*
*/
int ProcurarProximoIdCliente(ClienteLista* primeiroCliente) {
	ClienteLista* clienteAtual = primeiroCliente;
	int id = 0;

	while (clienteAtual != NULL) {

		if (clienteAtual->c.id > id)
			id = clienteAtual->c.id;

		clienteAtual = clienteAtual->proximo;
	}

	return id + 1;
}


/**
* \brief Devolve se o cliente tem saldo suficiente para realizar uma operação
*
* \return
* \author A. Cerqueira
*
*/
bool ClienteTemSaldoSuficiente(Cliente cliente, float valor) {
	return cliente.saldo >= valor;
}
