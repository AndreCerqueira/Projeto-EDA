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
* \brief Resetar lista ligada de Meios de Mobilidade, reescreve o ficheiro .dat com a lista vazia
*
* \return
* \author A. Cerqueira
*
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
* \brief Resetar dados atuais, carregar dados de um ficheiro .txt para uma lista ligada e guardar no ficheiro .dat
*
* \return
* \author A. Cerqueira
*
*/
MeioMobilidadeLista* CarregarMeiosMobilidadeIniciais(MeioMobilidadeLista* primeiroMeio, char* filePathInicial, char* saveFilePath) {
	LibertarMeiosMobilidade(primeiroMeio);
	primeiroMeio = LerMeiosMobilidadeIniciais(filePathInicial);
	GuardarMeiosMobilidade(saveFilePath, primeiroMeio);

	return primeiroMeio;
}


/**
* \brief Ler dados de um ficheiro de texto e retorna para guardar numa lista ligada
*
* \return
* \author A. Cerqueira
*
*/
MeioMobilidadeLista* LerMeiosMobilidadeIniciais(char* filePath) {
	FILE* file;
	MeioMobilidadeLista* primeiroMeio = NULL;
	char linha[MAX_SIZE];

	file = fopen(filePath, "r");
	if (file == NULL)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		MeioMobilidadeLista* novoMeio = (MeioMobilidadeLista*)malloc(sizeof(MeioMobilidadeLista));

		if (novoMeio == NULL)
			return NULL;

		char* contexto = NULL;
		char* campo = strtok(linha, ";");
		novoMeio->m.id = atoi(campo);

		campo = strtok(NULL, ";");
		novoMeio->m.tipo = (TipoMeioMobilidade)atoi(campo);

		campo = strtok(NULL, ";");
		novoMeio->m.cargaBateria = atof(campo);

		campo = strtok(NULL, ";");
		novoMeio->m.custoAluguer = atof(campo);

		campo = strtok(NULL, ";");
		strncpy(novoMeio->m.localizacao, campo, LOCALIZACAO_LENGHT);

		campo = strtok(NULL, ";");
		novoMeio->m.alugadoPorId = atoi(campo);

		campo = strtok(NULL, ";");
		novoMeio->m.ativo = (bool)atoi(campo);

		novoMeio->proximo = primeiroMeio;
		primeiroMeio = novoMeio;
	}

	fclose(file);

	return primeiroMeio;
}


/**
* \brief Ler dados de um ficheiro binario e guardar numa lista ligada
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
*/
MeioMobilidadeLista* LerMeiosMobilidade(char* filePath) {
	FILE* file;
	MeioMobilidadeLista* primeiroMeio = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;
	
	MeioMobilidade meio;
	size_t bytesLidos = fread(&meio, sizeof(MeioMobilidade), 1, file);
	
	while (bytesLidos > 0) {
		MeioMobilidadeLista* novoMeio = (MeioMobilidadeLista*)malloc(sizeof(MeioMobilidadeLista));

		if (novoMeio == NULL)
			return NULL;

		novoMeio->m.id = meio.id;
		novoMeio->m.tipo = meio.tipo;
		novoMeio->m.cargaBateria = meio.cargaBateria;
		novoMeio->m.custoAluguer = meio.custoAluguer;
		strcpy(novoMeio->m.localizacao, meio.localizacao);
		novoMeio->m.alugadoPorId = meio.alugadoPorId;
		novoMeio->m.ativo = meio.ativo;
		novoMeio->proximo = primeiroMeio;
		primeiroMeio = novoMeio;

		bytesLidos = fread(&meio, sizeof(MeioMobilidade), 1, file);
	}
	
	fclose(file);
	
	primeiroMeio = OrdenarMeiosMobilidadePorId(primeiroMeio);
	
	return primeiroMeio;
}


/**
* \brief Carregar dados inicial de um ficheiro de texto e guardar numa lista ligada
*
* \param clientes Lista ligada com os clientes
* \return
* \author A. Cerqueira
*
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
* \brief Adicionar um MeioMobilidade à lista ligada
*
* \return
* \author A. Cerqueira
*
*/
MeioMobilidadeLista* AdicionarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, MeioMobilidade novoMeio) {
	MeioMobilidadeLista* novoNode = (MeioMobilidadeLista*)malloc(sizeof(MeioMobilidadeLista));
	
	if (novoNode == NULL)
		return false;

	novoMeio.ativo = true;
	novoMeio.id = ProcurarProximoIdMeioMobilidade(primeiroMeio);
	novoNode->proximo = (primeiroMeio != NULL) ? primeiroMeio : NULL;

	novoNode->m = novoMeio;
	primeiroMeio = novoNode;
	
	return primeiroMeio;
}


/**
* \brief Remover um MeioMobilidade da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool RemoverMeioMobilidade(MeioMobilidadeLista* primeiroMeio, int id) {

	MeioMobilidadeLista* meioAtual = primeiroMeio;

	while (meioAtual != NULL) {

		if (meioAtual->m.id == id) {
			meioAtual->m.ativo = false;
			return;
		}

		meioAtual = meioAtual->proximo;
	}
	
	return true;
}


/**
* \brief Alterar um MeioMobilidade da lista ligada
*
* \return
* \author A. Cerqueira
*
*/
bool EditarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, MeioMobilidade meioSelecionado) {

	MeioMobilidadeLista* meioAtual = primeiroMeio;

	while (meioAtual != NULL) {

		if (meioAtual->m.id == meioSelecionado.id) {
			meioAtual->m.tipo = meioSelecionado.tipo;
			meioAtual->m.cargaBateria = meioSelecionado.cargaBateria;
			meioAtual->m.custoAluguer = meioSelecionado.custoAluguer;
			strcpy(meioAtual->m.localizacao, meioSelecionado.localizacao);
			return true;
		}

		meioAtual = meioAtual->proximo;
	}

	return false;
}


/**
* \brief Converter um TipoMeioMobilidade para string
*
* \return Lista ligada com os dados lidos
* \author A. Cerqueira
*
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
 * \brief Ordenar meios de mobilidade por id
 *
 * \param primeiroMeio
 * \return
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
 * \brief Ordenar meios de mobilidade por ordem decrescente de autonomia
 *
 * \param primeiroMeio
 * \return
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
* \brief Procurar meios de mobilidade em localização
*
* \param primeiroMeio
* \return
*/
MeioMobilidadeLista* ProcurarMeiosMobilidadePorLocalizacao(MeioMobilidadeLista* primeiroMeio, char* localizacao) {
	MeioMobilidadeLista* meiosMobilidadeLocalizacao = NULL;
	MeioMobilidadeLista* meioAtual = primeiroMeio;

	while (meioAtual != NULL) {

		if (strcmp(meioAtual->m.localizacao, localizacao) == 0) {
			meiosMobilidadeLocalizacao = AdicionarMeioMobilidade(meiosMobilidadeLocalizacao, meioAtual->m);
		}

		meioAtual = meioAtual->proximo;
	}

	return meiosMobilidadeLocalizacao;
}


/**
* \brief Devolve o Meio Mobilidade com o id selecionado
*
* \return
* \author A. Cerqueira
*
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
* \brief Devolve o proximo id disponivel para um MeioMobilidade
*
* \return
* \author A. Cerqueira
*
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
 * \brief Alugar um meio de mobilidade
 *
 * \param meioMobilidade
 * \param cliente
 * \return
 */
bool AlugarMeioMobilidade(MeioMobilidade* meioMobilidade, Cliente* cliente) {
	
	// Verificações iniciais
	if (!ClienteTemSaldoSuficiente(*cliente, meioMobilidade->custoAluguer))
		return false;

	if (meioMobilidade->ativo == false)
		return false;

	if (MeioMobilidadeAlugado(*meioMobilidade))
		return false;

	// Alugar
	meioMobilidade->alugadoPorId = cliente->id;
	cliente->saldo -= meioMobilidade->custoAluguer;

	return true;
}


/**
 * \brief Devolve se um meio de mobilidade está alugado ou não
 *
 * \param meioMobilidade
 * \param cliente
 * \return
 */
bool MeioMobilidadeAlugado(MeioMobilidade meioMobilidade) {
	return meioMobilidade.alugadoPorId != 0;
}
