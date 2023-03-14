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
	Cliente* primeiroCliente = LerClientes();
	MeioMobilidade* meiosMobilidade = LerMeiosMobilidade();
	Gestor* gestores = LerGestores();
	
	// Program loop
	while (op != 0) {
		MostrarMenuPrincipal(&op);
		
		switch (op) {
			case 1:
				MostrarMenuAdicionarCliente(primeiroCliente);
				break;
			case 2:
				MostrarMenuEditarCliente(primeiroCliente);
				break;
			case 3:
				MostrarMenuRemoverCliente(primeiroCliente);
				break;
			case 4:
				MostrarMenuListaClientes(primeiroCliente);
				break;
			case 5:
				MostrarMenuAdicionarMeioMobilidade(meiosMobilidade);
				break;
			case 6:
				MostrarMenuEditarMeioMobilidade(meiosMobilidade);
				break;
			case 7:
				MostrarMenuRemoverMeioMobilidade(meiosMobilidade);
				break;
			case 8:
				MostrarMenuListaMeiosMobilidade(meiosMobilidade);
				break;
			case 9:
				// TO DO
				break;
			case 10:
				// TO DO
				break;
			case 11:
				MostrarMenuAdicionarGestor(gestores);
				break;
			case 12:
				MostrarMenuEditarGestor(gestores);
				break;
			case 13:
				MostrarMenuRemoverGestor(gestores);
				break;
			case 14:
				MostrarMenuListaGestores(gestores);
				break;
			case 15:
				CarregarDadosIniciais(&primeiroCliente, meiosMobilidade, gestores);
				break;
			case 0:
				op = 0;
			default:
				break;
		}
	}
}


