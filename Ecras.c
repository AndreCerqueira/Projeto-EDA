/*****************************************************************//**
 * \file   Ecras.c
 * \brief  Funções que geram os ecrãs da aplicação
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

// includes
#include "Ecras.h"


// Funções


/**
 * .
 * 
 */
void MostrarMenuLogin() {

	// Variaveis
	char email[EMAIL_LENGHT];
	char password[PASSWORD_LENGHT];

	// Inserir os dados 
	system("cls");
	puts("+-------------------------------+");
	puts("|             Login             |");
	puts("+-------------------------------+");
	
	printf("Insira o email do gestor: ");
	scanf_s("%s", email, EMAIL_LENGHT);
	fflush(stdin);
	
	printf("Insira a palavra-passe do gestor: ");
	scanf_s("%s", password, PASSWORD_LENGHT);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva operação.
	// if (Confirmar() == IS_CANCELED)
	// 	return;

	// Atribuição de dados
}


/**
 * .
 * 
 * \param op
 */
void MostrarMenuPrincipal(int* op) {

	// Resetar Opção
	*op = -1;

	// Menu
	system("cls");
	puts("+---------------------------------------------------------------------------------------+");
	printf("|                                  Gestor de Mobilidade                                 |\n");
	puts("+---------------------------------------------------------------------------------------+");
	puts("| 1- Adicionar Clientes\t\t\t   | 12- Adicionar Gestores\t\t\t|");
	puts("|\t\t\t\t\t   |\t\t\t\t\t\t|");
	puts("| 2- Editar Clientes\t\t\t   | 13- Editar Gestores\t\t\t|");
	puts("|\t\t\t\t\t   |\t\t\t\t\t\t|");
	puts("| 3- Remover Clientes\t\t\t   | 14- Remover Gestores\t\t\t|");
	puts("|\t\t\t\t\t   |\t\t\t\t\t\t|");
	puts("| 4- Listar Clientes\t\t\t   | 15- Listar Gestores\t\t\t|");
	puts("+---------------------------------------------------------------------------------------+");
	puts("| 5- Adicionar Meios de mobilidade\t   | 17- Listar Postos\t\t\t\t|");
	puts("|\t\t\t\t\t   |\t\t\t\t\t\t|");
	puts("| 6- Editar Meios de mobilidade\t\t   | 18- Listar Postos com Adjacencias\t\t|");
	puts("|\t\t\t\t\t   |\t\t\t\t\t\t|");
	puts("| 7- Remover Meios de mobilidade\t   |                   \t\t\t\t|");
	puts("|\t\t\t\t\t   |\t\t\t\t\t\t|");
	puts("| 8- Alugar Meio de mobilidade\t\t   |                   \t\t\t\t|");
	puts("|\t\t\t\t\t   |\t\t\t\t\t\t|");
	puts("| 9- Listar Meios de mobilidade\t\t   |                   \t\t\t\t|");
	puts("|\t\t\t\t\t   |\t\t\t\t\t\t|");
	puts("| 10- Listar ordem decrescente de autonomia|                   \t\t\t\t|");
	puts("|\t\t\t\t\t   |\t\t\t\t\t\t|");
	puts("| 11- Procurar Meios em localização\t   |                   \t\t\t\t|");
	puts("+---------------------------------------------------------------------------------------+");
	puts("| 16- Carregar dados iniciais\t\t\t\t\t\t\t\t|");
	puts("+---------------------------------------------------------------------------------------+");
	puts("| 0- Sair\t\t\t\t\t\t\t\t\t\t|");
	puts("+---------------------------------------------------------------------------------------+");

	// Selecionar uma opção
	printf("Selecione uma opção: ");
	scanf_s("%d", op);
}


// Apaga os dados nos ficheiros binarios e carrega os dados iniciais
void CarregarDadosIniciais(ClienteLista** primeiroCliente, MeioMobilidadeLista** primeiroMeio, GestorLista** primeiroGestor, PostoVertice** primeiroPosto) {
	
	// Variaveis
	int op = -1;

	system("cls");

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
	
	*primeiroMeio = CarregarMeiosMobilidadeIniciais(*primeiroMeio, MEIO_INITDATA_FILE_NAME, MEIO_SAVE_FILE_NAME);
	*primeiroCliente = CarregarClientesIniciais(*primeiroCliente, CLIENTE_INITDATA_FILE_NAME, CLIENTE_SAVE_FILE_NAME);
	*primeiroGestor = CarregarGestoresIniciais(*primeiroGestor, GESTOR_INITDATA_FILE_NAME, GESTOR_SAVE_FILE_NAME);
	*primeiroPosto = CarregarPostosIniciais(*primeiroPosto, POSTO_INITDATA_FILE_NAME, POSTO_SAVE_FILE_NAME, POSTO_ADJ_INITDATA_FILE_NAME, POSTO_ADJ_SAVE_FILE_NAME);
	*primeiroPosto = CarregarPostosAdjacentesIniciais(*primeiroPosto, POSTO_ADJ_INITDATA_FILE_NAME, POSTO_ADJ_SAVE_FILE_NAME);
}


// Adicionar Cliente
void MostrarMenuAdicionarCliente(ClienteLista** primeiroCliente) {
	
	// Variaveis
	Cliente novoCliente;
	
	// Inserir os dados 
	system("cls");
	puts("+-------------------------------+");
	puts("|        Adicionar Cliente      |");
	puts("+-------------------------------+");

	printf("Insira o nome do cliente: ");
	scanf_s("%s", novoCliente.nome, NOME_LENGHT);
	fflush(stdin);

	printf("Insira o nif do cliente: ");
	scanf_s("%s", novoCliente.nif, NIF_LENGHT);
	fflush(stdin);

	printf("Insira a morada do cliente: ");
	scanf_s("%s", novoCliente.morada, MORADA_LENGHT);
	fflush(stdin);

	printf("Insira o saldo do cliente: ");
	scanf_s("%f", &novoCliente.saldo);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	novoCliente.ativo = 1;
	novoCliente.id = ProcurarProximoIdCliente(*primeiroCliente);
	
	*primeiroCliente = AdicionarCliente(*primeiroCliente, novoCliente);

	GuardarClientes(CLIENTE_SAVE_FILE_NAME, *primeiroCliente);
}


// Editar Cliente
void MostrarMenuEditarCliente(ClienteLista* primeiroCliente) {

	// Variaveis
	Cliente novoCliente;
	
	// Inserir os dados 
	system("cls");
	puts("+-------------------------------+");
	puts("|         Editar Cliente        |");
	puts("+-------------------------------+");

	printf("Insira o id do cliente: ");
	scanf_s("%d", &novoCliente.id);
	fflush(stdin);

	printf("Insira o nome do cliente: ");
	scanf_s("%s", novoCliente.nome, NOME_LENGHT);
	fflush(stdin);

	printf("Insira o nif do cliente: ");
	scanf_s("%s", novoCliente.nif, NIF_LENGHT);
	fflush(stdin);

	printf("Insira a morada do cliente: ");
	scanf_s("%s", novoCliente.morada, MORADA_LENGHT);
	fflush(stdin);

	printf("Insira o saldo do cliente: ");
	scanf_s("%f", &novoCliente.saldo);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Atribuição de dados
	EditarCliente(primeiroCliente, novoCliente);

	GuardarClientes(CLIENTE_SAVE_FILE_NAME, primeiroCliente);
}


// Remover Cliente
void MostrarMenuRemoverCliente(ClienteLista* primeiroCliente) {

	// Variaveis
	int id;

	// Inserir os dados 
	system("cls");
	puts("+-------------------------------+");
	puts("|        Remover Cliente        |");
	puts("+-------------------------------+");

	printf("Insira o id do cliente: ");
	scanf_s("%d", &id);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Atribuição de dados
	RemoverCliente(primeiroCliente, id);

	GuardarClientes(CLIENTE_SAVE_FILE_NAME, primeiroCliente);
}


// Lista de Clientes
void MostrarMenuListaClientes(ClienteLista* primeiroCliente) {

	// Mostrar os dados 
	system("cls");
	puts("+---------------------------------------------------------------------------------+");
	puts("|                                   Lista de Clientes                             |");
	puts("+---------------------------------------------------------------------------------+");
	puts("|  ID  |          Nome          |      Nif     |       Morada       |    Saldo    |");
	puts("+---------------------------------------------------------------------------------+");

	ClienteLista* cliente = primeiroCliente;
	while (cliente != NULL) {
		if (cliente->c.ativo == true)
		{
			printf("| %-4d | %-22s | %-12s | %-18s | %-11.2f |\n", cliente->c.id, cliente->c.nome, cliente->c.nif, cliente->c.morada, cliente->c.saldo);
		}

		cliente = cliente->proximo;
	}

	puts("+---------------------------------------------------------------------------------+");
	

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
}


// Adicionar Meio de mobilidade
void MostrarMenuAdicionarMeioMobilidade(MeioMobilidadeLista** primeiroMeio) {
	
	// Variaveis
	MeioMobilidade novoMeio;
	
	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|      Adicionar Meio de Mobilidade      |");
	puts("+----------------------------------------+");

	printf("\n0 - Bicibleta | 1 - Trotinente | 2 - Scooter | 3 - Skate Eletrico | 4 - Outro |\n");
	printf("Insira o tipo do meio de mobilidade: ");
	scanf_s("%d", &novoMeio.tipo);
	fflush(stdin);
	
	printf("Insira a carga da bateria do meio de mobilidade: ");
	scanf_s("%f", &novoMeio.cargaBateria);
	fflush(stdin);
	
	printf("Insira o custo de aluguer do meio de mobilidade: ");
	scanf_s("%f", &novoMeio.custoAluguer);
	fflush(stdin);
	
	printf("Insira a localizacao do meio de mobilidade: ");
	scanf_s("%s", novoMeio.localizacao, LOCALIZACAO_LENGHT);
	fflush(stdin);
	
	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	novoMeio.ativo = 1;
	novoMeio.id = ProcurarProximoIdMeioMobilidade(*primeiroMeio);

	*primeiroMeio = AdicionarMeioMobilidade(*primeiroMeio, novoMeio);

	GuardarMeiosMobilidade(MEIO_SAVE_FILE_NAME, *primeiroMeio);
}


// Editar Meio de mobilidade
void MostrarMenuEditarMeioMobilidade(MeioMobilidadeLista* primeiroMeio) {

	// Variaveis
	MeioMobilidade novoMeio;
	
	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|       Editar Meio de Mobilidade        |");
	puts("+----------------------------------------+");
	
	printf("Insira o id do meio de mobilidade: ");
	scanf_s("%d", &novoMeio.id);
	fflush(stdin);
	
	printf("\n0 - Bicibleta | 1 - Trotinente | 2 - Scooter | 3 - Skate Eletrico | 4 - Outro |\n");
	printf("Insira o tipo do meio de mobilidade: ");
	scanf_s("%d", &novoMeio.tipo);
	fflush(stdin);
	
	printf("Insira a carga da bateria do meio de mobilidade: ");
	scanf_s("%f", &novoMeio.cargaBateria);
	fflush(stdin);
	
	printf("Insira o custo de aluguer do meio de mobilidade: ");
	scanf_s("%f", &novoMeio.custoAluguer);
	fflush(stdin);
	
	printf("Insira a localizacao do meio de mobilidade: ");
	scanf_s("%s", novoMeio.localizacao, LOCALIZACAO_LENGHT);
	fflush(stdin);
	
	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
	
	EditarMeioMobilidade(primeiroMeio, novoMeio);
	
	GuardarMeiosMobilidade(MEIO_SAVE_FILE_NAME, primeiroMeio);
}


// Remover Meio de mobilidade
void MostrarMenuRemoverMeioMobilidade(MeioMobilidadeLista* primeiroMeio) {

	// Variaveis
	int id;

	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|      Remover Meio de Mobilidade        |");
	puts("+----------------------------------------+");

	printf("Insira o id do meio de mobilidade: ");
	scanf_s("%d", &id);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Atribuição de dados
	RemoverMeioMobilidade(primeiroMeio, id);

	GuardarMeiosMobilidade(MEIO_SAVE_FILE_NAME, primeiroMeio);
}


// Alugar Meio de mobilidade
void MostrarMenuAlugarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente) {

	// Variaveis
	int clienteId, meioId;

	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|       Alugar Meio de Mobilidade        |");
	puts("+----------------------------------------+");

	printf("Insira o id do cliente: ");
	scanf_s("%d", &clienteId);
	fflush(stdin);
	
	printf("Insira o id do meio de mobilidade: ");
	scanf_s("%d", &meioId);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Atribuição de dados
	Cliente* cliente = ProcurarClientePorId(primeiroCliente, clienteId);
	MeioMobilidade* meio = ProcurarMeioMobilidadePorId(primeiroMeio, meioId);
	
	if (cliente == NULL || meio == NULL)
		return;
	
	bool meioAlugado = AlugarMeioMobilidade(meio, cliente);
	
	if (meioAlugado)
		GuardarMeiosMobilidade(MEIO_SAVE_FILE_NAME, primeiroMeio);
}


// Lista de Meios de mobilidade
void MostrarMenuListaMeiosMobilidade(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente) {
	
	// Mostrar os dados 
	system("cls");
	puts("+---------------------------------------------------------------------------------------------------------+");
	puts("|                                         Lista de Meios de Mobilidade                                    |");
	puts("+---------------------------------------------------------------------------------------------------------+");
	puts("|  ID  |        Tipo        | Carga Bateria | Custo Aluguer |      Localizacao     |     Alugado por      |");
	puts("+---------------------------------------------------------------------------------------------------------+");

	// Mostrar os dados dos clientes
	MeioMobilidadeLista* meioAtual = primeiroMeio;
	while (meioAtual != NULL) {
		if (meioAtual->m.ativo == true)
		{
			Cliente* cliente = ProcurarClientePorId(primeiroCliente, meioAtual->m.alugadoPorId);
			char* nomeCliente = cliente == NULL ? "" : cliente->nome;

			printf("| %-4d | %-18s | %13.2f | %13.2f | %-20s | %-20s |\n", meioAtual->m.id, TipoMeioMobilidadeToString(meioAtual->m.tipo), meioAtual->m.cargaBateria, meioAtual->m.custoAluguer, meioAtual->m.localizacao, nomeCliente);
		}

		meioAtual = meioAtual->proximo;
	}

	puts("+---------------------------------------------------------------------------------------------------------+");

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
}


// Lista de Meios de mobilidade por autonomia
void MostrarMenuListaMeiosMobilidadePorAutonomia(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente) {
	primeiroMeio = OrdenarMeiosMobilidadePorAutonomia(primeiroMeio);
	MostrarMenuListaMeiosMobilidade(primeiroMeio, primeiroCliente);
	primeiroMeio = OrdenarMeiosMobilidadePorId(primeiroMeio);
}


// Lista de Meios de mobilidade de uma localizacao
void MostrarMenuListaMeiosMobilidadeLocalizacao(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente) {

	// Variaveis
	char localizacao[LOCALIZACAO_LENGHT];

	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|       Procurar por localização         |");
	puts("+----------------------------------------+");

	printf("Insira o geocódigo da localização: ");
	scanf_s("%s", localizacao, LOCALIZACAO_LENGHT);
	fflush(stdin);

	// ProcurarMeiosMobilidadePorLocalizacao
	MeioMobilidadeLista* primeiroMeioLocalizacao = ProcurarMeiosMobilidadePorLocalizacao(primeiroMeio, localizacao);
	
	// Mostrar os dados
	MostrarMenuListaMeiosMobilidade(primeiroMeioLocalizacao, primeiroCliente);

	LibertarMeiosMobilidade(primeiroMeioLocalizacao);

}


// Adicionar Gestor
void MostrarMenuAdicionarGestor(GestorLista** primeiroGestor) {
	
	// Variaveis
	Gestor novoGestor;

	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|          Adicionar Gestor              |");
	puts("+----------------------------------------+");

	printf("Insira o nome do gestor: ");
	scanf_s("%s", novoGestor.nome, NOME_LENGHT);
	fflush(stdin);

	printf("Insira o email do gestor: ");
	scanf_s("%s", novoGestor.email, EMAIL_LENGHT);
	fflush(stdin);

	printf("Insira a password do gestor: ");
	scanf_s("%s", novoGestor.password, PASSWORD_LENGHT);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	novoGestor.ativo = 1;
	novoGestor.id = ProcurarProximoIdGestor(*primeiroGestor);
	
	*primeiroGestor = AdicionarGestor(*primeiroGestor, novoGestor);

	GuardarGestores(GESTOR_SAVE_FILE_NAME, *primeiroGestor);
}


// Editar Gestor
void MostrarMenuEditarGestor(GestorLista* primeiroGestor) {
	
	// Variaveis
	Gestor novoGestor;
	
	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|          Editar Gestor                 |");
	puts("+----------------------------------------+");
	
	printf("Insira o id do gestor: ");
	scanf_s("%d", &novoGestor.id);
	fflush(stdin);
	
	printf("Insira o nome do gestor: ");
	scanf_s("%s", novoGestor.nome, NOME_LENGHT);
	fflush(stdin);
	
	printf("Insira o email do gestor: ");
	scanf_s("%s", novoGestor.email, EMAIL_LENGHT);
	fflush(stdin);

	printf("Insira a password do gestor: ");
	scanf_s("%s", novoGestor.password, PASSWORD_LENGHT);
	fflush(stdin);
	
	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
	
	EditarGestor(primeiroGestor, novoGestor);

	GuardarGestores(GESTOR_SAVE_FILE_NAME, primeiroGestor);
}


// Remover Gestor
void MostrarMenuRemoverGestor(GestorLista* primeiroGestor) {
	
	// Variaveis
	int id;

	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|          Remover Gestor                |");
	puts("+----------------------------------------+");

	printf("Insira o id do gestor: ");
	scanf_s("%d", &id);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Atribuição de dados
	RemoverGestor(primeiroGestor, id);

	GuardarGestores(GESTOR_SAVE_FILE_NAME, primeiroGestor);
}


// Lista de Gestores
void MostrarMenuListaGestores(GestorLista* primeiroGestor) {

	// Mostrar os dados 
	system("cls");
	puts("+---------------------------------------------------------------+");
	puts("|                          Lista de Gestores                    |");
	puts("+---------------------------------------------------------------+");
	puts("|  ID  |          Nome          |             Email             |");
	puts("+---------------------------------------------------------------+");

	// Mostrar os dados dos clientes
	GestorLista* gestorAtual = primeiroGestor;
	while (gestorAtual != NULL) {
		if (gestorAtual->g.ativo == true)
		{
			printf("| %-4d | %-22s | %-29s |\n", gestorAtual->g.id, gestorAtual->g.nome, gestorAtual->g.email);
		}

		gestorAtual = gestorAtual->proximo;
	}

	puts("+---------------------------------------------------------------+");

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
}


// Lista de Postos
void MostrarMenuListaPostos(PostoVertice* primeiroPosto) {

	// Mostrar os dados 
	system("cls");
	puts("+------------------------------------------------------------------------+");
	puts("|                          Lista de Postos                               |");
	puts("+------------------------------------------------------------------------+");
	puts("|  ID  |          Nome          |                Geocódigo               |");
	puts("+------------------------------------------------------------------------+");

	// Mostrar os dados dos clientes
	PostoVertice* postoAtual = primeiroPosto;
	while (postoAtual != NULL) {
		printf("| %-4d | %-22s | %-38s |\n", postoAtual->p.f.id, postoAtual->p.f.nome, postoAtual->p.f.geocode);

		postoAtual = postoAtual->proximo;
	}

	puts("+------------------------------------------------------------------------+");

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
}


// Lista de Postos com adjacencias
void MostrarMenuListaPostosComAdjacencias(PostoVertice* primeiroPosto) {

	// Mostrar os dados 
	system("cls");
	puts("+------------------------------------------------------------------------+");
	puts("|                          Lista de Postos                               |");
	puts("+------------------------------------------------------------------------+");
	puts("|  ID  |          Nome          |                Geocódigo               |");
	puts("+------------------------------------------------------------------------+");

	// Mostrar os dados dos clientes
	PostoVertice* postoAtual = primeiroPosto;
	while (postoAtual != NULL) {
		printf("| %-4d | %-22s | %-38s |\n", postoAtual->p.f.id, postoAtual->p.f.nome, postoAtual->p.f.geocode);
		puts("+------------------------------------------------------------------------+");

		PostoAdjacente* postoAdjAtual = postoAtual->p.primeiraAdjacencia;
		while (postoAdjAtual != NULL) {
			printf("  >  %-26s | %-5.2f Km \t\t\t\t |\n", postoAdjAtual->destino->p.f.nome, postoAdjAtual->f.distancia);
			
			postoAdjAtual = postoAdjAtual->proximo;
		}
		if (postoAtual->p.primeiraAdjacencia != NULL)
			puts("+------------------------------------------------------------------------+");

		postoAtual = postoAtual->proximo;
	}

	puts("+------------------------------------------------------------------------+");

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
}