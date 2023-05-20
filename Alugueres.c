/*****************************************************************//**
 * \file   Alugueres.c
 * \brief  Funções de Alugueres e Preços de Aluguer.
 *
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

#include "Alugueres.h"


 /**
 * \brief Liberta a memória da lista ligada de Alugueres.
 *
 * \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
 * \return true se a operação foi realizada com sucesso, false caso contrário
 * \author A. Cerqueira
 */
bool LibertarAlugueres(AluguerLista* primeiroAluguer) {
	AluguerLista* aluguerAtual = primeiroAluguer;

	while (aluguerAtual != NULL) {
		AluguerLista* aluguerAnterior = aluguerAtual;
		aluguerAtual = aluguerAtual->proximo;
		free(aluguerAnterior);
	}

	primeiroAluguer = NULL;

	return true;
}


/**
* \brief Carrega os dados iniciais dos Alugueres de um ficheiro .txt para uma lista ligada e guarda no ficheiro .dat.
*
* \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
* \param filePathInicial O caminho do ficheiro .txt com os dados iniciais dos Alugueres
* \param saveFilePath O caminho do ficheiro .dat para guardar a lista ligada
* \return O novo apontador para o primeiro elemento da lista ligada de Alugueres carregada
* \author A. Cerqueira
*/
AluguerLista* CarregarAlugueresIniciais(AluguerLista* primeiroAluguer, char* filePathInicial, char* saveFilePath) {
	LibertarAlugueres(primeiroAluguer);
	primeiroAluguer = LerAlugueresIniciais(filePathInicial);
	GuardarAlugueres(saveFilePath, primeiroAluguer);

	return primeiroAluguer;
}


/**
* \brief Lê os dados de um ficheiro .txt e retorna uma lista ligada de Alugueres.
*
* \param filePath O caminho do ficheiro .txt com os dados dos Alugueres
* \return O novo apontador para o primeiro elemento da lista ligada de Alugueres
* \author A. Cerqueira
*/
AluguerLista* LerAlugueresIniciais(char* filePath) {
	FILE* file;
	AluguerLista* primeiroAluguer = NULL;
	char linha[MAX_SIZE];

	file = fopen(filePath, "r");
	if (file == NULL)
		return NULL;

	while (fgets(linha, MAX_SIZE, file)) {
		Aluguer novoAluguer;

		int numLidos = sscanf(linha, "%d;%d;%d;%f;%[^;];%[^;];%d",
			&novoAluguer.id,
			&novoAluguer.clienteId,
			&novoAluguer.meioId,
			&novoAluguer.kmPercorridos,
			novoAluguer.dataInicio,
			novoAluguer.dataFim,
			&novoAluguer.ativo);

		if (numLidos != 7)
			continue;

		primeiroAluguer = AdicionarAluguer(primeiroAluguer, novoAluguer);
	}

	fclose(file);

	return primeiroAluguer;
}


/**
* \brief Lê os dados de um ficheiro .dat e retorna uma lista ligada de Alugueres.
*
* \param filePath O caminho do ficheiro .dat com os dados dos Alugueres
* \return O novo apontador para o primeiro elemento da lista ligada de Alugueres
* \author A. Cerqueira
*/
AluguerLista* LerAlugueres(char* filePath) {
	FILE* file;
	Aluguer* aluguer;
	AluguerLista* primeiroAluguer = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	aluguer = (Aluguer*)malloc(sizeof(Aluguer));

	while (aluguer != NULL && fread(aluguer, sizeof(Aluguer), 1, file)) {
		primeiroAluguer = AdicionarAluguer(primeiroAluguer, *aluguer);
		aluguer = (Aluguer*)malloc(sizeof(Aluguer));
	}

	fclose(file);

	primeiroAluguer = OrdenarAlugueresPorId(primeiroAluguer);

	return primeiroAluguer;
}


/**
* \brief Guarda a lista ligada de Alugueres em um arquivo .dat.
*
* \param filePath O caminho para o arquivo .dat onde os Alugueres serão guardados.
* \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
* \return true se a operação foi realizada com sucesso, false caso contrário
* \author A. Cerqueira
*/
bool GuardarAlugueres(char* filePath, AluguerLista* primeiroAluguer) {
	FILE* file;
	file = fopen(filePath, "wb");

	if (file == NULL)
		return false;

	AluguerLista* aluguerAtual = primeiroAluguer;

	while (aluguerAtual != NULL) {
		fwrite(&aluguerAtual->a, sizeof(Aluguer), 1, file);
		aluguerAtual = aluguerAtual->proximo;
	}

	fclose(file);

	return true;
}


/**
* \brief Adiciona um novo Aluguer ao inicio da lista ligada.
*
* \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
* \param novoAluguer O Aluguer que será adicionado à lista.
* \return O novo apontador para o primeiro elemento da lista ligada de Alugueres
* \author A. Cerqueira
*/
AluguerLista* AdicionarAluguer(AluguerLista* primeiroAluguer, Aluguer novoAluguer) {
	AluguerLista* novoNode = (AluguerLista*)malloc(sizeof(AluguerLista));

	if (novoNode == NULL)
		return primeiroAluguer;

	if (novoAluguer.ativo == NULL)
		novoAluguer.ativo = true;

	if (novoAluguer.id == NULL)
		novoAluguer.id = ProcurarProximoIdAluguer(primeiroAluguer);

	novoNode->proximo = (primeiroAluguer != NULL) ? primeiroAluguer : NULL;

	novoNode->a = novoAluguer;
	primeiroAluguer = novoNode;

	return primeiroAluguer;
}


/**
 * \brief Ordena a lista ligada de Alugueres por ID em ordem decrescente.
 *
 * \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
 * \return O novo apontador para o primeiro elemento da lista ligada de Alugueres ordenada
 * \author A. Cerqueira
 */
AluguerLista* OrdenarAlugueresPorId(AluguerLista* primeiroAluguer) {
	AluguerLista* atual;
	AluguerLista* proximo;
	Aluguer temp;

	for (atual = primeiroAluguer; atual != NULL; atual = atual->proximo) {
		for (proximo = atual->proximo; proximo != NULL; proximo = proximo->proximo) {

			if (atual->a.id < proximo->a.id) {
				temp = atual->a;
				atual->a = proximo->a;
				proximo->a = temp;
			}

		}
	}

	return primeiroAluguer;
}


/**
* \brief Procura o ultimo id de um Aluguer na lista ligada.
*
* \param primeiroAluguer O apontador para o primeiro elemento da lista ligada de Alugueres
* \return O proximo id a ser utilizado
* \author A. Cerqueira
*/
int ProcurarProximoIdAluguer(AluguerLista* primeiroAluguer) {
	AluguerLista* aluguerAtual = primeiroAluguer;
	int id = 0;

	while (aluguerAtual != NULL) {

		if (aluguerAtual->a.id > id)
			id = aluguerAtual->a.id;

		aluguerAtual = aluguerAtual->proximo;
	}

	return id + 1;
}


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
AluguerLista* AlugarMeioMobilidade(MeioMobilidade* meioMobilidade, Cliente* cliente, AluguerLista* primeiroAluguer, Posto destino, Percurso* percurso) {

	// Verificações iniciais
	if (!ClienteTemSaldoSuficiente(*cliente, meioMobilidade->custoAluguer))
		return primeiroAluguer; // return false;

	if (meioMobilidade->ativo == false)
		return primeiroAluguer; // false;

	// Criar aluguer
	Aluguer novoAluguer;
	novoAluguer.clienteId = cliente->id;
	novoAluguer.meioId = meioMobilidade->id;
	novoAluguer.kmPercorridos = ContarDistanciaEmPercurso(percurso);
	novoAluguer.id = NULL;
	GetCurrentDate(novoAluguer.dataFim);
	GetCurrentDate(novoAluguer.dataInicio);

	primeiroAluguer = AdicionarAluguer(primeiroAluguer, novoAluguer);

	// Atualizar dados
	cliente->saldo -= meioMobilidade->custoAluguer;
	meioMobilidade->postoId = destino.f.id;

	return primeiroAluguer;
	// return true;
}


/**
* \brief Calcula o custo de um Aluguer com base no meio de mobilidade utilizado e nos km percorridos.
*
* \param aluguer O Aluguer que será calculado o custo
* \param primeiroMeio O apontador para o primeiro elemento da lista ligada de Meios de Mobilidade
* \return O custo do Aluguer, multiplicando o custo do meio de mobilidade pelo numero de km percorridos
* \author A. Cerqueira
*/
float CalcularCustoAluguer(Aluguer aluguer, MeioMobilidadeLista* primeiroMeio) {
	MeioMobilidade* meio = ProcurarMeioMobilidadePorId(primeiroMeio, aluguer.meioId);

	if (meio == NULL)
		return 0;
	
	return meio->custoAluguer * aluguer.kmPercorridos;
}
