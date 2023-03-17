/*****************************************************************//**
 * \file   Gestor.h
 * \brief  Funções de Gestor
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

#ifndef GESTOR_H_
#define GESTOR_H_

	// Includes
	#include "Utils.h"

	// Constants
	#define NOME_LENGHT 50
	#define EMAIL_LENGHT 50
	#define PASSWORD_LENGHT 20

	#define GESTOR_INITDATA_FILE_NAME "D:/IPCA/Projeto-EDA/data/simulacao/Gestores.txt"
	#define GESTOR_SAVE_FILE_NAME "D:/IPCA/Projeto-EDA/data/save/Gestores.dat"

	// Structs
	typedef struct Gestor Gestor;
	typedef struct Gestor {
		int id;
		char nome[NOME_LENGHT];
		char email[EMAIL_LENGHT];
		char password[PASSWORD_LENGHT];
		bool ativo;
	};

	typedef struct GestorLista GestorLista;
	typedef struct GestorLista {
		Gestor g;
		GestorLista* proximo;
	};


	/**
	* \brief Resetar lista ligada de Gestores, reescreve o ficheiro .dat com a lista vazia
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool LibertarGestores(GestorLista* primeiroGestor);


	/**
	* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	bool CarregarGestoresIniciais(GestorLista** primeiroGestor, char* filePathInicial, char* saveFilePath);


	/**
	* \brief Ler Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	GestorLista* LerGestoresIniciais(char* filePath);


	/**
	* \brief Ler dados de um ficheiro de .dat e guardar numa lista ligada
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	GestorLista* LerGestores(char* filePath);


	/**
	* \brief Guardar dados de uma lista ligada num ficheiro .dat
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool GuardarGestores(char* filePath, GestorLista* primeiroGestor);


	/**
	* \brief Adicionar um Gestor Ã  lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool AdicionarGestor(GestorLista** primeiroGestor, Gestor* novoGestor);


	/**
	* \brief Remover um Gestor da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool RemoverGestor(GestorLista* primeiroGestor, int id);


	/**
	* \brief Alterar um Gestor da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	bool EditarGestor(GestorLista* primeiroGestor, Gestor* gestorSelecionado);
	
	
	/**
	 * \brief Ordenar gestores por id
	 *
	 * \param primeiroCliente
	 * \return
	 */
	bool OrdenarGestoresPorId(GestorLista** primeiroGestor);

#endif

	
