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

	// Inserir os dados da clinica
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
	puts("| 10- Listar por localização\t\t   |");
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

	// Selecionar uma opção
	printf("Selecione uma opção: ");
	scanf_s("%d", op);
}


// Apaga os dados nos ficheiros binarios e carrega os dados iniciais
void CarregarDadosIniciais(Cliente** primeiroCliente, MeioMobilidade** primeiroMeio, Gestor** ultimoGestor) {
	
	// Variaveis
	int op = -1;

	system("cls");

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
	
	CarregarMeiosMobilidadeIniciais(primeiroMeio, MEIO_INITDATA_FILE_NAME, MEIO_SAVE_FILE_NAME);
	CarregarClientesIniciais(primeiroCliente, CLIENTE_INITDATA_FILE_NAME, CLIENTE_SAVE_FILE_NAME);
	CarregarGestoresIniciais(ultimoGestor, GESTOR_INITDATA_FILE_NAME, GESTOR_SAVE_FILE_NAME);
}


// Adicionar Cliente
void MostrarMenuAdicionarCliente(Cliente* primeiroCliente) {
	
	// Variaveis
	char nome[NOME_LENGHT];
	char nif[NIF_LENGHT];
	char morada[MORADA_LENGHT];
	float saldo;
	Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));

	// Verificar se houve problema a alocar memoria
	if (novoCliente == NULL)
		return;
	
	// Inserir os dados da clinica
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

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	nome[NOME_LENGHT - 1] = '\0';
	nif[NIF_LENGHT - 1] = '\0';
	morada[MORADA_LENGHT - 1] = '\0';

	// Atribuição de dados
	strcpy_s(novoCliente->nome, NOME_CLIENTE_LENGHT, nome);
	strcpy_s(novoCliente->nif, NIF_LENGHT, nif);
	strcpy_s(novoCliente->morada, MORADA_LENGHT, morada);
	novoCliente->saldo = saldo;
	AdicionarCliente(primeiroCliente, novoCliente);

	GuardarClientes(CLIENTE_SAVE_FILE_NAME, primeiroCliente);
}


// Editar Cliente
void MostrarMenuEditarCliente(Cliente* primeiroCliente) {

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
	
	// Inserir os dados da clinica
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

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	nome[NOME_LENGHT - 1] = '\0';
	nif[NIF_LENGHT - 1] = '\0';
	morada[MORADA_LENGHT - 1] = '\0';

	// Atribuição de dados
	novoCliente->id = id;
	strcpy_s(novoCliente->nome, NOME_CLIENTE_LENGHT, nome);
	strcpy_s(novoCliente->nif, NIF_LENGHT, nif);
	strcpy_s(novoCliente->morada, MORADA_LENGHT, morada);
	novoCliente->saldo = saldo;

	// Atribuição de dados
	EditarCliente(primeiroCliente, novoCliente);

	GuardarClientes(CLIENTE_SAVE_FILE_NAME, primeiroCliente);
}


// Remover Cliente
void MostrarMenuRemoverCliente(Cliente* primeiroCliente) {

	// Variaveis
	int id;

	// Inserir os dados da clinica
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
void MostrarMenuListaClientes(Cliente* primeiroCliente) {

	// Variaveis
	int i;

	// Mostrar os dados da clinica
	system("cls");
	puts("+---------------------------------------------------------------------------------+");
	puts("|                                   Lista de Clientes                             |");
	puts("+---------------------------------------------------------------------------------+");
	puts("|  ID  |          Nome          |      Nif     |       Morada       |    Saldo    |");
	puts("+---------------------------------------------------------------------------------+");

	Cliente* cliente = primeiroCliente;
	while (cliente != NULL) {
		if (cliente->ativo == true)
		{
			printf("| %-4d | %-22s | %-12s | %-18s | %-11.2f |\n", cliente->id, cliente->nome, cliente->nif, cliente->morada, cliente->saldo);
		}

		cliente = cliente->proximo;
	}

	puts("+---------------------------------------------------------------------------------+");
	

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
}


// Adicionar Meio de mobilidade
void MostrarMenuAdicionarMeioMobilidade(MeioMobilidade* primeiroMeio) {
	
	// Variaveis
	TipoMeioMobilidade tipo;
	float cargaBateria;
	float custoAluguer;
	char localizacao[LOCALIZACAO_LENGHT];
	MeioMobilidade* novoMeio = (MeioMobilidade*)malloc(sizeof(MeioMobilidade));

	// Verificar se houve problema a alocar memoria
	if (novoMeio == NULL)
		return;
	
	// Inserir os dados da clinica
	system("cls");
	puts("+----------------------------------------+");
	puts("|      Adicionar Meio de Mobilidade      |");
	puts("+----------------------------------------+");

	printf("\n0 - Bicibleta | 1 - Trotinente | 2 - Scooter | 3 - Segway | 4 - Skate Eletrico | 5 - Outro |\n");
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
	
	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	localizacao[LOCALIZACAO_LENGHT - 1] = '\0';
	
	// Atribuição de dados
	novoMeio->tipo = tipo;
	novoMeio->cargaBateria = cargaBateria;
	novoMeio->custoAluguer = custoAluguer;
	strcpy_s(novoMeio->localizacao, LOCALIZACAO_LENGHT, localizacao);

	AdicionarMeioMobilidade(primeiroMeio, novoMeio);

	GuardarMeiosMobilidade(MEIO_SAVE_FILE_NAME, primeiroMeio);
}


// Editar Meio de mobilidade
void MostrarMenuEditarMeioMobilidade(MeioMobilidade* primeiroMeio) {

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
	
	// Inserir os dados da clinica
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
	
	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	localizacao[LOCALIZACAO_LENGHT - 1] = '\0';
	
	// Atribuição de dados
	novoMeio->id = id;
	novoMeio->tipo = tipo;
	novoMeio->cargaBateria = cargaBateria;
	novoMeio->custoAluguer = custoAluguer;
	strcpy_s(novoMeio->localizacao, LOCALIZACAO_LENGHT, localizacao);
	
	EditarMeioMobilidade(primeiroMeio, novoMeio);
	
	GuardarMeiosMobilidade(MEIO_SAVE_FILE_NAME, primeiroMeio);
}


// Remover Meio de mobilidade
void MostrarMenuRemoverMeioMobilidade(MeioMobilidade* primeiroMeio) {

	// Variaveis
	int id;

	// Inserir os dados da clinica
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


// Lista de Meios de mobilidade
void MostrarMenuListaMeiosMobilidade(MeioMobilidade* primeiroMeio) {
	
	// Variaveis
	int i;

	// Mostrar os dados da clinica
	system("cls");
	puts("+----------------------------------------------------------------------------------+");
	puts("|                             Lista de Meios de Mobilidade                         |");
	puts("+----------------------------------------------------------------------------------+");
	puts("|  ID  |        Tipo        | Carga Bateria | Custo Aluguer |     Localizacao      |");
	puts("+----------------------------------------------------------------------------------+");

	// Mostrar os dados dos clientes
	MeioMobilidade* meio = primeiroMeio;
	while (meio != NULL) {
		if (meio->ativo == true)
		{
			printf("| %-4d | %-18s | %13.2f | %13.2f | %-20s |\n", meio->id, TipoMeioMobilidadeToString(meio->tipo), meio->cargaBateria, meio->custoAluguer, meio->localizacao);
		}

		meio = meio->proximo;
	}

	puts("+----------------------------------------------------------------------------------+");

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
}


// Adicionar Gestor
void MostrarMenuAdicionarGestor(Gestor* ultimoGestor) {
	
	// Variaveis
	char nome[NOME_LENGHT];
	char email[EMAIL_LENGHT];
	char password[PASSWORD_LENGHT];
	Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));

	// Verificar se houve problema a alocar memoria
	if (novoGestor == NULL)
		return;

	// Inserir os dados da clinica
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

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	nome[NOME_LENGHT - 1] = '\0';
	email[EMAIL_LENGHT - 1] = '\0';
	password[PASSWORD_LENGHT - 1] = '\0';

	// Atribuição de dados
	strcpy_s(novoGestor->nome, NOME_LENGHT, nome);
	strcpy_s(novoGestor->email, EMAIL_LENGHT, email);
	strcpy_s(novoGestor->password, PASSWORD_LENGHT, password);
	
	AdicionarGestor(ultimoGestor, novoGestor);

	GuardarGestores(GESTOR_SAVE_FILE_NAME, ultimoGestor);
}


// Editar Gestor
void MostrarMenuEditarGestor(Gestor* ultimoGestor) {
	
	// Variaveis
	int id;
	char nome[NOME_LENGHT];
	char email[EMAIL_LENGHT];
	char password[PASSWORD_LENGHT];
	Gestor* novoGestor = (Gestor*)malloc(sizeof(Gestor));

	// Verificar se houve problema a alocar memoria
	if (novoGestor == NULL)
		return;
	
	// Inserir os dados da clinica
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
	
	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

	// Colocar o terminador de string
	nome[NOME_LENGHT - 1] = '\0';
	email[EMAIL_LENGHT - 1] = '\0';
	password[PASSWORD_LENGHT - 1] = '\0';

	// Atribuição de dados
	novoGestor->id = id;
	strcpy_s(novoGestor->nome, NOME_LENGHT, nome);
	strcpy_s(novoGestor->email, EMAIL_LENGHT, email);
	strcpy_s(novoGestor->password, PASSWORD_LENGHT, password);
	
	EditarGestor(ultimoGestor, id, nome, email, password);

	GuardarGestores(GESTOR_SAVE_FILE_NAME, ultimoGestor);
}


// Remover Gestor
void MostrarMenuRemoverGestor(Gestor* ultimoGestor) {
	
	// Variaveis
	int id;

	// Inserir os dados da clinica
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
	RemoverGestor(ultimoGestor, id);

	GuardarGestores(GESTOR_SAVE_FILE_NAME, ultimoGestor);
}


// Lista de Gestores
void MostrarMenuListaGestores(Gestor* ultimoGestor) {

	// Variaveis
	int i;

	// Mostrar os dados da clinica
	system("cls");
	puts("+---------------------------------------------------------------+");
	puts("|                          Lista de Gestores                    |");
	puts("+---------------------------------------------------------------+");
	puts("|  ID  |          Nome          |             Email             |");
	puts("+---------------------------------------------------------------+");

	// Mostrar os dados dos clientes
	Gestor* gestor = ultimoGestor;
	while (gestor != NULL) {
		if (gestor->ativo == true)
		{
			printf("| %-4d | %-22s | %-29s |\n", gestor->id, gestor->nome, gestor->email);
		}

		gestor = gestor->proximo;
	}

	puts("+---------------------------------------------------------------+");

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;

}



