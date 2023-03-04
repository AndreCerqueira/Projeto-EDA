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
	Cliente* clientes = LerClientesIniciais();
	MeioMobilidade* meiosMobilidade = LerMeiosMobilidadeIniciais();
	Gestor* gestores = LerGestoresIniciais();
	
	// Program loop
	while (op != 0) {
		MostrarMenuPrincipal(&op);
		
		switch (op) {
			case 1:
				MostrarMenuAdicionarCliente(&clientes);
				break;
			case 2:
				MostrarMenuEditarCliente(clientes);
				break;
			case 3:
				MostrarMenuRemoverCliente(clientes);
				break;
			case 4:
				MostrarMenuListaClientes(clientes);
				break;
			case 5:
				MostrarMenuAdicionarMeioMobilidade(&meiosMobilidade);
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
				MostrarMenuAdicionarGestor(&gestores);
				break;
			case 10:
				MostrarMenuEditarGestor(gestores);
				break;
			case 11:
				MostrarMenuRemoverGestor(gestores);
				break;
			case 12:
				MostrarMenuListaGestores(gestores);
				break;
			case 0:
				op = 0;
			default:
				break;
		}
	}
}


