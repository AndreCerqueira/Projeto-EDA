/*****************************************************************//**
 * \file   Ecras.h
 * \brief  Cabeçalho das Funções que geram os ecrãs da aplicação
 * 
 * \author A. Cerqueira
 * \date   March 2023
 *********************************************************************/
#pragma once

#ifndef ECRAS_H_
#define ECRAS_H_

	#include <locale.h>
	#include <stdio.h>
	#include "MeioMobilidade.h"
	#include "Cliente.h"
	#include "Gestor.h"
	#include "Localizacao.h"
	#include "Alugueres.h"
	#include "Utils.h"


	void MostrarMenuLogin();
	void MostrarMenuPrincipal(int* op);
	void CarregarDadosIniciais(ClienteLista** primeiroCliente, MeioMobilidadeLista** primeiroMeio, GestorLista** primeiroGestor, PostoVertice** primeiroPosto, AluguerLista** primeiroAluguer);
	
	void MostrarMenuAdicionarCliente(ClienteLista** primeiroCliente);
	void MostrarMenuEditarCliente(ClienteLista* primeiroCliente);
	void MostrarMenuRemoverCliente(ClienteLista* primeiroCliente);
	void MostrarMenuListaClientes(ClienteLista* primeiroCliente);
	
	void MostrarMenuAdicionarMeioMobilidade(MeioMobilidadeLista** primeiroMeio);
	void MostrarMenuEditarMeioMobilidade(MeioMobilidadeLista* primeiroMeio);
	void MostrarMenuRemoverMeioMobilidade(MeioMobilidadeLista* primeiroMeio);
	
	void MostrarMenuAlugarMeioMobilidade(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente, PostoVertice* primeiroPosto, AluguerLista** primeiroAluguer);

	void MostrarMenuListaMeiosMobilidade(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente, PostoVertice* primeiroPosto);
	void MostrarMenuListaMeiosMobilidadePorAutonomia(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente, PostoVertice* primeiroPosto);
	void MostrarMenuListaMeiosMobilidadeLocalizacao(MeioMobilidadeLista* primeiroMeio, ClienteLista* primeiroCliente, PostoVertice* primeiroPosto);
	
	void MostrarMenuAdicionarGestor(GestorLista** primeiroGestor);
	void MostrarMenuEditarGestor(GestorLista* primeiroGestor);
	void MostrarMenuRemoverGestor(GestorLista* primeiroGestor);
	void MostrarMenuListaGestores(GestorLista* primeiroGestor);
	void MostrarMenuListaPostos(PostoVertice* primeiroPosto);
	void MostrarMenuListaPostosComAdjacencias(PostoVertice* primeiroPosto);

	void MostrarMenuListaAlugueres(AluguerLista* primeiroAluguer, ClienteLista* primeiroCliente, MeioMobilidadeLista* primeiroMeio);

	void RecolherMeiosMobilidadeEcra(Camiao* camiao, PostoVertice* primeiroPosto, MeioMobilidadeLista** primeiroMeio);
	
#endif