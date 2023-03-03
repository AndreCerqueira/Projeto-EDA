/*****************************************************************//**
 * \file   Cliente.c
 * \brief  Funções de Cliente
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/


 // Includes
#include "Cliente.h"


// Funções

#define MAX_SIZE 1024


Cliente* LerDadosIniciais() {
    FILE* arquivo;
    Cliente* lista_clientes = NULL;
	char* fullPath = GetFullPath(HARDDATA_FILE_NAME);

    if (fopen_s(&arquivo, fullPath, "r") != 0) {
        printf("Erro ao abrir arquivo\n");
        return NULL;
    }

    char linha[MAX_SIZE];
    while (fgets(linha, MAX_SIZE, arquivo)) {
        Cliente* novo_cliente = (Cliente*)malloc(sizeof(Cliente));
        if (novo_cliente == NULL) {
            printf("Erro ao alocar memoria\n");
            return NULL;
        }

        char* contexto = NULL;
        char* campo = strtok_s(linha, ";", &contexto);
        strcpy_s(novo_cliente->uid, UID_LENGHT, campo);

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

    fclose(arquivo);
    return lista_clientes;
}