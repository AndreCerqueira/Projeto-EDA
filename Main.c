/*****************************************************************//**
 * \file   Main.c
 * \brief  Main do programa
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

// include
#include "Ecras.h"



void main() {
	setlocale(LC_ALL, "Portuguese");
	
	// Variables
	int op = -1;
	Cliente* primeiroCliente = LerClientes();
	MeioMobilidade* primeiroMeio = LerMeiosMobilidade();
	Gestor* primeiroGestor = LerGestores();
	
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
				MostrarMenuAdicionarMeioMobilidade(primeiroMeio);
				break;
			case 6:
				MostrarMenuEditarMeioMobilidade(primeiroMeio);
				break;
			case 7:
				MostrarMenuRemoverMeioMobilidade(primeiroMeio);
				break;
			case 8:
				MostrarMenuListaMeiosMobilidade(primeiroMeio);
				break;
			case 9:
				// TO DO
				break;
			case 10:
				// TO DO
				break;
			case 11:
				MostrarMenuAdicionarGestor(primeiroGestor);
				break;
			case 12:
				MostrarMenuEditarGestor(primeiroGestor);
				break;
			case 13:
				MostrarMenuRemoverGestor(primeiroGestor);
				break;
			case 14:
				MostrarMenuListaGestores(primeiroGestor);
				break;
			case 15:
				CarregarDadosIniciais(&primeiroCliente, &primeiroMeio, &primeiroGestor);
				break;
			case 0:
				op = 0;
			default:
				break;
		}
	}
}


