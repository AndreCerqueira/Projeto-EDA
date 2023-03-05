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

	#define HARDDATA_FILE_NAME "D:/IPCA/Projeto-EDA/data/simulacao/Gestores.txt"
	#define SAVE_FILE_NAME "D:/IPCA/Projeto-EDA/data/save/Gestores.dat"

	// Structs
	typedef struct Gestor Gestor;
	struct Gestor {
		int id;
		char nome[NOME_LENGHT];
		char email[EMAIL_LENGHT];
		char password[PASSWORD_LENGHT];
		bool ativo;
		Gestor* proximo;
	};
	

	/**
	* \brief Resetar lista ligada de Gestores, reescreve o ficheiro .dat com a lista vazia
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void ResetarGestores(Gestor* ultimoGestor);


	/**
	* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	void CarregarGestoresIniciais(Gestor* ultimoGestor);


	/**
	* \brief Ler Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	Gestor* LerGestoresIniciais();
	

	/**
	* \brief Ler dados de um ficheiro de .dat e guardar numa lista ligada
	*
	* \return Lista ligada com os dados lidos
	* \author A. Cerqueira
	*
	*/
	Gestor* LerGestores();


	/**
	* \brief Guardar dados de uma lista ligada num ficheiro .dat
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void GuardarGestores(Gestor* ultimoGestor);


	/**
	* \brief Adicionar um Gestor à lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void AdicionarGestor(Gestor** ultimoGestor, char* nome, char* email, char* password);


	/**
	* \brief Remover um Gestor da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void RemoverGestor(Gestor* ultimoGestor, int id);


	/**
	* \brief Alterar um Gestor da lista ligada
	*
	* \return
	* \author A. Cerqueira
	*
	*/
	void EditarGestor(Gestor* ultimoGestor, int id, char* nome, char* email, char* password);
	

#endif

	
