/*****************************************************************//**
 * \file   Gestor.h
 * \brief  Declarações das funções relacionadas aos gestores
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

	#define GESTOR_INITDATA_FILE_NAME "C:/IPCA/Projeto-EDA/data/simulacao/Gestores.txt"
	#define GESTOR_SAVE_FILE_NAME "C:/IPCA/Projeto-EDA/data/save/Gestores.dat"

	// Structs
	typedef struct Gestor Gestor;
	typedef struct GestorLista GestorLista;

	struct Gestor {
		int id;
		char nome[NOME_LENGHT];
		char email[EMAIL_LENGHT];
		char password[PASSWORD_LENGHT];
		bool ativo;
	};

	struct GestorLista {
		Gestor g;
		GestorLista* proximo;
	};


	/**
	* \brief Liberta a memória da lista ligada de gestores.
	*
	* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool LibertarGestores(GestorLista* primeiroGestor);


	/**
	* \brief Carrega os dados iniciais dos gestores de um ficheiro .txt para uma lista ligada e guarda no ficheiro .dat.
	*
	* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
	* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos gestores
	* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
	* \return O novo apontador para o primeiro elemento da lista ligada de gestores carregada
	* \author A. Cerqueira
	*/
	GestorLista* CarregarGestoresIniciais(GestorLista* primeiroGestor, char* filePathInicial, char* saveFilePath);


	/**
	* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de gestores.
	*
	* \param filePath O caminho do ficheiro .txt com os dados dos gestores
	* \return O novo apontador para o primeiro elemento da lista ligada de gestores
	* \author A. Cerqueira
	*/
	GestorLista* LerGestoresIniciais(char* filePath);


	/**
	* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de gestores.
	*
	* \param filePath O caminho do ficheiro .dat com os dados dos gestores
	* \return O novo apontador para o primeiro elemento da lista ligada de gestores
	* \author A. Cerqueira
	*/
	GestorLista* LerGestores(char* filePath);


	/**
	* \brief Guarda a lista ligada de gestores em um arquivo .dat.
	*
	* \param filePath O caminho para o arquivo .dat onde os gestores serão guardados.
	* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool GuardarGestores(char* filePath, GestorLista* primeiroGestor);


	/**
	* \brief Adiciona um novo Gestor ao inicio da lista ligada.
	*
	* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
	* \param novoGestor O Gestor que será adicionado à lista.
	* \return O novo apontador para o primeiro elemento da lista ligada de gestores
	* \author A. Cerqueira
	*/
	GestorLista* AdicionarGestor(GestorLista* primeiroGestor, Gestor novoGestor);


	/**
	* \brief Desativar um Gestor da lista ligada
	*
	* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
	* \param id O id do Gestor que será desativado
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool DesativarGestor(GestorLista* primeiroGestor, int id);
	

	/**
	* \brief Remover um Gestor da lista ligada
	*
	* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
	* \param id O id do Gestor que será removido
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	GestorLista* RemoverGestor(GestorLista* primeiroGestor, int id);


	/**
	* \brief Alterar um Gestor da lista ligada
	*
	* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
	* \param gestorSelecionado O Gestor que será alterado
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool EditarGestor(GestorLista* primeiroGestor, Gestor gestorSelecionado);
	
	
	/**
	 * \brief Ordena a lista ligada de gestores por ID em ordem decrescente.
	 *
	 * \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
	 * \return O novo apontador para o primeiro elemento da lista ligada de gestores ordenada
	 * \author A. Cerqueira
	 */
	GestorLista* OrdenarGestoresPorId(GestorLista* primeiroGestor);


	/**
	* \brief Procura o ultimo id de um Gestor na lista ligada.
	*
	* \param primeiroGestor O apontador para o primeiro elemento da lista ligada de gestores
	* \return O proximo id a ser utilizado
	* \author A. Cerqueira
	*/
	int ProcurarProximoIdGestor(GestorLista* primeiroGestor);

#endif

	
