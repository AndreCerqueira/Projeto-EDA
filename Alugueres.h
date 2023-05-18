/*****************************************************************//**
 * \file   Aluguer.h
 * \brief  Declarações das funções relacionadas aos Alugueres
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

#ifndef ALUGUERES_H_
#define ALUGUERES_H_

	 // Includes
	#include "Utils.h"
	#include "Cliente.h"
	#include "Localizacao.h"
	#include "MeioMobilidade.h"

	// Constants
	#define DATA_LENGHT 28

	#define ALUGUER_INITDATA_FILE_NAME "C:/IPCA/Projeto-EDA/data/simulacao/Alugueres.txt"
	#define ALUGUER_SAVE_FILE_NAME "C:/IPCA/Projeto-EDA/data/save/Alugueres.dat"
	#define PRECO_ALUGUER_INITDATA_FILE_NAME "C:/IPCA/Projeto-EDA/data/simulacao/PrecosAluguer.txt"
	#define PRECO_ALUGUER_SAVE_FILE_NAME "C:/IPCA/Projeto-EDA/data/save/PrecosAluguer.dat"

	// Structs
	typedef struct Aluguer Aluguer;
	typedef struct AluguerLista AluguerLista;
	typedef struct PrecoAluguer PrecoAluguer;
	typedef struct PrecoAluguerLista PrecoAluguerLista;

	struct Aluguer {
		int id;
		int clienteId;
		int meioId;
		float kmPercorridos;
		char dataInicio[DATA_LENGHT];
		char dataFim[DATA_LENGHT];
		bool ativo;
	};

	struct AluguerLista {
		Aluguer a;
		AluguerLista* proximo;
	};

	struct PrecoAluguer {
		char dataInicio[DATA_LENGHT];
		int meioId;
		float precoPorKm;
	};

	struct PrecoAluguerLista {
		PrecoAluguer p;
		PrecoAluguerLista* proximo;
	};


	/**
	* \brief Liberta a memória da lista ligada de Alugueres.
	*
	* \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool LibertarAlugueres(AluguerLista* primeiroAluguer);


	/**
	* \brief Carrega os dados iniciais dos Alugueres de um ficheiro .txt para uma lista ligada e guarda no ficheiro .dat.
	*
	* \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
	* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos Alugueres
	* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
	* \return O novo apontador para o primeiro elemento da lista ligada de Alugueres carregada
	* \author A. Cerqueira
	*/
	AluguerLista* CarregarAlugueresIniciais(AluguerLista* primeiroAluguer, char* filePathInicial, char* saveFilePath);


	/**
	* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de Alugueres.
	*
	* \param filePath O caminho do ficheiro .txt com os dados dos Alugueres
	* \return O novo apontador para o primeiro elemento da lista ligada de Alugueres
	* \author A. Cerqueira
	*/
	AluguerLista* LerAlugueresIniciais(char* filePath);


	/**
	* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de Alugueres.
	*
	* \param filePath O caminho do ficheiro .dat com os dados dos Alugueres
	* \return O novo apontador para o primeiro elemento da lista ligada de Alugueres
	* \author A. Cerqueira
	*/
	AluguerLista* LerAlugueres(char* filePath);


	/**
	* \brief Guarda a lista ligada de Alugueres em um arquivo .dat.
	*
	* \param filePath O caminho para o arquivo .dat onde os Alugueres serão guardados.
	* \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool GuardarAlugueres(char* filePath, AluguerLista* primeiroAluguer);


	/**
	* \brief Adiciona um novo Aluguer ao inicio da lista ligada.
	*
	* \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
	* \param novoAluguer O Aluguer que será adicionado à lista.
	* \return O novo apontador para o primeiro elemento da lista ligada de Alugueres
	* \author A. Cerqueira
	*/
	AluguerLista* AdicionarAluguer(AluguerLista* primeiroAluguer, Aluguer novoAluguer);


	/**
	 * \brief Ordena a lista ligada de Alugueres por ID em ordem decrescente.
	 *
	 * \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
	 * \return O novo apontador para o primeiro elemento da lista ligada de Alugueres ordenada
	 * \author A. Cerqueira
	 */
	AluguerLista* OrdenarAlugueresPorId(AluguerLista* primeiroAluguer);


	/**
	* \brief Procura o ultimo id de um Aluguer na lista ligada.
	*
	* \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
	* \return O proximo id a ser utilizado
	* \author A. Cerqueira
	*/
	int ProcurarProximoIdAluguer(AluguerLista* primeiroAluguer);

#endif


