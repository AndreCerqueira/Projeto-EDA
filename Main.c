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


	// Variables
	int op = -1;
	Cliente* listaClientes = NULL;


	
	listaClientes = LerDadosIniciais();

	// Loop listaClientes

	MostrarMenuListaClientes(listaClientes);


	MostrarMenuLogin();

	//// program loop
	//while (op != 0) {
	//	MostrarMenuPrincipal(&op);
	//	
	//	switch (op) {
	//	case 1:
	//		MostrarMenuAdicionarCliente();
	//		break;
	//	case 2:
	//		MostrarMenuEditarCliente();
	//		break;
	//	case 3:
	//		MostrarMenuRemoverCliente();
	//		break;
	//	case 4:
	//		MostrarMenuListaClientes();
	//		break;
	//	case 5:
	//		MostrarMenuAdicionarMeioMobilidade();
	//		break;
	//	case 6:
	//		MostrarMenuEditarMeioMobilidade();
	//		break;
	//	case 7:
	//		MostrarMenuRemoverMeioMobilidade();
	//		break;
	//	case 8:
	//		MostrarMenuListaMeiosMobilidade();
	//		break;
	//	case 9:
	//		MostrarMenuAdicionarGestor();
	//		break;
	//	case 10:
	//		MostrarMenuEditarGestor();
	//		break;
	//	case 11:
	//		MostrarMenuRemoverGestor();
	//		break;
	//	case 12:
	//		MostrarMenuListaGestores();
	//		break;
	//	case 0:
	//		// Sair
	//		break;
	//	default:
	//		// Opção inválida
	//		break;
	//	}
	//}
}


