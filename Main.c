/*****************************************************************//**
 * \file   Main.c
 * \brief  Main do programa
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

// include
#include "Ecras.h"

// main


/**
 * .
 * 
 */
void main() {
	setlocale(LC_ALL, "Portuguese");

	int op = -1;

	MostrarLoginMenu();

	// program loop
	while (op != 0) {
		MostrarMenuPrincipal(&op);
		switch (op) {
		case 1:
			// Adicionar Cliente
			break;
		case 2:
			// Editar Cliente
			break;
		case 3:
			// Remover Cliente
			break;
		case 0:
			// Sair
			break;
		default:
			// Opção inválida
			break;
		}
	}
}


