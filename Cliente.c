/*****************************************************************//**
 * \file   Cliente.c
 * \brief  Funções de Cliente
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/


 // Includes
#include "Cliente.h"


Cliente* LerDadosIniciais() {
    
    FILE* fp;
	char* fullPath = (char*)malloc(sizeof(char) * MAX_SIZE);
    GetFullPath(HARDDATA_FILE_NAME, fullPath);
    
    // create "Clientes.txt" in D
	if (fullPath == 0) {
		printf("Erro ao criar ficheiro\n");
		return NULL;
	}
    
	// read "Clientes.txt" in D
    if (fopen_s(&fp, fullPath, "r") != 0) {
        printf("Erro ao abrir ficheiro\n");
        free(fullPath);
        return NULL;
    }
    
	printf("Ficheiro aberto com sucesso\n");

	Cliente* lista_clientes = NULL;
	char linha[MAX_SIZE];
        
	while (fgets(linha, MAX_SIZE, fp)) {
		Cliente* novo_cliente = (Cliente*)malloc(sizeof(Cliente));
		if (novo_cliente == NULL) {
			printf("Erro ao alocar memoria\n");
			return NULL;
		}

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
        novo_cliente->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novo_cliente->nome, NOME_SIZE, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novo_cliente->nif, NIF_SIZE, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(novo_cliente->morada, MORADA_SIZE, campo);

		campo = strtok_s(NULL, ";", &contexto);
		novo_cliente->saldo = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		novo_cliente->ativo = (bool)atoi(campo);

		novo_cliente->proximo = lista_clientes;
		lista_clientes = novo_cliente;
	}

    return lista_clientes;
}




Cliente* GuardarDadosIniciais() {

	
}