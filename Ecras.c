/*****************************************************************//**
 * \file   Ecras.c
 * \brief  Fun��es que geram os ecr�s da aplica��o
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

// includes
#include "Ecras.h"


// Fun��es


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

	// Confirmar ou cancelar a respetiva opera��o.
	// if (Confirmar() == IS_CANCELED)
	// 	return;

	// Atribui��o de dados
}


/**
 * .
 * 
 * \param op
 */
void MostrarMenuPrincipal(int* op) {

	// Resetar Op��o
	*op = -1;

	// Menu
	system("cls");
	puts("+------------------------------------------+");
	printf("|\t    Gestor de Mobilidade\t   |\n");
	puts("+------------------------------------------+");
	puts("| 1- Adicionar Clientes\t\t\t   |");
	puts("|\t\t\t\t\t   |");
	puts("| 2- Editar Clientes\t\t\t   |");
	puts("|\t\t\t\t\t   |");
	puts("| 3- Remover Clientes\t\t\t   |");
	puts("|\t\t\t\t\t   |");
	puts("| 4- Listar Clientes\t\t\t   |");
	puts("+------------------------------------------+");
	puts("| 5- Adicionar Meios de mobilidade\t   |");
	puts("|\t\t\t\t\t   |");
	puts("| 6- Editar Meios de mobilidade\t\t   |");
	puts("|\t\t\t\t\t   |");
	puts("| 7- Remover Meios de mobilidade\t   |");
	puts("|\t\t\t\t\t   |");
	puts("| 8- Listar Meios de mobilidade\t\t   |");
	puts("|\t\t\t\t\t   |");
	puts("| 9- Listar ordem decrescente de autonomia |");
	puts("|\t\t\t\t\t   |");
	puts("| 10- Procurar Meios em localiza��o\t   |");
	puts("+------------------------------------------+");
	puts("| 11- Adicionar Gestores\t\t   |");
	puts("|\t\t\t\t\t   |");
	puts("| 12- Editar Gestores\t\t\t   |");
	puts("|\t\t\t\t\t   |");
	puts("| 13- Remover Gestores\t\t\t   |");
	puts("|\t\t\t\t\t   |");
	puts("| 14- Listar Gestores\t\t\t   |");
	puts("+------------------------------------------+");
	puts("| 15- Carregar dados iniciais\t\t   |");
	puts("+------------------------------------------+");
	puts("| 0- Sair\t\t\t\t   |");
	puts("+------------------------------------------+");

	// Selecionar uma op��o
	printf("Selecione uma op��o: ");
	scanf_s("%d", op);
}


// Apaga os dados nos ficheiros binarios e carrega os dados iniciais
void CarregarDadosIniciais(ClienteLista** primeiroCliente, MeioMobilidadeLista** primeiroMeio, GestorLista** primeiroGestor) {
	
	// Variaveis
	int op = -1;

	system("cls");

	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;
	
	CarregarMeiosMobilidadeIniciais(primeiroMeio, MEIO_INITDATA_FILE_NAME, MEIO_SAVE_FILE_NAME);
	CarregarClientesIniciais(primeiroCliente, CLIENTE_INITDATA_FILE_NAME, CLIENTE_SAVE_FILE_NAME);
	CarregarGestoresIniciais(primeiroGestor, GESTOR_INITDATA_FILE_NAME, GESTOR_SAVE_FILE_NAME);
}


// Adicionar Cliente
void MostrarMenuAdicionarCliente(ClienteLista** primeiroCliente) {
	
	// Variaveis
	char nome[NOME_LENGHT];
	char nif[NIF_LENGHT];
	char morada[MORADA_LENGHT];
	float saldo;
	Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

	// Verificar se houve problema a alocar memoria
	if (novoCliente == NULL)
		return;
	
	// Inserir os dados 
	system("cls");
	puts("+-------------------------------+");
	puts("|        Adicionar Cliente      |");
	puts("+-------------------------------+");

	printf("Insira o nome do cliente: ");
	scanf_s("%s", nome, NOME_LENGHT);
	fflush(stdin);

	printf("Insira o nif do cliente: ");
	scanf_s("%s", nif, NIF_LENGHT);
	fflush(stdin);

	printf("Insira a morada do cliente: ");
	scanf_s("%s", morada, MORADA_LENGHT);
	fflush(stdin);

	printf("Insira o saldo do cliente: ");
	scanf_s("%f", &saldo);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	nome[NOME_LENGHT - 1] = '\0';
	nif[NIF_LENGHT - 1] = '\0';
	morada[MORADA_LENGHT - 1] = '\0';

	// Atribui��o de dados
	strcpy_s(novoCliente->nome, NOME_CLIENTE_LENGHT, nome);
	strcpy_s(novoCliente->nif, NIF_LENGHT, nif);
	strcpy_s(novoCliente->morada, MORADA_LENGHT, morada);
	novoCliente->saldo = saldo;
	AdicionarCliente(primeiroCliente, novoCliente);

	GuardarClientes(CLIENTE_SAVE_FILE_NAME, *primeiroCliente);
}


// Editar Cliente
void MostrarMenuEditarCliente(ClienteLista* primeiroCliente) {

	// Variaveis
	int id;
	char nome[NOME_LENGHT];
	char nif[NIF_LENGHT];
	char morada[MORADA_LENGHT];
	float saldo;
	Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

	// Verificar se houve problema a alocar memoria
	if (novoCliente == NULL)
		return;
	
	// Inserir os dados 
	system("cls");
	puts("+-------------------------------+");
	puts("|         Editar Cliente        |");
	puts("+-------------------------------+");

	printf("Insira o id do cliente: ");
	scanf_s("%d", &id);
	fflush(stdin);

	printf("Insira o nome do cliente: ");
	scanf_s("%s", nome, NOME_LENGHT);
	fflush(stdin);

	printf("Insira o nif do cliente: ");
	scanf_s("%s", nif, NIF_LENGHT);
	fflush(stdin);

	printf("Insira a morada do cliente: ");
	scanf_s("%s", morada, MORADA_LENGHT);
	fflush(stdin);

	printf("Insira o saldo do cliente: ");
	scanf_s("%f", &saldo);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	nome[NOME_LENGHT - 1] = '\0';
	nif[NIF_LENGHT - 1] = '\0';
	morada[MORADA_LENGHT - 1] = '\0';

	// Atribui��o de dados
	novoCliente->id = id;
	strcpy_s(novoCliente->nome, NOME_CLIENTE_LENGHT, nome);
	strcpy_s(novoCliente->nif, NIF_LENGHT, nif);
	strcpy_s(novoCliente->morada, MORADA_LENGHT, morada);
	novoCliente->saldo = saldo;

	// Atribui��o de dados
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

	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;

	// Atribui��o de dados
	RemoverCliente(primeiroCliente, id);

	GuardarClientes(CLIENTE_SAVE_FILE_NAME, primeiroCliente);
}


// Lista de Clientes
void MostrarMenuListaClientes(ClienteLista* primeiroCliente) {

	// Variaveis
	int i;

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
	

	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;
}


// Adicionar Meio de mobilidade
void MostrarMenuAdicionarMeioMobilidade(MeioMobilidadeLista** primeiroMeio) {
	
	// Variaveis
	TipoMeioMobilidade tipo;
	float cargaBateria;
	float custoAluguer;
	char localizacao[LOCALIZACAO_LENGHT];
	MeioMobilidade* novoMeio = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));

	// Verificar se houve problema a alocar memoria
	if (novoMeio == NULL)
		return;
	
	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|      Adicionar Meio de Mobilidade      |");
	puts("+----------------------------------------+");

	printf("\n0 - Bicibleta | 1 - Trotinente | 2 - Scooter | 3 - Skate Eletrico | 4 - Outro |\n");
	printf("Insira o tipo do meio de mobilidade: ");
	scanf_s("%d", &tipo);
	fflush(stdin);
	
	printf("Insira a carga da bateria do meio de mobilidade: ");
	scanf_s("%f", &cargaBateria);
	fflush(stdin);
	
	printf("Insira o custo de aluguer do meio de mobilidade: ");
	scanf_s("%f", &custoAluguer);
	fflush(stdin);
	
	printf("Insira a localizacao do meio de mobilidade: ");
	scanf_s("%s", localizacao, LOCALIZACAO_LENGHT);
	fflush(stdin);
	
	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	localizacao[LOCALIZACAO_LENGHT - 1] = '\0';
	
	// Atribui��o de dados
	novoMeio->tipo = tipo;
	novoMeio->cargaBateria = cargaBateria;
	novoMeio->custoAluguer = custoAluguer;
	strcpy_s(novoMeio->localizacao, LOCALIZACAO_LENGHT, localizacao);

	AdicionarMeioMobilidade(primeiroMeio, novoMeio);

	GuardarMeiosMobilidade(MEIO_SAVE_FILE_NAME, *primeiroMeio);
}


// Editar Meio de mobilidade
void MostrarMenuEditarMeioMobilidade(MeioMobilidadeLista* primeiroMeio) {

	// Variaveis
	int id;
	TipoMeioMobilidade tipo;
	float cargaBateria;
	float custoAluguer;
	char localizacao[LOCALIZACAO_LENGHT];
	MeioMobilidade* novoMeio = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));

	// Verificar se houve problema a alocar memoria
	if (novoMeio == NULL)
		return;
	
	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|       Editar Meio de Mobilidade        |");
	puts("+----------------------------------------+");
	
	printf("Insira o id do meio de mobilidade: ");
	scanf_s("%d", &id);
	fflush(stdin);
	
	printf("\n0 - Bicibleta | 1 - Trotinente | 2 - Scooter | 3 - Skate Eletrico | 4 - Outro |\n");
	printf("Insira o tipo do meio de mobilidade: ");
	scanf_s("%d", &tipo);
	fflush(stdin);
	
	printf("Insira a carga da bateria do meio de mobilidade: ");
	scanf_s("%f", &cargaBateria);
	fflush(stdin);
	
	printf("Insira o custo de aluguer do meio de mobilidade: ");
	scanf_s("%f", &custoAluguer);
	fflush(stdin);
	
	printf("Insira a localizacao do meio de mobilidade: ");
	scanf_s("%s", localizacao, LOCALIZACAO_LENGHT);
	fflush(stdin);
	
	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	localizacao[LOCALIZACAO_LENGHT - 1] = '\0';
	
	// Atribui��o de dados
	novoMeio->id = id;
	novoMeio->tipo = tipo;
	novoMeio->cargaBateria = cargaBateria;
	novoMeio->custoAluguer = custoAluguer;
	strcpy_s(novoMeio->localizacao, LOCALIZACAO_LENGHT, localizacao);
	
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

	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;

	// Atribui��o de dados
	RemoverMeioMobilidade(primeiroMeio, id);

	GuardarMeiosMobilidade(MEIO_SAVE_FILE_NAME, primeiroMeio);
}


// Lista de Meios de mobilidade
void MostrarMenuListaMeiosMobilidade(MeioMobilidadeLista* primeiroMeio) {
	
	// Variaveis
	int i;

	// Mostrar os dados 
	system("cls");
	puts("+----------------------------------------------------------------------------------+");
	puts("|                             Lista de Meios de Mobilidade                         |");
	puts("+----------------------------------------------------------------------------------+");
	puts("|  ID  |        Tipo        | Carga Bateria | Custo Aluguer |     Localizacao      |");
	puts("+----------------------------------------------------------------------------------+");

	// Mostrar os dados dos clientes
	MeioMobilidadeLista* meioAtual = primeiroMeio;
	while (meioAtual != NULL) {
		if (meioAtual->m.ativo == true)
		{
			printf("| %-4d | %-18s | %13.2f | %13.2f | %-20s |\n", meioAtual->m.id, TipoMeioMobilidadeToString(meioAtual->m.tipo), meioAtual->m.cargaBateria, meioAtual->m.custoAluguer, meioAtual->m.localizacao);
		}

		meioAtual = meioAtual->proximo;
	}

	puts("+----------------------------------------------------------------------------------+");

	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;
}


// Lista de Meios de mobilidade por autonomia
void MostrarMenuListaMeiosMobilidadePorAutonomia(MeioMobilidadeLista* primeiroMeio) {
	OrdenarMeiosMobilidadePorAutonomia(&primeiroMeio);
	MostrarMenuListaMeiosMobilidade(primeiroMeio);
	OrdenarMeiosMobilidadePorId(&primeiroMeio);
}


// Lista de Meios de mobilidade de uma localizacao
void MostrarMenuListaMeiosMobilidadeLocalizacao(MeioMobilidadeLista* primeiroMeio) {

	// Variaveis
	char localizacao[LOCALIZACAO_LENGHT];

	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|       Procurar por localiza��o         |");
	puts("+----------------------------------------+");

	printf("Insira o geoc�digo da localiza��o: ");
	scanf_s("%s", localizacao, LOCALIZACAO_LENGHT);
	fflush(stdin);

	// ProcurarMeiosMobilidadePorLocalizacao
	MeioMobilidadeLista* primeiroMeioLocalizacao = ProcurarMeiosMobilidadePorLocalizacao(primeiroMeio, localizacao);
	
	// Mostrar os dados
	MostrarMenuListaMeiosMobilidade(primeiroMeioLocalizacao);

}


// Adicionar Gestor
void MostrarMenuAdicionarGestor(GestorLista** primeiroGestor) {
	
	// Variaveis
	char nome[NOME_LENGHT];
	char email[EMAIL_LENGHT];
	char password[PASSWORD_LENGHT];
	Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));

	// Verificar se houve problema a alocar memoria
	if (novoGestor == NULL)
		return;

	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|          Adicionar Gestor              |");
	puts("+----------------------------------------+");

	printf("Insira o nome do gestor: ");
	scanf_s("%s", nome, NOME_LENGHT);
	fflush(stdin);

	printf("Insira o email do gestor: ");
	scanf_s("%s", email, EMAIL_LENGHT);
	fflush(stdin);

	printf("Insira a password do gestor: ");
	scanf_s("%s", password, PASSWORD_LENGHT);
	fflush(stdin);

	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	nome[NOME_LENGHT - 1] = '\0';
	email[EMAIL_LENGHT - 1] = '\0';
	password[PASSWORD_LENGHT - 1] = '\0';

	// Atribui��o de dados
	strcpy_s(novoGestor->nome, NOME_LENGHT, nome);
	strcpy_s(novoGestor->email, EMAIL_LENGHT, email);
	strcpy_s(novoGestor->password, PASSWORD_LENGHT, password);
	
	AdicionarGestor(primeiroGestor, novoGestor);

	GuardarGestores(GESTOR_SAVE_FILE_NAME, *primeiroGestor);
}


// Editar Gestor
void MostrarMenuEditarGestor(GestorLista* primeiroGestor) {
	
	// Variaveis
	int id;
	char nome[NOME_LENGHT];
	char email[EMAIL_LENGHT];
	char password[PASSWORD_LENGHT];
	Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));

	// Verificar se houve problema a alocar memoria
	if (novoGestor == NULL)
		return;
	
	// Inserir os dados 
	system("cls");
	puts("+----------------------------------------+");
	puts("|          Editar Gestor                 |");
	puts("+----------------------------------------+");
	
	printf("Insira o id do gestor: ");
	scanf_s("%d", &id);
	fflush(stdin);
	
	printf("Insira o nome do gestor: ");
	scanf_s("%s", nome, NOME_LENGHT);
	fflush(stdin);
	
	printf("Insira o email do gestor: ");
	scanf_s("%s", email, EMAIL_LENGHT);
	fflush(stdin);

	printf("Insira a password do gestor: ");
	scanf_s("%s", password, PASSWORD_LENGHT);
	fflush(stdin);
	
	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	nome[NOME_LENGHT - 1] = '\0';
	email[EMAIL_LENGHT - 1] = '\0';
	password[PASSWORD_LENGHT - 1] = '\0';

	// Atribui��o de dados
	novoGestor->id = id;
	strcpy_s(novoGestor->nome, NOME_LENGHT, nome);
	strcpy_s(novoGestor->email, EMAIL_LENGHT, email);
	strcpy_s(novoGestor->password, PASSWORD_LENGHT, password);
	
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

	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;

	// Atribui��o de dados
	RemoverGestor(primeiroGestor, id);

	GuardarGestores(GESTOR_SAVE_FILE_NAME, primeiroGestor);
}


// Lista de Gestores
void MostrarMenuListaGestores(GestorLista* primeiroGestor) {

	// Variaveis
	int i;

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

	// Confirmar ou cancelar a respetiva opera��o.
	if (Confirmar() == IS_CANCELED)
		return;
}



