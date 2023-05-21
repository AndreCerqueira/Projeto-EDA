/*****************************************************************//**
 * \file   Localizacao.h
 * \brief  Declarações das funções relacionadas ás localizações
 *
 * \author A. Cerqueira
 * \date   February 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

#ifndef LOCALIZACAO_H_
#define LOCALIZACAO_H_

	// Includes
	#include "Utils.h"

	// Constants
	#define INFINITO 9999
	#define GEOCODE_LENGHT 100
	#define NOME_LOCALIZACAO_LENGHT 100

	#define POSTO_INITDATA_FILE_NAME "C:/IPCA/Projeto-EDA/data/simulacao/Postos.txt"
	#define POSTO_SAVE_FILE_NAME "C:/IPCA/Projeto-EDA/data/save/Postos.dat"
	#define POSTO_ADJ_INITDATA_FILE_NAME "C:/IPCA/Projeto-EDA/data/simulacao/PostoAdjacentes.txt"
	#define POSTO_ADJ_SAVE_FILE_NAME "C:/IPCA/Projeto-EDA/data/save/PostoAdjacentes.dat"

	// Structs

	typedef struct PostoFicheiro PostoFicheiro;
	typedef struct Posto Posto;
	typedef struct PostoVertice PostoVertice;
	typedef struct AdjacenciaFicheiro AdjacenciaFicheiro;
	typedef struct PostoAdjacente PostoAdjacente;
	typedef struct VerticeDijkstra VerticeDijkstra;
	typedef struct Percurso Percurso;

	struct PostoFicheiro {
		int id;
		char nome[NOME_LOCALIZACAO_LENGHT];
		char geocode[GEOCODE_LENGHT];
	};

	struct Posto {
		PostoFicheiro f;
		PostoAdjacente* primeiraAdjacencia;
	};

	struct PostoVertice {
		Posto p;
		PostoVertice* proximo;
	};

	struct AdjacenciaFicheiro {
		int origemId;
		int destinoId;
		float distancia;  // em km (peso)
	};
	
	struct PostoAdjacente {
		AdjacenciaFicheiro f;
		PostoVertice* origem;
		PostoVertice* destino;
		PostoAdjacente* proximo;
	};

	struct VerticeDijkstra {
		PostoVertice* vertice;
		float distancia;
		VerticeDijkstra* antecessor;
		bool visitado;
		VerticeDijkstra* proximo;
	};
	
	struct Percurso {
		PostoVertice* vertice;
		float distancia;
		Percurso* proximo;
	};


	/**
	* \brief Liberta a memória da lista ligada de postos
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool LibertarPostos(PostoVertice* primeiroPosto);


	/**
	* \brief Liberta a memória da lista ligada de postos adjacentes
	*
	* \param primeiroPostoAdjacente O apontador para o primeiro elemento da lista ligada de postos adjacentes
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool LibertarPostosAdjacentes(PostoAdjacente* primeiroPostoAdjacente);


	/**
	* \brief Carrega os dados iniciais dos postos de um ficheiro .txt para uma lista ligada e guarda no ficheiro .dat.
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos postos
	* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
	* \return O novo apontador para o primeiro elemento da lista ligada de postos carregada
	* \author A. Cerqueira
	*/
	PostoVertice* CarregarPostosIniciais(PostoVertice* primeiroPosto, char* filePathInicial, char* saveFilePath);


	/**
	* \brief Carrega os dados iniciais dos postos adjacentes de um ficheiro .txt para uma lista ligada.
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos postos adjacentes
	* \param saveFilePath O caminho do ficheiro .dat onde os postos adjacentes serão guardados
	* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes carregada
	* \author A. Cerqueira
	*/
	PostoVertice* CarregarPostosAdjacentesIniciais(PostoVertice* primeiroPosto, char* filePathInicial, char* saveFilePath);


	/**
	* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de postos.
	*
	* \param filePath O caminho do ficheiro .txt com os dados dos postos
	* \return O novo apontador para o primeiro elemento da lista ligada de postos
	* \author A. Cerqueira
	*/
	PostoVertice* LerPostosIniciais(char* filePath);


	/**
	* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de postos adjacentes.
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \param filePath O caminho do ficheiro .txt com os dados dos postos adjacentes
	* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes
	* \author A. Cerqueira
	*/
	PostoVertice* LerPostosAdjacentesIniciais(PostoVertice* primeiroPosto, char* filePath);


	/**
	* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de postos.
	*
	* \param filePath O caminho do ficheiro .dat com os dados dos postos
	* \return O novo apontador para o primeiro elemento da lista ligada de postos
	* \author A. Cerqueira
	*/
	PostoVertice* LerPostos(char* filePath);


	/**
	* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de postos adjacentes.
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \param posto O apontador para o posto atual
	* \param filePath O caminho do ficheiro .dat com os dados dos posto adjacentes.
	* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes
	* \author A. Cerqueira
	*/
	PostoVertice* LerPostosAdjacentes(PostoVertice* primeiroPosto, char* filePath);


	/**
	* \brief Guarda a lista ligada de postos em um arquivo .dat.
	*
	* \param filePath O caminho para o arquivo .dat onde os postos serão guardados.
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool GuardarPostos(char* filePath, PostoVertice* primeiroPosto);


	/**
	* \brief Guarda a lista ligada de postos adjacentes em um arquivo .dat.
	*
	* \param filePath O caminho para o arquivo .dat onde os postos adjacentes serão guardados.
	* \param primeiroPostoAdjacente O apontador para o primeiro elemento da lista ligada de postos adjacentes
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool GuardarPostosAdjacentes(char* filePath, PostoAdjacente* primeiroPostoAdjacente);


	/**
	* \brief Apaga o arquivo .dat com os dados dos postos.
	*
	* \param filePath O caminho para o arquivo .dat onde os postos serão guardados.
	* \return true se a operação foi realizada com sucesso, false caso contrário
	* \author A. Cerqueira
	*/
	bool ApagarPostosAdjacentesFicheiro(char* filePath);


	/**
	* \brief Adiciona um novo Posto ao inicio da lista ligada.
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \param novoPosto O Posto que será adicionado à lista.
	* \return O novo apontador para o primeiro elemento da lista ligada de postos
	* \author A. Cerqueira
	*/
	PostoVertice* AdicionarPosto(PostoVertice* primeiroPosto, Posto novoPosto);


	/**
	* \brief Adiciona um novo Posto adjacente ao inicio da lista ligada.
	*
	* \param posto O apontador para o posto atual
	* \param postoAdjacente O Posto adjacente que será adicionado à lista.
	* \return O novo apontador para o primeiro elemento da lista ligada de postos adjacentes
	* \author A. Cerqueira
	*/
	PostoVertice* AdicionarPostoAdjacente(PostoVertice* posto, PostoAdjacente* postoAdjacente);


	/**
	 * \brief Ordena a lista ligada de postos por ID em ordem decrescente.
	 *
	 * \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	 * \return O novo apontador para o primeiro elemento da lista ligada de postos ordenada
	 * \author A. Cerqueira
	 */
	PostoVertice* OrdenarPostosPorId(PostoVertice* primeiroPosto);


	/**
	* \brief Procura um posto na lista ligada a partir do seu ID.
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \param id O id do posto que será procurado
	* \return O apontador para o posto com o id selecionado
	* \author A. Cerqueira
	*/
	Posto* ProcurarPostoPorId(PostoVertice* primeiroPosto, int id);


	/**
	* \brief Procura um posto vertice na lista ligada a partir do seu ID.
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \param id O id do posto que será procurado
	* \return O apontador para o vertice do posto com o id selecionado
	* \author A. Cerqueira
	*/
	PostoVertice* ProcurarPostoVerticePorId(PostoVertice* primeiroPosto, int id);


	/**
	* \brief Procura o ultimo id de um posto na lista ligada.
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \return O proximo id a ser utilizado
	* \author A. Cerqueira
	*/
	int ProcurarProximoIdPosto(PostoVertice* primeiroPosto);
	

	/**
	* \brief Procura o id de um posto na lista ligada a partir do seu geocodigo.
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \param geocodigo O geocodigo do posto que será procurado
	* \return O id do posto com o geocodigo selecionado
	* \author A. Cerqueira
	*/
	int ProcurarIdPostoDeGeocodigo(PostoVertice* primeiroPosto, char* geocodigo);


	/** 
	* \brief Conta o numero de postos na lista ligada.
	* 
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \return O numero de postos na lista ligada
	* \author A. Cerqueira
	*/
	int ContarPostos(PostoVertice* primeiroPosto);
	

	/**
	* \brief Conta a distancia entre os postos na lista ligada.
	*
	* \param percurso O apontador para o primeiro elemento da lista ligada de postos do percurso
	* \return O numero de postos na lista ligada
	* \author A. Cerqueira
	*/
	float ContarDistanciaEmPercurso(Percurso* percurso);
	
	
	/**
	* \brief Procura o percurso mais rapido entre dois postos, utilizando o algoritmo de Dijkstra.
	*
	* \param origem O apontador para o vertice do posto de origem
	* \param destino O apontador para o vertice do posto de destino
	* \return O apontador para o vertice do posto de inicio do percurso mais rapido
	* \author A. Cerqueira
	*/
	Percurso* ProcurarPercursoMaisRapido(PostoVertice* origem, PostoVertice* destino, PostoVertice* primeiroPosto);
	
	
	/**
	 * \brief Constroi um percurso a partir de um vertice de destino do algoritmo de Dijkstra.
	 *
	 * \param dijkstraDestino O apontador para o vertice de destino do algoritmo de Dijkstra
	 * \return O apontador para o primeiro elemento da lista ligada de postos do percurso
	 */
	Percurso* ConstruirPercurso(VerticeDijkstra* dijkstraDestino);
	
	
	/**
	* \brief Inicializa o algoritmo de Dijkstra para um conjunto de vertices.
	*
	* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
	* \return O apontador para o primeiro elemento da lista ligada de vertices do algoritmo de Dijkstra
	*/
	VerticeDijkstra* InicializarDijkstraVertices(PostoVertice* primeiroPosto);


	/**
	 * \brief Encontra o proximo vertice a ser visitado no algoritmo de Dijkstra.
	 *
	 * \param dijkstraVertices O array com todos os vertices
	 * \return O apontador para o vertice a ser visitado
	 */
	VerticeDijkstra* EncontrarProximoVertice(VerticeDijkstra* dijkstraVertices);
	
	
	/**
	 * \brief Encontra um vertice na lista ligada de vertices do algoritmo de Dijkstra.
	 *
	 * \param dijkstraVertices A lista ligada de vertices do algoritmo de Dijkstra
	 * \param id O id do vertice a encontrar
	 * \return O apontador para o vertice encontrado
	 */
	VerticeDijkstra* EncontrarVerticeDijkstraPorId(VerticeDijkstra* dijkstraVertices, int id);


	/**
	 * \brief Liberta a memoria alocada para a lista ligada de vertices do algoritmo de Dijkstra.
	 *
	 * \param dijkstraVertices O apontador para o primeiro elemento da lista ligada de vertices do algoritmo de Dijkstra
	 */
	bool LibertarDijkstraVertices(VerticeDijkstra* dijkstraVertices);

#endif


