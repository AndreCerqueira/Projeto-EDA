/*****************************************************************//**
 * \file   MeioMobilidade.c
 * \brief  Fun��es de Meios de mobilidade
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

 // Includes
#include "MeioMobilidade.h"


/**
* \brief Liberta a mem�ria da lista ligada de meios mobilidade
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \return true se a opera��o foi realizada com sucesso, false caso contr�rio
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
* \brief L� os dados de um ficheiro .txt e retorna uma lista ligada de meios mobilidade.
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

		int numLidos = sscanf(linha, "%d;%d;%f;%f;%[^;];%d;%d",
			&novoMeio.id,
			(int*)&novoMeio.tipo,
			&novoMeio.cargaBateria,
			&novoMeio.custoAluguer,
			novoMeio.localizacao,
			&novoMeio.alugadoPorId,
			(int*)&novoMeio.ativo);

		if (numLidos != 7)
			continue;

		primeiroMeio = AdicionarMeioMobilidade(primeiroMeio, novoMeio);
	}

	fclose(file);

	return primeiroMeio;
}


/**
* \brief L� os dados de um ficheiro .dat e retorna uma lista ligada de meios mobilidade.
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
* \param filePath O caminho para o arquivo .dat onde os meios mobilidade ser�o guardados.
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \return true se a opera��o foi realizada com sucesso, false caso contr�rio
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
* \param novoMeio O Meio que ser� adicionado � lista.
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
* \param id O id do Meio que ser� removido
* \return true se a opera��o foi realizada com sucesso, false caso contr�rio
* \author A. Cerqueira
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
* \brief Alterar um Meio da lista ligada
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \param meioSelecionado O Meio que ser� alterado
* \return true se a opera��o foi realizada com sucesso, false caso contr�rio
* \author A. Cerqueira
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
 * \brief Procurar todos os meios de mobilidade que est�o numa determinada localiza��o.
 *
 * \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
 * \param localizacao A localiza��o onde os meios de mobilidade ser�o procurados
 * \return O novo apontador para o primeiro elemento da lista ligada de meios mobilidade ordenada
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
* \brief Procura um Meio na lista ligada a partir do seu ID.
*
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de meios mobilidade
* \param id O id do Meio que ser� procurado
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
 * \brief Alugar um meio de mobilidade
 *
 * \param meioMobilidade O meio de mobilidade que ser� alugado
 * \param cliente O cliente que vai alugar o meio de mobilidade
 * \return true se a opera��o foi realizada com sucesso, false caso contr�rio
 */
bool AlugarMeioMobilidade(MeioMobilidade* meioMobilidade, Cliente* cliente) {
	
	// Verifica��es iniciais
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
 * \brief Devolve se um meio de mobilidade est� alugado ou n�o
 *
 * \param meioMobilidade O meio de mobilidade que ser� verificado
 * \return true se o meio de mobilidade estiver alugado, false caso contr�rio
 */
bool MeioMobilidadeAlugado(MeioMobilidade meioMobilidade) {
	return meioMobilidade.alugadoPorId != 0;
}
