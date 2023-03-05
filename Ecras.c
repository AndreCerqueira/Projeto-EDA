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
void CarregarDadosIniciais(Cliente* ultimoCliente, MeioMobilidade* ultimoMeio, Gestor* ultimoGestor) {
	
	// Variaveis
	int op = -1;

	system("cls");

	// Confirmar ou cancelar a respetiva operação.
	if (Confirmar() == IS_CANCELED)
		return;
	
	CarregarMeiosMobilidadeIniciais(ultimoMeio);
	CarregarClientesIniciais(ultimoCliente);
	CarregarGestoresIniciais(ultimoGestor);
}


// Adicionar Cliente
void MostrarMenuAdicionarCliente(Cliente** ultimoCliente) {
	
	// Variaveis
	char nome[NOME_LENGHT];
	char nif[NIF_LENGHT];
	char morada[MORADA_LENGHT];
	float saldo;

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

	// Atribuição de dados
	AdicionarCliente(ultimoCliente, nome, nif, morada, saldo);
	
}


// Editar Cliente
void MostrarMenuEditarCliente(Cliente* ultimoCliente) {

	// Variaveis
	int id;
	char nome[NOME_LENGHT];
	char nif[NIF_LENGHT];
	char morada[MORADA_LENGHT];
	float saldo;

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

	// Atribuição de dados
	EditarCliente(ultimoCliente, id, nome, nif, morada, saldo);

}


// Remover Cliente
void MostrarMenuRemoverCliente(Cliente* ultimoCliente) {

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
	RemoverCliente(ultimoCliente, id);

}


// Lista de Clientes
void MostrarMenuListaClientes(Cliente* ultimoCliente) {

	// Variaveis
	int i;

	// Mostrar os dados da clinica
	system("cls");
	puts("+---------------------------------------------------------------------------------+");
	puts("|                                   Lista de Clientes                             |");
	puts("+---------------------------------------------------------------------------------+");
	puts("|  ID  |          Nome          |      Nif     |       Morada       |    Saldo    |");
	puts("+---------------------------------------------------------------------------------+");

	Cliente* cliente = ultimoCliente;
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
void MostrarMenuAdicionarMeioMobilidade(MeioMobilidade** ultimoMeio) {
	
	// Variaveis
	TipoMeioMobilidade tipo;
	float cargaBateria;
	float custoAluguer;
	char localizacao[LOCALIZACAO_LENGHT];
	
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
	
	// Atribuição de dados
	AdicionarMeioMobilidade(ultimoMeio, tipo, cargaBateria, custoAluguer, localizacao);
}


// Editar Meio de mobilidade
void MostrarMenuEditarMeioMobilidade(MeioMobilidade* ultimoMeio) {

	// Variaveis
	int id;
	TipoMeioMobilidade tipo;
	float cargaBateria;
	float custoAluguer;
	char localizacao[LOCALIZACAO_LENGHT];
	
	// Inserir os dados da clinica
	system("cls");
	puts("+----------------------------------------+");
	puts("|       Editar Meio de Mobilidade        |");
	puts("+----------------------------------------+");
	
	printf("Insira o id do meio de mobilidade: ");
	scanf_s("%d", &id);
	fflush(stdin);
	
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
	
	// Atribuição de dados
	EditarMeioMobilidade(ultimoMeio, id, tipo, cargaBateria, custoAluguer, localizacao);
	
}


// Remover Meio de mobilidade
void MostrarMenuRemoverMeioMobilidade(MeioMobilidade* ultimoMeio) {

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
	RemoverMeioMobilidade(ultimoMeio, id);

}


// Lista de Meios de mobilidade
void MostrarMenuListaMeiosMobilidade(MeioMobilidade* ultimoMeio) {
	
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
	MeioMobilidade* meio = ultimoMeio;
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
void MostrarMenuAdicionarGestor(Gestor** ultimoGestor) {
	
	// Variaveis
	char nome[NOME_LENGHT];
	char email[EMAIL_LENGHT];
	char password[PASSWORD_LENGHT];

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

	// Atribuição de dados
	AdicionarGestor(ultimoGestor, nome, email, password);

}


// Editar Gestor
void MostrarMenuEditarGestor(Gestor* ultimoGestor) {
	
	// Variaveis
	int id;
	char nome[NOME_LENGHT];
	char email[EMAIL_LENGHT];
	char password[PASSWORD_LENGHT];
	
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

	// Atribuição de dados
	EditarGestor(ultimoGestor, id, nome, email, password);
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



