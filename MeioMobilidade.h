/*****************************************************************//**
 * \file   MeioMobilidade.h
 * \brief  Funções de Meios de Mobilidade
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

#ifndef MEIO_MOBILIDADE_H_
#define MEIO_MOBILIDADE_H_

	 // Includes
	#include "Utils.h"
	#include "Cliente.h"
	#include "Localizacao.h"

	// Constants
	#define MEIO_INITDATA_FILE_NAME "C:/IPCA/Projeto-EDA/data/simulacao/MeiosMobilidade.txt"
	#define MEIO_SAVE_FILE_NAME "C:/IPCA/Projeto-EDA/data/save/MeiosMobilidade.dat"

	// Enums
	typedef enum {
		Bicibleta,
		Trotinente,
		Scooter,
		SkateEletrico,
		Outro
	} TipoMeioMobilidade;

	// Structs
	typedef struct MeioMobilidade MeioMobilidade;
	typedef struct MeioMobilidadeLista MeioMobilidadeLista;

	struct MeioMobilidade {
		int id;
		TipoMeioMobilidade tipo;
		float cargaBateria;
		float custoAluguer;
		int postoId;
		bool ativo;
	};

	struct MeioMobilidadeLista {
		MeioMobilidade m;
		MeioMobilidadeLista* proximo;
	};


	/**
	* \brief Liberta a memória da lista ligada de meios mobilidade
	*
	* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool LibertarMeiosMobilidade(MeioMobilidadeLista* primeiroMeio);


	/**
	* \brief Carrega os dados iniciais dos meios mobilidade de um ficheiro .txt para uma lista ligada e guarda no ficheiro .dat.
	*
	* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos meios mobilidade
	* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
	* \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade carregada
	* \author A. Cerqueira
	*/
	MeioMobilidadeLista* CarregarMeiosMobilidadeIniciais(MeioMobilidadeLista* primeiroMeio, char* filePathInicial, char* saveFilePath);


	/**
	* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de meios mobilidade.
	*
	* \param filePath O caminho do ficheiro .txt com os dados dos meios mobilidade
	* \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \author A. Cerqueira
	*/
	MeioMobilidadeLista* LerMeiosMobilidadeIniciais(char* filePath);


	/**
	* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de meios mobilidade.
	*
	* \param filePath O caminho do ficheiro .dat com os dados dos meios mobilidade
	* \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \author A. Cerqueira
	*/
	MeioMobilidadeLista* LerMeiosMobilidade(char* filePath);


	/**
	* \brief Guarda a lista ligada de meios mobilidade em um arquivo .dat.
	*
	* \param filePath O caminho para o arquivo .dat onde os meios mobilidade serão guardados.
	* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool GuardarMeiosMobilidade(char* filePath, MeioMobilidadeLista* primeiroMeio);


	/**
	* \brief Adiciona um novo Meio ao inicio da lista ligada.
	*
	* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \param novoMeio O Meio que será adicionado à lista.
	* \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \author A. Cerqueira
	*/
	MeioMobilidadeLista* AdicionarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, MeioMobilidade novoMeio);


	/**
	* \brief Remover um Meio da lista ligada
	*
	* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \param id O id do Meio que será removido
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool RemoverMeioMobilidade(MeioMobilidadeLista* primeiroMeio, int id);


	/**
	* \brief Alterar um Meio da lista ligada
	*
	* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \param meioSelecionado O Meio que será alterado
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool EditarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, MeioMobilidade meioSelecionado);


	/**
	* \brief Converter um TipoMeioMobilidade em string
	*
	* \param tipoMeioMobilidade O tipo de meio de mobilidade
	* \return O tipo de meio de mobilidade em string
	* \author A. Cerqueira
	*/
	char* TipoMeioMobilidadeToString(TipoMeioMobilidade tipoMeioMobilidade);


	/**
	 * \brief Ordena a lista ligada de meios mobilidade por ID em ordem decrescente.
	 *
	 * \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	 * \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade ordenada
	 * \author A. Cerqueira
	 */
	MeioMobilidadeLista* OrdenarMeiosMobilidadePorId(MeioMobilidadeLista* primeiroMeio);


	/**
	 * \brief Ordena a lista ligada de meios mobilidade por autonomia em ordem decrescente.
	 *
	 * \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	 * \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade ordenada
	 */
	MeioMobilidadeLista* OrdenarMeiosMobilidadePorAutonomia(MeioMobilidadeLista* primeiroMeio);


	/**
	 * \brief Procurar todos os meios de mobilidade que estão numa determinada localização.
	 *
	 * \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	 * \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	 * \param geocodigo O geocódigo da localização
	 * \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade ordenada
	 */
	MeioMobilidadeLista* ProcurarMeiosMobilidadePorLocalizacao(MeioMobilidadeLista* primeiroMeio, PostoVertice* primeiroPosto, char* geocodigo);


	/**
	* \brief Procura um Meio na lista ligada a partir do seu ID.
	*
	* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \param id O id do Meio que será procurado
	* \return O apontador para o Meio com o id selecionado
	* \author A. Cerqueira
	*/
	MeioMobilidade* ProcurarMeioMobilidadePorId(MeioMobilidadeLista* primeiroMeio, int id);


	/**
	* \brief Procura o ultimo id de um Meio na lista ligada.
	*
	* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
	* \return O proximo id a ser utilizado
	* \author A. Cerqueira
	*/
	int ProcurarProximoIdMeioMobilidade(MeioMobilidadeLista* primeiroMeio);

#endif