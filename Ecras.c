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
void MostrarLoginMenu() {

	// Variaveis
	char email[EMAIL_SIZE];
	char password[PASSWORD_SIZE];

	// Inserir os dados da clinica
	system("cls");
	puts("+-------------------------------+");
	puts("|             Login             |");
	puts("+-------------------------------+");
	
	printf("Insira o email do gestor: ");
	scanf_s("%s", email, EMAIL_SIZE);
	fflush(stdin);
	
	printf("Insira a palavra-passe do gestor: ");
	scanf_s("%s", password, PASSWORD_SIZE);
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
	puts("+--------------------------------+");
	printf("|\tGestor de Mobilidade\t |\n");
	puts("+--------------------------------+");
	puts("|\t\t\t\t |");
	puts("| 1- Adicionar Cliente\t\t |");
	puts("|\t\t\t\t |");
	puts("| 2- Editar Cliente\t\t |");
	puts("|\t\t\t\t |");
	puts("| 3- Remover Cliente\t\t |");
	puts("|\t\t\t\t |");
	puts("| 4- Lista de Clientes\t\t |");
	puts("|\t\t\t\t |");
	puts("+--------------------------------+");
	puts("|\t\t\t\t |");
	puts("| 5- Adicionar Meio de mobilidade|");
	puts("|\t\t\t\t |");
	puts("| 6- Editar Meio de mobilidade\t |");
	puts("|\t\t\t\t |");
	puts("| 7- Remover Meio de mobilidade\t |");
	puts("|\t\t\t\t |");
	puts("| 8- Lista de Meios de mobilidade|");
	puts("|\t\t\t\t |");
	puts("+--------------------------------+");
	puts("|\t\t\t\t |");
	puts("| 9- Adicionar Gestor\t\t |");
	puts("|\t\t\t\t |");
	puts("| 10- Editar Gestor\t\t |");
	puts("|\t\t\t\t |");
	puts("| 11- Remover Gestor\t\t |");
	puts("|\t\t\t\t |");
	puts("| 12- Lista de Gestores\t\t |");
	puts("|\t\t\t\t |");
	puts("+--------------------------------+");
	puts("| 0- Sair\t\t\t |");
	puts("+--------------------------------+");

	// Selecionar uma opção
	printf("Selecione uma opção: ");
	scanf_s("%d", op);
}


// Adicionar Cliente

