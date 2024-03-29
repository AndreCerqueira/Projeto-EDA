﻿/*****************************************************************//**
 * \file   Main.c
 * \brief  Main do programa
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/

// include
#include "Ecras.h"


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	// Variables
	int op = -1;
	ClienteLista* primeiroCliente = LerClientes(CLIENTE_SAVE_FILE_NAME);
	MeioMobilidadeLista* primeiroMeio = LerMeiosMobilidade(MEIO_SAVE_FILE_NAME);
	GestorLista* primeiroGestor = LerGestores(GESTOR_SAVE_FILE_NAME);
	PostoVertice* primeiroPosto = LerPostos(POSTO_SAVE_FILE_NAME);
	primeiroPosto = LerPostosAdjacentes(primeiroPosto, POSTO_ADJ_SAVE_FILE_NAME);
	AluguerLista* primeiroAluguer = LerAlugueres(ALUGUER_SAVE_FILE_NAME);

	Camiao camiao;
	camiao.capacidadeMaxima = 10000;
	camiao.capacidadeOcupada = 0;
	camiao.consumoBateriaPorKm = 1;
	camiao.cargaBateria = 100;
	camiao.localizacaoAtual = primeiroPosto;

	// Program loop
	while (op != 0) {
		MostrarMenuPrincipal(&op);
		
		switch (op) {
			case 1:
				MostrarMenuAdicionarCliente(&primeiroCliente);
				break;
			case 2:
				MostrarMenuEditarCliente(primeiroCliente);
				break;
			case 3:
				MostrarMenuRemoverCliente(&primeiroCliente);
				break;
			case 4:
				MostrarMenuListaClientes(primeiroCliente);
				break;
			case 5:
				MostrarMenuAdicionarMeioMobilidade(&primeiroMeio);
				break;
			case 6:
				MostrarMenuEditarMeioMobilidade(primeiroMeio);
				break;
			case 7:
				MostrarMenuRemoverMeioMobilidade(&primeiroMeio);
				break;
			case 8:
				MostrarMenuAlugarMeioMobilidade(primeiroMeio, primeiroCliente, primeiroPosto, &primeiroAluguer);
				break;
			case 9:
				MostrarMenuListaMeiosMobilidade(primeiroMeio, primeiroPosto);
				break;
			case 10:
				MostrarMenuListaMeiosMobilidadePorAutonomia(primeiroMeio, primeiroCliente, primeiroPosto);
				break;
			case 11:
				MostrarMenuListaMeiosMobilidadeLocalizacao(primeiroMeio, primeiroCliente, primeiroPosto);
				break;
			case 12:
				MostrarMenuAdicionarGestor(&primeiroGestor);
				break;
			case 13:
				MostrarMenuEditarGestor(primeiroGestor);
				break;
			case 14:
				MostrarMenuRemoverGestor(&primeiroGestor);
				break;
			case 15:
				MostrarMenuListaGestores(primeiroGestor);
				break;
			case 16:
				CarregarDadosIniciais(&primeiroCliente, &primeiroMeio, &primeiroGestor, &primeiroPosto, &primeiroAluguer);
				break;
			case 17:
				MostrarMenuListaPostos(primeiroPosto);
				break;
			case 18:
				MostrarMenuListaPostosComAdjacencias(primeiroPosto);
				break;
			case 19:
				MostrarMenuListaAlugueres(primeiroAluguer, primeiroCliente, primeiroMeio);
				break;
			case 20:
				RecolherMeiosMobilidadeEcra(&camiao, primeiroPosto, &primeiroMeio);
				break;
			case 21:
				ProcurarMeiosMobilidadeEmRaio(primeiroPosto, primeiroMeio);
				break;
			case 0:
				LibertarClientes(primeiroCliente);
				LibertarMeiosMobilidade(primeiroMeio);
				LibertarGestores(primeiroGestor);
				LibertarPostos(primeiroPosto);
				LibertarAlugueres(primeiroAluguer);
				op = 0;
			default:
				break;
		}
	}

	return 0;
}


