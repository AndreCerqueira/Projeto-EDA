/*****************************************************************//**
 * \file   MeioMobilidade.c
 * \brief  Funções de Meios de mobilidade
 *
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

 // Includes
#include "MeioMobilidade.h"


/**
* \brief Liberta a memória da lista ligada de meios mobilidade
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool LibertarMeiosMobilidade(MeioMobilidadeLista* primeiroMeio) {
	MeioMobilidadeLista* meioAtual = primeiroMeio;

	while (meioAtual != NULL) {
		MeioMobilidadeLista* meioAnterior = meioAtual;
		meioAtual = meioAtual->proximo;
		free(meioAnterior);
	}

	primeiroMeio = NULL;

	return true;
}


/**
* \brief Carrega os dados iniciais dos meios mobilidade de um ficheiro .txt para uma lista ligada e guarda no ficheiro .dat.
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos meios mobilidade
* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
* \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade carregada
* \author A. Cerqueira
*/
MeioMobilidadeLista* CarregarMeiosMobilidadeIniciais(MeioMobilidadeLista* primeiroMeio, char* filePathInicial, char* saveFilePath) {
	LibertarMeiosMobilidade(primeiroMeio);
	primeiroMeio = LerMeiosMobilidadeIniciais(filePathInicial);
	GuardarMeiosMobilidade(saveFilePath, primeiroMeio);

	return primeiroMeio;
}


/**
* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de meios mobilidade.
*
* \param filePath O caminho do ficheiro .txt com os dados dos meios mobilidade
* \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade
* \author A. Cerqueira
*/
MeioMobilidadeLista* LerMeiosMobilidadeIniciais(char* filePath) {
	FILE* file;
	MeioMobilidadeLista* primeiroMeio = NULL;
	char linha[MAX_SIZE];

	file = fopen(filePath, "r");
	if (file == NULL)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		MeioMobilidade novoMeio;

		int numLidos = sscanf(linha, "%d;%d;%f;%f;%f;%d;%d",
			&novoMeio.id,
			(int*)&novoMeio.tipo,
			&novoMeio.cargaBateria,
			&novoMeio.custoAluguer,
			&novoMeio.peso,
			&novoMeio.postoId,
			(int*)&novoMeio.ativo);

		if (numLidos != 7)
			continue;

		primeiroMeio = AdicionarMeioMobilidade(primeiroMeio, novoMeio);
	}

	fclose(file);

	return primeiroMeio;
}


/**
* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de meios mobilidade.
*
* \param filePath O caminho do ficheiro .dat com os dados dos meios mobilidade
* \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade
* \author A. Cerqueira
*/
MeioMobilidadeLista* LerMeiosMobilidade(char* filePath) {
	FILE* file;
	MeioMobilidade* meio;
	MeioMobilidadeLista* primeiroMeio = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	meio = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));

	while (meio != NULL && fread(meio, sizeof(MeioMobilidade), 1, file)) {
		primeiroMeio = AdicionarMeioMobilidade(primeiroMeio, *meio);
		meio = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));
	}

	fclose(file);

	primeiroMeio = OrdenarMeiosMobilidadePorId(primeiroMeio);

	return primeiroMeio;
}


/**
* \brief Guarda a lista ligada de meios mobilidade em um arquivo .dat.
*
* \param filePath O caminho para o arquivo .dat onde os meios mobilidade serão guardados.
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool GuardarMeiosMobilidade(char* filePath, MeioMobilidadeLista* primeiroMeio) {
	FILE* file;
	file = fopen(filePath, "wb");

	if (file == NULL)
		return false;

	MeioMobilidadeLista* meioAtual = primeiroMeio;

	while (meioAtual != NULL) {
		fwrite(&meioAtual->m, sizeof(MeioMobilidade), 1, file);
		meioAtual = meioAtual->proximo;
	}

	fclose(file);

	return true;
}


/**
* \brief Adiciona um novo Meio ao inicio da lista ligada.
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \param novoMeio O Meio que será adicionado à lista.
* \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade
* \author A. Cerqueira
*/
MeioMobilidadeLista* AdicionarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, MeioMobilidade novoMeio) {
	MeioMobilidadeLista* novoNode = (MeioMobilidadeLista*)malloc(sizeof(MeioMobilidadeLista));

	if (novoNode == NULL)
		return primeiroMeio;

	if (novoMeio.ativo == NULL)
		novoMeio.ativo = true;

	if (novoMeio.id == NULL)
		novoMeio.id = ProcurarProximoIdMeioMobilidade(primeiroMeio);

	novoNode->proximo = (primeiroMeio != NULL) ? primeiroMeio : NULL;

	novoNode->m = novoMeio;
	primeiroMeio = novoNode;

	return primeiroMeio;
}


/**
* \brief Remover um Meio da lista ligada
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \param id O id do Meio que será removido
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
MeioMobilidadeLista* RemoverMeioMobilidade(MeioMobilidadeLista* primeiroMeio, int id) {

	MeioMobilidadeLista* meioAtual = primeiroMeio;
	MeioMobilidadeLista* meioAnterior = NULL;

	while (meioAtual != NULL) {

		if (meioAtual->m.id == id) {

			if (meioAnterior == NULL) {
				primeiroMeio = meioAtual->proximo;
			}
			else {
				meioAnterior->proximo = meioAtual->proximo;
			}

			free(meioAtual);
			return primeiroMeio;
		}

		meioAnterior = meioAtual;
		meioAtual = meioAtual->proximo;
	}

	return primeiroMeio;
}


/**
* \brief Desativar um Meio da lista ligada
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \param id O id do Meio que será desativado
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool DesativarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, int id) {

	MeioMobilidadeLista* meioAtual = primeiroMeio;

	while (meioAtual != NULL) {

		if (meioAtual->m.id == id) {
			meioAtual->m.ativo = false;
			return true;
		}

		meioAtual = meioAtual->proximo;
	}

	return false;
}


/**
* \brief Alterar um Meio da lista ligada
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \param meioSelecionado O Meio que será alterado
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool EditarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, MeioMobilidade meioSelecionado) {

	MeioMobilidadeLista* meioAtual = primeiroMeio;

	while (meioAtual != NULL) {

		if (meioAtual->m.id == meioSelecionado.id) {
			meioAtual->m.tipo = meioSelecionado.tipo;
			meioAtual->m.cargaBateria = meioSelecionado.cargaBateria;
			meioAtual->m.custoAluguer = meioSelecionado.custoAluguer;
			meioAtual->m.postoId = meioSelecionado.postoId;
			return true;
		}

		meioAtual = meioAtual->proximo;
	}

	return false;
}


/**
* \brief Converter um TipoMeioMobilidade em string
*
* \param tipoMeioMobilidade O tipo de meio de mobilidade
* \return O tipo de meio de mobilidade em string
* \author A. Cerqueira
*/
char* TipoMeioMobilidadeToString(TipoMeioMobilidade tipoMeioMobilidade) {

	switch (tipoMeioMobilidade) {
	case Bicibleta:
		return "Bicibleta";
	case Trotinente:
		return "Trotinente";
	case Scooter:
		return "Scooter";
	case SkateEletrico:
		return "SkateEletrico";
	case Outro:
		return "Outro";
	default:
		return "Desconhecido";
	}
}


/**
 * \brief Ordena a lista ligada de meios mobilidade por ID em ordem decrescente.
 *
 * \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
 * \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade ordenada
 * \author A. Cerqueira
 */
MeioMobilidadeLista* OrdenarMeiosMobilidadePorId(MeioMobilidadeLista* primeiroMeio) {
	MeioMobilidadeLista* atual;
	MeioMobilidadeLista* proximo;
	MeioMobilidade temp;

	for (atual = primeiroMeio; atual != NULL; atual = atual->proximo) {
		for (proximo = atual->proximo; proximo != NULL; proximo = proximo->proximo) {

			if (atual->m.id < proximo->m.id) {
				temp = atual->m;
				atual->m = proximo->m;
				proximo->m = temp;
			}

		}
	}

	return primeiroMeio;
}


/**
 * \brief Ordena a lista ligada de meios mobilidade por autonomia em ordem decrescente.
 *
 * \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
 * \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade ordenada
 */
MeioMobilidadeLista* OrdenarMeiosMobilidadePorAutonomia(MeioMobilidadeLista* primeiroMeio) {
	MeioMobilidadeLista* atual;
	MeioMobilidadeLista* proximo;
	MeioMobilidade temp;

	for (atual = primeiroMeio; atual != NULL; atual = atual->proximo) {
		for (proximo = atual->proximo; proximo != NULL; proximo = proximo->proximo) {

			if (atual->m.cargaBateria < proximo->m.cargaBateria) {
				temp = atual->m;
				atual->m = proximo->m;
				proximo->m = temp;
			}

		}
	}

	return primeiroMeio;
}


/**
 * \brief Procurar todos os meios de mobilidade que estão numa determinada localização.
 *
 * \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
 * \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
 * \param geocodigo O geocódigo da localização
 * \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade ordenada
 */
MeioMobilidadeLista* ProcurarMeiosMobilidadePorLocalizacao(MeioMobilidadeLista* primeiroMeio, PostoVertice* primeiroPosto, char* geocodigo) {
	MeioMobilidadeLista* meiosMobilidadeLocalizacao = NULL;
	MeioMobilidadeLista* meioAtual = primeiroMeio;

	// Get Posto Id By Geocode
	int postoIdSelecionado = ProcurarIdPostoDeGeocodigo(primeiroPosto, geocodigo);

	while (meioAtual != NULL) {

		if (meioAtual->m.postoId == postoIdSelecionado) {
			meiosMobilidadeLocalizacao = AdicionarMeioMobilidade(meiosMobilidadeLocalizacao, meioAtual->m);
		}

		meioAtual = meioAtual->proximo;
	}

	return meiosMobilidadeLocalizacao;
}


/**
* \brief Procura um Meio na lista ligada a partir do seu ID.
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \param id O id do Meio que será procurado
* \return O apontador para o Meio com o id selecionado
* \author A. Cerqueira
*/
MeioMobilidade* ProcurarMeioMobilidadePorId(MeioMobilidadeLista* primeiroMeio, int id) {
	MeioMobilidadeLista* meioAtual = primeiroMeio;

	while (meioAtual != NULL) {

		if (meioAtual->m.id == id) {
			return &(meioAtual->m);
		}

		meioAtual = meioAtual->proximo;
	}

	return NULL;
}


/**
* \brief Procura o ultimo id de um Meio na lista ligada.
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \return O proximo id a ser utilizado
* \author A. Cerqueira
*/
int ProcurarProximoIdMeioMobilidade(MeioMobilidadeLista* primeiroMeio) {
	MeioMobilidadeLista* meioAtual = primeiroMeio;
	int id = 0;

	while (meioAtual != NULL) {

		if (meioAtual->m.id > id)
			id = meioAtual->m.id;

		meioAtual = meioAtual->proximo;
	}

	return id + 1;
}


/**
* \brief Conta o numero de postos na lista ligada.
*
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \return O numero de postos na lista ligada
* \author A. Cerqueira
*/
int ContarMeiosPorRecolherEmPosto(PostoVertice* posto, MeioMobilidadeLista* primeiroMeio) {
	MeioMobilidadeLista* meioAtual = primeiroMeio;
	int nMeios = 0;

	while (meioAtual != NULL) {

		if (meioAtual->m.postoId == posto->p.f.id && meioAtual->m.cargaBateria < BATERIA_MINIMA_PARA_RECOLHA)
			nMeios++;

		meioAtual = meioAtual->proximo;
	}

	return nMeios;
}


/**
* \brief Recolhe todos os meios de mobilidade que estão numa determinada localização, e que tenham menos de 50% de bateria.
*
* \param camiao O apontador para o camiao que vai recolher os meios de mobilidade
* \param posto O apontador para o posto onde o camiao se dirige
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \param meiosFaltaRecolher O apontador para o primeiro elemento da lista ligada de meios mobilidade que falta recolher
* \return Os meios de mobilidade recolhidos pelo camiao no posto
* \author A. Cerqueira
*/
MeioMobilidadeLista* RecolherMeiosMobilidadeEmPosto(Camiao* camiao, PostoVertice* posto, PostoVertice* primeiroPosto, MeioMobilidadeLista* primeiroMeio, MeioMobilidadeLista** meiosFaltaRecolher) {
	float capacidadeOcupada = 0;
	MeioMobilidadeLista* meioAtual = (*meiosFaltaRecolher == NULL) ? primeiroMeio : *meiosFaltaRecolher;
	
	while (meioAtual != NULL) {
		
		if (meioAtual->m.postoId != posto->p.f.id || meioAtual->m.cargaBateria > BATERIA_MINIMA_PARA_RECOLHA) {
			meioAtual = meioAtual->proximo;
			continue;
		}
			
		// Verificar se o caminhão tem capacidade para recolher o meio de mobilidade
		if (capacidadeOcupada + meioAtual->m.peso > camiao->capacidadeMaxima) {
			break;
		}

		// Atualizar o meio de mobilidade
		meioAtual->m.postoId = camiao->localizacaoAtual->p.f.id;
		capacidadeOcupada += meioAtual->m.peso;
		
		meioAtual = meioAtual->proximo;
	}

	*meiosFaltaRecolher = meioAtual;
	return primeiroMeio;
}


/**
* \brief Recolhe todos os meios de mobilidade em todas as localizações uma de cada vez e volta até a origem no final de cada
*
* \param camiao O apontador para o camiao que vai recolher os meios de mobilidade
* \param primeiroPosto O apontador para o primeiro elemento da lista ligada de postos
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \return Km percorridos pelo camiao
* \author A. Cerqueira
*/
MeioMobilidadeLista* RecolherMeiosMobilidade(Camiao* camiao, PostoVertice* primeiroPosto, MeioMobilidadeLista* primeiroMeio, char* saveFilePath, int* kmPercorridos) {
	PostoVertice* postoAtual = primeiroPosto;
	*kmPercorridos = 0;

	while (postoAtual != NULL) {

		MeioMobilidadeLista* meiosFaltaRecolher = NULL;
		int nMeios = ContarMeiosPorRecolherEmPosto(postoAtual, primeiroMeio);
		if (nMeios == 0) {
			postoAtual = postoAtual->proximo;
			continue;
		}

		do
		{
			Percurso* percurso = ProcurarPercursoMaisRapido(camiao->localizacaoAtual, postoAtual, primeiroPosto);
			*kmPercorridos += ContarDistanciaEmPercurso(percurso);
			primeiroMeio = RecolherMeiosMobilidadeEmPosto(camiao, postoAtual, primeiroPosto, primeiroMeio, &meiosFaltaRecolher);
		} while (meiosFaltaRecolher != NULL);

		postoAtual = postoAtual->proximo;
	}

	GuardarMeiosMobilidade(saveFilePath, primeiroMeio);

	return primeiroMeio;
}
