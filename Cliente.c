/*****************************************************************//**
 * \file   Cliente.c
 * \brief  Implementação das funções relacionadas aos clientes
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

 // Includes
#include "Cliente.h"


/**
* \brief Liberta a memória da lista ligada de clientes.
*
* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
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
* \brief Carrega os dados iniciais dos clientes de um ficheiro .txt para uma lista ligada e guarda no ficheiro .dat.
*
* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos clientes
* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
* \return O novo apontador para o primeiro elemento da lista ligada de clientes carregada
* \author A. Cerqueira
*/
ClienteLista* CarregarClientesIniciais(ClienteLista* primeiroCliente, char* filePathInicial, char* saveFilePath) {
	LibertarClientes(primeiroCliente);
	primeiroCliente = LerClientesIniciais(filePathInicial);
	GuardarClientes(saveFilePath, primeiroCliente);

	return primeiroCliente;
}


/**
* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de clientes.
*
* \param filePath O caminho do ficheiro .txt com os dados dos clientes
* \return O novo apontador para o primeiro elemento da lista ligada de clientes
* \author A. Cerqueira
*/
ClienteLista* LerClientesIniciais(char* filePath) {
	FILE* file;
	ClienteLista* primeiroCliente = NULL;
	char linha[MAX_SIZE];

	file = fopen(filePath, "r");
	if (file == NULL)
		return NULL;
	
	while (fgets(linha, MAX_SIZE, file)) {
		Cliente novoCliente;

		int numLidos = sscanf(linha, "%d;%[^;];%[^;];%[^;];%f;%d",
			&novoCliente.id, 
			novoCliente.nome, 
			novoCliente.nif, 
			novoCliente.morada, 
			&novoCliente.saldo, 
			&novoCliente.ativo);

		if (numLidos != 6)
			continue;
		
		primeiroCliente = AdicionarCliente(primeiroCliente, novoCliente);
	}

	fclose(file);

	return primeiroCliente;
}


/**
* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de clientes.
*
* \param filePath O caminho do ficheiro .dat com os dados dos clientes
* \return O novo apontador para o primeiro elemento da lista ligada de clientes
* \author A. Cerqueira
*/
ClienteLista* LerClientes(char* filePath) {
	FILE* file;
	Cliente* cliente;
	ClienteLista* primeiroCliente = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	cliente = (Cliente*)malloc(sizeof(Cliente));
	
	while (cliente != NULL && fread(cliente, sizeof(Cliente), 1, file)) {
		primeiroCliente = AdicionarCliente(primeiroCliente, *cliente);
		cliente = (Cliente*)malloc(sizeof(Cliente));
	}
	
	fclose(file);

	primeiroCliente = OrdenarClientesPorId(primeiroCliente);

	return primeiroCliente;
}


/**
* \brief Guarda a lista ligada de clientes em um arquivo .dat.
*
* \param filePath O caminho para o arquivo .dat onde os clientes serão guardados.
* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
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
* \brief Adiciona um novo cliente ao inicio da lista ligada.
*
* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
* \param novoCliente O cliente que será adicionado à lista.
* \return O novo apontador para o primeiro elemento da lista ligada de clientes
* \author A. Cerqueira
*/
ClienteLista* AdicionarCliente(ClienteLista* primeiroCliente, Cliente novoCliente) {
	ClienteLista* novoNode = (ClienteLista*)malloc(sizeof(ClienteLista));
	
	if (novoNode == NULL)
		return primeiroCliente;

	if (novoCliente.ativo == NULL)
		novoCliente.ativo = true;

	if (novoCliente.id == NULL)
		novoCliente.id = ProcurarProximoIdCliente(primeiroCliente);
	
	novoNode->proximo = (primeiroCliente != NULL) ? primeiroCliente : NULL;
	
	novoNode->c = novoCliente;
	primeiroCliente = novoNode;
	
	return primeiroCliente;
}


/**
* \brief Remover um cliente da lista ligada
*
* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
* \param id O id do cliente que será removido
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
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
* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
* \param clienteSelecionado O cliente que será alterado
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool EditarCliente(ClienteLista* primeiroCliente, Cliente clienteSelecionado) {

	ClienteLista* clienteAtual = primeiroCliente;

	while (clienteAtual != NULL) {

		if (clienteAtual->c.id == clienteSelecionado.id) {
			strcpy(clienteAtual->c.nome, clienteSelecionado.nome);
			strcpy(clienteAtual->c.nif, clienteSelecionado.nif);
			strcpy(clienteAtual->c.morada, clienteSelecionado.morada);
			clienteAtual->c.saldo = clienteSelecionado.saldo;
			return true;
		}

		clienteAtual = clienteAtual->proximo;
	}

	return false;
}


/**
 * \brief Ordena a lista ligada de clientes por ID em ordem decrescente.
 *
 * \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
 * \return O novo apontador para o primeiro elemento da lista ligada de clientes ordenada
 * \author A. Cerqueira
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
* \brief Procura um cliente na lista ligada a partir do seu ID.
*
* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
* \param id O id do cliente que será procurado
* \return O apontador para o cliente com o id selecionado
* \author A. Cerqueira
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
* \brief Procura o ultimo id de um cliente na lista ligada.
*
* \param primeiroCliente O apontador para o primeiro elemento da lista ligada de clientes
* \return O proximo id a ser utilizado
* \author A. Cerqueira
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
* \brief Devolve se o cliente tem saldo suficiente para realizar uma operação.
*
* \param cliente O cliente que será verificado
* \param O valor da operação
* \return true se o cliente tem saldo suficiente, false caso contrário
* \author A. Cerqueira
*/
bool ClienteTemSaldoSuficiente(Cliente cliente, float valor) {
	return cliente.saldo >= valor;
}
