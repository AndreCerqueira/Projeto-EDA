/*****************************************************************//**
 * \file   Aluguer.h
 * \brief  Declarações das funções relacionadas aos Alugueres e Preços de Aluguer.
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

	// Structs
	typedef struct Aluguer Aluguer;
	typedef struct AluguerLista AluguerLista;

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

	
	/**
	 * \brief Alugar um meio de mobilidade
	 *
	 * \param meioMobilidade O meio de mobilidade que será alugado
	 * \param cliente O cliente que vai alugar o meio de mobilidade
	 * \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de alugueres
	 * \param destino O posto de destino ao qual o cliente pretende ir
	 * \param percurso O percurso que o cliente vai fazer
	 * \return O apontador para o primeiro elemento da lista ligada de alugueres
	 */
	AluguerLista* AlugarMeioMobilidade(MeioMobilidade* meioMobilidade, Cliente* cliente, AluguerLista* primeiroAluguer, Posto destino, Percurso* percurso);
	

	/**
	* \brief Calcula o custo de um Aluguer com base no meio de mobilidade utilizado e nos km percorridos.
	*
	* \param aluguer O Aluguer que será calculado o custo
	* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de Meios de Mobilidade
	* \return O custo do Aluguer, multiplicando o custo do meio de mobilidade pelo numero de km percorridos
	* \author A. Cerqueira
	*/
	float CalcularCustoAluguer(Aluguer aluguer, MeioMobilidadeLista* primeiroMeio);

#endif


